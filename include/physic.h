#ifndef PHYSIC_H_INCLUDED
#define PHYSIC_H_INCLUDED

#define PI  3.14159265358979323846264338327950288419716939937510582
#define G   9.80665
#define WATER_DENSITY 0.1

#include <iostream>

#include "forms.h"

double sphere_submerged_volume(Point sphere_center, double sphere_radius, Vector v1, Vector v2, Point eau);
double archimede(double submerged_volume);

#endif // PHYSIC_H_INCLUDED
