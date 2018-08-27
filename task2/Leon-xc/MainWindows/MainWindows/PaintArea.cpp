#include "PaintArea.h"
#include "QDebug"

PaintArea::PaintArea()
{
	Image = QImage(700, 500, QImage::Format_RGB32); //画布初始化
	backColor = qRgb(255, 255, 255);
	Image.fill(backColor);

	//参数初始化
	isDrawing = false;
	angle = 0;
	shear = 0;
	scale = 1;
	curShape = None;
	isDrawing = false;
	penColor = Qt::black;              //设置画笔初始值
	penWidth = 5;
	penStyle = Qt::SolidLine;
}

PaintArea::~PaintArea()
{

}

//1.整图效果设置

void PaintArea::Rotate() //旋转
{
	angle += 45;
	update();
}

void PaintArea::Shear() //拉伸
{
	shear = 0.2;
	update();
}

void PaintArea::Clear() //清空
{
	Image.fill(backColor);
	update();
}

void PaintArea::zoomIn()//放大
{
	scale *= 1.2;
	update();
}
void PaintArea::zoomOut()
{
	scale /= 1.2;
	update();
}

void PaintArea::zoomReturn()
{
	scale = 1;
	angle = 0;
	update();
}



void  PaintArea::setPenStyle(Qt::PenStyle style)                 //2.画笔设置
{

	penStyle = style;
}

void  PaintArea::setPenWidth(int width)
{
	penWidth = width;
}

void  PaintArea::setPenColor(QColor color)
{
	penColor = color;
}

//void  PaintArea::setBrushColor(QColor color)       //2.0补充项
//{
//	brushColor = color;
//}



void PaintArea::setImageSize(int width, int height)
{
	QImage newImage(width, height, QImage::Format_RGB32);
	Image = newImage;
	update();
}

//void PaintArea::setImageColor(QColor color)
//{
//	backColor = color.rgb();
//	Image.fill(backColor);
//	update();
//}



QSize PaintArea::getImageSize()
{
	return Image.size();
}



bool PaintArea::saveImage(const QString& fileName, const char* fileFormat)//保存图片
{
	QImage visibleImage = Image;
	if (visibleImage.save(fileName, fileFormat))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PaintArea::openImage(const QString& fileName)
{
	QImage loadedImage;
	loadedImage.load(fileName);
	QSize newSize = loadedImage.size();

	setImageSize(newSize.width(), newSize.height());
	Image = loadedImage;
	update();
	return true;
}

/////////////////////////////////////////

void PaintArea::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		isDrawing = true;
		lastPoint = event->pos();
	}
}

void PaintArea::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		endPoint = event->pos();
		isDrawing = false;
		paint(Image);                                                            //在原图上的最后一次绘图
	}
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)                                    //应用双缓冲
{

	endPoint = event->pos();
	if (curShape == None || curShape == ERASER)
	{
		paint(Image);
		isDrawing = false;
	}
	else
	{
		temImage = Image;
		paint(temImage);
	}
}

void PaintArea::paintEvent(QPaintEvent *event)
{

	QPainter painter(this);

	painter.scale(scale, scale);
	painter.drawImage(0, 0, Image);

	if (isDrawing)
	{
		painter.drawImage(0, 0, temImage);
	}
	else
	{
		if (angle)
		{
			QImage copyImage = Image;
			QPainter p(&copyImage);
			QPointF center(copyImage.width() / 2.0, copyImage.height() / 2.0);

			//QPainter p(&Image);
			//QPointF center(Image.width() / 2.0, Image.height() / 2.0);         //有误

			p.translate(center);
			p.rotate(angle);
			p.translate(-center);
			p.drawImage(0, 0, Image);                                      //不能随意复制坐标系统，会出问题
			Image = copyImage;
			angle = 0;

		}

		if (shear)
		{
			QImage copyImage = Image;
			QPainter p(&copyImage);
			p.shear(shear, shear);
			p.drawImage(0, 0, Image);
			Image = copyImage;
			shear = 0;
			//有bug
		}
	}

}

void PaintArea::setShape(ShapeType shape)                        //4.设置作画图形 3.橡皮
{
	curShape = shape;
}


void PaintArea::paint(QImage& TheImage)
{
	QPainter p(&TheImage);   //在临时绘图区上绘图

	QPen pen;                                                      //可以添加填充brush 2.0
	pen.setColor(penColor);
	pen.setWidth(penWidth);
	pen.setStyle(penStyle);
	p.setPen(pen);

	QRect rect;

	int a, b, c, d;
	a = lastPoint.x() / scale;
	b = lastPoint.y() / scale;
	c = (endPoint.x() - a) / scale;
	d = (endPoint.y() - b) / scale;

	switch (curShape)
	{
	case None:    //画笔选项
	{
		p.drawLine(lastPoint / scale, endPoint / scale);
		lastPoint = endPoint;
		break;
	}
	case Rectangle:
	{
		p.drawRect(a, b, c, d);
		break;
	}
	case Ellipse:
	{
		p.drawEllipse(a, b, c, d);
		break;
	}
	case ERASER:
	{
		rect = QRect(lastPoint, QPoint(lastPoint.x() + 10, lastPoint.y() + 10));
		p.eraseRect(rect);
		lastPoint = endPoint;
		break;
	}
	case SEED_FILL4:
	{
		QColor backColor = Image.pixelColor(lastPoint);
		int x = lastPoint.x();
		int y = lastPoint.y();
		seedFill4(x, y, penColor);
	}
	case FILL_SCAN:
	{
		QColor backColor = Image.pixelColor(lastPoint);
		points seed;
		seed.x = lastPoint.x();
		seed.y = lastPoint.y();
		FillScan(seed, penColor);
	}
	}
	update();

}


