#include "TrackBall.h"
#include <SDL2/SDL.h>
#include <GL/GLU.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
using namespace std;

TrackBall::TrackBall()
{
    _holdRight = false;
    _holdLeft = false;
    _angleY = 45;
    _angleZ = 90;
    _distance = 6;
    _motionSensivity = 0.3;
    _scrollSensivity = 1;
    _cibleY = 2;
    _cibleZ = 0;

}
TrackBall::~TrackBall()
{
}


void TrackBall::OnMouseMotion(const SDL_MouseMotionEvent & event)
{
    if (_holdLeft)
    {
        _angleZ += event.xrel*_motionSensivity;
        _angleY += event.yrel*_motionSensivity;
        if (_angleY > 90)
            _angleY = 90;
        else if (_angleY < -90)
            _angleY = -90;
    }
    if (_holdRight)
    {
        _cibleY -= event.xrel * 0.01;
        _cibleZ += event.yrel * 0.01;

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
        if ((_holdLeft)&&(event.type == SDL_MOUSEBUTTONUP))
        {
            _holdLeft = false;
        }
        else if ((!_holdLeft)&&(event.type == SDL_MOUSEBUTTONDOWN))
        {
            _holdLeft = true;
        }
    }
    else if (event.button == SDL_BUTTON_RIGHT)
    {
        if ((_holdRight)&&(event.type == SDL_MOUSEBUTTONUP))
        {
            _holdRight = false;
        }
        else if ((!_holdRight)&&(event.type == SDL_MOUSEBUTTONDOWN))
        {
            _holdRight = true;
        }
    }
}

void TrackBall::OnKeyboard(const SDL_KeyboardEvent & event)
{
    if ((event.type == SDL_KEYDOWN)&&(event.keysym.sym == SDLK_x))
    {
        _angleY = 45;
        _angleZ = 90;
        _distance = 6;
        _cibleY = 2;
        _cibleZ = 0;
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

void TrackBall::setTranslationSensivity(double sensivity)
{
    _translationSensitivity = sensivity;
}

void TrackBall::look()
{
    gluLookAt(_distance,_cibleY,_cibleZ,
              0,_cibleY,_cibleZ,
              0,0,1);
    glRotated(_angleY,0,1,0);
    glRotated(_angleZ,0,0,1);
}
