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
    for (int x=0; x<xSize; ++x)
		{
			for (int y=0; y<ySize; ++y)
			{
				double red = (static_cast<double>(x)/xSize) * 255.0;
				double green = (static_cast<double>(y)/ySize) * 255.0;
				outputImage.SetPixel(x, y, red, green, 0);
			}
		}    

    return true;


}