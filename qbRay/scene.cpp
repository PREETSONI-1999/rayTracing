//scene.cpp

#include "scene.hpp"

//the construtor
qbRT::Scene::Scene(){
	//configure the camera
	m_camera.SetPosition(qbVector<double>{std::vector<double>{0.0,-10.0,-1.0}});
	m_camera.SetLookAt(qbVector<double>{std::vector<double>{0.0,0.0,0.0}}); //look at origin
	m_camera.SetUp(qbVector<double>{std::vector<double>{0.0,0.0,1.0}});
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0/9.0);
	m_camera.UpdateCameraGeometry();

	// Construct a test sphere.
	// Construct a test sphere.
	m_objectList.push_back(std::make_shared<qbRT::ObjectSphere> (qbRT::ObjectSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjectSphere> (qbRT::ObjectSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjectSphere> (qbRT::ObjectSphere()));

	//construct a plane for testing
	m_objectList.push_back(std::make_shared<qbRT::ObjectPlane> (qbRT::ObjectPlane()));
	// m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double>{128.0,128.0,128.0}}; //I guess in future we want btw 0..1
	m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double>{0.5,0.5,0.5}};


	//define a transform for the plane
	qbRT::GTform planeMatrix;
	planeMatrix.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}} ,
	qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
	qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});
	m_objectList.at(3) -> SetTransformMatrix(planeMatrix);

	// Modify the spheres.
	qbRT::GTform testMatrix1, testMatrix2, testMatrix3;
	testMatrix1.SetTransform(	qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});
														
	testMatrix2.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});
														
	testMatrix3.SetTransform(	qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});
														
	m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
	m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
	m_objectList.at(2) -> SetTransformMatrix(testMatrix3);
	
	//all colors I guess will be in range 0..1
	// m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{64.0, 128.0, 200.0}};
	// m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{255.0, 128.0, 0.0}};
	// m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{255.0, 200.0, 0.0}};
	m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{0.25, 0.5, 0.8}};
	m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{1.0,0.5, 0.0}};
	m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{1.0,0.8, 0.0}};
	
	// Construct a test light.
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {5.0, -10.0, -5.0}};


	// m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {255.0, 255.0, 255.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};

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

			//test for intersection with all objectsin the scene
			std::shared_ptr<qbRT::ObjectBase> closestObject;
			qbVector<double> closestIntPoint {3};
			qbVector<double> closestLocalNormal {3};
			qbVector<double> closestLocalColor {3};

			double minDist = 1e6;
			bool intersectionFound = false;

			

			
			// Test for intersections with all objects in the scene.
			for (auto currentObject : m_objectList)
			{
				bool validInt = currentObject -> TestIntersection(cameraRay, intPoint, localNormal, localColor);
				
				// // If we have a valid intersection, change pixel color to red.
				// if (validInt)
				// {
				// 	// Compute intensity of illumination.
				// 	double intensity;
				// 	qbVector<double> color {3};
				// 	bool validIllum = false;
				// 	for (auto currentLight : m_lightList)
				// 	{
				// 		validIllum = currentLight->ComputeIllumination(intPoint, localNormal, m_objectList, currentObject, color, intensity);
				// 	}
				
				// 	// Compute the distance between the camera and the point of intersection.
				// 	double dist = (intPoint - cameraRay.m_point1).norm();
				// 	if (dist > maxDist)
				// 		maxDist = dist;
					
				// 	if (dist < minDist)
				// 		minDist = dist;
				
				// 	//outputImage.SetPixel(x, y, 255.0 - ((dist - 8.0) / 0.94101) * 255.0, 0.0, 0.0);
				// 	if (validIllum)
				// 	{
				// 		// outputImage.SetPixel(x, y, 255.0 * intensity, 0.0, 0.0);
				// 		outputImage.SetPixel(x, y,	localColor.GetElement(0) * intensity,
				// 						localColor.GetElement(1) * intensity,
				// 						localColor.GetElement(2) * intensity);

				// 	}
				// 	else
				// 	{
				// 		// outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
				// 	}
				// }

				//if we have a valid intersection
				if(validInt){
					intersectionFound = true;

					//compute the distasne between camera and point of intersection
					double dist=(intPoint - cameraRay.m_point1).norm();

					//if this object is closer to camera than any other object we have,
					//then store a reference to it

					if(dist < minDist){
						minDist = dist;
						closestObject = currentObject;
						closestIntPoint = intPoint;
						closestLocalNormal = localNormal;
						closestLocalColor = localColor;
					}
				}
				else
				{

					// outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
				}				
			}
			//compute the illumination for the closest object,assuming there was a valid lintersectiojn 
			if(intersectionFound){
				//compute the intensity of the illuniatiuon
				double intensity;
				qbVector<double>color {3};
				double red =0.0;
				double green=0.0;
				double blue=0.0;
				bool validIllum = false;
				bool illumFound=false;
				for(auto currentLight : m_lightList){
					validIllum = currentLight -> ComputeIllumination(closestIntPoint,closestLocalNormal,m_objectList,closestObject,color,intensity);

					if(validIllum){
						illumFound=true;
						red+=color.GetElement(0)*intensity;
						green+=color.GetElement(1)*intensity;
						blue+=color.GetElement(2)*intensity;						 
					}
				}
				if(illumFound){
					red*= closestLocalColor.GetElement(0);
					green*=closestLocalColor.GetElement(1);
					blue*=closestLocalColor.GetElement(2);
					outputImage.SetPixel(x,y,red,green,blue);
				}
				
			}
		}
	}
	
	std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;

return true;

}