// Screen dimension constants
#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 820

#include <sstream>
#include <string>
#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "antIHM.h"


//IHM VARS
extern double default_val_masse ;
extern double default_val_speed;
extern double default_val_densite ;
extern  double default_val_rayon ;

extern double old_val_masse;
extern double old_val_densite;
extern double old_val_rayon;

extern double ralenti;

extern TwBar * mainBar;
extern TwBar * materialBar;

extern double default_scroll_sensivity;
extern double default_mouse_sensitivity;
extern double default_translation_sensitivity;

//SPHERE
extern SDL_Surface* herbe_text ;
extern SDL_Surface* terre_text ;
extern SDL_Surface* wood_text ;
extern SDL_Surface* metal_text;
extern SDL_Surface* pvc_text;

extern bool displayVect;

using namespace std;
