#include "mywin.h"

mywin::mywin(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

mywin::~mywin()
{
}

void mywin::on_pushButton_clicked()                               //打开按钮被点击时间函数
{
	
	QString fileName = QFileDialog::getOpenFileName(this, tr("OpenFile"), QDir::currentPath());
	if (!fileName.isEmpty())
	{
		loadedImage.load(fileName);
		QSize newSize = loadedImage.size();
	}
	//加载image

	//QPainter painter(ui.widget);                                                        //法三，用painter 来画pixmap
	//QPixmap pix;

	//pix = pix.fromImage(loadedImage);// 2

	//painter.drawPixmap(0, 0, (ui.widget->size()).width(), (ui.widget->size()).height(), pix);
	//update();
	
	ui.label_2->setScaledContents(true);
	ui.label_2->setPixmap((QPixmap::fromImage(loadedImage)).scaled(ui.label_2->size().width(),ui.label_2->size().height()));             //显示区为label,法一
	                                                                                                                                     //在label中显示pixmap
	
	
	/*ui.widget->setAutoFillBackground(true);                     //显示窗口为widget，法二
	QPalette palette;                                             //用QPalette来加载image。
	palette.setBrush(this->backgroundRole(), QBrush(loadedImage));
	ui.widget->setPalette(palette);*/

	record.append( "open a picture !!!\n");                //用record记录操作
	ui.textBrowser->setText(record);               //记录操作，每次点击记录open a picture
}

void mywin::on_toolButton_clicked()
{
	record.append( "a toolbutton is clicked !!!\n");                //用record记录操作

	ui.textBrowser->setText(record);
}
void mywin::on_horizontalSlider_valueChanged(int value)
{
	record.append("horizontalSlider value Changed !!!\n");                //用record记录操作	

	ui.textBrowser->setText(record);
}
void mywin::on_verticalSlider_valueChanged(int value)
{
	record.append("verticalSlider value Changed !!!\n");                //用record记录操作

	ui.textBrowser->setText(record);
}
void mywin::on_buttonBox_clicked()
{
    record.append("buttonBox is clicked !!!\n");                //用record记录操作

	ui.textBrowser->setText(record);
}
