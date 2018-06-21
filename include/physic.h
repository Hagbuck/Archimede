#ifndef PHYSIC_H_INCLUDED
#define PHYSIC_H_INCLUDED

#define PI 3.14159265358979323846264338327950288419716939937510582

#include <iostream>

#include "forms.h"

double sphere_submerged_volume(Sphere* sphere, Vector v1, Vector v2, Point ori);

#endif // PHYSIC_H_INCLUDED
