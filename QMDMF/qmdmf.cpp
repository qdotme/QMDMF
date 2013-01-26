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
        qDebug() << __FILE__ << __LINE__ << __PRETTY_FUNCTION__ << data.toPercentEncoding() << "Not CallerID data[0]";
        return;
    }
    if (data.at(1) != data.length() - 3) {
        qDebug() << __FILE__ << __LINE__ << __PRETTY_FUNCTION__ << data.toPercentEncoding() << "Length error - expected" << (int)data.at(1) << "got" << data.length();
        return;
    }
    /// @todo: Checksum
    QString n;
    for (int i=2; i+1 < data.length(); ) {
        switch (data.at(i)) {
        case 0x11:
            qDebug() << __FILE__ << __LINE__ << __PRETTY_FUNCTION__ << "Call Type Message";
            break;
        case 0x01:
            qDebug() << __FILE__ << __LINE__ << __PRETTY_FUNCTION__ << "Date & Time Parameter";
            break;
        case 0x02:
            qDebug() << __FILE__ << __LINE__ << __PRETTY_FUNCTION__ << "Calling Number Parameter";
            n = data.mid(i+2, data.at(i+1));
            qDebug() << __FILE__ << __LINE__ << __PRETTY_FUNCTION__ << "Extracted Number" << n;
            emit VCIDNMBR(n);
            break;
        case 0x04:
            qDebug() << __FILE__ << __LINE__ << __PRETTY_FUNCTION__ << "Reason for absence of number";
            if (data.at(i+2) == 'P') {
                emit VCIDNMBR("WITHHELD");
                break;
            }
            if (data.at(i+2) == 'O') {
                emit VCIDNMBR("UNAVAILABLE");
                break;
            }
            qDebug() << __FILE__ << __LINE__ << __PRETTY_FUNCTION__ << "Cannot understand reasons: " << data.mid(i+2, 1).toHex();
            break;
        case 0x07:
            qDebug() << __FILE__ << __LINE__ << __PRETTY_FUNCTION__ << "Calling Name Parameter";
            break;
        default:
            qDebug() << __FILE__ << __LINE__ << __PRETTY_FUNCTION__ << "Cannot understand Parameter: 0x" << data.mid(i, 1).toHex();
        }
        i += data.at(i+1) + 2;
    }
}
