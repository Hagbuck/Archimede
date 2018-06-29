#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include <iostream>


#include "forms.h"
#include "water.h"
#include "physic.h"
#include "antIHM.h"

#define SPHERE_SLICES   10
#define SPHERE_STACKS   10
#define STEP_ANIM       0.01
#define SPEED_INIT      0.01
#define SPEED_INIT_Y    1
#define DELTA_ERR       1

class Sphere : public Form
{
private:
    Water* water;
    double radius;
    double poid;
    Vector v_archimede;
    Vector v_masse;
    Vector v_vitesse;
    Vector v_frottement;
    Vector v_somme;
    Point origin;
    double delta;
    int count_water_jump;
public:
    Sphere(Water* water_ptr, double r = RAYON_DEFAULT / 100, double p = 1.0, Point ori = Point(2,1.5,0), Color cl = Color());
    const double getRadius(void) {return radius;}
    void setRadius(double r) {radius = r;}
    void update(double delta_t);
    void render(void);

    Point getCenter(void);
    void setMasse(Vector masse_vec);

    void resetPosition(void);
};

#endif // SPHERE_H_INCLUDED
