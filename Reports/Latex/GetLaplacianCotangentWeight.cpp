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
       for ( set <int> :: iterator it =  mesh.P2P_Neigh[i].begin();
			it !=  mesh.P2P_Neigh[i].end(); ++it)
       {
            vj = vertices[*it]; //point to point
            cotangent_weight = CalculateCotangentWeight( i, *it );
            laplaceMatrix(i,*it) = cotangent_weight;
            laplaceMatrix(*it, i) = cotangent_weight;
       }
    }

    cout<<"Write Laplacian matrix to text file."<<endl;
    QString path1 = "laplacian_cot.txt";
    SaveMatrixXd( laplaceMatrix, path1 );
}
