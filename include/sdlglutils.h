#ifndef SDLGLUTILS_H
#define SDLGLUTILS_H

#include <GL/gl.h>
#include <SDL2/SDL.h>
<<<<<<< HEAD
=======
#include <iostream>
>>>>>>> origin/dev

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

<<<<<<< HEAD
GLuint loadTexture(const char * filename,bool useMipMap = true);
=======
GLuint prepareTexture(SDL_Surface* surface_texture,bool useMipMap = true);
SDL_Surface* loadTexture(const char * filename);
>>>>>>> origin/dev

void drawAxis(double scale = 1);


#endif //SDLGLUTILS_H
