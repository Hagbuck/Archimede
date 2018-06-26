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
        virtual void setTranslationSensivity(double sensivity);
        virtual ~TrackBall();

    protected:
        double _motionSensivity;
        double _scrollSensivity;
        double _translationSensitivity;

        bool _holdRight;
        bool _holdLeft;
        double _distance;
        double _angleY;
        double _angleZ;

        double _cibleY;
        double _cibleZ;

    private:
};

#endif // TRACKBALL_H
