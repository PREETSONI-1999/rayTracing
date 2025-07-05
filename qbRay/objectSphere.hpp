#ifndef OBJECTSPHERE_H
#define OBJECTSPHERE_H

#include "objectBase.hpp"
#include "gtfm.hpp"

namespace qbRT {
class ObjectSphere : public ObjectBase 
{
    public :
    /*the default constructor which will create unit sphere at origin*/
    ObjectSphere();

    //overriding the destructor
    virtual ~ObjectSphere() override; //note the override keyword

    //overriding to test intersections
    virtual bool TestIntersection(const qbRT::Ray &castRay,qbVector<double>&intPoint , qbVector<double> &localNormal , qbVector<double> &localColor) override;



    //private members
    private:
};
}

#endif