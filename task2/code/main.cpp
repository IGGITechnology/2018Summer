#include "task2.h"
#include <QtWidgets/QApplication>
#include<qlabel.h>
#include<qpixmap.h>
#include<qtimer.h>
int debug = 0;
bool on_render = 0;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	task2 w;
	w.show();
	return a.exec();
}
void myWidget::on_draw_trigger() {
	
	qDebug() << "1";
	myDialog* dlg = new myDialog;
	dlg->setWindowFlag(Qt::WindowStaysOnTopHint);
	dlg->setWindowTitle(tr("finish?"));

	QPushButton* undo = new QPushButton(tr("undo"));
	connect(undo, &QPushButton::clicked, [this]() {
		if (!allDraw.empty()) {
			allDraw.pop_back();
			update();
		}
	});

	QHBoxLayout* layout = new QHBoxLayout(dlg);
	layout->addWidget(undo);
	layout->addWidget(dlg->ok);
    dlg->show();
	//显示对话框，两个按钮一个是用于表明绘制完毕的OK,myDialog的close()函数用信号槽连接，
	//close()会调用我自己重载的closeevent()函数，关闭窗口，并发出finish信号
	connect(dlg, &myDialog::finished, [this]() {
		//这里让一个函数去关心finished信号，信号发出是，startdrawing函数和stopdrawing函数不在关心鼠标press和release信号
		//也就是说，当点击OK后，用鼠标去点击界面将不会有函数去响应，
		qDebug() << "F";
		disconnect(this, &myWidget::startDrawing, 0, 0);
		disconnect(this, &myWidget::stopDrawing, 0, 0);
		isModified = true;
		//我们的画笔是在QWidget上进行绘制的，当用画笔画完笔迹之后，必需把他同步到QImage中，这样brush才能正常工作
		//这里用到的render函数，是把*this中显示的用img来表达，N次失败后我发现render会调用*this的绘制函数
		//我想这也就是“表达”的含义，是它要把自己当作img展现，就算画在img上也是调用自己的paintEvent
		//所以这么作会先把原来的img个擦除，这也就是我用tmp去临时保存它的内容的原因
		on_render = 1;
		tmp = *img;
		this->render(img);
		on_render = 0;
	});

	connect(this, &myWidget::startDrawing, [this](QPoint start) {
		qDebug() << "p";
		current = QPainterPath(start);
		connect(this, &myWidget::onDrawing, [this](QPoint end) {
			qDebug() << "m";
			current.lineTo(end);
		});
	});
	connect(this, &myWidget::stopDrawing, [this]() {
		qDebug() << "R";
		disconnect(this, &myWidget::onDrawing, 0, 0);
		allDraw.push_back(current);
		update();
	});
}
void myWidget::on_brush_trigger() {
	myDialog* dlg = new myDialog;
	dlg->setWindowFlag(Qt::WindowStaysOnTopHint);
	QTextBrowser* tb = new  QTextBrowser(dlg);
	QHBoxLayout *layout=new QHBoxLayout(dlg);
	layout->addWidget(dlg->ok);
	layout->addWidget(tb);
	dlg->setWindowTitle(tr("finish?"));
	dlg->show();

	connect(dlg, &myDialog::finished, [this]() {
		qDebug() << "F";
		disconnect(this, &myWidget::startDrawing, 0, 0);
	});
	Geometry result;
	connect(this, &myWidget::startDrawing, [this,tb,&result](QPoint start) {
		isModified = true;
		result = seedSearchBrush(start.x(),start.y(),pen.color(),brush.color());
		QString str;
		str.sprintf("height: %f  width: %f  surface: %f", result.h, result.w, result.s);
		tb->setText(str);
		update();
	});
}
Geometry myWidget::seedSearchBrush(int x, int y, QColor boundColor,QColor brushColor) {
	QPoint cur;
	double pixelAmt = 0, maxH = 0, maxW = 0, minH = 10000, minW = 10000;
	int wLimit = this->width(), hLimit = this->height();
	if (img->pixelColor(x, y) != boundColor&&img->pixelColor(x,y)!=brushColor) {
		img->setPixelColor(x, y, brushColor);
		pointsToSearch.push_back(QPoint(x, y));
		pixelAmt++;
	}
	while (!pointsToSearch.empty()) {
		cur = pointsToSearch.front();
		pointsToSearch.pop_front();

		if (cur.x() > maxW) maxW = cur.x();
		if (cur.y() > maxH) maxH = cur.y();
		if (cur.x() < minW) minW = cur.x();
		if (cur.y() < minH) minH = cur.y();
		
		if (cur.x() + 1 <= wLimit && img->pixelColor(cur.x()+1, cur.y()) != brushColor && img->pixelColor(cur.x() + 1, cur.y()) != boundColor) {
			img->setPixelColor(cur.x()+1,cur.y(), brushColor);
			pointsToSearch.push_back(QPoint(cur.x() + 1, cur.y()));
			pixelAmt++;
		}
		if (cur.x() - 1 >= 0 && img->pixelColor(cur.x() - 1, cur.y()) != boundColor && img->pixelColor(cur.x() - 1, cur.y()) != brushColor) {
			img->setPixelColor(cur.x() - 1, cur.y(), brushColor);
			pointsToSearch.push_back(QPoint(cur.x() -1, cur.y()));
			pixelAmt++;
		}
		if (cur.y() + 1 <= hLimit && img->pixelColor(cur.x() , cur.y()+1) != boundColor && img->pixelColor(cur.x(), cur.y() + 1) != brushColor) {
			img->setPixelColor(cur.x(), cur.y()+1, brushColor);
			pointsToSearch.push_back(QPoint(cur.x(), cur.y()+1));
			pixelAmt++;
		}
		if (cur.y() -1 >= 0 && img->pixelColor(cur.x(), cur.y() - 1) != boundColor && img->pixelColor(cur.x(), cur.y() - 1) != brushColor) {
			img->setPixelColor(cur.x(), cur.y() - 1, brushColor);
			pointsToSearch.push_back(QPoint(cur.x(), cur.y() - 1));
			pixelAmt++;
		}
	}
	long dencePerCM = img->dotsPerMeterX() * img->dotsPerMeterY()/10000;
	qDebug() << (maxH - minH) / (img->dotsPerMeterY() / 100) << " " << (maxW - minW) / (img->dotsPerMeterX() / 100) << " " << pixelAmt / dencePerCM;
	return Geometry{ (maxH-minH)/(img->dotsPerMeterY()/100),(maxW-minW)/(img->dotsPerMeterX() / 100),pixelAmt / dencePerCM };
}

