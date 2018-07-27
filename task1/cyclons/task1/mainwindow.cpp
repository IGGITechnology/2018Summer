// ========== mainwindow.cpp
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include<QImage>
#include"opencv2/opencv.hpp"
#include <QStatusBar>
#include <QToolBar>
#include "ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainWindow)
{
    setWindowTitle(tr("Main Window"));

ui->setupUi(this);
ui->centralWidget->setLayout(ui->gridLayout);//设置layout

    openAction = new QAction(QIcon(":/images/doc-open"), tr("&打开..."), this);
    createAction=new QAction(QIcon(":/images/doc-open"), tr("&新建"), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    QMenu *file = menuBar()->addMenu(tr("&文件"));
    file->addAction(createAction);
    file->addAction(openAction);
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(ClickButton()));
}

MainWindow::~MainWindow()
{
}
void MainWindow::ClickButton()
{
    //what you want to do
   //QMessageBox::information(this, "My Tittle", "Hello World!");
ui->textBrowser->append("Button1_pressed");
}
void MainWindow::open()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));//输出为文件路径，参数为（父窗口，对话框标题，默认目录，过滤器）
       cv::Mat image=cv::imread( path.toStdString());//读取指定路径图片,参数为文件路径

       if(!image.data){
           //QMessageBox::warning(this, tr("警告"),tr("图片打开失败"));
           ui->textBrowser->append("图片打开失败");
                       return;
       }
       else{
           cv::cvtColor(image,image,CV_BGR2RGB);//将BGR顺序的opencv图片转为RGB的顺序，参数为输入图片，输出图片，格式
              QImage img = QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);//将MAT格式转换为QImage格式
              QImage imgscaled=img.scaled(ui->graphicsView->size(),Qt::KeepAspectRatio);//对图片缩放，参数为缩放尺寸
              QGraphicsScene *scene = new QGraphicsScene;//创建场景
              scene->addPixmap(QPixmap::fromImage(imgscaled));//为场景添加图片，参数为Qpixmap类型图像
              ui->graphicsView->setScene(scene);//graphicsView绑定场景，参数为scene
              ui->graphicsView->adjustSize();
              ui->graphicsView->show();
              ui->textBrowser->append("open"+path);//设置textbrowser内容
       }

}

