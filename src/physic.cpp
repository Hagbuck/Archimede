#include "physic.h"

double sphere_submerged_volume(Sphere* sphere, Vector v1, Vector v2, Point ori)
{
    double hbas = sphere->getAnim().getPos().y - sphere->getRadius();
    double hc = 2 * sphere->getRadius();
    if(hbas > hc)
        hc = ori.y - hbas;
    std::cout << "Y : " << sphere->getAnim().getPos().y << " - HC : " << hc << std::endl;
    double vc = (PI * hc * (3 * sphere->getRadius() - hc)) / 3;

    return vc;
}
