#include "InputPayLoad.h"

namespace facelift {

InputPayLoad::InputPayLoad(const QByteArray &payloadArray) :
    m_payloadArray(payloadArray),
    m_dataStream(m_payloadArray)
{
}

const QByteArray &InputPayLoad::getContent() const
{
    return m_payloadArray;
}

}
