#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "forms.h"
#include <cstdlib>

using namespace std;


void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Form::render()
{

    Point org = anim.getPos();
    glTranslated(org.x, org.y, org.z);
    //glColor3f(col.r, col.g, col.b);

}


Sphere::Sphere(double r, Color cl, Point * p)
{
    radius = r;
    col = cl;
    origin = p;
}


void Sphere::update(double delta_t)
{
    // Complete this part
    /*Vector* test = new Vector(Point(1,1,1),Point(0,0,0));
    anim.setTheta(anim.getTheta()+1);
    anim.setPhi(anim.getPhi()+1);
    anim.setSpeed(anim.getSpeed()+*test);
    anim.setAccel(anim.getAccel()+*test);*/


}


void Sphere::render()
{
    GLUquadric *quad;

    quad = gluNewQuadric();

    gluQuadricDrawStyle(quad,GLU_LINE);

    gluSphere(quad,radius,40,40);

    gluDeleteQuadric(quad);
}


Cube_face::Cube_face(Vector v1, Vector v2, Point org, double l, double w, Color cl,GLuint textureToApply)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim.setPos(org);
    length = l;
    width = w;
    col = cl;
    texture = textureToApply;
}


void Cube_face::update(double delta_t)
{
    // Do nothing, no physics associated to a Cube_face
}


void Cube_face::render()
{
    Point p1 = Point();
    Point p2 = p1, p3, p4 = p1;
    p2.translate(length*vdir1);
    p3 = p2;
    p3.translate(width*vdir2);
    p4.translate(width*vdir2);

    Form::render();

    glBindTexture(GL_TEXTURE_2D, this->texture);
    glBegin(GL_QUADS);
    {
        glColor3f(col.r,col.g,col.b);
        glTexCoord2d(0,1);
        glVertex3d(p1.x, p1.y, p1.z);
        glTexCoord2d(0,0);
        glVertex3d(p2.x, p2.y, p2.z);
        glTexCoord2d(1,0);
        glVertex3d(p3.x, p3.y, p3.z);
        glTexCoord2d(1,1);
        glVertex3d(p4.x, p4.y, p4.z);
    }
    glEnd();
}
