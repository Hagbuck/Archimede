#include "sphere.h"

Sphere::Sphere(Water* water_ptr, double r, Color cl)
{
    water = water_ptr;
    archimede = Vector(0,0,0);
    apesanteur = Vector(0,0.01,0);
    radius = r;
    col = cl;
}


void Sphere::update(double delta_t)
{
    double y = anim.getPos().y;

    if(y - apesanteur.y - radius > 0)
    {
        anim.setPos(Point(0, y - apesanteur.y, 0));
        std::cout << "Vol : " << sphere_submerged_volume(anim.getPos(), radius, water->getLvl()->getVdir1(), water->getLvl()->getVdir2(), water->getLvl()->getAnim().getPos()) << std::endl;
    }
}


void Sphere::render(void)
{
    GLUquadric *quad = NULL;

    quad = gluNewQuadric();

    gluQuadricDrawStyle(quad, GLU_LINE);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    Point pos = anim.getPos();
    glTranslated(pos.x, pos.y, pos.z);

    gluSphere(quad, radius, SPHERE_SLICES, SPHERE_STACKS);

    glPopMatrix();

    gluDeleteQuadric(quad);
}

Point Sphere::getCenter(void)
{
    return anim.getPos();
}

void Sphere::setApesanteur(Vector apesanteur_vec)
{
    apesanteur_vec = apesanteur_vec;
}
