#ifndef QBIMAGE_H
#define QBIMAGE_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include<iostream>

using namespace std;
class qbImage{
    public:
        //constructor 
        qbImage();

        //destructor
        ~qbImage();

        //function to initialize
        void Initialize(int xSize,int ySize,SDL_Renderer *pRenderer);

        //function to set the color of the pixel
        void SetPixel(int x,int y,double red,double green,double blue);

        //function to return the image for display
        void Display();


        //function to return the dmensions of the image
        int GetXSize();
        int GetYSize();

    private:
        Uint32 ConvertColor(double red,double green,double blue);
        void InitTexture();

        //arrays to store image data 
        vector<vector<double>>m_rChannel;
        vector<vector<double>>m_gChannel;
        vector<vector<double>>m_bChannel;

        //image dimensions
        int m_xSize, m_ySize;

        //SDL2
        SDL_Renderer *m_pRenderer;
        SDL_Texture *m_pTexture;

};

#endif