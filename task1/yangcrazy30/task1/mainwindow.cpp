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
    ui->centralWidget->setLayout(ui->gridLayout);//设置layout
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
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
          ui->textBrowser->setText("open"+path);//设置textbrowser内容


         /* cv::Mat image=cv::imread(path.toStdString());
          cv::namedWindow("My image");
          cv::imshow("My image",image);//参数为窗口标题以及图片 */
          //通过打开新窗口显示图片的形式
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{
}
