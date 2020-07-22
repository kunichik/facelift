#pragma once

#include <QByteArray>
#include <QDataStream>

#if defined(FaceliftIPCCommonLib_LIBRARY)
#  define FaceliftIPCCommonLib_EXPORT Q_DECL_EXPORT
#else
#  define FaceliftIPCCommonLib_EXPORT Q_DECL_IMPORT
#endif

namespace facelift {

class FaceliftIPCCommonLib_EXPORT OutputPayLoad
{

public:
    OutputPayLoad(QByteArray &payloadArray);

    template<typename Type>
    void writeSimple(const Type &v)
    {
        //        qCDebug(LogIpc) << "Writing to message : " << v;
        m_dataStream << v;
    }

    const QByteArray &getContent() const;

private:
    QByteArray& m_payloadArray;
    QDataStream m_dataStream;
};

}


