#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(true);
    ui->CamgroupBox->setEnabled(false);
    ui->GeodesicSpectrumradioButton->setChecked(true);
    ui->IntensitylineEdit->setEnabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",tr("VRML File (*.wrl)"));
    ui->filePathEditor->setText(fileName);

}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->filePathEditor->toPlainText();
    if( !str.isEmpty() )
    {
        ui->progressEditor->append("Generating mesh . . . . ");
        int eigenVal = ui->eigenSpinBox->value();

        bool isDefaultPos = ui->checkBox->checkState();
        Vector3d camPos = GetCameraPosition();

        UpdateLighting();


        if( ui->GeodesicSpectrumradioButton->isChecked() )
        {
            ui->RenderingView->renderMesh( str.toStdString(), GEODESIC, eigenVal,isDefaultPos, camPos ) ;
         }
        else if( ui->UniformradioButton->isChecked() )
        {
             ui->RenderingView->renderMesh( str.toStdString(), UNIFORMWEIGHT, eigenVal,isDefaultPos, camPos);
        }
        else if( ui->CotangentradioButton->isChecked() )
        {
             ui->RenderingView->renderMesh( str.toStdString(), COTANGENTWEIGHT, eigenVal,isDefaultPos, camPos);
        }
        else if( ui->MeanradioButton->isChecked() )
        {
             ui->RenderingView->renderMesh( str.toStdString(), MEANVALUE, eigenVal, isDefaultPos, camPos );
        }
        ui->progressEditor->append(QString::fromStdString (ui->RenderingView->message ));
        ui->progressEditor->append("Finish generating mesh . . . . ");
    }

    Vector3d cam_pos = ui->RenderingView->sceneGL.GetPosition();
    ui->xHorizontalSlider->setValue(cam_pos[0]);
    ui->yHorizontalSlider_2->setValue(cam_pos[1]);
    ui->zHorizontalSlider->setValue(cam_pos[2]);

    UpdateLightingValue();
    ui->eigenSpinBox->setMaximum(ui->RenderingView->vertexNumber);

}
void MainWindow::UpdateLightingValue()
{
    GLfloat* am = ui->RenderingView->sceneGL.GetAmbient();

    ui->AmRHorizontalSlider->setValue( am[0]*100 );
    ui->AmGHorizontalSlider->setValue( am[1]*100);
    ui->AmBHorizontalSlider->setValue( am[2]*100);
    ui->AmAHorizontalSlider->setValue( am[3]*100);

    GLfloat* df= ui->RenderingView->sceneGL.GetDiffuse();
    ui->DiffRHorizontalSlider->setValue( df[0]*100 );
    ui->DiffGHorizontalSlider->setValue( df[1]*100 );
    ui->DiffBHorizontalSlider->setValue( df[2]*100 );
    ui->DiffAHorizontalSlider->setValue( df[3]*100 );

    GLfloat* sp = ui->RenderingView->sceneGL.GetSpecular();
    ui->SpecRHorizontalSlider->setValue( sp[0]*100);
    ui->SpecGHorizontalSlider->setValue( sp[1]*100);
    ui->SpecBHorizontalSlider->setValue( sp[2]*100);
    ui->SpecAHorizontalSlider->setValue( sp[3]*100);

    GLfloat* in = ui->RenderingView->sceneGL.GetIntensity();
    //convert float to QString
    QString s = QString::number( in[0] );
    ui->IntensitylineEdit->setText( s );

}

Vector3d MainWindow::GetCameraPosition()
{
    Vector3d camPos;
    camPos[0] = ui->xHorizontalSlider->value();
    camPos[1] = ui->yHorizontalSlider_2->value();
    camPos[2] = ui->zHorizontalSlider->value();
    return camPos;
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked )
    {
        ui->CamgroupBox->setEnabled(false);
        ui->DiffgroupBox->setEnabled(false);
        ui->SpecgroupBox->setEnabled(false);
        ui->AmgroupBox->setEnabled(false);
        ui->IntensitylineEdit->setEnabled(false);
    }
    else
    {
        ui->CamgroupBox->setEnabled(true);
        ui->DiffgroupBox->setEnabled(true);
        ui->SpecgroupBox->setEnabled(true);
        ui->AmgroupBox->setEnabled(true);
         ui->IntensitylineEdit->setEnabled(true);
    }
}

