#ifndef SCENE_H
#define SCENE_H

#include<vector>
#include<SDL2/SDL.h>
#include "qbImage.hpp"
#include "camera.hpp"
#include "objectSphere.hpp"
#include<memory>
#include "objectSphere.hpp"
#include "objectPlane.hpp"
#include "pointLight.hpp"

namespace qbRT {

//global class to handle all the scene related functionalities
class Scene{

    public:
    //the default constructor
    Scene();


    // m_camerahandler
    // m_rendere
    // m_texture

    //function for rendering
    bool Render(qbImage &outputImage); //argukment is a reference to qbImage instance , which will be used for the output

    //private functions
    private:

    //private members
    private:
    //the camera that we will use
    qbRT::Camera m_camera;

    //Unit sphere for testing
    // qbRT :: ObjectSphere m_testSphere;
    
// The list of objects in the scene.
			std::vector<std::shared_ptr<qbRT::ObjectBase>> m_objectList;

            			std::vector<std::shared_ptr<qbRT::LightBase>> m_lightList;


};
}


#endif


