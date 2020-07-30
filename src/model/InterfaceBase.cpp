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

#include "InterfaceBase.h"

namespace facelift {

InterfaceBase::InterfaceBase(QObject *parent) :
    QObject(parent)
{
}

void InterfaceBase::setImplementationID(const QString &id)
{
    m_implementationID = id;
}

const QString &InterfaceBase::implementationID() const
{
    return m_implementationID;
}

QObject *InterfaceBase::impl()
{
    return this;
}

const QString &InterfaceBase::interfaceID() const
{
    return m_interfaceName;
}

void InterfaceBase::setComponentCompleted() {
    if (!m_componentCompleted) {
        m_componentCompleted = true;
        emit componentCompleted();
    }
}

bool InterfaceBase::isComponentCompleted() const {
    return m_componentCompleted;
}

void InterfaceBase::init(const QString &interfaceName)
{
    m_interfaceName = interfaceName;
}

void registerInterfaceImplementationInstance(InterfaceBase & i)
{
    facelift::ServiceRegistry::instance().registerObject(&i);
}


}