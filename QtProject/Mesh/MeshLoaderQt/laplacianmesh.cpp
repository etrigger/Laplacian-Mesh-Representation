/***************************************************************************
                                  laplacianmesh.cpp
                             -------------------
    update               : 2014 - 01 - 12
    copyright            : (C) 2014 by Pramita Winata
    email                : pramita.winata@gmail.com
 *                                                                         *
 *   Description :
 *   This class is used to compute the Laplace spectral representation of a mesh
 *   There are three methods supported :
 *   1. Uniform weight
 *   2. Cotangent weight
 *   3. Mean value coordinate
 *   Eigen decomposition and color map will be generated to illustrate the result.                                                                       *
 ***************************************************************************/

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <GL/glut.h>
#include "laplacianmesh.h"
#include "Neighbormesh.h"
#include "Useful.h"


using namespace std;
LaplacianMesh::LaplacianMesh(NeighborMesh m)
{
    //initiate values
    mesh = m;
    vertices = mesh.Vertices(); // vertices vector
    faces = mesh.Faces(); //Faces vector
    vertexNumber = mesh.VertexNumber();
}
LaplacianMesh::~LaplacianMesh()
{

}

void LaplacianMesh::GetLaplacianUniformWeight()
{
    laplaceMatrix.resize(vertexNumber, vertexNumber);
        //set everything to zero first
    laplaceMatrix.setZero(vertexNumber, vertexNumber);

    for ( int i = 0; i <vertexNumber; i ++ )
    {
       laplaceMatrix(i,i) = mesh.P2P_Neigh[i].size();//neighbour size here

       for ( set <int> :: iterator it = mesh.P2P_Neigh[i].begin();
             it != mesh.P2P_Neigh[i].end() ; ++it)
       {
           laplaceMatrix(i,*it) = -1;
           laplaceMatrix(*it, i) = -1;
       }
     }

    QString path1 = "E:/LaplaceTxt/laplacianuniform.txt";
    SaveMatrixXd( laplaceMatrix, path1 );
    cout<<"Laplacian matrix can be found in "<<path1.toStdString()<<endl;
}

void LaplacianMesh::GetLaplacianCotangentWeight()
{
    double cotangent_weight = 0;
    Vector3d vi, vj;

    laplaceMatrix.resize(vertexNumber, vertexNumber);

    //set everything to zero first
    laplaceMatrix.setZero(vertexNumber, vertexNumber);

    for ( int i = 0; i <vertexNumber; i ++ )
    {
        laplaceMatrix(i,i) = 1;
        vi = vertices[i];
       //Get neighbourhood points
       for ( set <int> :: iterator it =  mesh.P2P_Neigh[i].begin(); it !=  mesh.P2P_Neigh[i].end(); ++it)
       {
            vj = vertices[*it]; //point to point
            cotangent_weight = CalculateCotangentWeight( i, *it );
            laplaceMatrix(i,*it) = cotangent_weight;
            laplaceMatrix(*it, i) = cotangent_weight;
       }
    }

    cout<<"Write Laplacian matrix to text file."<<endl;
    QString path1 = "E:/LaplaceTxt/laplaciancotangent.txt";
    SaveMatrixXd( laplaceMatrix, path1 );
}

void LaplacianMesh::GetLaplacianMeanValue()
{
    double cotangent_weight = 0;
    Vector3d vi, vj;

    laplaceMatrix.resize(vertexNumber, vertexNumber);

    //set everything to zero first
    laplaceMatrix.setZero(vertexNumber, vertexNumber);

    for ( int i = 0; i <vertexNumber; i ++ )
    {
        laplaceMatrix(i,i) = 1;
        vi = vertices[i];
       //Get neighbourhood points
       for ( set <int> :: iterator it =  mesh.P2P_Neigh[i].begin(); it !=  mesh.P2P_Neigh[i].end(); ++it)
       {
            vj = vertices[*it]; //point to point
            cotangent_weight = CalculateMeanValueWeight( i, *it );
            laplaceMatrix(i,*it) = cotangent_weight;
            laplaceMatrix(*it, i) = cotangent_weight;
       }
    }

    cout<<"Write Laplacian matrix to text file."<<endl;
    QString path1 = "E:/LaplaceTxt/laplacianMeanValue.txt";
    SaveMatrixXd( laplaceMatrix, path1 );
}

