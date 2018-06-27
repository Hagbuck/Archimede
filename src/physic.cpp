#include "physic.h"

double sphere_submerged_volume(Point sphere_center, double sphere_radius, Vector v1, Vector v2, Point eau)
{
    double ball_y = sphere_center.y;

    double hbas = ball_y - sphere_radius;
    double hc = eau.y - hbas;

    if(ball_y + sphere_radius <= eau.y)
        hc = 2 * sphere_radius;
    else if(ball_y - sphere_radius > eau.y)
        hc = 0;

    double vc = (PI * hc * hc * (3 * sphere_radius - hc)) / 3;
    return vc;
}

double archimede(double submerged_volume)
{
    double archimede = WATER_DENSITY * submerged_volume * G;
    return archimede;
}
