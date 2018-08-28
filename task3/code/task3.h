#pragma once
#include <QtWidgets/QMainWindow>
#include<qaction.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<qmenubar.h>
#include<qfiledialog.h>
#include<string>
#include<qstring.h>
#include<qthread.h>
#include<qtimer.h>
#include<vector>
#include<qpushbutton.h>
#include"videoplayer.h"
#include"judge.h"
#include<QMetaType>
#define H_MAX 43
#define H_MIN 9
using namespace std;
using namespace cv;
class judge;
class task3 : public QMainWindow
{
	Q_OBJECT
public:
	task3(QWidget *parent = Q_NULLPTR);
	void on_learning_trigger();
	void on_updateModel_trigger(Mat MatJustBeShowed);
	void get_edges(Mat source);
	void on_stop();
    signals:
		void play(QString videoName);
		void inquiry(VideoCapture& learnVido);
		void updateModelMat(Mat MatJustBeShowed);
		void stopLearn();
		void startGrab();
private:
	QMenuBar* menu=new QMenuBar(this);
	QAction* preview = new QAction(tr("&preview"), this);
	QAction* learn = new QAction(tr("&learn"));
	QFileDialog* fDlg = new QFileDialog(this);
	VideoPlayer vp;          //用于预览视频，在线程thd中运行
	judge* jg;                //用于从相机获取视频，并判断是否符合轮廓，在th2中运行
	VideoCapture learnVido;
	workThread thd;
	workThread thd2;
	Mat curFlame;      
	Mat model;             //用于保存当前用户看到的轮廓的mask图
	QTimer tm;
	QPushButton* stop = new QPushButton("STOP");
};
