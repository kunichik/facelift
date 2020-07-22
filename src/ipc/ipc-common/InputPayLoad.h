#pragma once

#if defined(FaceliftIPCCommonLib_LIBRARY)
#  define FaceliftIPCCommonLib_EXPORT Q_DECL_EXPORT
#else
#  define FaceliftIPCCommonLib_EXPORT Q_DECL_IMPORT
#endif

#include <QByteArray>
#include <QDataStream>

namespace facelift {

class FaceliftIPCCommonLib_EXPORT InputPayLoad
{

public:
    InputPayLoad(const QByteArray &payloadArray);

    ~InputPayLoad() = default;

    template<typename Type>
    void readNextParameter(Type &v)
    {
        m_dataStream >> v;
        //        qCDebug(LogIpc) << "Read from message : " << v;
    }

    const QByteArray &getContent() const;

private:
    const QByteArray& m_payloadArray;
    QDataStream m_dataStream;
};

}

