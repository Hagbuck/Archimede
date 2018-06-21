#include "physic.h"

double sphere_submerged_volume(Sphere* sphere, Vector v1, Vector v2, Point eau)
{
    double ball_y = sphere->getCenter().y;
    double ball_r = sphere->getRadius();

    double hbas = ball_y - ball_r;
    double hc = eau.y - hbas;

    if(ball_y + ball_r <= eau.y)
        hc = 2 * ball_r;
    else if(ball_y - ball_r > eau.y)
        hc = 0;

    //std::cout << "Y : " << ball_y << " - HC : " << hc << std::endl;

    double vc = (PI * hc * hc * (3 * ball_r - hc)) / 3;
    return vc;
}
