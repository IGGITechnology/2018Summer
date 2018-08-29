#include"videoplayer.h"
int g_interrupt = 0;
workThread::~workThread() {
	g_interrupt = 1;
	quit();
	wait();
}
int VideoPlayer::on_play_trigger(QString fileName) {
	Mat tmp;
	qDebug() << "p";
	if (pvuVideo.isOpened()) pvuVideo.release();
	namedWindow("wd");
	pvuVideo.open(fileName.   toStdString());
	if (!pvuVideo.isOpened())
		abort();
	videoName = fileName;
	while (!g_interrupt) {
		pvuVideo >> flame;
		if (flame.empty()) break;
		imshow("wd", flame);
		if (waitKey(33) >=0) break;
	}
	qDebug() << "sp";
	destroyWindow("wd");
	if (pvuVideo.isOpened())  pvuVideo.release();
	return 27;
}
void VideoPlayer::on_inquiry_trigger(VideoCapture& learnVido) {
	qDebug() << "inq";
	if (pvuVideo.isOpened()) {
		//learnVido = pvuVideo;
		learnVido.open(videoName.toStdString());
		learnVido.set(CV_CAP_PROP_POS_FRAMES,pvuVideo.get(CV_CAP_PROP_POS_FRAMES));
	}
	else if (learnVido.isOpened()) learnVido.release();
}