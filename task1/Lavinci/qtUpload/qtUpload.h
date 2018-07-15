#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtUpload.h"
#include <opencv2\opencv.hpp>

class qtUpload : public QMainWindow
{
	Q_OBJECT

public:
	qtUpload(QWidget *parent = Q_NULLPTR);
	QString content;
private:
	Ui::qtUploadClass ui;
private slots:
	void btnClicked();
};
