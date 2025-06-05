#ifndef RAY_HPP
#define RAY_HPP

#include "../qbLinAlg/qbVector.h"
//namespace needed??

namespace qbRT{
//class to handle rays in our scene
    class Ray{

        public:
        //default constructor
        Ray();
        //constructor (Ray between 2 vectors pt1 and pt2)
        Ray(const qbVector<double> &point1 , const qbVector<double> &point2);

        qbVector<double> GetPoint1() const;
        qbVector<double> GetPoint2() const;



        //public members (internal so its okay to be)
        public:
        qbVector<double> m_point1 {3};
        qbVector<double> m_point2 {3};
        //vector from point a to b called | l      |
        //                                |  (ab)  |
        qbVector<double> m_lab{3};


        //Private members
        private:



    };
}



#endif