#pragma once
#include"task3.h"
#include<qlabel>
#include<deque>
class mylabel : public QLabel {
public:
	void show() {
		qDebug() << "show cmr";
		QLabel::show();
		QTimer::singleShot(2000,this,&QLabel::close);
	}
};
class judge :public QObject {
	Q_OBJECT
private:
	VideoCapture camera;
	Mat* imitate;
	Mat* model;
	Mat tmp;
	mylabel info;
public:
	judge(Mat* model){
		this->model = model;
		imitate = new Mat;
		camera.open(0);
		info.setText("goodjob");
		connect(this, &judge::show, &info,&mylabel::show);
	}
	void on_grab();
	bool isCorrespond(Mat camera, Mat model);
signals:
	void show();
};