#ifndef SCENEGL_H
#define SCENEGL_H

#include "NeighborMesh.h"
#include <GL/glu.h>

using namespace Eigen;

class SceneGL
{
public:
    SceneGL();

    Vector3d GetTarget();
    Vector3d GetPosition();
    double GetDistance();

    //camera
    double SetCameraDefaultPosition(const NeighborMesh& mesh);
    double GetZnear ();
    double GetZfar ();

    //lighting variables
    void SetLightingDefaultPosition();
    GLfloat* GetAmbient();
    GLfloat* GetDiffuse();
    GLfloat* GetSpecular();
    GLfloat* GetIntensity();

    //update camera ang lighting
    void UpdateCamera	( 	const NeighborMesh& mesh, bool isDefault, 
							Vector3d userPosition );
    void UpdateLighting	( 	bool isDefault, GLfloat a[4], 
							GLfloat s[4], GLfloat d[4], GLfloat i);


private:
    //camera variables
    Vector3d position;
    Vector3d target;
    double znear;
    double zfar;
    double distance;

    //lighting variables
    GLfloat specular[4]={1.0, 1.0, 1.0, 1.0};
    //intensity of the shining...
    GLfloat intensity[1]={100};
    //ambient and diffuse light
    GLfloat ambient[4]={0.1, 0.1, 0.1, 1.0};
    GLfloat diffuse[4]={0.4, 0.4, 0.4, 1.0};


};


#endif // SCENEGL_H
