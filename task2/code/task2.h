#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_task2.h"
#include<qdebug.h>
#include<qevent.h>
#include<QMouseEvent>
#include<qdialog.h>
#include<qpainter.h>
#include<qpainterpath.h>
#include<qpoint.h>
#include<qpushbutton.h>
#include<vector>
#include<deque>
#include<qlayout.h>
#include<qtextbrowser.h>
#include<qimage.h>
#include<qmessagebox.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<qfiledialog.h>
extern int debug;
extern bool on_render;
struct Geometry {
	double h = 0, w = 0,s = 0;//记录上漆部分的几何参数
};

class myWidget :public QWidget {
	Q_OBJECT
private:
    //呈现给用户的笔记根据paintpath绘制出来，paintpath是由小段小段的直线形成
	//用户点击myWidget上一点，该店的坐标通过信号槽传给start,之后再不断的MouseMove中
	//鼠标的新坐标会不断的传给end值，每次传给end值后，只要把path用Lineto函数延长到end坐标就行
	QPoint start = QPoint(0, 0), end = QPoint(0, 0); 
	QPen pen = QPen(Qt::black, 5);   
	QBrush brush = QBrush(Qt::red);
	QPainterPath current;
	QImage* img;    //用于像素操作的图片
	QImage tmp;      //只是在render中用到，后面会说明
	cv::Mat mat;     //用于借助opencv的函数打开和保存图片，只是在QImage和用户选择图片之间的一个中介，主要的操作在QImage上
	std::vector<QPainterPath> allDraw;    //用于保存所有的笔记，鼠标每按下抬起一次就是一次笔迹
	std::deque<QPoint> pointsToSearch;     //用于种子搜索算法的队列

	Geometry seedSearchBrush(int x, int y,QColor boundColer, QColor brushColor);
	int saveOrDiscard();
	bool isModified=false;    //用于记录图片上是否有修改，以此判断是否调用saveOrDiscard
public:
    myWidget(QWidget* parent=Q_NULLPTR)
		:QWidget(parent)
	{
	    img = new QImage(this->size(), QImage::Format_RGB888);
		setPalette(QPalette(Qt::white));
	}
	void on_draw_trigger();
	void on_brush_trigger();
	void on_open_trigger();
protected:
	//当myWidget对象创建并显示出来时，鼠标的行为会导致这些事件处理函数不断的发出信号
	void mousePressEvent(QMouseEvent* e) {
		emit startDrawing(e->pos());
	}
	void mouseReleaseEvent(QMouseEvent* e) {
		emit stopDrawing();
	}
	void mouseMoveEvent(QMouseEvent* e) {
		emit onDrawing(e->pos());
	}
	void paintEvent(QPaintEvent* e) {
		//myWidget中显示的由2部分组成，第一部分是QImage对象被drawImage函数画在myWidget上的图像
		//（这也包括上漆的部分，因为上漆就是在Image上进行的)，第二部分是之后画上去的每一笔QPaintPath,
		QPainter painter(this);
		painter.setPen(pen);
		painter.setBrush(Qt::NoBrush);
		qDebug() << "pAINT";
		if (on_render) { painter.drawImage(0, 0, tmp); }  
		else painter.drawImage(0,0,*img);            
		//每当自动调用或者update()主动调用paintevent()函数时，我的理解是，他默认只会画出Widget中与具体细节无关的部分
		//也就是整个窗体的边框什么的，窗体中像笔迹这样的细节要是paintevent也知道要怎么去画，那它也太牛逼了，它不可能去定义要怎么去画，
		//因此必须在每次重绘时把之前的所有笔迹都重绘，不然之前的笔迹不会显示。
		for (auto iter = allDraw.begin(); iter != allDraw.end(); iter++) {
			painter.drawPath(*iter);
		}
		painter.end();
	}
	signals:
		void startDrawing(QPoint);
	signals:
		void stopDrawing();
	signals:
		void onDrawing(QPoint);

};

class task2 : public QMainWindow
{
	Q_OBJECT
private:
	Ui::task2Class ui;
	myWidget wd;     //主窗体除了基本的工具栏之外，以myWidget作为显示图片的centerWidget
public:
	task2(QWidget *parent = Q_NULLPTR)
		:QMainWindow(parent)
	{
		ui.setupUi(this);
	    //定义了3个动作到工具栏，分别实现打开图片，画笔，上漆功能
		QAction* open = new QAction(tr("open"), this);
		QAction* draw=new QAction(tr("&draw"),this);
		QAction* brush=new QAction(tr("&brush"),this);
		open->setShortcut(QKeySequence::Open);
		connect(open, &QAction::triggered, &wd, &myWidget::on_open_trigger);   
		connect(draw, &QAction::triggered, &wd, &myWidget::on_draw_trigger);
		connect(brush, &QAction::triggered, &wd, &myWidget::on_brush_trigger);
		ui.mainToolBar->addAction(open);
		ui.mainToolBar->addAction(draw);
		ui.mainToolBar->addAction(brush);
		
		setCentralWidget(&wd);
	}
};

class myDialog :public QDialog {
	Q_OBJECT
		
public:
	QPushButton *ok;
	myDialog(QWidget* parent = nullptr)
		:QDialog(parent)
	{
		ok = new QPushButton(tr("ok"), this);
		QObject::connect(ok, &QPushButton::clicked, this, &myDialog::close);
	}
	signals:
		void finished();
protected:
	void closeEvent(QCloseEvent* e) {
		qDebug() << "C";
		emit finished();
		QDialog::closeEvent(e);
	}
};
