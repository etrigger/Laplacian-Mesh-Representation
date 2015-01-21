void LaplacianMesh::CalculateEigenDecomposition()
{
    if( laplaceMatrix.data() == NULL ){ return; }
    else
    {
        cout<<"Computing Eigen decomposition "<<endl;
        EigenSolver<MatrixXd> eigen;
        eigen.compute(laplaceMatrix);

        MatrixXd eigenvector = eigen.eigenvectors().real();
        QString path2 = "eigenvectors_matrix.txt";
        SaveMatrixXd( eigenvector, path2 );

        myEigen.resize( laplaceMatrix.rows() );
        myEigen = eigenvector.col(2);
        QString path3 = "eigenvector.txt";
        SaveVectorXd( myEigen, path3 );
    }
}
}