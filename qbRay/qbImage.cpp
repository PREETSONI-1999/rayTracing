#include "qbImage.hpp"
#include <fstream>


// defualt constructpr
qbImage::qbImage()
{
    m_xSize = 0;
    m_ySize = 0;
    m_pTexture = NULL;
}

qbImage::~qbImage()
{
    if (m_pTexture != NULL)
    {
        SDL_DestroyTexture(m_pTexture);
    }
}

void qbImage::Initialize(int xSize, int ySize, SDL_Renderer *pRenderer)
{
    // resize the imagr arrays
    m_rChannel.resize(xSize, vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, vector<double>(ySize, 0.0));

    // store the dimensions
    m_xSize = xSize;
    m_ySize = ySize;

    // store the pointer ti the renderer
    m_pRenderer = pRenderer;

    // Initialize the texture
    InitTexture();
}

// Funtion to setPixels
void qbImage ::SetPixel(int x, int y, double red, double green, double blue)
{
    m_rChannel.at(x).at(y) = red;
    m_gChannel.at(x).at(y) = green;
    m_bChannel.at(x).at(y) = blue;
}

void qbImage ::Display()
{
    // allocate memory for pixel buffer
    Uint32 *tempPixels = new Uint32[m_xSize * m_ySize];

    // clear the pixel buffer
    memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

    for (int x = 0; x < m_xSize; x++)
    {
        for (int y = 0; y < m_ySize; y++)
        {
            tempPixels[x + (y * m_xSize)] = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
        }
    }

    // update the texture with pixel Buffer
    SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));

    // deleye the Pixel buffer
    delete[] tempPixels;

    // copy the texture to the renderer
    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_ySize;
    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

// Initialize the texture
void qbImage ::InitTexture()
{

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    // delete any previously deleted texture
    if (m_pTexture != NULL)
        SDL_DestroyTexture(m_pTexture);

    // create the texture that will store the image
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

// function to convert color to UInt32
Uint32 qbImage ::ConvertColor(double red, double green, double blue)
{
    // cinvert the colors to unsigned integers
    unsigned char r = static_cast<unsigned char>(red);
    unsigned char g = static_cast<unsigned char>(green);
    unsigned char b = static_cast<unsigned char>(blue);
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
	#else
		Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
	#endif
	
	return pixelColor;

}

//return the dimensions of the image
int qbImage::GetXSize(){
    return m_xSize;
}

int qbImage::GetYSize(){
    return m_ySize;
}
