#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->FolderPathLabel->setReadOnly(true);

    /// Preset of Camera Calibration Screen ///
    ui->StopStreamingButton->hide();
    ui->ConfigurationModeButton->hide();
    ui->ConfigurationModeLabel->hide();
    //////////////////////////////////////////

    timer = new QTimer(this);

    connect(ui->TabOfMainProgram, SIGNAL(currentChanged(int)), this, SLOT(tabHasChanged()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


////////////////////////////////////////////////////////////////////////////
///////////////////// MULTI CAMERAS SCREEN ////////////////////////////
////////////////////////////////////////////////////////////////////////////
void MainWindow::timerForTabHasChanged(){
    ui->multiCamerasWidget->setImageToLabel(camerasread, onoff=1);
}

void MainWindow::tabHasChanged(){

    if(ui->TabOfMainProgram->currentIndex()==2){
        timer->start(17);
        cout<<"Starting cameras..."<<endl;
        vector<int> cameras;
        int opened=1, i=0;
        while(opened==1){
            opened=0;
            captureVideo.release();
            captureVideo.open(i);
            if (captureVideo.isOpened() == true){
                opened = 1;
                cameras.push_back(1);
                captureVideo.release();
            }
            i++;
        }
        if (cameras.size()>0){
            for(unsigned int j=0; j<cameras.size(); ++j)
                cout << "Cameras: " << j << " ";
            cout << endl;

            camerasread = cameras.size();

            ui->multiCamerasWidget->addLayout(camerasread);

            connect(timer, SIGNAL(timeout()), this, SLOT(timerForTabHasChanged()));

        }else{
                cout << "No cameras opened" << endl;
            }
        }
    else{
        timer->stop();
        ui->multiCamerasWidget->setImageToLabel(camerasread, onoff=0);
    }
}

////////////////////////////////////////////////////////////////////////////
///////////////////// CAMERA CALIBRATION SCREEN ////////////////////////////
////////////////////////////////////////////////////////////////////////////
void MainWindow::on_CamerasList_itemSelectionChanged(){
    ui->StartStreamingButton->setEnabled(true);
}

void MainWindow::on_ConfigurationModeButton_clicked(){
    if (ui->ConfigurationModeButton->isChecked()){
        ui->ConfigurationModeButton->setText("ON");
        ui->StopStreamingButton->setEnabled(false);
    }
    else{
        ui->ConfigurationModeButton->setText("OFF");
        ui->StopStreamingButton->setEnabled(true);
    }
}

void MainWindow::on_StartStreamingButton_clicked()
{
    int cameraPosition = ui->CamerasList->currentRow();
    ui->cameraImageWidget->startStreaming(cameraPosition);
    ui->StartStreamingButton->hide();
    ui->StopStreamingButton->show();
    ui->CheckCamerasButton->setEnabled(false);
    ui->CamerasList->setEnabled(false);

    ui->ConfigurationModeButton->setEnabled(true);
    ui->ConfigurationModeLabel->setEnabled(true);
    ui->ConfigurationModeButton->show();
    ui->ConfigurationModeLabel->show();
}

void MainWindow::on_StopStreamingButton_clicked()
{
    ui->cameraImageWidget->stopStreaming();
    ui->StopStreamingButton->hide();
    ui->StartStreamingButton->show();
    ui->CheckCamerasButton->setEnabled(true);
    ui->CamerasList->setEnabled(true);

    ui->ConfigurationModeButton->setEnabled(false);
    ui->ConfigurationModeLabel->setEnabled(false);
    ui->ConfigurationModeButton->hide();
    ui->ConfigurationModeLabel->hide();
}

void MainWindow::on_CheckCamerasButton_clicked()
{
    captureVideo.release();
    ui->cameraImageWidget->stopStreaming();
    ui->CamerasList->clear();
    vector<int> cameras;
    int opened=1, i=0;
    while(opened==1){
        opened=0;
        captureVideo.release();
        captureVideo.open(i);
        if (captureVideo.isOpened() == true)
        {
            opened=1;
            cameras.push_back(1);

            QString cameraString = "Camera ";
            QString cameraPosition = QString::number(i+1);
            cameraString.append(cameraPosition);

            ui->CamerasList->addItem(cameraString);
            captureVideo.release();
        }
        i++;
     }
     ui->StartStreamingButton->setEnabled(false);
     update();
}

////////////////////////////////////////////////////////////////////////////
//////////////////////////// LOCAL IMAGE SCREEN ////////////////////////////
////////////////////////////////////////////////////////////////////////////
void MainWindow::on_ChoseFolderButton_clicked()
{
    QString folder = QFileDialog::getExistingDirectory(this,
                                                       tr("Choose Folder"),
                                                       "/home");
    ui->FolderPathLabel->setText(folder);
}

void MainWindow::on_OpenMessageBoxButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Closing..."),
                                  tr("Are you sure?"));

    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        QApplication::quit();
      } else {
        qDebug() << "Yes was *not* clicked";}
}
