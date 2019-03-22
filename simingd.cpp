#include "simingd.h"
#include "math.h"
#include <QFile>
using namespace std;
#define PI 3.1415926535897932384626433832795
SiMingD::SiMingD(QObject *parent) : QObject(parent)
{
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(work()));
}
void SiMingD::start()
{
    if(timer->isActive())
    {

    }
    else
    {
        timer->start(1000);
    }
}
void SiMingD::stop()
{
    if(timer->isActive())
    {
        timer->stop();
    }
    else
    {

    }
}
void SiMingD::work()
{
    int bengzhuiyin=0;
    //0=empty,1=use,2=cd;
    int fu1=0;
    int fu2=0;
    int fu3=0;
    int countFuCd=0;
    int countFuEmpty=0;
    int countFuUse=0;
    QColor colorBiu(255,239,173);
    QColor colorWrite(255,255,255);
    QColor fuCD(143,115,100);
    QColor fuUse(209,242,239);
    QColor freeHongGuangColor(117,244,213);
    QColor fuEmpty(54,84,72);
    bool hongguang=false;
    bool wahuang=false;
    bool qianjiewanhe=false;
    bool zhouqing=false;
    bool chaoyanzhou=false;
    bool chengtianmu=false;
    bool yuhongqingjue=false;
    bool freehongguang=false;

    //===================================boss状态============================================
    if(true)
    {

          // QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(), x, y, 1, 1);

            QList<QScreen *> list_screen =  QGuiApplication::screens(); //可能电脑接了多个屏幕

            QPixmap pixmap = list_screen.at(0)->grabWindow(0,347,89,260,28);
            if (!pixmap.isNull()) //如果像素图不为NULL
            {
                QImage image = pixmap.toImage();//将像素图转换为QImage
                if (!image.isNull()) //如果image不为空
                {
                    int biux=13;
                    int biuy=1;
                    for(int i=0;i<8;i++)
                    {
                        if (image.valid(biux, biuy)) //坐标位置有效
                        {
                            QColor color = image.pixel(biux, biuy);
                            if(colorDiff(color,colorBiu)<3)//如果相似度高，发现了
                            {
                                QColor color_2=image.pixel(biux+12, biuy+23);
                                QColor color_3=image.pixel(biux+12, biuy+22);
                                QColor color_4=image.pixel(biux+12, biuy+20);
                                if(colorDiff(color_2,colorWrite)<3)
                                {
                                    bengzhuiyin=2;
                                }
                                else if(colorDiff(color_3,colorWrite)<3)
                                {
                                    bengzhuiyin=3;
                                }
                                else if(colorDiff(color_4,colorWrite)<3)
                                {
                                    bengzhuiyin=4;
                                }
                                else
                                {
                                    bengzhuiyin=1;
                                }
                                break;
                            }
                            biux+=32;
                        }
                        else //坐标位置无效了，没找到黄箭头
                        {
                            bengzhuiyin=0;
                            break;
                        }
                    }



                }
            }
            qDebug()<<"泵坠印层数为"<<bengzhuiyin;
    }
    //=======================================女娲符印==============================
    if(true)
    {

        QList<QScreen *> list_screen =  QGuiApplication::screens(); //可能电脑接了多个屏幕
        int X=list_screen.at(0)->size().width();
        int Y=list_screen.at(0)->size().height();
        QPixmap pixmap = list_screen.at(0)->grabWindow(0,(X/2-56),(Y-196),477,161);
        if (!pixmap.isNull()) //如果像素图不为NULL
        {

            QImage image = pixmap.toImage();//将像素图转换为QImage
            if (!image.isNull()) //如果image不为空
            {
               int fu1x=55;
               int fu1y=29;
               int fu2x=19;
               int fu2y=48;
               int fu3x=91;
               int fu3y=48;
               if(image.valid(fu1x, fu1y)) //坐标位置有效
               {
                   QColor color=image.pixel(fu1x, fu1y);
                   //0=empty,1=use,2=cd;
                   qDebug()<<colorDiff(color,fuUse)<<colorDiff(color,fuCD)<<colorDiff(color,fuEmpty);
                   if(colorDiff(color,fuUse)<3)
                   {
                       fu1=1;
                   }
                   else if(colorDiff(color,fuCD)<3)
                   {
                       fu1=2;
                   }
                   else
                   {
                       fu1=0;
                   }

               }

               if(image.valid(fu2x, fu2y)) //坐标位置有效
               {
                   QColor color=image.pixel(fu2x, fu2y);
                   qDebug()<<colorDiff(color,fuUse)<<colorDiff(color,fuCD)<<colorDiff(color,fuEmpty);
                   //0=empty,1=use,2=cd;
                   if(colorDiff(color,fuUse)<3)
                   {
                       fu2=1;
                   }
                   else if(colorDiff(color,fuCD)<3)
                   {
                       fu2=2;
                   }
                   else
                   {
                       fu2=0;
                   }

               }

               if(image.valid(fu3x, fu3y)) //坐标位置有效
               {
                   QColor color=image.pixel(fu3x, fu3y);
                   qDebug()<<colorDiff(color,fuUse)<<colorDiff(color,fuCD)<<colorDiff(color,fuEmpty);
                   //0=empty,1=use,2=cd;
                   if(colorDiff(color,fuUse)<3)
                   {
                       fu3=1;
                   }
                   else if(colorDiff(color,fuCD)<3)
                   {
                       fu3=2;
                   }
                   else
                   {
                       fu3=0;
                   }

               }

               {
                   int tmp=fu1;
                   if(tmp==0)
                   {
                       countFuEmpty++;
                   }
                   else if(tmp==1)
                   {
                       countFuUse++;
                   }
                   else
                   {
                       countFuCd++;
                   }
               }
               {
                   int tmp=fu2;
                   if(tmp==0)
                   {
                       countFuEmpty++;
                   }
                   else if(tmp==1)
                   {
                       countFuUse++;
                   }
                   else
                   {
                       countFuCd++;
                   }
               }
               {
                   int tmp=fu3;
                   if(tmp==0)
                   {
                       countFuEmpty++;
                   }
                   else if(tmp==1)
                   {
                       countFuUse++;
                   }
                   else
                   {
                       countFuCd++;
                   }
               }


            }
        }
    }
    qDebug()<<"女娲符印使用中"<<countFuUse<<"女娲符印CD中"<<countFuCd<<"女娲符印空闲中"<<countFuEmpty;
    //===================================技能CD==============================
    if(true)
    {

        QList<QScreen *> list_screen =  QGuiApplication::screens(); //可能电脑接了多个屏幕
        int X=list_screen.at(0)->size().width();
        int Y=list_screen.at(0)->size().height();
        QPixmap pixmap = list_screen.at(0)->grabWindow(0,(X/2-56),(Y-196),477,161);
        if (!pixmap.isNull()) //如果像素图不为NULL
        {
            QImage image = pixmap.toImage();//将像素图转换为QImage
            if (!image.isNull()) //如果image不为空
            {
               int x=88;
               int y=141;

               if(image.valid(x, y)) //弘光坐标位置有效
               {
                   QColor color=image.pixel(x, y);
                   if(color.hsvSaturationF()<0.129)
                   {
                       hongguang=false;
                   }
                   else
                   {
                       hongguang=true;
                   }

               }
               x+=44;

               if(image.valid(x, y)) //娲皇坐标位置有效
               {
                   QColor color=image.pixel(x, y);
                   if(color.hsvSaturationF()<0.202)
                   {
                       wahuang=false;
                   }
                   else
                   {
                       wahuang=true;
                   }

               }
               x+=44;

               if(image.valid(x, y)) //千劫坐标位置有效
               {
                   QColor color=image.pixel(x, y);
                   if(color.hsvSaturationF()<0.259)
                   {
                       qianjiewanhe=false;
                   }
                   else
                   {
                       qianjiewanhe=true;
                   }

               }
               x+=44;

               if(image.valid(x, y)) //昼晴坐标位置有效
               {
                   QColor color=image.pixel(x-5, y);
                   if(color.hsvSaturationF()<0.31)
                   {
                       zhouqing=false;
                   }
                   else
                   {
                       zhouqing=true;
                   }

               }
               x+=44;

               if(image.valid(x, y)) //朝焱咒坐标位置有效
               {
                   QColor color=image.pixel(x, y);
                   if(color.hsvSaturationF()<0.506)
                   {
                       chaoyanzhou=false;
                   }
                   else
                   {
                       chaoyanzhou=true;
                   }

               }
               x+=44;

               if(image.valid(x, y)) //承天暮坐标位置有效
               {
                   QColor color=image.pixel(x, y);
                   if(color.hsvSaturationF()<0.268)
                   {
                       chengtianmu=false;
                   }
                   else
                   {
                       chengtianmu=true;
                   }

               }
               x+=44;

               if(image.valid(x, y)) //玉虹清绝坐标位置有效
               {
                   QColor color=image.pixel(x, y);
                   if(color.hsvSaturationF()<0.228)
                   {
                       yuhongqingjue=false;
                   }
                   else
                   {
                       yuhongqingjue=true;
                   }

               }

               if(image.valid(81, 120)) //玉虹清绝坐标位置有效
               {
                   QColor color=image.pixel(81, 120);
                   if(colorDiff(color,freeHongGuangColor)<3)
                   {
                       freehongguang=true;
                   }
                   else
                   {
                       freehongguang=false;
                   }

               }

            }
        }
    }
    qDebug()<<"弘光"<<hongguang<<"娲皇"<<wahuang<<"千劫"<<qianjiewanhe<<"昼晴"<<chaoyanzhou<<"朝焱咒"<<chengtianmu<<"承天暮"<<chengtianmu<<"玉虹清绝"<<yuhongqingjue;
    int keyCount=0;
    if(hongguang)
    {
        if(freehongguang)
        {
            if(bengzhuiyin>=2)
            {
                g->sendCache.append("58");
                qDebug()<<"使用免费弘光";
                keyCount++;
            }
        }
        else
        {
            if(bengzhuiyin==4)
            {
                g->sendCache.append("58");
                qDebug()<<"使用弘光";
                keyCount++;
            }
        }

    }

    if(wahuang)
    {
        if(countFuEmpty>0)
        {
            g->sendCache.append("66");
            g->sendCache.append("59");
            qDebug()<<"使用娲皇+滚石";
            keyCount++;
            keyCount++;
        }
    }
    if(countFuEmpty>0)
    {
        g->sendCache.append("66");
        qDebug()<<"使用滚石";
        keyCount++;
    }
    if(qianjiewanhe)
    {
        g->sendCache.append("60");
        qDebug()<<"使用千劫";
        keyCount++;
    }

    if(zhouqing)
    {
        if(countFuUse>=2)
        {
            g->sendCache.append("61");
            qDebug()<<"使用昼晴";
            keyCount++;
        }
    }
    if(chaoyanzhou)
    {

    }

    if(chengtianmu)
    {
        g->sendCache.append("63");
        qDebug()<<"使用承天暮";
        keyCount++;
    }

    if(yuhongqingjue)
    {
        if(countFuCd>=2)
        {
            g->sendCache.append("64");
            qDebug()<<"使用玉虹清绝";
            keyCount++;
        }

    }
    //弘光58 娲皇59 千劫60 昼晴61 朝焱咒62 承天暮63 玉虹清绝64 右键65 滚石66 左键67
    if(bengzhuiyin>1)
    {

            if(bengzhuiyin<=3)
            {
                g->sendCache.append("65");
                qDebug()<<"使用右键";
                keyCount++;
            }



    }




}
double SiMingD::colorDiff(QColor hsv1,QColor hsv2)
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