void LaplacianMesh::CalculateEigenDecomposition( int eigenCol)
{
    if( laplaceMatrix.data() == NULL ){ return; }
    else
    {
        cout<<"Computing Eigen decomposition "<<endl;
        EigenSolver<MatrixXd> eigen;
        eigen.compute(laplaceMatrix);
        cout<<"finish eigen compute"<<endl;
        MatrixXd eigenvector = eigen.eigenvectors().real();
        QString path2 = "E:/LaplaceTxt/eigenvectors_matrix.txt";
        SaveMatrixXd( eigenvector, path2 );

        myEigen.resize( laplaceMatrix.rows() );
        myEigen = eigenvector.col(eigenCol);
        QString path3 = "E:/LaplaceTxt/eigenvector.txt";
        SaveVectorXd( myEigen, path3 );
    }
}

double LaplacianMesh::CalculateCotangent(  Vector3d vi, Vector3d vj, Vector3d vk , double &A )
{
    //Based on "Cotangent Laplacian for Images as Surfaces paper "
    //get length of each edge
    double lij,ljk,lki;
    double r, cos_alphaij, sin_alphaij, tan_alphaij;

    lij = (vi - vj).norm();
    ljk = (vj - vk).norm();
    lki = (vk - vi).norm();

    //r is semiparameter
    r = 0.5 * ( lij + ljk + lki );

    //triangle area
    A = sqrt( r*(r-lij)*(r-ljk)*(r-lki) );

    //derive the cosine and sine
    // lij^2 =  ljk^2 + lki^2 - 2*ljk*lki*cos_alphaij
    cos_alphaij = ( ljk*ljk + lki*lki - lij*lki ) / ( 2*ljk*lki );

    sin_alphaij = 2*A / ( ljk*lki );

    tan_alphaij = sin_alphaij / cos_alphaij ;

    return tan_alphaij;
}

double LaplacianMesh::CalculateTangent(  Vector3d vi, Vector3d vj, Vector3d vk )
{
    //get length of each edge
    double lij,ljk,lki,A;
    double r, cos_alphaij, sin_alphaij, tan_alphaij;

    lij = (vi - vj).norm();
    ljk = (vj - vk).norm();
    lki = (vk - vi).norm();

    //r is semiparameter
    r = 0.5 * ( lij + ljk + lki );

    //triangle area
    A = sqrt( r*(r-lij)*(r-ljk)*(r-lki) );

    //derive the cosine and sine
    // lij^2 =  ljk^2 + lki^2 - 2*ljk*lki*cos_alphaij
    cos_alphaij = ( ljk*ljk + lki*lki - lij*lki ) / ( 2*ljk*lki );

    sin_alphaij = 2*A / ( ljk*lki );

    tan_alphaij = cos_alphaij / sin_alphaij;

    return tan_alphaij;
}

