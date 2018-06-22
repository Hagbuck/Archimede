#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include <iostream>

#include "forms.h"
#include "water.h"
#include "physic.h"

#define SPHERE_SLICES 10
#define SPHERE_STACKS 10

class Sphere : public Form
{
private:
    Water* water;
    double radius;
    double poid;
    Vector v_archimede;
    Vector v_masse;
    Point origin;
public:
    Sphere(Water* water_ptr, double r = 1.0, double p = 1.0, Point ori = Point(0,1.5,0), Color cl = Color());
    const double getRadius(void) {return radius;}
    void setRadius(double r) {radius = r;}
    void update(double delta_t);
    void render(void);

    Point getCenter(void);
    void setMasse(Vector masse_vec);

    void resetPosition(void);
};

#endif // SPHERE_H_INCLUDED
