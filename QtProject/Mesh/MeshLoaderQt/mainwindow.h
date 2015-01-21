#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QFutureWatcher>
#include <QMainWindow>
#include "myGLWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Vector3d GetCameraPosition();
    void UpdateCamera();
    void UpdateLighting();
    void UpdateLightingValue();

    GLfloat* GetAmbient();
    GLfloat* GetDiffuse();
    GLfloat* GetSpecular();    
    GLfloat* GetIntensity();

private slots:

    void on_searchButton_clicked();
    void on_pushButton_clicked(); 
    void on_checkBox_toggled(bool checked);
    void on_xHorizontalSlider_valueChanged(int value);
    void on_yHorizontalSlider_2_valueChanged(int value);
    void on_zHorizontalSlider_valueChanged(int value);

    void on_AmRHorizontalSlider_valueChanged(int value);

    void on_AmAHorizontalSlider_valueChanged(int value);

    void on_AmGHorizontalSlider_valueChanged(int value);

    void on_AmBHorizontalSlider_valueChanged(int value);

    void on_IntensitylineEdit_textChanged(const QString &arg1);

    void on_SpecRHorizontalSlider_valueChanged(int value);

    void on_SpecGHorizontalSlider_valueChanged(int value);

    void on_DiffRHorizontalSlider_valueChanged(int value);

    void on_DiffGHorizontalSlider_valueChanged(int value);

    void on_DiffBHorizontalSlider_valueChanged(int value);

    void on_DiffAHorizontalSlider_valueChanged(int value);

    void on_SpecAHorizontalSlider_valueChanged(int value);

    void on_SpecBHorizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
 };

#endif // MAINWINDOW_H