double LaplacianMesh::CalculateCotangentWeight ( int vi_index, int vj_index )
{
    Vector3i f;
    double cotangent_weight = 0, area;
    int v1_index, v2_index ,v3_index, vk_index ;
    Vector3d vi, vj, vk;

    double cot_alphaij = 0;
    //Get neighbourhood faces
    for ( set <int> :: iterator it2 =  mesh.P2F_Neigh[vi_index].begin(); it2 !=  mesh.P2F_Neigh[vi_index].end(); ++it2)
    {

        //cout<<"Face index "<<*it2<<endl;
        f = faces[*it2];

        // the face that contains the point vi, vj is correct face
        if( mesh.FaceHasVertex( *it2 , vj_index ) )
        {
            //get vk
            v1_index = mesh.FaceIndex(*it2,0);
            v2_index = mesh.FaceIndex(*it2,1);
            v3_index = mesh.FaceIndex(*it2,2);

            if ( ( v1_index == vi_index  && v2_index == vj_index ) ||
                 ( v1_index == vj_index  && v2_index == vi_index ) )
                vk_index = v3_index;
            else if( ( v2_index == vi_index  && v3_index == vj_index )||
                ( v2_index == vj_index  && v3_index == vi_index ) )
                vk_index = v1_index;
            else
                vk_index = v2_index;

            vi = vertices[vi_index];
            vj = vertices[vj_index];
            vk = vertices[vk_index];

           cot_alphaij = CalculateCotangent( vi, vj, vk, area);
           if( cotangent_weight == 0.0 ){ cotangent_weight = 0.5; } //initiate the weight

           cotangent_weight = cotangent_weight * cot_alphaij;
        }
    }
    return cotangent_weight;
}

double LaplacianMesh::CalculateMeanValueWeight( int vi_index, int vj_index )
{
    Vector3i f;
    int v1_index, v2_index ,v3_index, vk_index ;
    Vector3d vi, vj, vk;

    double tan_thetaij = 0, sumAngle = 0;

    //Get neighbourhood faces
    for ( set <int> :: iterator it2 =  mesh.P2F_Neigh[vi_index].begin(); it2 !=  mesh.P2F_Neigh[vi_index].end(); ++it2)
    {

        //cout<<"Face index "<<*it2<<endl;
        f = faces[*it2];

        // the face that contains the point vi, vj is correct face
        if( mesh.FaceHasVertex( *it2 , vj_index ) )
        {
            //get vk
            v1_index = mesh.FaceIndex(*it2,0);
            v2_index = mesh.FaceIndex(*it2,1);
            v3_index = mesh.FaceIndex(*it2,2);

            if ( ( v1_index == vi_index  && v2_index == vj_index ) ||
                 ( v1_index == vj_index  && v2_index == vi_index ) )
                vk_index = v3_index;
            else if( ( v2_index == vi_index  && v3_index == vj_index )||
                ( v2_index == vj_index  && v3_index == vi_index ) )
                vk_index = v1_index;
            else
                vk_index = v2_index;

            vi = vertices[vi_index];
            vj = vertices[vj_index];
            vk = vertices[vk_index];

           tan_thetaij = CalculateTangent( vj, vk, vi);

           sumAngle = sumAngle + tan_thetaij/2;
        }
    }

    return ( 1 / ( (vi-vj).norm() ) ) * sumAngle;
}


void LaplacianMesh::DrawTriangularMesh()
{
    Vector3d vi, vj;
    for ( int i = 0; i <100; i ++ )
    {
        vi = vertices[i];
        for ( set <int> :: iterator it =  mesh.P2P_Neigh[i].begin(); it !=  mesh.P2P_Neigh[i].end(); ++it)
        {
            vj= vertices[*it]; //point to point

            //Draw mesh
            glLineWidth(3);
            glColor3f(0,0,0);
            glBegin(GL_LINES);
            glVertex3f(vi[0],vi[1],vi[2]);
            glVertex3f(vj[0],vj[1],vj[2]);
            glEnd();

        }

      }

}

void LaplacianMesh::BuildColorMap(  NeighborMesh *m )
{
    double eMin =  myEigen.coeff( 0 ) ;
    double eMax =  myEigen.coeff( myEigen.size()-1);

    m->colors.clear();

   //translate values into [0,1], then convert into color, and store
   for(int i=0; i< myEigen.size(); i++)
    {
      Vector3d d2C = DoubleToColor ( (myEigen.coeff(i) - eMin )/(eMax-eMin) );
       m->colors.push_back( d2C );

    }

   QString path2 = "E:/LaplaceTxt/color.txt";
   SaveVector3d( (m->colors) , path2);
}




