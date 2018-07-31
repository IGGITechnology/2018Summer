#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QColorDialog>

static bool imgOpened = false;
static int *c_data; // 计算数据

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    console = Console(ui->console);
    console.log(u8"程序启动成功");
    palette = Palette();
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
    int height = ui->imageBoxContent->size().height()/1.1;
    int width = (ui->imageBoxContent->size().height()/1.1)*palette.sHeight()/palette.sWidth();
    ui->imageBox->setFixedHeight(height);
    ui->imageBox->setFixedWidth(width);
    palette.resize(height,width);
    ui->imageBox->setPixmap(QPixmap::fromImage(palette.image()));
}

/**
 * @name resizeEvent
 * @namespace MainWindow
 * @brief resize事件响应函数
 * @param size 窗口调整后的大小
 * @return void
 */
static int last_height;
void MainWindow::resizeEvent(QResizeEvent *size)
{
    int width = size->size().width();
    int height = size->size().height();
    if(!palette.isEmpty() && !last_height && last_height != height) {
        refreshImg();
    }
    console.log(QString(u8"窗口大小变化为:") + "(" + QString::number(width) + "," + QString::number(height) + ")", -1);
    last_height = height;
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
    QColor l_c = palette.lineColor;
    QColor f_c = palette.fillColor;
    palette = Palette(filename);
    palette.lineColor = l_c;
    palette.fillColor = f_c;
    refreshImg();
    imgOpened = true;
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
    QColor l_c = palette.lineColor;
    QColor f_c = palette.fillColor;
    palette = Palette(QSize(400,400));
    palette.lineColor = l_c;
    palette.fillColor = f_c;
    refreshImg();
    imgOpened = true;
}

void MainWindow::on_pen_clicked(bool checked)
{
    if(checked) {
        ui->pen->setText(u8"开始擦");
    } else {
        ui->pen->setText(u8"开始画");
    }
}

void MainWindow::on_colorLine_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    palette.lineColor = color;
    QString color_rgb = "rgb("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")";
    ui->colorLine->setStyleSheet("background-color:"+color_rgb);
    console.log(u8"线条颜色更改为:"+color_rgb);
}


void MainWindow::on_colorFill_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    palette.fillColor = color;
    QString color_rgb = "rgb("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")";
    ui->colorFill->setStyleSheet("background-color:"+color_rgb);
    console.log(u8"填充颜色更改为:"+color_rgb);
}

void MainWindow::on_fill_clicked(bool checked)
{
    if(checked) {
        ui->fill->setText(u8"停止填充");
        ui->pen->setDisabled(true);
    } else {
        ui->fill->setText(u8"开始填充");
        ui->pen->setEnabled(true);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton && imgOpened) {
        mouseDraw(event->pos());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton && imgOpened) {
        mouseDraw(event->pos());
    }
}

void MainWindow::mouseDraw(const QPoint &pos)
{
    QPoint t_pos = ui->imageBox->mapFrom(this, pos);
    if(t_pos.y() < ui->imageBox->height() && t_pos.x() < ui->imageBox->width()) {
        if(ui->compute->isChecked()) {
            c_data = palette.countFill(t_pos.y(),t_pos.x());
            console.log(u8"欲计算数据的起始点为("+QString::number(t_pos.x())+","+QString::number(t_pos.y())+")",1);
            return;
        }
        if(ui->fill->isChecked()) {
            palette.fill(t_pos.y(), t_pos.x());
            console.log(u8"填充图形的起始点为("+QString::number(t_pos.x())+","+QString::number(t_pos.y())+")",2);
        } else if(ui->pen->isChecked()) {
            palette.draw(t_pos.y(), t_pos.x());
            console.log(u8"画笔画在了点("+QString::number(t_pos.x())+","+QString::number(t_pos.y())+")",3);
        } else {
            palette.erase(t_pos.y(), t_pos.x());
            console.log(u8"擦出了点("+QString::number(t_pos.x())+","+QString::number(t_pos.y())+")",4);
        }
        refreshImg();
    }
}

void MainWindow::on_compute_clicked(bool checked)
{
    if(ui->compute->isChecked()) {
        ui->fill->setVisible(false);
        ui->pen->setVisible(false);
        ui->compute->setText(u8"退出点选");
    } else {
        ui->fill->setVisible(true);
        ui->pen->setVisible(true);
        ui->compute->setText(u8"计算数据");
    }
}

void MainWindow::on_cout_clicked()
{
    console.log(u8"选中的图形宽度为:"+QString::number(c_data[0])+u8",高度为:"+QString::number(c_data[1])+u8"面积为:"+QString::number(c_data[2]));
}
