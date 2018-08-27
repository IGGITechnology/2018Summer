//drawwidget.cpp
//DrawWidget构造函数完成对窗体参数及部分功能的初始化工作
#include "drawwidget.h"
#include <QtGui>
#include <QPen>
#include <QFileDialog>
#include <iostream>
#include <windows.h>
#include <QRgb>
#include <stack>
#include <qmessagebox.h>

using namespace std; //hi

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true); //对窗体背景色的设置
    QPalette palette = this->palette();
    QString path = QFileDialog::getOpenFileName(this, "Open Image", ".", "Image File(*.png *.jpg *.jpeg *.bmp)"); //输出为文件路径，参数为（父窗口，对话框标题，默认目录，过滤器）
    cv::Mat image = cv::imread(path.toStdString());                                                               //读取指定路径图片,参数为文件路径
    cv::cvtColor(image, image, CV_BGR2RGB);                                                                       //将BGR顺序的opencv图片转为RGB的顺序，参数为输入图片，输出图片，格式
    QImage img = QImage((const unsigned char *)(image.data), image.cols, image.rows, QImage::Format_RGB888);      //将MAT格式转换为QImage格式
    QImage imgscaled = img.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);                   //对图片缩放，参数为缩放尺寸

    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap::fromImage(imgscaled))); // 使用平滑的缩放方式
    setPalette(palette);                                     
    pix = new QPixmap(size());                               //此QPixmap对象用来准备随时接受绘制的内容
    pix->fill(Qt::transparent);                              
    setMinimumSize(600, 400);                                //设置绘制区窗体的最小尺寸
}

//接受主窗体传来的线型风格参数
void DrawWidget::setStyle(int s)
{
    style = s;
}

//setWidth()接受主窗体传来的线宽参数值
void DrawWidget::setWidth(int w)
{
    weight = w;
}

//接受主窗体传来的画笔颜色值
void DrawWidget::setColor(QColor c)
{
    color = c;
    qDebug() << color.rgb();
}

void DrawWidget::area()
{

     int result=LineFill(areaPos.x(), areaPos.y());
     int H=maxH-minH;
     int W=maxW-minW;
     QString r=QString::number(result, 10);
      QString h=QString::number(H, 10);
       QString w=QString::number(W, 10);
     QMessageBox msgBox;
     QString s="Area:"+r+" H:"+h+" W:"+w;
     msgBox.setText(s);
     msgBox.exec();

}

//重定义鼠标按下事件--按下鼠标时,记录当前鼠标位置值startPos
void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        startPos = e->pos();
        beginPos = e->pos();
        //    drawP(e->pos().x(),e->pos().y());
        maxH=startPos.y();
        minH=startPos.y();
        maxW=startPos.x();
        minW=startPos.x();
    }
    if (e->button() == Qt::RightButton)
    {
        areaPos = e->pos();
        qDebug() << areaPos;
    }
}
void DrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPainter *painter = new QPainter; //新建一个QPainter对象
        QPen pen;                         //新建一个QPen对象
                                          //设置画笔的线型,style表示当前选择的线型是Qt::PenStyle枚举数据中的第几个元素
        pen.setStyle((Qt::PenStyle)style);
        pen.setWidth(weight); //设置画笔的线宽值
        pen.setColor(color);  //设置画笔的颜色
        painter->begin(pix);
        painter->setPen(pen); //将QPen对象应用到绘制对象当中
        painter->drawLine(event->pos(), beginPos);
        painter->end();
        update();
    }
}

//重定义鼠标移动事件
void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{

    QPainter *painter = new QPainter; //新建一个QPainter对象
    QPen pen;                         //新建一个QPen对象
                                      //设置画笔的线型,style表示当前选择的线型是Qt::PenStyle枚举数据中的第几个元素
    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(weight); //设置画笔的线宽值
    pen.setColor(color);  //设置画笔的颜色
    painter->begin(pix);
    painter->setPen(pen); //将QPen对象应用到绘制对象当中
    //绘制从startPos到鼠标当前位置的直线
    painter->drawLine(startPos, e->pos());
    painter->end();      //绘制成功返回true
    startPos = e->pos(); //更新鼠标的当前位置,为下次绘制做准备
    update();            //重绘绘制区窗体
    if(e->pos().x()>maxW)
    {
        maxW=e->pos().x();
    }
    if(e->pos().x()<minW)
    {
        minW=e->pos().x();
    }
    if(e->pos().y()>maxH)
    {
        maxH=e->pos().y();
    }
    if(e->pos().y()<minH)
    {
        minH=e->pos().y();
    }

}


void DrawWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
}

void DrawWidget::resizeEvent(QResizeEvent *event)
{
    //判断改变后的窗体长或宽是否大于原窗体的长和宽;
    //若大于则进行相应调整;
    if (height() > pix->height() || width() > pix->width())
    {
        QPixmap *newPix = new QPixmap(size()); //创建一个新的QPixmap对象
        newPix->fill(Qt::white);               //填充新QPixmap对象newPix的颜色为白色背景色
        QPainter p(newPix);
        p.drawPixmap(QPoint(0, 0), *pix); //在newPix中绘制原pix中内容
        pix = newPix;                     //将newPix赋值给Pix作为新的绘制图形接收对象
    }
    //否则直接调用QWidget的resizeEvent()函数返回
    QWidget::resizeEvent(event); //完成其余工作
}

/***
 * clear()函数完成绘制区的清除工作,只需要一个新的，干净的QPixmap对象代替pix,并调用update()重绘即可
 */
void DrawWidget::clear()
{
    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill(Qt::white);
    pix = clearPix;
    update();
}

int DrawWidget::LineFill(int x, int y)//扫描线填充算法
{
    int area = 0;
    int xl, xr;
    bool scanNeedFill;
    QPoint pt;
    stack<QPoint> Sstack;
    while (!Sstack.empty())
    {
        Sstack.pop();
    }
    pt.setX(x);
    pt.setY(y);
    Sstack.push(pt);
    QRgb old = getRgb(x + 1, y + 1);

    while (!Sstack.empty())
    {
        pt = Sstack.top();
        Sstack.pop();
        int xt, yt;
        xt = pt.x();
        yt = pt.y();
        QRgb temp = getRgb(xt, yt);
        while (temp == old)
        {
            drawP(xt, yt);
            xt++;
            temp = getRgb(xt, yt);
        }
        xr = xt - 1;

        xt = pt.x() - 1;
        while (getRgb(xt, yt) == old)
        {
            drawP(xt, yt);
            xt--;
        }
        xl = xt + 1;

        area = area + xr - xl + 1;

        xt = xl;
        yt = yt + 1;
        while (xt < xr)
        {
            scanNeedFill = false;
            while (getRgb(xt, yt) == old)
            {
                scanNeedFill = true;
                xt++;
            }

            if (scanNeedFill)
            {
                pt.setX(xt - 1);
                pt.setY(yt);
                Sstack.push(pt);
                scanNeedFill = false;
            }
            while (getRgb(xt, yt) != old && xt < xr)
            {
                xt++;
            }
        }

        xt = xl;
        yt = yt - 2;
        while (xt < xr)
        {
            scanNeedFill = false;
            while (getRgb(xt, yt) == old)
            {
                scanNeedFill = true;
                xt++;
            }

            if (scanNeedFill)
            {
                pt.setX(xt - 1);
                pt.setY(yt);
                Sstack.push(pt);
                scanNeedFill = false;
            }
            while (getRgb(xt, yt) != old && xt < xr)
            {
                xt++;
            }
        }
    }

    return area;
}

QRgb DrawWidget::getRgb(int x, int y)
{
    QRgb pixvlaue = pix->toImage().pixel(x, y);//获取像素点的颜色值
    return pixvlaue;
}

void DrawWidget::drawP(int x, int y)
{
    QPainter *painter = new QPainter; //新建一个QPainter对象
    QPen pen;                         //新建一个QPen对象
                                      //设置画笔的线型,style表示当前选择的线型是Qt::PenStyle枚举数据中的第几个元素
    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(weight); //设置画笔的线宽值
    pen.setColor(color);  //设置画笔的颜色
    painter->begin(pix);
    painter->setPen(pen);     //将QPen对象应用到绘制对象当中
    painter->drawPoint(x, y); //画一个点
    painter->end();           //绘制成功返回true
    update();
}
