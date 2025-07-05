#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "../qbLinAlg/qbVector.h"
#include "./ray.hpp"
#include "gtfm.hpp"


namespace qbRT
{

    // Basew class allowing different objects to inherit from
    class ObjectBase
    {
        public:
        //constructor
        ObjectBase();

        //virtual destructure for inherited classes to implement
        //their own destructure
        virtual ~ObjectBase();

        //function to test for intersection
        virtual bool TestIntersection(const qbRT::Ray &castRay,qbVector<double>&intPoint , qbVector<double> &localNormal , qbVector<double> &localColor);

// Function to set the transform matrix.
			void SetTransformMatrix(const qbRT::GTform &transformMatrix);

            //fniction to test whether 2 doubles are APPROX equal
            bool CloseEnough(const double f1,const double f2);

        





        // public member vars
        qbVector<double> m_baseColor {3};

        // The geometric transform applied to the object.
			qbRT::GTform m_transformMatrix;
    };

}

#endif