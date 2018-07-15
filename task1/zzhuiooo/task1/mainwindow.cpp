#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->action, SIGNAL(triggered(bool)), this, SLOT(menunew()));
    QObject::connect(ui->action_2,SIGNAL(triggered(bool)),this,SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->append("open picture");
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
       cv::Mat image=cv::imread( path.toStdString());
       cv::cvtColor(image,image,CV_BGR2RGB);
          QImage img = QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
          QImage imgscaled=img.scaled(ui->graphicsView->size(),Qt::KeepAspectRatio);
          QGraphicsScene *scene = new QGraphicsScene;
          scene->addPixmap(QPixmap::fromImage(imgscaled));
          ui->graphicsView->setScene(scene);
          ui->graphicsView->adjustSize();
          ui->graphicsView->show();
}
void MainWindow::on_pushButton_2_clicked()
{
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addText(NULL);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(10,10,220,239);
    ui->graphicsView->show();
    ui->textBrowser->append("clear picture");
}
void MainWindow::menunew()
{
    ui->textBrowser->append("new open picture");
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
       cv::Mat image=cv::imread( path.toStdString());
       cv::cvtColor(image,image,CV_BGR2RGB);
          QImage img = QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
          QImage imgscaled=img.scaled(ui->graphicsView->size(),Qt::KeepAspectRatio);
          QGraphicsScene *scene = new QGraphicsScene;
          scene->addPixmap(QPixmap::fromImage(imgscaled));
          ui->graphicsView->setScene(scene);
          ui->graphicsView->adjustSize();
          ui->graphicsView->show();
}
