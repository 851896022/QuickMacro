#ifndef SIMINGD_H
#define SIMINGD_H

#include <QObject>
#include "QApplication"
#include "QPixmap"
#include "QImage"
#include "QColor"
#include "QScreen"
#include "QDebug"
#include <QTimer>
class SiMingD : public QObject
{
    Q_OBJECT
public:
    explicit SiMingD(QObject *parent = nullptr);
    QTimer *timer;
signals:

public slots:
    void work();
    double colorDiff(QColor hsv1,QColor hsv2);
    void start();
    void stop();
};
#include "global.h"
#endif // SIMINGD_H
