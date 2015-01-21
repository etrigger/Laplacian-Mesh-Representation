void LaplacianMesh::GetLaplacianUniformWeight()
{
    laplaceMatrix.resize(vertexNumber, vertexNumber);

    //set everything to zero first
    laplaceMatrix.setZero(vertexNumber, vertexNumber);

    for ( int i = 0; i <vertexNumber; i ++ )
    {
       laplaceMatrix(i,i) = mesh.P2P_Neigh[i].size();//neighbour size here
       for ( set <int> :: iterator it =  mesh.P2P_Neigh[i].begin(); 
			it !=  mesh.P2P_Neigh[i].end(); ++it)
       {
           laplaceMatrix(i,*it) = -1;
           laplaceMatrix(*it, i) = -1;
        }
     }

    QString path1 = "laplacian.txt";
    SaveMatrixXd( laplaceMatrix, path1 );
    cout<<"Laplacian matrix can be found in "<<path1.toStdString()<<endl;
}