#ifndef MULTICAMERAS_H
#define MULTICAMERAS_H

////// INCLUDING OPENCV ///////
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
///////////////////////////////

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QDebug>

class multicameras : public QWidget
{
    Q_OBJECT
public:
    explicit multicameras(QWidget *parent = nullptr);

signals:

private:
    QGridLayout *mainLayout;
    QLayoutItem *child;
    QTimer *timer;
    QLabel *cameraLabel[100];
    int i=0;

    // CV VARIABLES //
    QPixmap pixmap;
    cv::VideoCapture captureVideo[100];
    cv::Mat tmpImage[100];
    cv::Mat image[100];

public slots:
    void addLayout(int numberofcameras);
    void setImageToLabel(int numberofcameras, int onoff);

};

#endif // MULTICAMERAS_H
