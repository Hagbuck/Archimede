#include "TrackBall.h"
#include <SDL2/SDL.h>
#include <GL/GLU.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
using namespace std;

TrackBall::TrackBall()
{
    _hold = false;
    _angleY = 0;
    _angleZ = 0;
    _distance =4;
    _motionSensivity = 0.3;
    _scrollSensivity = 1;

}
TrackBall::~TrackBall()
{
}


void TrackBall::OnMouseMotion(const SDL_MouseMotionEvent & event)
{
    if (_hold)
    {
        _angleZ += event.xrel*_motionSensivity;
        _angleY += event.yrel*_motionSensivity;
        if (_angleY > 90)
            _angleY = 90;
        else if (_angleY < -90)
            _angleY = -90;
    }
}

void TrackBall::OnMouseScroll(const SDL_MouseWheelEvent & event)
{
    if(event.y > 0) // scroll up
    {
        _distance -= _scrollSensivity;
        if (_distance < 0.1)
            _distance = 0.1;
    }
    else if(event.y < 0) // scroll down
    {
         _distance += _scrollSensivity;
    }
}


void TrackBall::OnMouseButton(const SDL_MouseButtonEvent & event)
{
    if (event.button == SDL_BUTTON_LEFT)
    {
        if ((_hold)&&(event.type == SDL_MOUSEBUTTONUP))
        {
            _hold = false;
        }
        else if ((!_hold)&&(event.type == SDL_MOUSEBUTTONDOWN))
        {
            _hold = true;
        }
    }
}

void TrackBall::OnKeyboard(const SDL_KeyboardEvent & event)
{
    if ((event.type == SDL_KEYDOWN)&&(event.keysym.sym == SDLK_x))
    {
        _angleY = 0;
        _angleZ = 0;
    }
}

void TrackBall::setMotionSensivity(double sensivity)
{
    _motionSensivity = sensivity;
}

void TrackBall::setScrollSensivity(double sensivity)
{
    _scrollSensivity = sensivity;
}

void TrackBall::look()
{
    gluLookAt(_distance,0,0,
              0,0,0,
              0,0,1);
    glRotated(_angleY,0,1,0);
    glRotated(_angleZ,0,0,1);
}
