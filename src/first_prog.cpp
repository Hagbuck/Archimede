// Using SDL, SDL OpenGL and standard IO
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include <AntTweakBar.h>
#include <stdio.h>
#include <string>
#include "main.h"
#include "antIHM.h"
#include <TrackBall.h>
#include "sdlglutils.h"
// Module for space geometry
#include "geometry.h"
// Module for generating and rendering forms
#include "forms.h"

#include "physic.h"

#include "sphere.h"

#include "water.h"


using namespace std;


/***************************************************************************/
/* Constants and functions declarations                                    */
/***************************************************************************/

//IHM VARS (IHM CONSERVE)
double default_val_masse = MASSE_DEFAULT;
double default_val_speed = SPEED_DEFAULT;
double default_val_densite = DEFAULT_WATER_DENSITY;
double default_val_rayon = RAYON_DEFAULT;
//OLD VALUES (USE FOR MAJ BALL)
double old_val_masse = MASSE_DEFAULT;
double old_val_densite = DEFAULT_WATER_DENSITY;
double old_val_rayon = RAYON_DEFAULT;
//SCROLL FUNCTIONS
double default_scroll_sensivity = 2.5;
double default_mouse_sensitivity = 2.5;
double default_translation_sensitivity = 1.5;
//RALENTIT
double ralenti = 1;


SDL_Surface* terre_text = loadTexture("img/herbe.jpg");
SDL_Surface* herbe_text = loadTexture("img/terre.jpg");
SDL_Surface* wood_text = loadTexture("img/wood.jpg");

Sphere* sp = NULL;


// Max number of forms : static allocation
const int MAX_FORMS_NUMBER = 100;

//calcul en ms
const Uint32 ANIM_DELAY = 5;

//Handle for the AntBar
int handledAnt;

// Starts up SDL, creates window, and initializes OpenGL
bool init(SDL_Window** window, SDL_GLContext* context);

// Initializes matrices and clear color
bool initGL();

// Updating forms for animation
void update(Form* formlist[MAX_FORMS_NUMBER], double delta_t);

// Renders scene to the screen
const void render(Form* formlist[MAX_FORMS_NUMBER], const Point &cam_pos, bool show_axes = true);

// Frees media and shuts down SDL
void close(SDL_Window** window);

// Init AntTweakBar
void init_AntTweakBar();

TrackBall * camera;

/***************************************************************************/
/* Functions implementations                                               */
/***************************************************************************/
bool init(SDL_Window** window, SDL_GLContext* context)
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        // Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // Create window
        *window = SDL_CreateWindow( "Archimède Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( *window == NULL )
        {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            // Create context
            *context = SDL_GL_CreateContext(*window);
            if( *context == NULL )
            {
                cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                // Use Vsync
                if(SDL_GL_SetSwapInterval(1) < 0)
                {
                    cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
                }

                // Initialize OpenGL
                if( !initGL() )
                {
                    cout << "Unable to initialize OpenGL!"  << endl;
                    success = false;
                }
            }
        }
    }

    return success;
}


bool initGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;

    // Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport : use all the window to display the rendered scene
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Fix aspect ratio and depth clipping planes
    gluPerspective(40.0, (GLdouble)SCREEN_WIDTH/SCREEN_HEIGHT, 1.0, 100.0);


    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Initialize clear color : black with no transparency
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    // Activate Z-Buffer


    // Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        cout << "Error initializing OpenGL!  " << gluErrorString( error ) << endl;
        success = false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable ( GL_COLOR_MATERIAL ) ;


   //TEST  LUMIERE INTERFACE
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    double a=0;
    //Position de la lumiere
    int LightPos[4] = {2,-20,-10,1};
    // ????
    int MatSpec [4] = {1,1,1,1};
    glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,6,6,0,0,0,0,1,0);
    glRotated(a,0,1,0);
    glLightiv(GL_LIGHT0,GL_POSITION,LightPos);

    return success;
}

void update(Form* formlist[MAX_FORMS_NUMBER], double delta_t)
{
    // Update the list of forms
    unsigned short i = 0;
    while(formlist[i] != NULL)
    {
        formlist[i]->update(delta_t);
        i++;
    }
}

const void render(Form* formlist[MAX_FORMS_NUMBER], const Point &cam_pos, bool show_axes)
{
    // Clear color buffer and Z-Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    camera->look();

    glPushMatrix(); // Preserve the camera viewing point for further forms

    if(show_axes)
    {
         // X, Y and Z axis
        glPushMatrix(); // Preserve the camera viewing point for further forms
        // Render the coordinates system
        glBegin(GL_LINES);
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3i(0, 0, 0);
            glVertex3i(1, 0, 0);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3i(0, 0, 0);
            glVertex3i(0, 1, 0);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3i(0, 0, 0);
            glVertex3i(0, 0, 1);
        }
        glEnd();
        glPopMatrix(); // Restore the camera viewing point for next object
    }

    // Render the list of forms
    unsigned short i = 0;
    while(formlist[i] != NULL)
    {
        glPushMatrix(); // Preserve the camera viewing point for further forms
        formlist[i]->render();
        glPopMatrix(); // Restore the camera viewing point for next object
        i++;
    }
}

