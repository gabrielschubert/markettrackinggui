#include "multicameras.h"
#include <iostream>

using namespace std;

multicameras::multicameras(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout;
    setLayout(mainLayout);

}

void multicameras::addLayout(int numberofcameras){

    while ((child = mainLayout->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
    delete mainLayout;

    mainLayout = new QGridLayout;

    for(int i=0;i<numberofcameras;i++){
        cameraLabel[i] = new QLabel("");
        if(i%2==0 || i==0)
            mainLayout->addWidget(cameraLabel[i], i, 0);
        else
            mainLayout->addWidget(cameraLabel[i], i-1, 1);

    }
    setLayout(mainLayout);
}


void multicameras::setImageToLabel(int numberofcameras, int onoff){

    if (onoff==1){
        for(i=0;i<numberofcameras;i++){
            if (captureVideo[i].isOpened() == false)
                captureVideo[i].open(i);

            captureVideo[i].read(tmpImage[i]);

            if (tmpImage[i].empty() == true){
                //qDebug() << "EMPTY!";
                return;
            }

            cv::cvtColor(tmpImage[i], image[i], CV_BGR2RGB);
            QImage img((const unsigned char*)(image[i].data), image[i].cols, image[i].rows, QImage::Format_RGB888);

            pixmap = QPixmap::fromImage(img);

            cameraLabel[i]->setPixmap(pixmap.scaled(cameraLabel[i]->size(), Qt::KeepAspectRatio));
            cameraLabel[i]->setAlignment(Qt::AlignCenter);
            //cameraLabel[i]->setScaledContents(true);
            cameraLabel[i]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        }
    }
    else{
        for(int i=0;i<numberofcameras;i++){
            captureVideo[i].release();
        }
    }
}
