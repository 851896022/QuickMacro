#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "global.h"
#include "math.h"
using namespace std;
#define PI 3.1415926535897932384626433832795
namespace Ui {
class window;
}

class window : public QMainWindow
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0);
    ~window();
    QTimer delayCount;
private slots:
    void on_test_clicked();

    void on_btnAdd2_clicked();

    void on_btnDel2_clicked();

    void on_btnStart2_clicked();

    void pressNextButton();
    void on_startLink_clicked();

    void on_btnStop2_clicked();

    double colorDiff(QColor hsv1,QColor hsv2);
private:
    Ui::window *ui;
};

#endif // WINDOW_H
