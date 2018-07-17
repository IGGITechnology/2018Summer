#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<QGraphicsScene>
#include<QGraphicsView>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void soltExitRestart();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void newB();
    void reset();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
