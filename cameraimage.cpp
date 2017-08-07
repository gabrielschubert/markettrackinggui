#include "cameraimage.h"
#include <iostream>

using namespace std;

cameraimage::cameraimage(QWidget *parent) : QWidget(parent)

{

    setMouseTracking(true);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void cameraimage::startStreaming(int cameraPosition)
{
    qDebug() << "Starting Streaming on camera " << cameraPosition;
    captureVideo.open(cameraPosition);
    if (captureVideo.isOpened() == false){
        qDebug() << "Camera can't open";
        return;
    }
    timer->start(17);
}

void cameraimage::stopStreaming()
{
    captureVideo.release();
    timer->stop();
    update();
}


void cameraimage::mouseMoveEvent(QMouseEvent *event)
{
    mPoint = event->pos();
    //qDebug()<<mPoint.x()<<endl;
    update();
}

//void cameraimage::mousePressEvent(QMouseEvent *event){
//    vector<QPoint> points;
//}

void cameraimage::paintEvent(QPaintEvent *){
        cv::Mat tmpImage;
        cv::Mat image;
        captureVideo.read(tmpImage);

        if (tmpImage.empty() == true){
            //qDebug() << "EMPTY!";
            return;
        }

        //cout << "Mat width: " << tmpImage.cols << endl;
        //cout << "Mat height: " << tmpImage.rows << endl;

        cv::cvtColor(tmpImage, image, CV_BGR2RGB);
        QImage img((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);

        QPixmap pixmap = QPixmap::fromImage(img);
        QPainter painter(this);

        float comprimento = 1.0*width()/pixmap.width();
        float altura = 1.0*height()/pixmap.height();
        float ratio = 0.;

        if (comprimento<=altura)
            ratio = comprimento;
        else
            ratio = altura;

        QSize size = ratio*pixmap.size();
        size.setHeight(size.height()-10);

        QPoint p;
        p.setX(0 + (width()-size.width())/2);
        p.setY(5);

        painter.drawPixmap(QRect(p, size), pixmap.scaled(size, Qt::KeepAspectRatio));
        painter.setPen(QPen(Qt::red, 5, Qt::SolidLine));

        if(!mPoint.isNull()){
            if(mPoint.x() >= p.x() && mPoint.x() <= (p.x()+size.width())
                    && mPoint.y() >= p.y() && mPoint.y() <= p.y()+size.height()){
                //qDebug() << mPoint;
                painter.drawText(mPoint.x()+15, mPoint.y(), "Click to define");
                painter.drawEllipse(mPoint, 5 , 5);
             }
        }
}
