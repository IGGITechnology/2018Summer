#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QResizeEvent>
#include "palette.h"
#include "console.h"

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

    void on_pen_clicked(bool checked);

    void on_colorLine_clicked();

    void on_colorFill_clicked();

    void on_fill_clicked(bool checked);

    void on_compute_clicked(bool checked);

    void on_cout_clicked();

protected:
    void mousePressEvent(QMouseEvent* event);  //鼠标按下事件

    void mouseMoveEvent(QMouseEvent* event);  //鼠标移动事件

private:
    Ui::MainWindow *ui;
    Console console;
    Palette palette;
    void mouseDraw(const QPoint &pos);
};

#endif // MAINWINDOW_H
