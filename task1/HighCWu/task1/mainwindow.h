#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QResizeEvent>
#include <opencv2/opencv.hpp>
#include "console.h"

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void refreshImg();
    void resizeEvent(QResizeEvent* size);

private slots:
    void on_action_exit_triggered();

    void on_action_open_triggered();

    void on_action_new_triggered();

private:
    Ui::MainWindow *ui;
    Mat image;
    Console console;
};

#endif // MAINWINDOW_H