void PaintArea::seedFill4(int x, int y, QColor Fcolor)
{
	QColor currentColor = Image.pixelColor(x, y);
	if (currentColor == backColor)
	{
		Image.setPixelColor(x, y, Fcolor);
		seedFill4(x, y - 1, Fcolor);
		seedFill4(x, y + 1, Fcolor);
		seedFill4(x - 1, y, Fcolor);
		seedFill4(x + 1, y, Fcolor);
	}
}

void PaintArea::FillScan(points seed, QColor Fcolor)
{
	
	//填充栈中的种子点并寻找新的种子点

	SeedPoints_Stack.push(seed);                                       //起始点为鼠标点击点，得到坐标，压入栈
	while (!SeedPoints_Stack.isEmpty())                                //栈中不为空就填充
	{
		points seedXY;
		seedXY = SeedPoints_Stack.pop();

		int seedX = seedXY.x;                             //种子点的x,y坐标
		int seedY = seedXY.y;

		int xR = seedX;                                  //向左右延伸
		int xL = seedX;
		int y = seedY;                                   //在该行延申
		while (backColor == Image.pixelColor(xR, y))     //向右延申，如果颜色为原背景色，那么就填充
		{
			Image.setPixelColor(xR, y, Fcolor);
			xR++;
			c_area++;                                    //用来统计面积
		}
		xR--;                                            //回到区域内
		xL--;                                            //起始点左侧一点，因为刚刚xL已经被上过色了
		while (backColor == Image.pixelColor(xL, y))
		{
			Image.setPixelColor(xL, y, Fcolor);
			xL--;
			c_area++;                                    //用来统计面积
		}
		xL++;                                            //回到区域内
	
		//向上寻找种子点

		points ScanPoint;                                //新的扫描点，为最左侧上的一点
		ScanPoint.x = xL;
		ScanPoint.y = y + 1;
		//该算法的顺序问题
	Judgement:
		switch (Image.pixelColor(ScanPoint.x, ScanPoint.y) == backColor)
		{
		case 1:                                              //新的点如果是背景色，则继续向右扫描
			ScanPoint.x++;
			remark = 1;
			goto Judgement;
			break;
		case 0:                                               //新的点如果是不为背景色，remark就是==1，则将改点前一个压栈
			if (remark)
			{
				ScanPoint.x--;
				SeedPoints_Stack.push(ScanPoint);
				remark = 0;
				ScanPoint.x++;
			}

			if (ScanPoint.x <= xR - 2)                       //判断是不是最后与边界相连的黑点
			{
				ScanPoint.x++;
				goto Judgement;
			}
			break;
		}

		//向下寻找种子点，与上同理。
		ScanPoint.x = xL;                                               //扫描点为下方的点
		ScanPoint.y = y - 1;
	Judgement2:
		switch (Image.pixelColor(ScanPoint.x, ScanPoint.y) == backColor)
		{
		case 1:
			ScanPoint.x++;
			remark2 = 1;
			goto Judgement2;
			break;
		case 0:
			if (remark2)
			{
				ScanPoint.x--;
				SeedPoints_Stack.push(ScanPoint);
				remark2 = 0;
				ScanPoint.x++;
			}

			if (ScanPoint.x <= xR - 2)
			{
				ScanPoint.x++;
				goto Judgement2;
			}
			break;
		}
	}
}

int PaintArea::get_data()
{
	return c_area;
}

void PaintArea::height_width()
{
	int x, y;
	c_width = 0;
	bool remark=1;
	int width_x=0, height_y=0;
	
	for ( y = 0; y < 500; y++)  //从第一个点开始判断，直到找到第一个黑点，再找到最后一个黑点，即为改行最大值，所有行最大值即为总的宽度
	{
        for ( x = 0; x < 700; x++)
		{
			if ((Image.pixelColor(x, y) != backColor))
			{
				if (remark==1)
				{
					width_x = x;
					remark = 0;
				}
				if (c_width<x-width_x)
				{
					c_width = x - width_x;
				}
			}
		}
		x = 0;
		remark = 1;
	}
	c_width++;

	c_height = 0;
	remark = 1;
	width_x = 0, height_y = 0;   //高度与宽度的方法相同

	for (x = 0; x < 700; x++)
	{
		for (y = 0; y < 500; y++)
		{
			if ((Image.pixelColor(x, y) != backColor))
			{
				if (remark == 1)
				{
					c_height = y;
					remark = 0;
				}
				if (c_height<y - height_y)
				{
					c_height=y-height_y;
				}
			}
		}
		y = 0;
		remark = 1;
	}
	c_height++;
}