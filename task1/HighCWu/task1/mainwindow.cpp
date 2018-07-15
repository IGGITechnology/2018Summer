#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    console = Console(ui->console);
    console.log(u8"程序启动成功");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @name refreshImg
 * @namespace MainWindow
 * @brief 用于刷新图片显示
 * @return void
 */
void MainWindow::refreshImg()
{
    //设定图像大小自适应label窗口的大小
    cv::Size cvS;
    cvS.height = ui->imageBox->size().height()/1.1;
    cvS.width = (ui->imageBox->size().height()/1.1)*image.cols/image.rows;
    cv::resize(image, image, cvS);
    QImage img = QImage((const unsigned char*)(image.data),
                            image.cols, image.rows, image.cols*image.channels(),QImage::Format_RGB888);
    ui->imageBox->setPixmap(QPixmap::fromImage(img));
}

/**
 * @name resizeEvent
 * @namespace MainWindow
 * @brief resize事件响应函数
 * @param size 窗口调整后的大小
 * @return void
 */
void MainWindow::resizeEvent(QResizeEvent *size)
{
    if(!image.empty()) {
        refreshImg();
        int width = size->size().width();
        int height = size->size().height();
        console.log(QString(u8"窗口大小变化为:") + "(" + QString::number(width) + "," + QString::number(height) + ")", true);
    }
}

/**
 * @name on_action_exit_triggered
 * @namespace MainWindow
 * @brief 退出Item触发响应
 * @return void
 */
void MainWindow::on_action_exit_triggered()
{
    console.log(u8"退出程序中...");
    this->close();
}

/**
 * @name on_action_exit_triggered
 * @namespace MainWindow
 * @brief 打开Item触发响应，弹出文件选择框，若有选择图片则加载到Label中
 * @return void
 */
void MainWindow::on_action_open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                        u8"打开图片文件",
                                                        ".",
                                                        u8"图片文件(*.png *.jpg *.bmp)");
    if(filename.isEmpty()) {console.log(u8"图片打开失败");return;}
    console.log(u8"打开了图片文件:"+filename);
    image = imread(filename.toLocal8Bit().data());
    cvtColor(image, image, CV_BGR2RGB);//BGR转RGB
    refreshImg();
}

/**
 * @name on_action_new_triggered
 * @namespace MainWindow
 * @brief 新建Item触发响应，清空Label图片显示
 * @return void
 */
void MainWindow::on_action_new_triggered()
{
    console.log(u8"新建");
    image = Mat();
    ui->imageBox->setPixmap(QPixmap());
}
