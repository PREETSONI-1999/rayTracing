//scene.cpp

#include "scene.hpp"

//the construtor
qbRT::Scene::Scene(){



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