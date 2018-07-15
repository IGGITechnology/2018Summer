#include "qtUpload.h"
#include <Windows.h>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
using namespace cv;

qtUpload::qtUpload(QWidget *parent)
	: QMainWindow(parent)
{
	
	ui.setupUi(this);
}

void qtUpload::btnClicked()
{
	QString path =QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image File(*.png *.jpg *.jpeg *.bmp)"));

	Mat img = imread(path.toStdString());
	cv::resize(img, img, Size(img.cols / 3, img.rows / 3), 0, 0, INTER_LINEAR);
	content = content+path + "   opened\n";
	ui.textBrowser->setText( content);
	imshow("¡¾ÔØÈëµÄÍ¼Æ¬¡¿",img);
}
