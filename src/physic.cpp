#include "physic.h"
<<<<<<< HEAD
#include "antIHM.h"
=======
>>>>>>> origin/dev

double sphere_submerged_volume(Point sphere_center, double sphere_radius, Vector v1, Vector v2, Point eau)
{
    double ball_z = sphere_center.z;

    double hbas = ball_z - sphere_radius;
    double hc = eau.z - hbas;

    if(ball_z + sphere_radius <= eau.z)
        hc = 2 * sphere_radius;
    else if(ball_z - sphere_radius > eau.z)
        hc = 0;

    double vc = (PI * hc * hc * (3 * sphere_radius - hc)) / 3;
    return vc;
}

double archimede(double submerged_volume)
{
<<<<<<< HEAD
    double archimede = default_val_densite * submerged_volume * G;
    return archimede;
}

double calcul_new_rayon(double requireMasse,double masseVol)
{
    double sousRacine = (3 * (requireMasse / masseVol) )/ (4 * PI);
    return pow(sousRacine, 1.0/3.0) * 100;
}
=======
    double archimede = WATER_DENSITY * submerged_volume * G;
    return archimede;
}
>>>>>>> origin/dev
