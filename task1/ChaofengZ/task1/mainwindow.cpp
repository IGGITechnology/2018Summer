#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QObject::connect(ui->actionxinjian, SIGNAL(triggered(bool)), this, SLOT(newB()));
    QObject::connect(ui->action, SIGNAL(triggered(bool)), this, SLOT(reset()));
    QObject::connect(ui->action_2, SIGNAL(triggered(bool)), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->append("open and show pic");
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));//输出为文件路径，参数为（父窗口，对话框标题，默认目录，过滤器）
       cv::Mat image=cv::imread( path.toStdString());//读取指定路径图片,参数为文件路径
       cv::cvtColor(image,image,CV_BGR2RGB);//将BGR顺序的opencv图片转为RGB的顺序，参数为输入图片，输出图片，格式
          QImage img = QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);//将MAT格式转换为QImage格式
          QImage imgscaled=img.scaled(ui->graphicsView->size(),Qt::KeepAspectRatio);//对图片缩放，参数为缩放尺寸
          QGraphicsScene *scene = new QGraphicsScene;//创建场景
          scene->addPixmap(QPixmap::fromImage(imgscaled));//为场景添加图片，参数为Qpixmap类型图像
          ui->graphicsView->setScene(scene);//graphicsView绑定场景，参数为scene
          ui->graphicsView->adjustSize();
          ui->graphicsView->show();

}

void MainWindow::on_pushButton_2_clicked()
{

   QGraphicsScene *scene = new QGraphicsScene;
   scene->addText(NULL);
   ui->graphicsView->setScene(scene);
   ui->graphicsView->setGeometry(124,1,305,136);
   ui->graphicsView->show();
   ui->textBrowser->append("close picture");
}

void MainWindow::newB()
{
    ui->textBrowser->append("新建一下（除了显示字并没有什么用）nn");
}
void MainWindow::reset()
{
    ui->textBrowser->append("重置一下n");
    //  773 = 'r'+'e'+'s'+'t'+'a'+'r'+'t'
        //  ==>restart
        //#define EXIT_RESTART  773
        qApp->exit(773);
}

