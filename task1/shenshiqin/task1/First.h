#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_First.h"
#include<qpushbutton.h>
#include<Qimage>
#include<QGraphicsview>
#include<QGraphicsScene>
#include<qfiledialog>
#include<QLayout>
#include<qmessagebox.h>
#include<qaction.h>
#include<QCloseEvent>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
namespace Ui {
	class MainWindow;
}
class First : public QMainWindow
{
	Q_OBJECT

public:
	First(QWidget *parent = Q_NULLPTR);
public slots:
	void on_OpenImage_trigger();
private:
	Ui::FirstClass ui;
	cv::Mat img;	
	QGraphicsScene* sence;
	int saveOrDiscard();	

};