void MainWindow::on_xHorizontalSlider_valueChanged(int value)
{
   UpdateCamera();
}

void MainWindow::on_yHorizontalSlider_2_valueChanged(int value)
{
    UpdateCamera();
}

void MainWindow::on_zHorizontalSlider_valueChanged(int value)
{
    UpdateCamera();
}

void MainWindow::UpdateCamera()
{
    bool isDefaultPos = ui->checkBox->checkState();
    Vector3d camPos = GetCameraPosition();
    ui->RenderingView->UpdateCamera( isDefaultPos, camPos );
}

void MainWindow::UpdateLighting()
{
    bool isDefaultPos = ui->checkBox->checkState();
    GLfloat i =  (ui->IntensitylineEdit->text()).toFloat();
    GLfloat am[4] = { ui->AmRHorizontalSlider->value()/ 100.0,
                      ui->AmGHorizontalSlider->value()/ 100.0,
                      ui->AmBHorizontalSlider->value()/ 100.0,
                      ui->AmAHorizontalSlider->value()/ 100.0 };
    GLfloat diff[4] = {ui->DiffRHorizontalSlider->value()/ 100.0,
                       ui->DiffGHorizontalSlider->value()/ 100.0,
                       ui->DiffBHorizontalSlider->value()/ 100.0,
                       ui->DiffAHorizontalSlider->value()/ 100.0 };
    GLfloat spec[4] = { ui->SpecRHorizontalSlider->value()/ 100.0,
                       ui->SpecGHorizontalSlider->value()/ 100.0,
                       ui->SpecBHorizontalSlider->value()/ 100.0,
                       ui->SpecAHorizontalSlider->value()/ 100.0 };

    ui->RenderingView->sceneGL.UpdateLighting( isDefaultPos, am, spec,diff, i );
}


GLfloat* MainWindow::GetAmbient()
{
    float r = ui->AmRHorizontalSlider->value()/ 100;
    float g = ui->AmGHorizontalSlider->value()/ 100;
    float b = ui->AmBHorizontalSlider->value()/ 100;
    float a = ui->AmAHorizontalSlider->value()/ 100;

    GLfloat am[] = {r,g,b,a};
    return am;
}

GLfloat* MainWindow::GetDiffuse()
{
    float r = ui->DiffRHorizontalSlider->value()/ 100;
    float g = ui->DiffGHorizontalSlider->value()/ 100;
    float b = ui->DiffBHorizontalSlider->value()/ 100;
    float a = ui->DiffAHorizontalSlider->value()/ 100;

    GLfloat df[] = {r,g,b,a};
    return df;
}

GLfloat* MainWindow::GetSpecular()
{
    float r = ui->SpecRHorizontalSlider->value()/ 100;
    float g = ui->SpecGHorizontalSlider->value()/ 100;
    float b = ui->SpecBHorizontalSlider->value()/ 100;
    float a = ui->SpecAHorizontalSlider->value()/ 100;

    GLfloat spec[] = {r,g,b,a};
    return spec;
}
GLfloat* MainWindow::GetIntensity()
{
    GLfloat i =  (ui->IntensitylineEdit->text()).toFloat();

    GLfloat it[] = {i};

    return it;
}
void MainWindow::on_AmRHorizontalSlider_valueChanged(int value)
{
    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}

void MainWindow::on_AmAHorizontalSlider_valueChanged(int value)
{
    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}

void MainWindow::on_AmGHorizontalSlider_valueChanged(int value)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}

void MainWindow::on_AmBHorizontalSlider_valueChanged(int value)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}
void MainWindow::on_IntensitylineEdit_textChanged(const QString &arg1)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}

void MainWindow::on_SpecRHorizontalSlider_valueChanged(int value)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}

void MainWindow::on_SpecGHorizontalSlider_valueChanged(int value)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}
void MainWindow::on_SpecAHorizontalSlider_valueChanged(int value)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}
void MainWindow::on_SpecBHorizontalSlider_valueChanged(int value)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}
void MainWindow::on_DiffRHorizontalSlider_valueChanged(int value)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}

void MainWindow::on_DiffGHorizontalSlider_valueChanged(int value)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}

void MainWindow::on_DiffBHorizontalSlider_valueChanged(int value)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}

void MainWindow::on_DiffAHorizontalSlider_valueChanged(int value)
{

    UpdateLighting(); //update lighting in SceneGL
    ui->RenderingView->UpdateLighting();
}



