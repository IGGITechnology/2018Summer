//以上为能够响应鼠标事件进行绘图功能的窗体类实现
//主窗口的实现
//mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QLabel>
#include <QComboBox> //下拉列表框
#include <QSpinBox>  //自选盒
#include "drawwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createToolBar(); //创建工具栏
  public slots:
    void ShowStyle(); //进行选择线型风格的槽函数
    void ShowColor(); //选择颜色的槽函数
  private:
    DrawWidget *drawWidget; //创建能够响应鼠标事件进行绘图功能的窗体类
    QLabel *styleLabel;     //风格
    QComboBox *styleComboBox;
    QLabel *widthLabel;     //线宽
    QSpinBox *widthSpinBox; //线宽自旋框
    QToolButton *colorBtn;  //颜色工具
    QToolButton *clearBtn;  //清除按钮
    QToolButton *areaBtn;   //面积计算按钮
    QLabel *area;
};

#endif // MAINWINDOW_H
