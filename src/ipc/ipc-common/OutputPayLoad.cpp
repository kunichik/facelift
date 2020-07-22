#include "OutputPayLoad.h"

namespace facelift {

OutputPayLoad::OutputPayLoad(QByteArray &payloadArray) : m_payloadArray(payloadArray), m_dataStream(&m_payloadArray, QIODevice::WriteOnly)
{
}

const QByteArray &OutputPayLoad::getContent() const
{
    return m_payloadArray;
}

}