#pragma once
#include "qwidget.h"
#include "QWidget"
#include "QMouseEvent"
#include "QPoint"
#include "QPaintEvent"
#include "QPainter"
#include "QPen"
#include "QStack"


class PaintArea :
	public QWidget
{
public:
	PaintArea();
	~PaintArea();



	//创建栈
	struct points
	{
		int x;
		int y;
	};

	QStack<points> SeedPoints_Stack;

	//设置画布参数
	void setImageSize(int width, int height);
	void setImageColor(QColor color);


	bool saveImage(const QString& fileName, const char* fileFormat);//保存图片
	bool openImage(const QString& fileName);
	QSize getImageSize();

	//各种功能函数，包括画笔风格 颜色，宽度，填充颜色                                 ??

	void setPenStyle(Qt::PenStyle style);
	void setPenWidth(int width);
	void setPenColor(QColor color);
	void seedFill4(int x, int y, QColor Fcolor);
	void FillScan(points seed, QColor Fcolor);

	//设置图形菜单，包括画笔
	enum ShapeType  //枚举变量，几个图形的选择
	{
		None,
		Rectangle,
		Ellipse,
		ERASER,
		SEED_FILL4,
		FILL_SCAN
	};
	ShapeType curShape;

	//旋转，缩放，拉伸
	void zoomIn(); //放大
	void zoomOut();
	void zoomReturn();

	void Rotate(); //旋转
	void Shear();  //拉伸
	void Clear();  //清空
	void setShape(ShapeType shape);  //设置要绘制的图形


private:

	//各种参数

	QImage Image;
	QImage temImage;
	QColor backColor;          //整体参数

	int angle;
	qreal scale;
	qreal shear;              //旋转拉伸放大等参数

	QColor penColor;
	int penWidth;
	Qt::PenStyle penStyle;

	QPoint lastPoint, endPoint;

	bool isDrawing;

	bool remark;
	bool remark2;
	//标记量，判断从白变到了黑。

	//鼠标事件与绘画事件
	void paintEvent(QPaintEvent *event);//重绘事件
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent* event);
	void paint(QImage& TheImage);

public:
	//得到数据
	int get_data();
	void height_width();

	//数据参数
	int c_height;
	int c_width;
	int c_area = 0;
};


