#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include "simingd.h"

class GLobal : public QObject
{
    Q_OBJECT
public:
    explicit GLobal(QObject *parent = nullptr);
    ~GLobal();
    QStringList keyNameList;
    QList<int> keyNoList;
    QStringList comNameList;
    QSerialPort *serialPort=NULL;
    QStringList sendCache;
    QTimer sendTimer;
    SiMingD siMingD;
    int temp=600;
signals:

public slots:
    bool startLink(QString name);
    void onReceived();
    void sendData();
};
extern GLobal *g;
#endif // GLOBAL_H
