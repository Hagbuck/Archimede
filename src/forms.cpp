#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "forms.h"
#include <cstdlib>
#include "sdlglutils.h"

using namespace std;

void Form::setTextureBoolean(bool textureOn)
{
    textureToApply = textureOn;

}

void Form::setOpacity(double opacityToApply)
{
    opacity = opacityToApply;
}

void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Form::render()
{
    Point org = anim.getPos();
    glTranslated(org.x, org.y, org.z);
    glColor3f(1, 1, 1);

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,  texture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glColor3f(col.r, col.g, col.b);

}

Cube_face::Cube_face(Vector v1, Vector v2, Point org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim.setPos(org);
    length = l;
    width = w;
    col = cl;
    textureToApply = true;
}


void Cube_face::update(double delta_t)
{
    // Do nothing, no physics associated to a Cube_face
}


void Cube_face::setTexture(SDL_Surface* surface_texture)
{
    texture = prepareTexture(surface_texture);
}


void Cube_face::render()
{
    glPushMatrix();
    Point p1 = Point();
    Point p2 = p1, p3, p4 = p1;
    p2.translate(length*vdir1);
    p3 = p2;
    p3.translate(width*vdir2);
    p4.translate(width*vdir2);

    Form::render();

    if(textureToApply)
    {
        glBegin(GL_QUADS);
        {
            //glColor3f(col.r,col.g,col.b);
            glTexCoord2d(0,length);
            glVertex3d(p1.x, p1.y, p1.z);
            glTexCoord2d(0,0);
            glVertex3d(p2.x, p2.y, p2.z);
            glTexCoord2d(width,0);
            glVertex3d(p3.x, p3.y, p3.z);
            glTexCoord2d(width,length);
            glVertex3d(p4.x, p4.y, p4.z);
        }
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        {
            glColor4f(col.r,col.g,col.b,0.5);
            glVertex3d(p1.x, p1.y, p1.z);
            glVertex3d(p2.x, p2.y, p2.z);
            glVertex3d(p3.x, p3.y, p3.z);
            glVertex3d(p4.x, p4.y, p4.z);
        }
        glEnd();
    }
    glPopMatrix();

}

Vector Cube_face::getVdir1(void)
{
    return vdir1;
}

Vector Cube_face::getVdir2(void)
{
    return vdir2;
}
