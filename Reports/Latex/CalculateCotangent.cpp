double LaplacianMesh::CalculateCotangent(  Vector3d vi, Vector3d vj, 
								Vector3d vk , double &A )
{
    //Based on "Cotangent Laplacian for Images as Surfaces paper "

    //get length of each edge
    double lij,ljk,lki;
    double r, cos_alphaij, sin_alphaij, cot_alphaij;

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

    cot_alphaij = cos_alphaij / sin_alphaij;

    return cot_alphaij;
}