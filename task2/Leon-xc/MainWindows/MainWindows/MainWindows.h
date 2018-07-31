#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindows.h"
#include"PaintArea.h"
#include "QScrollArea"
#include "QFileDialog"
#include "QPainter"
#include "QString"
#include "QMessageBox"
#include "QDebug"

class MainWindows : public QMainWindow
{
	Q_OBJECT

public:
	MainWindows(QWidget *parent = Q_NULLPTR);
	void doOpen();
	bool doFileSave();
	bool doFileSaveas();
	bool SaveFile(QString filename);

	//信号和槽的连接
	private slots:

	void OnTriggerOpen();
	void OnTriggerSave();
	void OnTriggerZoomIn();
	void OnTriggerZoomOut();
	void OnTriggerReturn();
	void OnTriggerRotate();
	void OnTriggerShear();
	void OnTriggerClear();
	void OnTriggerEraser();
	void OnTriggerPen();
	void OnTriggerRect();
	void OnTriggerEllipse();
	void on_comboBoxLine_currentIndexChanged(int index);
	void on_comboBoxColor_currentIndexChanged(int index);
	void on_horizontalSlider_valueChanged(int value);
	void on_actionPainter_2_0_triggered(bool);
	void on_actionProgrammer_triggered(bool);
	void on_actfill4_triggered();
	void on_actFillScan_triggered();
	void on_pushButton_data_clicked();

private:
	Ui::MainWindowsClass ui;
	PaintArea *area;
	QScrollArea *scrollarea;
	QString curFile;
	bool isSaved;
};
