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

#include <memory>
#include <functional>

#include <QObject>
#include <QDebug>
#include <QMap>
#include <qqml.h>

#include "FaceliftCommon.h"
#include "AsyncAnswer.h"
#include "PropertyInterface.h"
#include "ModelPropertyInterface.h"
#include "ServicePropertyInterface.h"

#if defined(FaceliftModelLib_LIBRARY)
#  define FaceliftModelLib_EXPORT Q_DECL_EXPORT
#else
#  define FaceliftModelLib_EXPORT Q_DECL_IMPORT
#endif


namespace facelift {

template<typename ElementType>
using Map = QMap<QString, ElementType>;


template<typename InterfaceType, typename PropertyType>
using PropertyGetter = const PropertyType &(*)();

/**
 * Base interface which every interface inherits from
 */
class FaceliftModelLib_EXPORT InterfaceBase : public QObject
{
    Q_OBJECT

public:
    typedef void QMLAdapterType;

    InterfaceBase(QObject *parent = nullptr) :
        QObject(parent)
    {
    }

    void setImplementationID(const QString &id)
    {
        m_implementationID = id;
    }

    const QString &implementationID() const
    {
        return m_implementationID;
    }

    virtual bool ready() const = 0;

    Q_SIGNAL void readyChanged();

    QObject *impl()
    {
        return this;
    }

    void init(const QString &interfaceName);

    const QString &interfaceID() const
    {
        return m_interfaceName;
    }

    void setComponentCompleted() {
        if (!m_componentCompleted) {
            m_componentCompleted = true;
            emit componentCompleted();
        }
    }

    bool isComponentCompleted() const {
        return m_componentCompleted;
    }

    Q_SIGNAL void componentCompleted();

protected:
    friend class ModelQMLImplementationBase;

private:
    QString m_implementationID = "Undefined";
    QString m_interfaceName;

    bool m_componentCompleted = false;

};

template<typename QMLType>
void qmlRegisterType(const char *uri, const char *typeName)
{
    ::qmlRegisterType<QMLType>(uri, 1, 0, typeName);
}

template<typename QMLType>
void qmlRegisterType(const char *uri)
{
    ::qmlRegisterType<QMLType>(uri, QMLType::INTERFACE_NAME);
}


FaceliftModelLib_EXPORT void registerInterfaceImplementationInstance(InterfaceBase & i);

}

template<typename ElementType>
inline QTextStream &operator<<(QTextStream &outStream, const facelift::Map<ElementType> &f)
{
    outStream << "[";
    for (const auto &e : f.toStdMap()) {
        outStream << e.first << "=" << e.second << ", ";
    }
    outStream << "]";
    return outStream;
}


Q_DECLARE_METATYPE(facelift::InterfaceBase *)
