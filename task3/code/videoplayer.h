#pragma once
#include <QtWidgets/QMainWindow>
#include<qaction.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<string>
#include<qthread.h>
#include<qdebug.h>
using namespace std;
using namespace cv;
class workThread :public QThread {
public:
	explicit workThread(QObject *parent = 0)
		: QThread(parent) {}
	~workThread();
};
class VideoPlayer :public QObject{
	Q_OBJECT
private:
	Mat flame;
	VideoCapture pvuVideo;
	
public:
	QString videoName=NULL;
	int on_play_trigger(QString fileName);
	void on_inquiry_trigger(VideoCapture& learnVideo);
};
