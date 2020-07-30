/**********************************************************************
**
** Copyright (C) 2020 Luxoft Sweden AB
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

//#include <memory>
//#include <functional>

#include <QObject>
#include <QMap>

#include "ServiceRegistry.h"

#if defined(FaceliftModelLib_LIBRARY)
#  define FaceliftModelLib_EXPORT Q_DECL_EXPORT
#else
#  define FaceliftModelLib_EXPORT Q_DECL_IMPORT
#endif


namespace facelift {

/**
 * Base interface which every interface inherits from
 */
class FaceliftModelLib_EXPORT InterfaceBase : public QObject
{
    Q_OBJECT

public:
    typedef void QMLAdapterType;

    InterfaceBase(QObject *parent = nullptr);

    void setImplementationID(const QString &id);

    const QString &implementationID() const;

    virtual bool ready() const = 0;

    Q_SIGNAL void readyChanged();

    QObject *impl();

    void init(const QString &interfaceName);

    const QString &interfaceID() const;

    void setComponentCompleted();

    bool isComponentCompleted() const;

    Q_SIGNAL void componentCompleted();

protected:
    friend class ModelQMLImplementationBase;

private:
    QString m_implementationID = "Undefined";
    QString m_interfaceName;

    bool m_componentCompleted = false;

};

// void registerInterfaceImplementationInstance(InterfaceBase & i)
// {
//     facelift::ServiceRegistry::instance().registerObject(&i);
// }

FaceliftModelLib_EXPORT void registerInterfaceImplementationInstance(InterfaceBase & i);

}

Q_DECLARE_METATYPE(facelift::InterfaceBase *)