#include "palette.h"
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>

Palette::Palette()
{
    dxy = 1;
    m_image = Mat();
    p_image = Mat();
    t_image = Mat();
    lineColor = QColor(255,255,255);
    fillColor = QColor(255,255,255);
}

Palette::Palette(const QString &filename)
{
    Palette();
    m_image = cv::imread(filename.toLocal8Bit().data());
    cv::cvtColor(m_image, m_image, CV_BGR2RGB);//BGR转RGB
    p_image = Mat(m_image.rows,m_image.cols, CV_8UC4, cv::Scalar(255,255,255,0));//白色画布
    t_image = m_image.clone();
}

Palette::Palette(const QSize &size)
{
    Palette();
    m_image = Mat(size.height(),size.width(), CV_8UC3, cv::Scalar::all(255));//白色画布
    p_image = Mat(size.height(),size.width(), CV_8UC4, cv::Scalar(255,255,255,0));//白色画布
    t_image = m_image.clone();
}

void mergeImg(cv::Mat &dst, cv::Mat &src)
{
    std::vector<cv::Mat>src_channels;
    std::vector<cv::Mat>dst_channels;
    cv::split(src, src_channels);
    cv::split(dst, dst_channels);

    for (int i = 0; i < 3; i++)
    {
        dst_channels[i] = dst_channels[i].mul(1 - src_channels[3]);
        dst_channels[i] += src_channels[i].mul(src_channels[3]);
    }
    cv::merge(dst_channels, dst);
}

void Palette::resize(int height, int width)
{
    cv::Size cvS;
    cvS.height = height;
    cvS.width = width;
    cv::resize(p_image, t_image, cvS, 0, 0, cv::INTER_LANCZOS4);
    Mat tt_image;
    cv::resize(m_image, tt_image, cvS, 0, 0, cv::INTER_LANCZOS4);
    mergeImg(tt_image, t_image);
    t_image = tt_image;

    float size, o_size;

    if(p_image.cols > p_image.rows) {
        size = p_image.cols;
        o_size = t_image.cols;
    } else {
        size = p_image.rows;
        o_size = t_image.rows;
    }
    dxy = size/o_size;
}

int Palette::height()
{
    return t_image.cols;
}

int Palette::width()
{
    return t_image.rows;
}

int Palette::sHeight()
{
    return m_image.cols;//返回原始高度
}

int Palette::sWidth()
{
    return m_image.rows;//返回原始宽度
}

QImage Palette::image()
{
    return QImage((const unsigned char*)(t_image.data),
                  t_image.cols, t_image.rows, t_image.cols*t_image.channels(),QImage::Format_RGB888);
}

bool Palette::isEmpty()
{
    return t_image.empty();
}

static clock_t last_time;
static clock_t this_time;
static int last_y;
static int last_x;

void Palette::draw(int y, int x)
{
    int t_y = int(round(y*dxy)), t_x = int(round(x*dxy));
    if(t_y < 0 || t_y >= p_image.rows || t_x < 0 || t_x >= p_image.cols) return;
    this_time = clock();
    if(this_time-last_time<1000) {
        cv::line(p_image, cv::Point(last_x, last_y), cv::Point(t_x, t_y), cv::Scalar(lineColor.red(),lineColor.green(),lineColor.blue(),1));
    } else {
        cv::circle(p_image, cv::Point(t_x, t_y), 1, cv::Scalar(lineColor.red(),lineColor.green(),lineColor.blue(),1));
    }
    last_time = this_time;
    last_y = t_y;
    last_x = t_x;
    resize(t_image.rows, t_image.cols);
}

void Palette::erase(int y, int x)
{
    int t_y = int(round(y*dxy)), t_x = int(round(x*dxy));
    if(t_y < 0 || t_y >= p_image.rows || t_x < 0 || t_x >= p_image.cols) return;
    this_time = clock();
    if(this_time-last_time<1000) {
        cv::line(p_image, cv::Point(last_x, last_y), cv::Point(t_x, t_y), cv::Scalar(255,255,255,0));
    } else {
        cv::circle(p_image, cv::Point(t_x, t_y), 1, cv::Scalar(255,255,255,0));
    }
    last_time = this_time;
    last_y = t_y;
    last_x = t_x;
    resize(t_image.rows, t_image.cols);
}

