#include "SceneGL.h"
#include <iostream>
SceneGL::SceneGL()
{
}


double SceneGL::SetCameraDefaultPosition(const NeighborMesh& mesh)
{
    //roughly adjust view frustrum to object and camera position
    Vector3d Pmin(mesh.vertices[0]), Pmax(mesh.vertices[0]);
    Vector3d Center(0,0,0);

    for( int i=0; i< mesh.vertices.size(); i++)
    {
        Vector3d P(mesh.vertices[i]);
        for( int j=0; j<2; j++)
        {
            Pmin[j] = min(Pmin[j],P[j]);
            Pmax[j] = max(Pmax[j],P[j]);
        }
        Center += P;
    }

    Center/= mesh.vertices.size();
    target = Center;

    //length of the diagonal of the bouding box
    double distance = (Pmax-Pmin).norm();

    //set arbitraty position to camera and adjusts max and min view planes
    position = target + Vector3d( 0,0, distance*3);
    znear = distance*0.1;
    zfar = distance*5;

    return distance;
}

Vector3d SceneGL::GetTarget()
{
    return target;
}

Vector3d SceneGL::GetPosition()
{
    return position;
}
double SceneGL::GetDistance()
{ return distance; }

double SceneGL::GetZnear ()
{
    return znear;
}
double SceneGL::GetZfar ()
{
    return zfar;
}


GLfloat* SceneGL:: GetAmbient()
{
    return ambient;
}
GLfloat* SceneGL:: GetDiffuse()
{
    return diffuse;
}
GLfloat* SceneGL:: GetSpecular()
{
    return specular;
}
GLfloat* SceneGL:: GetIntensity()
{
    return intensity;
}

void SceneGL::UpdateCamera( const NeighborMesh& mesh,
							bool isDefault, Vector3d userPosition )
{
    Vector3d Center(0,0,0);

    if( isDefault )
        distance =  SetCameraDefaultPosition( mesh );
    else
    {

        for( int i=0; i< mesh.vertices.size(); i++)
        {
            Vector3d P(mesh.vertices[i]);
            Center += P;
        }

        Center /= mesh.vertices.size();
        position = userPosition;
        distance = (Center - position).norm();

        znear = distance*0.1;
        zfar = distance*3;
    }

}

void SceneGL::UpdateLighting( bool isDefault, GLfloat a[4], 
							GLfloat s[4], GLfloat d[4], GLfloat i)

{
    if( isDefault )
        SetLightingDefaultPosition();
    else
    {
        for(int i=0; i<4;i++)
        {
            diffuse[i]= d[i];
            specular[i]= s[i];
            ambient[i]= a[i];
        }
        intensity[0] = i;
    }
  }

void SceneGL::SetLightingDefaultPosition()
{
    color of reflected light
    GLfloat s[4]={1.0, 1.0, 1.0, 1.0};
    //intensity of the shining
    GLfloat i[1]={100};
    //ambient and diffuse light
    GLfloat a[4]={0.1, 0.1, 0.1, 1.0};
    GLfloat d[4]={0.4, 0.4, 0.4, 1.0};

  diffuse[0]= *(d+0);diffuse[1]= *(d+1);diffuse[2]= *(d+2);diffuse[3]= *(d+3);
  specular[0]= *(s+0);specular[1]= *(s+1);specular[2]= *(s+2);specular[3]= *(s+3);
  ambient[0]= *(a+0);ambient[1]= *(a+1);ambient[2]= *(a+2);ambient[3]= *(a+3);
  intensity[0] = *(i+0);

}
