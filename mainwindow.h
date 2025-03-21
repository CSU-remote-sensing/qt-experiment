#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    struct point
    {
        int number;
        QString code;
        double x;
        double y;
        double h;
    };

point points[1000];
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_open_clicked();

    void on_pushButton_clicked();



    void on_pushButton_save_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
