//scene.cpp

#include "scene.hpp"

//the construtor
qbRT::Scene::Scene(){
	//configure the camera
	m_camera.SetPosition(qbVector<double>{std::vector<double>{0.0,-10.0,0.0}});
	m_camera.SetLookAt(qbVector<double>{std::vector<double>{0.0,0.0,0.0}}); //look at origin
	m_camera.SetUp(qbVector<double>{std::vector<double>{0.0,0.0,1.0}});
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0/9.0);
	m_camera.UpdateCameraGeometry();


}


//function to perform the rendering
bool qbRT::Scene::Render(qbImage &outputImage){
    
    //get the dimensions of the output image
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    //create some color variations
    // for (int x=0; x<xSize; ++x)
	// 	{
	// 		for (int y=0; y<ySize; ++y)
	// 		{
	// 			double red = (static_cast<double>(x)/xSize) * 255.0;
	// 			double green = (static_cast<double>(y)/ySize) * 255.0;
	// 			outputImage.SetPixel(x, y, red, green, 0);
	// 		}
	// 	}    

    // return true;



	//instances to get before looping over each pixels
	qbRT::Ray cameraRay;
	qbVector<double> intPoint {3};
	qbVector<double> localNormal {3};
	qbVector<double> localColor {3};


	//for scaling from 1290:720 to -1:1 , precomputing certain values
	double xFact = 1.0 / (static_cast<double>(xSize)/2.0); //this will restrict from 0 to 2
	double yFact = 1.0 / (static_cast<double>(ySize)/2.0); //this will restrict from 0 to 2
	double minDist = 1e6;
	double maxDist = 0.0 ;


	//looping over each pixel;
	for (int x=0; x<xSize; ++x)
	{
		for (int y=0; y<ySize; ++y)
		{
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;
			
			// Generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);
			
			// Test if we have a valid intersection.
			bool validInt = m_testSphere.TestIntersection(cameraRay, intPoint, localNormal, localColor);
			
			// If we have a valid intersection, change pixel color to red.
			if (validInt)
			{
				// Compute the distance between the camera and the point of intersection.
				double dist = (intPoint - cameraRay.m_point1).norm();
				if (dist > maxDist)
					maxDist = dist;
				
				if (dist < minDist)
					minDist = dist;
				
				outputImage.SetPixel(x, y, 255.0 - ((dist - 8.0) / 0.94101) * 255.0, 0.0, 0.0);
			}
			else
			{
				outputImage.SetPixel(x, y, 100.0, 100.0, 100.0);
			}
		}
	}
	
	std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;



}