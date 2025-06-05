#include "./camera.hpp"
#include "./ray.hpp"
#include <math.h>

qbRT::Camera::Camera()
{
    // dfault  constructor
    m_cameraPosition = qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}};
    m_cameraLookAt = qbVector<double>{std ::vector < double>{0.0, 0.0, 0.0}};
    m_cameraUp = qbVector<double>{std ::vector < double>{0.0, 0.0, 1.0}};
    m_cameraLength = 1.0;
    m_cameraHorzSize = 1.0;
    m_cameraAspectRatio = 1.0;
}

// function to Set stuffs

void qbRT::Camera::SetPosition(const qbVector<double> &newPosition)
{
    m_cameraPosition = newPosition;
}

void qbRT::Camera::SetLookAt(const qbVector<double> &newLookAt)
{
    m_cameraLookAt = newLookAt;
}

void qbRT::Camera::SetUp(const qbVector<double> &upVector)
{
    m_cameraUp = upVector;
}

void qbRT::Camera::Setlength(double newLength)
{
    m_cameraLength = newLength;
}

void qbRT::Camera::SetHorzSize(double newHorsSize)
{
    m_cameraHorzSize = newHorsSize;
}

void qbRT::Camera::SetAspect(double newAspect)
{
    m_cameraAspectRatio = newAspect;
}

// function to get camera position
qbVector<double> qbRT::Camera::GetPosition()
{
    return m_cameraPosition;
}

qbVector<double> qbRT::Camera::GetLookAt()
{
    return m_cameraLookAt;
}

qbVector<double> qbRT::Camera::GetUp()
{
    return m_cameraUp;
}

double qbRT::Camera::GetLength()
{
    return m_cameraLength;
}

double qbRT::Camera::GetHorzSize()
{
    return m_cameraHorzSize;
}

double qbRT::Camera::GetAspect()
{
    return m_cameraAspectRatio;
}

qbVector<double> qbRT::Camera::GetU()
{
    return m_projectionScreenU;
}

qbVector<double> qbRT::Camera::GetV()
{
    return m_projectionScreenV;
}

qbVector<double> qbRT::Camera::GetScreenCentre()
{
    return m_projectionScreenCentre;
}

// calculating parameters (fo rthe geometry of the rayTracing)

// function to compute the camera geometry
void qbRT::Camera::UpdateCameraGeometry()
{
    // first , compute the vector from cameraPosition to the LookAt posoition
    //(principal axis)
    m_alignmentVector = m_cameraLookAt - m_cameraPosition;
    m_alignmentVector.Normalize();

    // secondly compute the U and V vectors
    m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
    m_projectionScreenU.Normalize();

    m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
    m_projectionScreenV.Normalize();

    // thirdly compute the position of the centre point of the screen
    m_projectionScreenCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);

    // finally modify U and V to match the size and aspect ratio
    m_projectionScreenU = (m_projectionScreenU * m_cameraHorzSize);
    m_projectionScreenV = (m_projectionScreenV* (m_cameraHorzSize/m_cameraAspectRatio));
}


bool qbRT::Camera::GenerateRay(float proScreenX,float proScreenY , qbRT::Ray &cameraRay)
{
	// Compute the location of the screen point in world coordinates.
	qbVector<double> screenWorldPart1 = m_projectionScreenCentre + (m_projectionScreenU * proScreenX);
	qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);
	
	// Use this point along with the camera position to compute the ray.
    cameraRay.m_point1 = m_cameraPosition;
    cameraRay.m_point1 = screenWorldCoordinate;
    cameraRay.m_lab=screenWorldCoordinate - m_cameraPosition;

     return true;
}

