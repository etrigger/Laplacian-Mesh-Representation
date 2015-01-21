void LaplacianMesh::DrawTriangularMesh()
{
    Vector3d vi, vj;
    for ( int i = 0; i <100; i ++ )
    {
        vi = vertices[i];
        for ( set <int> :: iterator it =  mesh.P2P_Neigh[i].begin(); 
		      it !=  mesh.P2P_Neigh[i].end(); ++it)
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