int myWidget::saveOrDiscard() {
	QMessageBox msg;
	msg.setText("save the picture?");
	msg.setStandardButtons(QMessageBox::Save
		| QMessageBox::Discard
		| QMessageBox::Cancel);
	msg.setDefaultButton(QMessageBox::Save);
	int selt = msg.exec();
	QString savePath; std::string;
	std::string fileAsSave;
	//QScreen *screen = QGuiApplication::primaryScreen();
	switch (selt) {
	case QMessageBox::Save:
		savePath = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png *.bmp *.jpg)"));
		fileAsSave = savePath.toStdString();
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		cv::imwrite(fileAsSave, mat);
		return QMessageBox::Save;
		break;
	case QMessageBox::Discard:
		return QMessageBox::Discard;
		break;
	case QMessageBox::Cancel:
		return QMessageBox::Cancel;
		break;
	}
}
void myWidget::on_open_trigger() {
	qDebug() << "open";
	int selt;
	if (isModified) {
		selt = saveOrDiscard();
		if (selt == QMessageBox::Cancel) return;
	}
	//出现一个选择打开文件的对画框，父组件是整个程序窗口，名字是打开图片，默认路径为最外层，文件类型过滤为上述文件
	QFileDialog* seltOpenFile = new QFileDialog(this, tr("打开图片"), ".", tr("Image File(*.jpg *.png *.bmp)"));
	label: QString path = seltOpenFile->getOpenFileName();
	mat = cv::imread(path.toStdString());  //初始化图片对象

	if (mat.channels() == 3) cv::cvtColor(mat, mat, CV_BGR2RGB);
	else {
		if(QMessageBox::warning(this, tr("Unsupported Image Type"), tr("try again?"),QMessageBox::Ok|QMessageBox::Cancel)==QMessageBox::Ok)
			goto label;
		else return;
	}

	//将MAT格式转换为QImage格式，并将大小设置为和myWidget大小一样
	*img= (QImage((const unsigned char*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888)).scaled(this->size(), Qt::KeepAspectRatio);  //将图片按比例缩放为视窗大小

	allDraw.clear();
	update();
}
