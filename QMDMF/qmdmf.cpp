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
        qDebug() << __PRETTY_FUNCTION__ << data.toPercentEncoding();
    }
}

