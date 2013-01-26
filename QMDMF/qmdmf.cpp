#include "qmdmf.h"

#include <QDebug>
#include <QTimer>

QMDMF::QMDMF()
{
}

QMDMF::QMDMF(const QString &name) : QextSerialPort(name)
{
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onDataAvailable()));
    timer->start(100);
}

void QMDMF::onDataAvailable()
{
    if (bytesAvailable() > 0) {
        QByteArray data = readAll();
        parseMDMF(data);
        qDebug() << __PRETTY_FUNCTION__ << data.toPercentEncoding();
    }
}

void QMDMF::parseMDMF(QByteArray data) {
    if (data.at(0) != (char)0x80) {
        qDebug() << __PRETTY_FUNCTION__ << data.toPercentEncoding() << "Not CallerID data[0]";
        return;
    }
    if (data.at(1) != data.length() - 3) {
        qDebug() << __PRETTY_FUNCTION__ << data.toPercentEncoding() << "Length error - expected" << (int)data.at(1) << "got" << data.length();
        return;
    }
    /// @todo: Checksum
    QString n;
    for (int i=2; i+1 < data.length(); ) {
        switch (data.at(i)) {
        case 0x11:
            qDebug() << "Call Type Message";
            break;
        case 0x01:
            qDebug() << "Date & Time Parameter";
            break;
        case 0x02:
            qDebug() << "Calling Number Parameter";
            n = data.mid(i+2, data.at(i+1));
            qDebug() << "Extracted Number" << n;
            emit VCIDNMBR(n);
            break;
        case 0x07:
            qDebug() << "Calling Name Parameter";
            break;
        default:
            qDebug() << "Cannot understand Parameter: 0x" << data.mid(i, 1).toHex();
        }
        i += data.at(i+1) + 2;
    }
}
