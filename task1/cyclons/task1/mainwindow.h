// !!! Qt 5
// ========== mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFile>
#include<QFileDialog>
#include<QGraphicsScene>
#include<QGraphicsView>
#include <QTextEdit>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void ClickButton();

private:
    void open();
Ui::MainWindow *ui;

    QAction *openAction;
    QAction *createAction;
};

#endif // MAINWINDOW_H
