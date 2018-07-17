#pragma once

#include <QWidget>
#include "ui_mywin.h"
#include"QFileDialog"
#include "qpainter.h"
#include"QPainter"
class mywin : public QWidget
{
	Q_OBJECT

public:
	mywin(QWidget *parent = Q_NULLPTR);
	~mywin();

	private slots:           //²Ûº¯Êý
	void on_pushButton_clicked();     
	void on_toolButton_clicked();
	void on_horizontalSlider_valueChanged(int value);
	void on_verticalSlider_valueChanged(int value);
	void on_buttonBox_clicked();

private:
	Ui::mywin ui;
	QImage loadedImage;    //¼ÓÔØÍ¼Æ¬´æ´¢
	QString record;
};
