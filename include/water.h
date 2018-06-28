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
    Water(Point deep_pt = Point(0,0,-2.5), Vector deep_v1 = Vector(1,0,0), Vector deep_v2 = Vector(0,1,0),
          Point lvl_pt = Point(0,0,0), Vector lvl_v1 = Vector(1,0,0), Vector lvl_v2 = Vector(0,1,0));
    ~Water(void);
    void update(double delta_t);
    void render(void);

    Cube_face* getDeep(void);
    Cube_face* getLvl(void);
    Point getLvlPoint(void);
    double getLvlz(void);
    Point getDeepPoint(void);
    double getDeepz(void);
};

#endif // WATER_H_INCLUDED
