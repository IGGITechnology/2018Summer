#ifndef PALETTE_H
#define PALETTE_H

#include <opencv2/opencv.hpp>
#include <QImage>
#include <QColor>

using cv::Mat;

class Palette
{
public:
    Palette();
    Palette(const QString &filename);
    Palette(const QSize &size);
    void resize(int height, int width);
    int height();
    int width();
    int sHeight();
    int sWidth();
    QImage image();
    bool isEmpty();
    void draw(int y, int x);
    void erase(int y, int x);
    void fill(int y, int x);
    int *countFill(int y, int x);
    QColor lineColor;
    QColor fillColor;
private:
    Mat m_image;
    Mat p_image;
    Mat t_image;
    float dxy;
    int *seedFill(Mat &img, cv::Point p, cv::Vec4b f_color);
};

#endif // PALETTE_H
