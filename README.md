# rayTracing : (Art of OOP) something that I wanted to build, learn, experience and just jump in. Without looking or researching first.

Summer '25 Project 

C++ with SDL2 library

## Instructions
To build the project, run the following command:

```bash
make all
```

This will create the `bin` and `obj` directories

now run:
```bash
bash run.sh
```

NOTE : Vector Maths and Matrix computations (using double precision arithmetics mostly) are not entirely written from scratch.
Indeed used librlary calls for the same

The library is qbLinAlg:
It is a # HEADER_ONLY Library


## Important Definitions :

You create a renderer for your window:
SDL_Renderer *renderer = SDL_CreateRenderer(window, ...);

You load or create textures:
SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

You draw the texture using the renderer:
SDL_RenderCopy(renderer, texture, ...);

You present the final image:
SDL_RenderPresent(renderer);

Analogy
Think of the renderer as a movie projector and textures as film reels. The projector (renderer) can show images, but only if you give it a film reel (texture) to display. The projector itself does not contain the images.

## Important Concepts :
To represent objects in local coordinate systems and then
map (transform) them to global coordinate system is a powerful
technique which keeps things very simple 
