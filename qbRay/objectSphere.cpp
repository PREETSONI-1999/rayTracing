#include "objectSphere.hpp"
#include <cmath>

// the default constructor
qbRT::ObjectSphere::ObjectSphere()
{
}

// virtual destructot
qbRT ::ObjectSphere::~ObjectSphere()
{
}

bool qbRT::ObjectSphere::TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    /* computing values a ,b ,c according to

        t^2 (v · v) + 2t (p1 · v) + (p1 · p1) - r^2 = 0

        at^2 + bt + c = 0

        a = (v · v)

        b = 2 (p1 · v)

        c = (p1 · p1) - r^2 (r=1.0 for unit sphere)

        t = [ -b ± sqrt(b^2 - 4ac) ] / (2a)

        b^2 - 4ac > 0

        (a is cast ray , v is direction Vector)
        */
    qbVector<double> vhat = castRay.m_lab;
    vhat.Normalize();

    // a's value will always be 1, as it is square of magnitude of unit vector

    double b = 2.0 * qbVector<double>::dot(castRay.m_point1, vhat);

    double c = qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

    // test whether intesection
    double intTest = b * b - 4 * 1.0 * c;
    if (intTest > 0.0)
    {

        // calculating exactly where thr intersection is by updating the intPoint vector
        double numeratorSqrt = sqrt(intTest);
        double t1 = (-b + numeratorSqrt) / 2 * 1.0;
        double t2 = (-b - numeratorSqrt) / 2 * 1.0;

        //if either t1 or t2 is negative => part of image is behind the camera and so we will ignore it
        if((t1<0.0) || (t2<0.0)){
            return false;
        }
        else{
            if(t1<t2){
                intPoint = castRay.m_point1 + (vhat*t1);

            }
            else{
                intPoint = castRay.m_point1 + (vhat*t2);

            }

            // Compute the local normal (easy for a sphere at the origin!).
			localNormal = intPoint;
			localNormal.Normalize();
        }


        return true;
    }
    return false;
}