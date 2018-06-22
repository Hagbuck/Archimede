#include "sphere.h"

Sphere::Sphere(Water* water_ptr, double r, double p, Point ori, Color cl)
{
    water = water_ptr;
    v_archimede = Vector(0,0,0);
    v_masse = Vector(0,p,0);
    poid = p;
    radius = r;
    col = cl;
    origin = ori;

    resetPosition();
}


void Sphere::update(double delta_t)
{
    double y = anim.getPos().y;
    double futur_pos = y - v_masse.y + v_archimede.y;
    // Si le prochain mouvement se retrouve ne se retrouve pas sous le sol.
    if(futur_pos - radius > 0)
    {
        anim.setPos(Point(0, futur_pos, 0));

        double submerged_volume = sphere_submerged_volume(anim.getPos(), radius, water->getLvl()->getVdir1(), water->getLvl()->getVdir2(), water->getLvl()->getAnim().getPos());
        v_archimede.y = archimede(submerged_volume);

        //std::cout << "Vol : " << archimede.y << std::endl;
    }
    else // La sphère se retrouve sous le sol.
    {
        anim.setPos(Point(0, radius, 0)); // On met la sphère sur le sol.
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

    gluDeleteQuadric(quad);

    glBegin(GL_LINE_LOOP);
    {
        glColor3f(255,0,0);
        glVertex3d(0,0,0);
        glVertex3d(v_archimede.x, v_archimede.y * 10, v_archimede.z);

        glColor3f(0,150,150);
        glVertex3d(0,0,0);
        glVertex3d(-v_masse.x, - v_masse.y *10, -v_masse.z);
    }
    glEnd();

    glPopMatrix();
}

Point Sphere::getCenter(void)
{
    return anim.getPos();
}

void Sphere::setMasse(Vector masse_vec)
{
    v_masse = masse_vec;
}

void Sphere::resetPosition(void)
{
    anim.setPos(origin);
}
