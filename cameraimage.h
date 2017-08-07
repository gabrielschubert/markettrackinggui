#ifndef CAMERAIMAGE_H
#define CAMERAIMAGE_H
////// INCLUDING OPENCV ///////
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
///////////////////////////////
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QSize>
#include <QColor>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QFile>


class cameraimage : public QWidget
{
    Q_OBJECT
public:
    explicit cameraimage(QWidget *parent = nullptr);

signals:

private:
    QPoint mPoint;
    QTimer *timer;
    cv::VideoCapture captureVideo;

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void mouseMoveEvent(QMouseEvent * event);
    void startStreaming(int camera);
    void stopStreaming();

};

#endif // CAMERAIMAGE_H
