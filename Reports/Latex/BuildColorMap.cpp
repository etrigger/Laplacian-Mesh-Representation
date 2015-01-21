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

   QString path2 = "color2.txt";
   SaveVector3d( (m->colors) , path2);
}