void Palette::fill(int y, int x)
{
    int t_y = int(round(y*dxy)), t_x = int(round(x*dxy));
    if(t_y < 0 || t_y >= p_image.rows || t_x < 0 || t_x >= p_image.cols) return;
    /* opencv自带方案
    cv::Scalar color_1(fillColor.red(), fillColor.green(), fillColor.blue());
    cv::Scalar color_2(1);
    std::vector<cv::Mat> channels;
    cv::split(p_image, channels);
    std::vector<cv::Mat> channels_3 = { channels[0],channels[1],channels[2] };
    Mat tt_image;
    cv::merge(channels_3, tt_image);
    cv::floodFill(tt_image, cv::Point(t_x, t_y), color_1);// 泛洪填充  /漫水填充 / 种子填充
    cv::floodFill(channels[3], cv::Point(t_x, t_y), color_2);
    cv::split(tt_image, channels_3);
    std::vector<cv::Mat> channels_4 = { channels_3[0],channels_3[1],channels_3[2],channels[3] };
    cv::merge(channels_4, p_image);
    */
    seedFill(p_image, cv::Point(t_x, t_y), cv::Vec4b(fillColor.red(), fillColor.green(), fillColor.blue(), 1));
    resize(t_image.rows, t_image.cols);
}

int* Palette::countFill(int y, int x)
{
    int t_y = int(round(y*dxy)), t_x = int(round(x*dxy));
    if(t_y < 0 || t_y >= p_image.rows || t_x < 0 || t_x >= p_image.cols) return 0;
    Mat tt_image = p_image.clone();
    int* c_data = seedFill(tt_image, cv::Point(t_x, t_y), cv::Vec4b(0, 0, 0, 2));
    return c_data;
}

int* Palette::seedFill(cv::Mat &img, cv::Point p, cv::Vec4b f_color)
{
    std::stack<cv::Point> Ps;
    Ps.push(p);
    int width,height,s=0,min_x=p.x,max_x=p.x,min_y=p.y,max_y=p.y;
    cv::Point c,tp;
    cv::Vec4b b_color=img.at<cv::Vec4b>(p), color;
    bool b_alpha=false;
    if(b_color[3]==0) {
        b_color = cv::Vec4b(255,255,255,0);
        b_alpha=true;
    }
    while(!Ps.empty()) {
        cv::Point c = Ps.top();
        Ps.pop();
        if(img.at<cv::Vec4b>(c) != f_color) {
            s+=1;
        } else continue;
        img.at<cv::Vec4b>(c) = f_color;
        min_x = std::min(c.x,min_x);
        max_x = std::max(c.x,max_x);
        min_y = std::min(c.y,min_y);
        max_y = std::max(c.y,max_y);

        tp = cv::Point(c.x, c.y-1);//上移一个像素
        if(tp.x>=0&&tp.y>=0&&tp.x<img.cols&&tp.y<img.rows) {
            color = img.at<cv::Vec4b>(tp);
            if((b_alpha && color[3]==0)||(!b_alpha && b_color==color)) {
                Ps.push(tp);
            }
        }

        tp = cv::Point(c.x+1, c.y);//右移一个像素
        if(tp.x>=0&&tp.y>=0&&tp.x<img.cols&&tp.y<img.rows) {
            color = img.at<cv::Vec4b>(tp);
            if((b_alpha && color[3]==0)||(!b_alpha && b_color==color)) {
                Ps.push(tp);
            }
        }

        tp = cv::Point(c.x, c.y+1);//下移一个像素
        if(tp.x>=0&&tp.y>=0&&tp.x<img.cols&&tp.y<img.rows) {
            color = img.at<cv::Vec4b>(tp);
            if((b_alpha && color[3]==0)||(!b_alpha && b_color==color)) {
                Ps.push(tp);
            }
        }

        tp = cv::Point(c.x-1, c.y);//左移一个像素
        if(tp.x>=0&&tp.y>=0&&tp.x<img.cols&&tp.y<img.rows) {
            color = img.at<cv::Vec4b>(tp);
            if((b_alpha && color[3]==0)||(!b_alpha && b_color==color)) {
                Ps.push(tp);
            }
        }
    }
    width=max_x-min_x+1;
    height=max_y-min_y+1;
    int *ret = new int[3];
    ret[0] = width;// 宽度
    ret[1] = height;// 高度
    ret[2] = s;// 面积
    return ret;
}
