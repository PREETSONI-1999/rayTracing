#include "objectBase.hpp"
#include "ray.hpp"
#include <math.h>

#define EPSILON 1e-21f;

//default constructor
qbRT::ObjectBase::ObjectBase(){


}

//default destructor
qbRT :: ObjectBase::~ObjectBase(){
    //anyways is virtuial so will be overwritten
}

//function to test for intersection
bool qbRT::ObjectBase::TestIntersection(const qbRT::Ray &castRay , qbVector<double> &intPoint , qbVector<double>& localNormal, 
qbVector<double> &localColor){
    //ewill also be overwritten
    return false;
}

void qbRT::ObjectBase::SetTransformMatrix(const qbRT::GTform &transformMatrix)
{
	m_transformMatrix = transformMatrix;
}

//function to test if 2 floating points nos are close to being equal
bool qbRT::ObjectBase:: CloseEnough(const double f1,const double f2){
    return fabs(f1-f2) < EPSILON;
}

