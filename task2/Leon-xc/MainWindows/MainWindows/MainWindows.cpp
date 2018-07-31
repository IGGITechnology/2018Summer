#include "MainWindows.h"
#include "QColor"

MainWindows::MainWindows(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	resize(900, 700);                                             //widget尺寸
	area = new PaintArea;
	scrollarea = new QScrollArea;
	scrollarea->setBackgroundRole(QPalette::Dark);
	scrollarea->setWidget(area);
	scrollarea->widget()->setMinimumSize(1000, 800);              //滚动区域最小尺寸
	setCentralWidget(scrollarea);

	curFile = tr("newname.png");                                  //新建图片名
	isSaved = false;                                              //是否保存标记量


	//各种信号和槽部分
	ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	connect(
		ui.actOpen, SIGNAL(triggered()), this, SLOT(OnTriggerOpen())

		);
	connect(
		ui.actSave, SIGNAL(triggered()), this, SLOT(OnTriggerSave())
		);
	connect(
		ui.actZoomIn, SIGNAL(triggered()), this, SLOT(OnTriggerZoomIn())
		);
	connect(
		ui.actZoomOut, SIGNAL(triggered()), this, SLOT(OnTriggerZoomOut())
		);
	connect(
		ui.actReturn, SIGNAL(triggered()), this, SLOT(OnTriggerReturn())
		);
	connect(
		ui.actRotate, SIGNAL(triggered()), this, SLOT(OnTriggerRotate())
		);
	connect(
		ui.actShear, SIGNAL(triggered()), this, SLOT(OnTriggerShear())
		);
	connect(
		ui.actClear, SIGNAL(triggered()), this, SLOT(OnTriggerClear())
		);
	connect(
		ui.actEraser, SIGNAL(triggered()), this, SLOT(OnTriggerEraser())
		);
	connect(
		ui.actPen, SIGNAL(triggered()), this, SLOT(OnTriggerPen())
		);
	connect(
		ui.actRect, SIGNAL(triggered()), this, SLOT(OnTriggerRect())
		);
	connect(
		ui.actEllipse, SIGNAL(triggered()), this, SLOT(OnTriggerEllipse())
		);
}

void MainWindows::doOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("OpenFile"), QDir::currentPath());
	if (!fileName.isEmpty())
	{
		area->openImage(fileName);
		scrollarea->widget()->resize(area->getImageSize());
		curFile = fileName;
		isSaved = true;
	}
}

bool MainWindows::SaveFile(QString filename) //实现保存功能
{
	if (area->saveImage(filename, "png"))
	{
		isSaved = true;
		return true;
	}
	return false;
}

bool MainWindows::doFileSave()
{
	if (isSaved)
	{
		return SaveFile(curFile);
	}
	else
	{
		return doFileSaveas();
	}
}

bool MainWindows::doFileSaveas()  //具体实现保存功能
{
	QString Filename = QFileDialog::getSaveFileName(this, tr("SaveAs"), curFile);
	if (Filename.isEmpty())
	{
		return false;
	}
	return SaveFile(Filename);
}

//信号与槽函数
void MainWindows::OnTriggerOpen()
{
	doOpen();
}
void MainWindows::OnTriggerSave()
{
	doFileSave();
}
void MainWindows::OnTriggerZoomIn()
{
	area->zoomIn();
}
void MainWindows::OnTriggerZoomOut()
{
	area->zoomOut();
}
void MainWindows::OnTriggerReturn()
{
	area->zoomReturn();
}
void MainWindows::OnTriggerRotate()
{
	area->Rotate();
}
void MainWindows::OnTriggerShear()
{
	area->Shear();
}
void MainWindows::OnTriggerClear()
{
	area->Clear();
}
void MainWindows::OnTriggerEraser()
{
	area->setShape(PaintArea::ERASER);
}
void MainWindows::OnTriggerPen()
{
	area->setShape(PaintArea::None);
}
void MainWindows::OnTriggerRect()
{
	area->setShape(PaintArea::Rectangle);
}
void MainWindows::OnTriggerEllipse()
{
	area->setShape(PaintArea::Ellipse);
}

void MainWindows::on_comboBoxLine_currentIndexChanged(int index) //功能选择总方法
{
	switch (index)
	{
	case 0:
		area->setPenStyle(Qt::SolidLine);
		break;
	case 1:
		area->setPenStyle(Qt::DotLine);
		break;
	case 2:
		area->setPenStyle(Qt::DashLine);
		break;
	case 3:
		area->setPenStyle(Qt::DashDotDotLine);
		break;
	}
}
void MainWindows::on_comboBoxColor_currentIndexChanged(int index)
{
	switch (index)
	{
	case 0:
		area->setPenColor(Qt::black);
		break;
	case 1:
		area->setPenColor(Qt::white);
		break;
	case 2:
		area->setPenColor(Qt::red);
		break;
	case 3:
		area->setPenColor(Qt::green);
		break;
	case 4:
		area->setPenColor(Qt::blue);
		break;
	case 5:
		area->setPenColor(Qt::cyan);
		break;
	case 6:
		area->setPenColor(Qt::magenta);
		break;
	case 7:
		area->setPenColor(Qt::yellow);
		break;
	}
}

void MainWindows::on_horizontalSlider_valueChanged(int value)    //调增画笔粗细
{
	QString s = QString::number(value, 10);
	area->setPenWidth(value);
	ui.textBrowser->setText(s);
	ui.textBrowser->show();
}

void MainWindows::on_actionPainter_2_0_triggered(bool)  //程序基本信息
{
	QMessageBox msgBox;
	msgBox.setText("There will be drawing board 2.0 to repair several problems \n and add some new function, such as color brush etc.\n                                to be continued.\n");
	msgBox.setWindowTitle("about 1.0");
	msgBox.exec();
}

void MainWindows::on_actionProgrammer_triggered(bool)   //程序基本信息
{
	QMessageBox msgBox;
	msgBox.setText(" This software is programmed by XuCheng,\n and the programmer searched several website for help.\n such as CSDN and Codeforge. ");
	msgBox.setWindowTitle("about programmer");
	msgBox.exec();
}

void MainWindows::on_actfill4_triggered()   //填充方法，四种子填充
{
	area->setShape(PaintArea::SEED_FILL4);
}

void MainWindows::on_actFillScan_triggered() //扫描线种子填充
{
	area->setShape(PaintArea::FILL_SCAN);
}

void MainWindows::on_pushButton_data_clicked()  //显示长宽高面积等信息
{
	QMessageBox msgBox;
	area->height_width();

	QString c_data = "area: ";
	c_data.append(QString::number(area->get_data() / 3090.2481));
	c_data.append(" cm^2\n width: ");
	c_data.append(QString::number((area->c_width)/55.59));
	c_data.append(" cm\n height: ");
	c_data.append(QString::number((area->c_height) / 55.59));
	c_data.append(" cm\n ");
	msgBox.setText(c_data);

	msgBox.setWindowTitle("area");
	area->c_area = 0;
	msgBox.exec();

}