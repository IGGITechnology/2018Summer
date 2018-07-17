#include "First.h"
#include"ui_First.h"
#include<string>
First::First(QWidget *parent)
	: QMainWindow(parent) 

{
	ui.setupUi(this);
	connect(ui.pushButton,SIGNAL(clicked()) ,this, SLOT(on_OpenImage_trigger()));
	//connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(quit()));
	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(ui.pushButton);
	mainLayout->addWidget(ui.graphicsView);
	mainLayout->addWidget(ui.textBrowser);
	//mainLayout->addWidget(ui.pushButton_2);
	ui.centralWidget->setLayout(mainLayout);
    QAction* openAction = new QAction(tr("&open"), this);
	QAction* newAction = new QAction(tr("&new"), this);
	QAction* saveAction = new QAction(tr("&save"), this);
	ui.menuBar->addAction(openAction);
	ui.menuBar->addSeparator();
	ui.menuBar->addAction(newAction);
	ui.menuBar->addSeparator();
	ui.menuBar->addAction(saveAction);
	ui.menuBar->addSeparator();
	
}
void First::on_OpenImage_trigger() {
	//我的窗口中，当打开新图片的时候，旧图片就消失了，假设我的窗口有编辑功能，如果用户就这样失去了改动，会很头疼
	int selt;
	if (ui.graphicsView->scene()!=0) {
		selt=saveOrDiscard();
		sence->clear();
	}
	if (selt == QMessageBox::Cancel) {
		ui.textBrowser->setText("operation cancel");   //取消打开图片
		return;
	} 
	if (selt == QMessageBox::Discard) {
		sence->clear();  
	}
	QFileDialog* seltOpenFile = new QFileDialog(this, tr("打开图片"), ".", tr("Image File(*.jpg *.png *.bmp)"));
	//出现一个选择打开文件的对画框，父组件是整个程序窗口，名字是打开图片，默认路径为最外层，文件类型过滤为上述文件
	QString path = seltOpenFile->getOpenFileName();

	//下面4行是看yangcrazy30的代码，还没来得及去看opencv，只是看代码从表面上了解这是在干什么，回头再去学

	img = cv::imread(path.toStdString());  //初始化图片对象
	cv::cvtColor(img, img, CV_BGR2RGB);//将BGR顺序的opencv图片转为RGB的顺序，参数为输入图片，输出图片，格式，PS:也就是将img转换后的返回值回头附给QImg
	QImage QImg = QImage((const unsigned char*)(img.data), img.cols, img.rows, QImage::Format_RGB888);//将MAT格式转换为QImage格式，
	QImage scaledImg = QImg.scaled(ui.graphicsView->size(), Qt::KeepAspectRatio);   //将图片按比例缩放为视窗大小

    sence = new QGraphicsScene;        //创建场景并将图片加入场景
	sence->addPixmap(QPixmap::fromImage(scaledImg));
	ui.graphicsView->setScene(sence);//graphicsView绑定场景
	ui.graphicsView->show();
	ui.textBrowser->setText("open" + path);
}

int First::saveOrDiscard(){
	QMessageBox msg;
	msg.setText("save the picture?");
	msg.setStandardButtons(QMessageBox::Save
		| QMessageBox::Discard
		| QMessageBox::Cancel);
	msg.setDefaultButton(QMessageBox::Save);
	int selt = msg.exec();
	QString savePath; std::string ;
	std::string fileAsSave;
	//QScreen *screen = QGuiApplication::primaryScreen();
	switch (selt) {
	case QMessageBox::Save:
		savePath = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png *.bmp *.jpg)"));
		fileAsSave = savePath.toStdString();
		cv::imwrite(fileAsSave, img);
		ui.textBrowser->setText(savePath + "saved");
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
