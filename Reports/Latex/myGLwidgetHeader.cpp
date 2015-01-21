#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <GL/glu.h>
#include <string>
#include "NeighborMesh.h"
#include "Stopwatch.h"
#include "Constante.h"
#include "scenegl.h"
#include <iostream>

class myGLWidget : public QGLWidget
{
     Q_OBJECT

public:

    //explicit constructor
    myGLWidget(QWidget *parent = 0);

    // message string to show the computation time in the widget
    string message;

    //to store the camera position and lighting
    SceneGL sceneGL;

    //initialization
    void initializeGL();

    // functions for Mesh rendering
    void InitGLForRender();
    void renderMesh( string filename, int option, 
	                 int eigenCol, 
					 double isDefaultPos, Vector3d camPos  );
    void settingUpMeshBasic( double isDefaultPos, Vector3d camPos  );
    void renderToLaplaceRepresentation( int weightOption, int eigenCol );
    void renderToGeodesicRepresentation();

    //function called when the widget is resized
    void resizeGL (int width, int height );

    //function called when the widget should be drawn or updated
    void paintGL();

    //update camera position
    void UpdateCamera( bool isDefaultPos, Vector3d camPos );
    //update lighting
    void UpdateLighting();

    //function handler for user interaction
    void keyPressEvent( QKeyEvent *keyEvent );
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * mouse);
    void mouseReleaseEvent(QMouseEvent* mouse);
    void Mouse (QMouseEvent* event);
    void Motion( int x ,int y);
    void MouseRelease(QMouseEvent* event);

public slots:
    void timeOutSlot();

private:
    //timer for frame rate
    QTimer *t_Timer;

    //frames per second
    float framesPerSecond;

    //frame counter
    int n;

    // 3D variables initiation
    int window_width = 640;
    int window_height = 200;
    int window_number = 0;
    double view_angle = 45;
    Vector3d translations = Vector3d(0,0,0);
    Vector3d rotations = Vector3d(0,0,0);
    Vector2i previous_mouse_position = Vector2i(0,0);
    Vector3d previous_trackball_position = Vector3d(0,0,0);
    Vector3d rotation_axis = Vector3d(0,0,0);
    double rotation_angle = 0;
    float trackball_transform[4][4] = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};

    //timer to calculate computation time
    Stopwatch timer;

    //mesh to be drawn
    NeighborMesh globalmesh;
    int id_globalmesh;

    //Mouse handling variables
      //Trackball mapping
    static Vector3d TrackballMapping( int x, int y );
    //Variable to control old values of x and y of the mouse
    int oldx,oldy;
    float Current_Matrix[4][4];

    //Controls the light
    int lights_on;
    //function to create lighting and update the camera position
    void createLighting();

    //Object movement variables
    //Object move speed;
    Vector3d objectMove;
    // for rotation and translation
    int rotate,translate;
    int Axis;
    int Axis_Id_List; 

    // for the color bar
    vector<Vector3d> Color_Steps;
    //Function to draw color bar on the side
    void Draw_Color_Bar(int size_x, int size_y,int x_init,int y_init);

    //function to cast double to string
    //usefull when computation time need to be shown n Qstring
    string DoubleToString ( double d );

};


#endif // MYGLWIDGET_H


