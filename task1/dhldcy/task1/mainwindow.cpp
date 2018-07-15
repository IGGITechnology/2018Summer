#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("EMMMMMMMM");
    QObject::connect(ui->openaction,SIGNAL(triggered()),this,SLOT(openFileSlot()));//打开
    QObject::connect(ui->exitaction,SIGNAL(triggered()),this,SLOT(exit()));//退出
    QObject::connect(ui->aboutQtaction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));//显示
    QObject::connect(ui->aboutWebaction,SIGNAL(triggered()),this,SLOT(aboutWebsiteSlot()));//网页

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openFileSlot()
{
    QString filename;
        filename=QFileDialog::getOpenFileName(this,
                                              tr("选择图像"),
                                              "",
                                              tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
        if(filename.isEmpty())
        {
             return;
        }
        else
        {
            QImage* img=new QImage;

            if(! ( img->load(filename) ) ) //加载图像
            {
                QMessageBox::information(this,
                                         tr("打开图像失败"),
                                         tr("打开图像失败!"));
                delete img;
                return;
            }
            img->scaled(ui->label->size(),
                         Qt::KeepAspectRatio);
            ui->label->setScaledContents(true);
            ui->label->setPixmap(QPixmap::fromImage(*img));
            ui->textEdit->setText("打开 "+filename);



        }

}

void MainWindow::exit()
{
  this->close();
}
void MainWindow::aboutWebsiteSlot()
{
   QDesktopServices::openUrl( QUrl("http://www.bilibili.com"));
}

