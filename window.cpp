#include "window.h"
#include "ui_window.h"
#include "QApplication"
#include "QPixmap"
#include "QImage"
#include "QColor"
#include "QScreen"
#include "QDebug"
window::window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window)
{
    ui->setupUi(this);
    ui->keyList1->addItems(g->keyNameList);
    ui->keyList2->addItems(g->keyNameList);
    delayCount.setSingleShot(true);
    connect(&delayCount,SIGNAL(timeout()),this,SLOT(pressNextButton()));
    ui->comList->addItems(g->comNameList);

    QTimer *timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(on_test_clicked()));
    timer->start(100);

}

window::~window()
{
    delete ui;
}

void window::on_test_clicked()
{

    int x ;
        int y ;
      // QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(), x, y, 1, 1);

        QList<QScreen *> list_screen =  QGuiApplication::screens(); //可能电脑接了多个屏幕
        int w=list_screen.at(0)->geometry().width();
        int h=list_screen.at(0)->geometry().height();
        x=w-392;
        y=h-460;
        QPixmap pixmap = list_screen.at(0)->grabWindow(0,x,y,1,1);
        if (!pixmap.isNull()) //如果像素图不为NULL
        {
            QImage image = pixmap.toImage();//将像素图转换为QImage
            if (!image.isNull()) //如果image不为空
            {
                QColor color1,color2(250,237,189);
                if (image.valid(0, 0)) //坐标位置有效
                {

                    color1 = image.pixel(0, 0);
                    if(colorDiff(color1,color2)<10)
                    {
                        g->siMingD.start();
                        //qDebug()<<"开始！！！！！！！！！！！！";
                    }
                    else
                    {
                        g->siMingD.stop();
                        //qDebug()<<"停止！！！！！！！！！！！！";
                    }


                }

            }
        }
}

void window::on_btnAdd2_clicked()
{
    QString msg;
    msg.append(QString::number(g->keyNoList.at(ui->keyList2->currentIndex())));
    msg.append("|");
    msg.append(ui->keyList2->currentText());
    msg.append("|");
    msg.append(ui->delay2->text());
    ui->taskList2->addItem(msg);
}

void window::on_btnDel2_clicked()
{
    ui->taskList2->takeItem(ui->taskList2->currentRow());
}

void window::on_btnStart2_clicked()
{
    ui->btnAdd2->setEnabled(false);
    ui->btnDel2->setEnabled(false);
    ui->btnSave2->setEnabled(false);
    ui->btnStart2->setEnabled(false);
    ui->btnStop2->setEnabled(true);
    ui->taskList2->setCurrentRow(0);
    delayCount.start(10);
}
void window::pressNextButton()
{
    QString task=ui->taskList2->item(ui->taskList2->currentRow())->text();
    QStringList taskList=task.split("|");
    g->sendCache.append( taskList.at(0));
    if(ui->taskList2->currentRow()==(ui->taskList2->count()-1))
    {
       ui->taskList2->setCurrentRow(0);
    }
    else
    {
        ui->taskList2->setCurrentRow(ui->taskList2->currentRow()+1);
    }
    delayCount.start(taskList.at(2).toInt());
}

void window::on_startLink_clicked()
{
    if(g->startLink(ui->comList->currentText()))
    {
        ui->comList->setEnabled(false);
        ui->startLink->setEnabled(false);
    }
    else
    {

    }
}

void window::on_btnStop2_clicked()
{
    ui->btnAdd2->setEnabled(true);
    ui->btnDel2->setEnabled(true);
    ui->btnSave2->setEnabled(true);
    ui->btnStart2->setEnabled(true);
    ui->btnStop2->setEnabled(false);
    ui->taskList2->setCurrentRow(0);
    delayCount.stop();
    g->sendCache.append(QString::number(0));
}
double window::colorDiff(QColor hsv1,QColor hsv2)
{


    //self-defined
    static double R = 100;
    static double angle = 30;
    static double h = R * cos(angle / 180 * PI);
    static double r = R * sin(angle / 180 * PI);


    double x1 = r * hsv1.valueF() * hsv1.hsvSaturationF() * cos(hsv1.hsvHueF() / 180 * PI);
    double y1 = r * hsv1.valueF() * hsv1.hsvSaturationF() * sin(hsv1.hsvHueF() / 180 * PI);
    double z1 = h * (1 - hsv1.valueF());
    double x2 = r * hsv2.valueF() * hsv2.hsvSaturationF() * cos(hsv2.hsvHueF() / 180 * PI);
    double y2 = r * hsv2.valueF() * hsv2.hsvSaturationF() * sin(hsv2.hsvHueF() / 180 * PI);
    double z2 = h * (1 - hsv2.valueF());
    double dx = x1 - x2;
    double dy = y1 - y2;
    double dz = z1 - z2;
    return sqrt(dx * dx + dy * dy + dz * dz);

}
