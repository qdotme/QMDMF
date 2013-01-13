#ifndef QMDMF_H
#define QMDMF_H

#include "QMDMF_global.h"

#include "qextserialport.h"

class QMDMFSHARED_EXPORT QMDMF : public QextSerialPort
{
    Q_OBJECT
public:
    QMDMF();
    QMDMF(const QString &name);

public slots:
    void onDataAvailable();
signals:
    void VCIDNMBR(QString n);
};

#endif // QMDMF_H
