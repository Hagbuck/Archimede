#ifndef TRACKBALL_H
#define TRACKBALL_H
#include <SDL2/SDL.h>

class TrackBall
{
    public:
        TrackBall();

        virtual void OnMouseMotion(const SDL_MouseMotionEvent & event);
        virtual void OnMouseButton(const SDL_MouseButtonEvent & event);
        virtual void OnMouseScroll(const SDL_MouseWheelEvent & event);
        virtual void OnKeyboard(const SDL_KeyboardEvent & event);

        virtual void look();
        virtual void setMotionSensivity(double sensivity);
        virtual void setScrollSensivity(double sensivity);
        virtual ~TrackBall();

    protected:
        double _motionSensivity;
        double _scrollSensivity;
        bool _hold;
        double _distance;
        double _angleY;
        double _angleZ;



    private:
};

#endif // TRACKBALL_H
