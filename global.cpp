#include "global.h"
GLobal *g;
#include <QThread>
#include "windows.h"
GLobal::GLobal(QObject *parent) : QObject(parent)
{

    
    {
        QString filename;
        filename+=(":/KeyList.txt");
        //判断文件是否存在
        QFile *file = new QFile(filename);
        if(file->open(QIODevice::ReadOnly))
        {
            for(int i=0;i<10000;i++)
            {
                {
                    QString ba(file->readLine());
                    ba.remove("\r");
                    ba.remove("\n");
                    QStringList list=ba.split("|");
                    keyNameList.append(list.at(1));
                    keyNoList.append(list.at(0).toInt());
                }


                if(file->atEnd())break;
            }
            file->close();
        }
        file->deleteLater();
    }
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        comNameList << info.portName();
    }
    connect(&sendTimer,SIGNAL(timeout()),this,SLOT(sendData()));
    if(DD_key)
    {
        sendTimer.start(50);
    }

}
GLobal::~GLobal()
{

}
bool GLobal::startLink(QString name)
{
    if(!(serialPort==NULL))
    {
        serialPort->deleteLater();
    }
    serialPort=new QSerialPort(name);
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(onReceived()));
    serialPort->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向
    serialPort->setDataBits(QSerialPort::Data8);      //数据位为8位
    serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    serialPort->setParity(QSerialPort::NoParity); //无校验位
    serialPort->setStopBits(QSerialPort::OneStop); //一位停止位
    if(serialPort->open(QIODevice::ReadWrite))
    {

        return true;
    }
    else
    {
        return  false;
    }
}
void GLobal::onReceived()
{
    qDebug()<< serialPort->readAll();
    return;
}
void GLobal::sendData()
{
    





    char data[13];

    data[0]=(char)0xE5;
    data[1]=(char)0x00;
    data[2]=(char)0xA3;
    data[3]=(char)0x08;
    data[4]=(char)0x00;
    data[5]=(char)0x00;
    data[6]=(char)0x00;
    data[7]=(char)0x00;
    data[8]=(char)0x00;
    data[9]=(char)0x00;
    data[10]=(char)0x00;
    data[11]=(char)0x00;

    /*
    data[0]=(char)0x0C;
    data[1]=(char)0x00;
    data[2]=(char)0xA1;
    data[3]=(char)0x01;
    data[4]=(char)0x00;
    data[5]=(char)0x00;
    data[6]=(char)0x00;
    data[7]=(char)0x00;
    data[8]=(char)0x00;
    data[9]=(char)0x00;
    data[10]=(char)0x00;
    data[11]=(char)0x00;
    */
        if(!sendCache.isEmpty())
        {

            data[6]=(char)(sendCache.first().toInt());


            sendCache.removeFirst();
        }
        else
        {

        }


    data[12]=data[1]+data[2]+data[3]+data[4]+data[5]+data[6]+data[7]+data[8]+data[9]+data[10]+data[11];
    if(!(serialPort==NULL))
    {
        serialPort->write(data,13);
    }

}