void close(SDL_Window** window)
{
    //Destroy window
    SDL_DestroyWindow(*window);
    *window = NULL;
     delete camera;
    //Quit SDL subsystems
    SDL_Quit();
}


/***************************************************************************/
/* MAIN Function                                                           */
/***************************************************************************/
int main(int argc, char* args[])
{
    // The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    // OpenGL context
    SDL_GLContext gContext;


    // Start up SDL and create window
    if( !init(&gWindow, &gContext))
    {
        cout << "Failed to initialize!" << endl;
    }
    else
    {
        //INIT ANT WINDOWS
        if(!TwInit(TW_OPENGL, NULL))
        {
            printf("[ERROR] - Impossible d'initialiser l'IHM Ant.");
            return false;
        }
        //DISPLAY IHMS
        TwWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
        antIHM::buildAntIHM();
        antIHM::buildAntSensitive();
        // Main loop flag
        bool quit = false;
        Uint32 current_time, previous_time, elapsed_time;

        // Event handler
        SDL_Event event;

        // Camera position
        camera = new TrackBall();
        camera->setScrollSensivity(0.2);
        camera->setMotionSensivity(0.5);
        camera->setTranslationSensivity(0.001);

        // The forms to render
        Form* forms_list[MAX_FORMS_NUMBER];
        unsigned short number_of_forms = 0, i;
        for (i=0; i<MAX_FORMS_NUMBER; i++)
        {
            forms_list[i] = NULL;
        }




        Water* water = new Water();


        sp = new Sphere(water, RAYON_DEFAULT / 100.0, MASSE_DEFAULT, Point(2,1.5,2));
        sp->setTextureBoolean(true);
        sp->setTexture(wood_text);
        forms_list[number_of_forms] = sp;
        number_of_forms++;


        //surface
        Cube_face *ground_zero = NULL;
        Cube_face *ground_two = NULL;
        Cube_face *ground_three = NULL;

        //profondeur
        Cube_face *prof_zero = NULL;
        Cube_face *prof_one = NULL;
        Cube_face *prof_two = NULL;
        Cube_face *prof_three = NULL;
        Cube_face *prof_four = NULL;
        Cube_face *prof_five = NULL;
        Cube_face *prof_six = NULL;
        Cube_face *prof_seven = NULL;
        Cube_face *prof_eight = NULL;

        //fond
        Cube_face *fond_zero = NULL;
        Cube_face *fond_one = NULL;

        //Test
        Cube_face *water_surface = NULL;
        Cube_face *water_coupe = NULL;


        const double LARGEUR_SCENE = 4.0;
        const double LONGUEUR_SCENE = 3;
        const double PROFONDEUR_SCENE = 3;

        const double LARGEUR_BORD_SURFACE = 0.5;
        const double LONGUEUR_BORD_SURFACE = 1;

        const double PROFONDEUR_BASSIN = 2.5;





        //Surface
        ground_zero = new Cube_face(Vector(1,0,0), Vector(0,1,0), Point(0,0,0),0.5,3,GREEN);
        ground_two = new Cube_face(Vector(1,0,0), Vector(0,1,0), Point(3.5,0,0),0.5,3,GREEN);
        ground_three = new Cube_face(Vector(1,0,0), Vector(0,1,0), Point(0.5,2,0),3,1,GREEN);


        // Profondeur
        prof_zero = new Cube_face(Vector(0,1,0), Vector(0,0,-1), Point(0,0,0),3,3,Color(0.6,0.4,0));
        prof_one = new Cube_face(Vector(0,1,0), Vector(0,0,-1), Point(4,0,0),3,3,Color(0.6,0.4,0));
        prof_two = new Cube_face(Vector(1,0,0), Vector(0,0,-1), Point(0,3,0),4,3,Color(0.6,0.4,0));
        prof_three = new Cube_face(Vector(1,0,0), Vector(0,0,-1), Point(0.5,2,0),3,2.5,BLUE);
        prof_four = new Cube_face(Vector(0,1,0), Vector(0,0,-1), Point(0.5,0,0),2,2.5,BLUE);
        prof_five = new Cube_face(Vector(0,1,0), Vector(0,0,-1), Point(3.5,0,0),2,2.5,BLUE);
        prof_six = new Cube_face(Vector(1,0,0), Vector(0,0,-1), Point(0,0,0),0.5,3,Color(0.6,0.4,0));
        prof_seven = new Cube_face(Vector(1,0,0), Vector(0,0,-1), Point(3.5,0,0),0.5,3,Color(0.6,0.4,0));
        prof_eight = new Cube_face(Vector(1,0,0), Vector(0,0,1), Point(0.5,0,-3),3,0.5,Color(0.6,0.4,0));

        //fond
        fond_zero = new Cube_face(Vector(1,0,0), Vector(0,1,0), Point(0,0,-3),4,3,Color(0,0.4,0.4));
        fond_one = new Cube_face(Vector(1,0,0), Vector(0,1,0), Point(0.5,0,-2.5),3,3,Color(0,0.4,0.4));



        water_surface = new Cube_face(Vector(1,0,0), Vector(0,1,0), Point(0.5,0,0),3,2,BLUE);
        water_surface->setTextureBoolean(false);

        water_coupe = new Cube_face(Vector(1,0,0), Vector(0,0,-1), Point(0.5,0,0),3,2.5,BLUE);
        water_coupe->setTextureBoolean(false);

        ground_zero->setTexture(herbe_text);
        ground_two->setTexture(herbe_text);
        ground_three->setTexture(herbe_text);

        prof_zero->setTexture(terre_text);
        prof_one->setTexture(terre_text);
        prof_two->setTexture(terre_text);

        prof_three->setTexture(terre_text);
        prof_four->setTexture(terre_text);
        prof_five->setTexture(terre_text);
        prof_six->setTexture(terre_text);
        prof_seven->setTexture(terre_text);
        prof_eight->setTexture(terre_text);

        fond_zero->setTexture(terre_text);
        fond_one->setTexture(terre_text);

        forms_list[number_of_forms] = ground_zero;
        number_of_forms++;
        forms_list[number_of_forms] = ground_two;
        number_of_forms++;
        forms_list[number_of_forms] = ground_three;
        number_of_forms++;


        forms_list[number_of_forms] = prof_zero;
        number_of_forms++;
        forms_list[number_of_forms] = prof_one;
        number_of_forms++;
        forms_list[number_of_forms] = prof_two;
        number_of_forms++;
        forms_list[number_of_forms] = prof_three;
        number_of_forms++;
        forms_list[number_of_forms] = prof_four;
        number_of_forms++;
        forms_list[number_of_forms] = prof_five;
        number_of_forms++;
        forms_list[number_of_forms] = prof_six;
        number_of_forms++;
        forms_list[number_of_forms] = prof_seven;
        number_of_forms++;
        forms_list[number_of_forms] = prof_eight;
        number_of_forms++;
        forms_list[number_of_forms] = fond_zero;
        number_of_forms++;
        forms_list[number_of_forms] = fond_one;
        number_of_forms++;
        forms_list[number_of_forms] = water_surface;
        number_of_forms++;
        forms_list[number_of_forms] = water_coupe;
        number_of_forms++;

        // Get first "current time"
        previous_time = SDL_GetTicks();
        // While application is running
        while(!quit)
        {
            while(SDL_PollEvent(&event) ) //!=0
            {
                int x = 0, y = 0;
                SDL_Keycode key_pressed = event.key.keysym.sym;

                // send event to AntTweakBar
                handledAnt = TwEventSDL(&event ,SDL_MAJOR_VERSION, SDL_MINOR_VERSION);

                if( ! handledAnt ) // !handledAnt // if event has not been handled by AntTweakBar, process it
                {

                    switch(event.type)
                    {
                    // User requests quit
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;

                    case SDL_MOUSEMOTION:
                            camera->OnMouseMotion(event.motion);
                            break;

                    case SDL_MOUSEBUTTONUP:
                    case SDL_MOUSEBUTTONDOWN:
                        camera->OnMouseButton(event.button);
                        break;

                    case SDL_MOUSEWHEEL:
                        camera->OnMouseScroll(event.wheel);
                        break;

                    case SDL_KEYDOWN:
                    // Handle key pressed with current mouse position
                        SDL_GetMouseState( &x, &y );
                        switch(key_pressed)
                        {
                            case SDLK_q:
                            case SDLK_ESCAPE:
                                quit = true;
                                break;
                            case SDLK_SPACE:
                            // On reset la position de la sphère
                            sp->resetPosition();
                            break;
                            case SDLK_x:
                                camera->OnKeyboard(event.key);
                                break;
                            default:
                                break;
                        }
                    }

                }
            }

            // Update the scene
            current_time = SDL_GetTicks(); // get the elapsed time from SDL initialization (ms)

            elapsed_time = current_time - previous_time;
            if (elapsed_time > ANIM_DELAY)
            {
                previous_time = current_time;
                update(forms_list, 1e-3 * ralenti * elapsed_time); //RA
            }
            camera->setScrollSensivity(default_scroll_sensivity / 10 );
            camera->setMotionSensivity(default_mouse_sensitivity / 10);
            camera->setTranslationSensivity(default_translation_sensitivity / 100);
            // Render the scene
            Point camera_position(0,0,4);
            render(forms_list, camera_position, false);

            // /!\ DON'T MOVE IT
            TwDraw();

            // Update window screen
            SDL_GL_SwapWindow(gWindow);
        }
        //delete sp;
        SDL_FreeSurface(terre_text);
        SDL_FreeSurface(herbe_text);

    }

    // Free resources and close SDL
    TwTerminate();
    close(&gWindow);

    return 0;
}
