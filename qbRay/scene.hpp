#ifndef SCENE_H
#define SCENE_H

#include<vector>
#include<SDL2/SDL.h>
#include "qbImage.hpp"

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




};
}


#endif


