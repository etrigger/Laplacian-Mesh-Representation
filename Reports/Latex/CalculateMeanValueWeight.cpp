double LaplacianMesh::CalculateMeanValueWeight( int vi_index, int vj_index )
{
    Vector3i f;
    int v1_index, v2_index ,v3_index, vk_index ;
    Vector3d vi, vj, vk;

    double tan_thetaij = 0, sumAngle = 0;

    //Get neighbourhood faces
    for ( set <int> :: iterator it2 =  mesh.P2F_Neigh[vi_index].begin(); 
			it2 !=  mesh.P2F_Neigh[vi_index].end(); ++it2)
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