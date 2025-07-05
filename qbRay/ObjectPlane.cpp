#include "./objectPlane.hpp"
#include<cmath>

//default constructor
qbRT::ObjectPlane::ObjectPlane(){

}

//the destructor
qbRT::ObjectPlane::~ObjectPlane(){


}

//the function to test for intersection
bool qbRT::ObjectPlane::TestIntersection(const qbRT::Ray &castRay , qbVector<double> &intPoint,
        qbVector<double>&localNormal, qbVector<double>&localColor)
{
    //copy the ray and apply the backward transform

    //we get the transform matanrix from the base class
    qbRT::Ray bckRay = m_transformMatrix.Apply(castRay, qbRT::BCKTFORM);

    //copy the m_lab vector from bckRay and normalize it
    qbVector<double> k = bckRay.m_lab;
    k.Normalize();

    /* check if there is an intersection.
    i.e if the cast ray is not parallel to the plane
    */
   if(!CloseEnough(k.GetElement(2),0.0)){
     //if there is an intersection  (t=az/-kz)
     double t = bckRay.m_point1.GetElement(2)/ -k.GetElement(2);

     //if t is neg, intersection point is behinf and is ignored
     if(t>0.0){
        //instead of creating infinite plane, we can crete unit plane 
        //centered at origin and transform matrix se we can accordingly scale  

        //lets compute u and v
        double u = bckRay.m_point1.GetElement(0) + (k.GetElement(0)*t);
        double v = bckRay.m_point1.GetElement(1) + (k.GetElement(1)*t);

        //if the magnitude of u and v is <= 1, then we must be in the plane
        if(abs(u) < 1.0 && abs(v) < 1.0){
             //compute the point of intersection
             qbVector<double> poi = bckRay.m_point1 + t*k;

             //ransforminf intersectouin point  back to world coordinates
             intPoint = m_transformMatrix.Apply(poi, qbRT::FWDTFORM);

             //compute the local normal
             qbVector<double> localOrigin {std::vector<double> {0.0,0.0,0.0}};
             qbVector<double> normalVector {std::vector<double> {0.0,0.0,-1.0}};

             qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin,qbRT::FWDTFORM);
             localNormal = m_transformMatrix.Apply(normalVector,qbRT::FWDTFORM) - globalOrigin;
             localNormal.Normalize();

             localColor=m_baseColor;

             return true;




        }
        return false;
     }
     return false;


    }
    return false;
}
 