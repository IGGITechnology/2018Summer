#include "task3.h"
task3* tmp;
task3::task3(QWidget *parent)
	: QMainWindow(parent)
{
	qRegisterMetaType< Mat >("Mat");   //登记Mat，用于后面队列连接的信号槽中
	tmp = this;
	jg = new judge(&model);
	jg->moveToThread(&thd2);
	vp.moveToThread(&thd);
	menu->addAction(preview);
	menu->addAction(learn);
	connect(preview, &QAction::triggered, [this]() {
		QString filename = fDlg->getOpenFileName();
		if (filename == NULL) return;                  //打开文件需阻塞主线程，之后队列连接交给子线程响应
		emit play(filename);
	});                     
	connect(this, &task3::play, &vp, &VideoPlayer::on_play_trigger);
	connect(learn, &QAction::triggered, this, &task3::on_learning_trigger);
	connect(this, &task3::inquiry, &vp, &VideoPlayer::on_inquiry_trigger, Qt::BlockingQueuedConnection);  
	//用于从子线程中获取learnVido，询问是否已经用预览视频正在播放，若是，则直接从播放的视频开始学习
	connect(this, &task3::updateModelMat, this, &task3::on_updateModel_trigger, Qt::QueuedConnection);  
	//以对列连接，保证model的更新不在imshow函数将新图片呈现给用户之前
	connect(stop, &QPushButton::clicked, [this]() {
		emit stopLearn();
	});
	//同上，保证关闭事件被加入到事件队列最后 ,在之前的事件执行后再执行。
	connect(this, &task3::stopLearn, this, &task3::on_stop, Qt::QueuedConnection);
	//通知位于thd2的judge开始Grab
	connect(this, &task3::startGrab, jg, &judge::on_grab);
	thd.start();
	thd2.start();
	emit startGrab();
}
void task3::on_learning_trigger() {
    tm.stop();
	emit inquiry(learnVido);
	QString filename;
	if (!learnVido.isOpened()) {           //通过learnVido是否为打开状态判断是否从预览中获得了视频，无论如何，原视频都会被关闭
		filename = fDlg->getOpenFileName();
		if (filename == NULL) {
			emit stopLearn();       //若是点击取消，直接关闭学习；
			return;             
		}
		learnVido.open(filename.toStdString());
	}
	learnVido >> curFlame;
	get_edges(curFlame); 
	
	tm.start(10000);
	connect(&tm, &QTimer::timeout, [this]() {
		learnVido.set(CV_CAP_PROP_POS_FRAMES, (int)learnVido.get(CV_CAP_PROP_POS_FRAMES) + 300);//10秒后的帧
		learnVido >> curFlame;
		if (curFlame.empty())
			; //tm.stop()  这条语句永远报错。。。
		else 
			get_edges(curFlame);
	});
	stop -> show();                                                              
}
void task3::get_edges(Mat source) {
	
	cvtColor(source, source, cv::COLOR_BGR2HSV);
	//GaussianBlur(source, source,Size(5,5),0,0);
	Mat mask,tmp, resultMat = Mat(source.rows, source.cols, CV_8UC1, Scalar(255));
	inRange(source, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
	mask.copyTo(tmp);     //findcontours会破坏mask
	vector<vector<Point>> contours;
	vector<Vec4i> topo;
	findContours(tmp, contours, topo,CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	/*int i =  topo[0][2];
	while (i != -1) {
		drawContours(resultMat, contours, i, 0, 2);
		i = topo[i][0];
	}*/
	for (int i = 0; i < contours.size(); i++) {
		if(contours[i].size()>30)drawContours(resultMat, contours, i, 0, 2);
	}
	cv::imshow("result",resultMat);  // 保证所要模仿的图片的更新必然是在imshow事件被处理后随即执行
	emit updateModelMat(mask);  //防止代码中已经将模范图片更新，而用户端却因为imshow事件的滞后执行而无法看到新的模范图片
}
void task3::on_updateModel_trigger(Mat matJustBeShowed) {
	qDebug() << "upmodl";
	model = matJustBeShowed;
}
void task3::on_stop() {
	tm.stop();
	model.release();
	destroyWindow("result");
	destroyWindow("imitation");
	stop->close();
}