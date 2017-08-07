#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////// INCLUDING OPENCV ////////////////
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
////////////////////////////////////////
#include <vector>
#include <string>

#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTimer>
#include <QFile>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_ChoseFolderButton_clicked();
    void on_OpenMessageBoxButton_clicked();

public slots:
    void on_CamerasList_itemSelectionChanged();
    void on_CheckCamerasButton_clicked();
    void on_StartStreamingButton_clicked();
    void on_StopStreamingButton_clicked();
    void on_ConfigurationModeButton_clicked();

    void tabHasChanged();
    void timerForTabHasChanged();


private:
    int camerasread;
    int onoff;
    QTimer *timer;
    cv::VideoCapture captureVideo;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
