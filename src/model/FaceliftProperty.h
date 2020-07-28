/**********************************************************************
**
** Copyright (C) 2018 Luxoft Sweden AB
**
** This file is part of the FaceLift project
**
** Permission is hereby granted, free of charge, to any person
** obtaining a copy of this software and associated documentation files
** (the "Software"), to deal in the Software without restriction,
** including without limitation the rights to use, copy, modify, merge,
** publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so,
** subject to the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
** BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
** ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
** CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
** SPDX-License-Identifier: MIT
**
**********************************************************************/

#pragma once

#include <QString>
#include <QObject>
#include <functional>

#include "FaceliftCommon.h"
#include "FaceliftModel.h"

#include "FaceliftStringConversion.h"

#include "PropertyBase.h"
#include "TProperty.h"

namespace facelift {

template<typename Type, typename Enable = void>
class Property : public TProperty<Type>
{
public:
    using TProperty<Type>::operator=;

    Property(Type initialValue) : TProperty<Type>(initialValue)
    {
    }

    Property()
    {
    }

};



/**
 * Specialization used to store a reference to an interface.
 */
template<typename Type>
class ServiceProperty : public TProperty<Type *>
{

public:
    template<typename Class, typename PropertyType>
    ServiceProperty &bind(const ServicePropertyInterface<Class, PropertyType> &property)
    {
        this->bind([property] () {
                return property.value();
            }).addTrigger(property.object(), property.signal());
        return *this;
    }

    Type *operator=(Type *right)
    {
        ServiceProperty::setValue(right);
        return this->m_value;
    }

    void setValue(Type *newValue)
    {
        if (newValue != m_pointer) {
            m_valueChanged = true;
            // Store as a QPointer in order to be able to detect object destructions and generate a change signal even if the same
            // pointer is assigned later on
            m_pointer = newValue;
        }

        TProperty<Type *>::setValue(newValue);
    }

    bool isDirty() const override
    {
        return ((this->m_previousValue != this->value()) || m_valueChanged);
    }

    void clean() override
    {
        TProperty<Type *>::clean();
        m_valueChanged = false;
    }

    using TProperty<Type *>::bind;

private:
    bool m_valueChanged = false;

    QPointer<Type> m_pointer;
};



template<typename Type>
class Property<Type *, typename std::enable_if<std::is_base_of<QObject *, Type>::value>::type> : public ServiceProperty<Type>
{
public:
    using ServiceProperty<Type>::operator=;

    Property()
    {
    }

};



template<typename ElementType>
class ListProperty : public TProperty<QList<ElementType> >
{

public:
    using TProperty<QList<ElementType> >::operator=;

    void removeAt(int i)
    {
        this->modifiableValue().removeAt(i);
        this->triggerValueChangedSignal();
    }

    void addElement(ElementType element)
    {
        this->modifiableValue().append(element);
        this->triggerValueChangedSignal();
    }

    int size() const
    {
        return this->value().size();
    }

private:
    QList<ElementType> &modifiableValue()
    {
        this->breakBinding();
        return this->m_value;
    }

};


template<typename ElementType>
class Property<QList<ElementType> > : public ListProperty<ElementType>
{
public:
    using TProperty<QList<ElementType> >::operator=;

};


template<typename ElementType>
class Property<QMap<QString, ElementType> > : public TProperty<QMap<QString, ElementType> >
{

public:
    using TProperty<QMap<QString, ElementType> >::operator=;

    void removeAt(int i)
    {
        this->modifiableValue().removeAt(i);
        this->triggerValueChangedSignal();
    }

    void addElement(ElementType element)
    {
        this->modifiableValue().append(element);
        this->triggerValueChangedSignal();
    }

    int size() const
    {
        return this->value().size();
    }

private:
    QMap<QString, ElementType> &modifiableValue()
    {
        this->breakBinding();
        return this->m_value;
    }

};


template<typename ElementType>
class ModelProperty : public Model<ElementType>, public PropertyBase
{
public:
    typedef std::function<ElementType(int)> ElementGetter;

    ModelProperty()
    {
    }

    template<typename Class>
    ModelProperty &bind(const ModelPropertyInterface<Class, ElementType> &property)
    {
        facelift::Model<ElementType>* model = property.property();
        this->bindOtherModel(model);

        this->beginResetModel();
        this->reset(property.property()->size(), [model](int index) {
            return model->elementAt(index);
        });
        this->endResetModel();
        return *this;
    }

    ElementType elementAt(int index) const override
    {
        Q_ASSERT(m_elementGetter);
        Q_ASSERT(!this->m_resettingModel);
        Q_ASSERT(index < this->size());
        return m_elementGetter(index);
    }

    void reset(int size, ElementGetter getter)
    {
        this->setSize(size);
        m_elementGetter = getter;
    }

    bool isDirty() const override
    {
        return m_modified;
    }

    void clean() override
    {
        m_modified = false;
    }

    QString toString() const override
    {
        return QString("Model ") + name();
    }

private:
    ElementGetter m_elementGetter;
    bool m_modified = false;
};


template<typename InterfaceType>
struct PropertyConnector
{
    typedef void (InterfaceType::*ChangeSignal)();

    template<typename Param1, typename Param2>
    static QMetaObject::Connection connect(const PropertyBase &property, Param1 *context, const Param2 &p2)
    {
        auto signal = static_cast<ChangeSignal>(property.signalPointer());
        auto source = static_cast<InterfaceType *>(property.owner());
        return QObject::connect(source, signal, context, p2);
    }

};

}
