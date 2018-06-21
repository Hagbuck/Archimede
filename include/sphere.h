#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>

#include "forms.h"

#define SPHERE_SLICES 40
#define SPHERE_STACKS 40

class Sphere : public Form
{
private:
    double radius;
public:
    Sphere(double r = 1.0, Color cl = Color());
    const double getRadius(void) {return radius;}
    void setRadius(double r) {radius = r;}
    void update(double delta_t);
    void render(void);

    Point getCenter(void);
};

#endif // SPHERE_H_INCLUDED
