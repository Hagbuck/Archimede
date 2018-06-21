#ifndef WATER_H_INCLUDED
#define WATER_H_INCLUDED

#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include <iostream>

#include "forms.h"

class Water : public Form
{
private:
    Cube_face *deep;
    Cube_face *lvl;
public:
    Water(Point deep_pt = Point(-.5,0,-.5), Vector deep_v1 = Vector(1,0,0), Vector deep_v2 = Vector(0,0,1),
          Point lvl_pt = Point(-.5,0.7,-.5), Vector lvl_v1 = Vector(1,0,0), Vector lvl_v2 = Vector(0,0,1));
    ~Water(void);
    void update(double delta_t);
    void render(void);

    Cube_face* getDeep(void);
    Cube_face* getLvl(void);
};

#endif // WATER_H_INCLUDED
