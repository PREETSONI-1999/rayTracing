#ifndef CAMERA_H
#define CAMERA_H

#include "../qbLinAlg/qbVector.h"
#include "./ray.hpp"

namespace qbRT
{
    class Camera
    {

    public:
        // constructor camera
        Camera();

        // functions to set camaera parameters
        void SetPosition(const qbVector<double> &newPosition);
        void SetUp(const qbVector<double> &upVector);
        void SetLookAt(const qbVector<double> &newLookAt);
        void Setlength(double newLength);
        void SetHorzSize(double newSize);
        void SetAspect(double newAspect);

        // functions to return camera parameters
        qbVector<double> GetPosition();
        qbVector<double> GetLookAt();
        qbVector<double> GetUp();
        qbVector<double> GetU(); // for the virtual screen I Guess (u and folowinG v)
        qbVector<double> GetV();
        qbVector<double> GetScreenCentre();
        double GetLength();
        double GetHorzSize();
        double GetAspect();

        // function to generate a ray
        //  return a ray which goes from pinhole out FROM a particular position on the screen
        //(viz proScreenX,proScreenY)
        // intended to vary between -1 to 1 (0 representing centre of screen)
        Ray GenerateRay(float proScreenX, float proScreenY);

            // function to update the camera geometry
            void UpdateCameraGeometry();

    private:
        qbVector<double> m_cameraPosition{3};
        qbVector<double> m_cameraUp{3};
        qbVector<double> m_cameraLookAt{3};
        double m_cameraLength;
        double m_cameraHorzSize;
        double m_cameraAspectRatio;
        qbVector<double>m_alignmentVector {3}; //prinicpal axis of cam
        qbVector<double>m_projectionScreenU {3};
        qbVector<double>m_projectionScreenV{3};
        qbVector<double>m_projectionScreenCentre{3};


    };
}

#endif