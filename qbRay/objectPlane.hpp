#ifndef OBJECTPLANE_H
#define OBJECTPLANE_H

#include "./objectBase.hpp"
#include "./gtfm.hpp"

namespace qbRT{ 

    class ObjectPlane : public ObjectBase
    {

        public:
        //default constructor
        ObjectPlane();

        //override the destructor
        virtual ~ObjectPlane() override;

        //override the fucnation to test for intersection
        virtual bool TestIntersection(const qbRT::Ray &castRay , qbVector<double> &intPoint,
        qbVector<double>&localNormal, qbVector<double>&localColor) override;

    private:
    

    };
}


#endif
