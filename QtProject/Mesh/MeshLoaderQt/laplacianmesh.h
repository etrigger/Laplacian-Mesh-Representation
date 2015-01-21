#ifndef LAPLACIANMESH_H
#define LAPLACIANMESH_H

#include <Eigen/Core>
#include <Eigen/Geometry>
#include<vector>
#include "NeighborMesh.h"

using namespace Eigen;

class LaplacianMesh
{
public:
    LaplacianMesh( NeighborMesh m );
    virtual~LaplacianMesh();

    //mesh detail
    NeighborMesh mesh;
    vector<Vector3d> vertices;
    vector<Vector3i> faces;
    int vertexNumber;

    //Laplace attributes
    MatrixXd laplaceMatrix;
    VectorXd myEigen;

    // Laplace related functions
    void GetLaplacianUniformWeight();
    void GetLaplacianCotangentWeight();
    void GetLaplacianMeanValue();
    void CalculateEigenDecomposition( int eigenCol);

    //weight calculation
    double CalculateCotangent(  Vector3d v1, Vector3d v2, Vector3d v3, double &A  );
    double CalculateTangent( Vector3d v1, Vector3d v2, Vector3d v3 );
    double CalculateCotangentWeight ( int vi_index, int vj_index );
    double CalculateMeanValueWeight( int vi_index, int vj_index );

    //Draw and render
    void DrawTriangularMesh();
    void BuildColorMap( NeighborMesh *m );
};

#endif // LAPLACIANMESH_H
