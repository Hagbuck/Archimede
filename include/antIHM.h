#ifndef ANTIHM_H
#define ANTIHM_H

#include <AntTweakBar.h>
#include <stdio.h>
#include "main.h"
<<<<<<< HEAD
#include "physic.h"
=======
>>>>>>> origin/dev

/******************************************************************/
/************* CONFIG DEFAULT VALS FOR PREDEF OBJECTS *************/
/******************************************************************/

//DEFAULT VALUES
<<<<<<< HEAD
#define SPEED_DEFAULT 10
#define DENSITE_DEFAULT 1000
#define RAYON_DEFAULT 20.0
#define MASSE_DEFAULT 20

//CONFIG SPEED CONFIG
#define SPEED_MAX 20
#define SPEED_MIN 1
#define SPEED_STEP 0.5

//CONFIG MASSE CONFIG
#define MASSE_MAX 1000.0
#define MASSE_MIN 1.0
#define MASSE_STEP 0.1

//CONFIG RAYON CONFIG
#define RAYON_MAX 100
#define RAYON_MIN 10
#define RAYON_STEP 1

//CONFIG DENSITE CONFIG
#define DENSITE_MAX 10000
#define DENSITE_MIN 100
#define DENSITE_STEP 100
=======
#define SPEED_DEFAULT 20
#define DENSITE_DEFAULT 20
#define RAYON_DEFAULT 20
#define MASSE_DEFAULT 20;

//CONFIG SPEED CONFIG
#define SPEED_MAX 200
#define SPEED_MIN 10
#define SPEED_STEP 0.5

//CONFIG MASSE CONFIG
#define MASSE_MAX 200
#define MASSE_MIN 10
#define MASSE_STEP 0.5

//CONFIG RAYON CONFIG
#define RAYON_MAX 200
#define RAYON_MIN 10
#define RAYON_STEP 0.5

//CONFIG DENSITE CONFIG
#define DENSITE_MAX 200
#define DENSITE_MIN 10
#define DENSITE_STEP 0.5
>>>>>>> origin/dev

//CONFIG SCROLL CONFIG
#define SCROLL_MAX 5
#define SCROLL_MIN 1
#define SCROLL_STEP 0.5

//CONFIG MOUSE CONFIG
#define MOUSE_MAX 5
#define MOUSE_MIN 1
#define MOUSE_STEP 0.5

//CONFIG TRANSLATION CONFIG
#define TRANS_MAX 5
#define TRANS_MIN 1
#define TRANS_STEP 0.5

//CONFIG DEFAULT VALUES BY MAT
<<<<<<< HEAD
#define WOOD_MASS_VOL 610
#define FER_MASS_VOL 7860
#define PVC_MASS_VOL 1380
=======
#define WOOD_DEFAULT_MASSE 30
#define METAL_DEFAULT_MASSE 75
#define PLASTIC_DEFAULT_MASSE 15
>>>>>>> origin/dev

void initSS(void);

class antIHM
{
    public:
        antIHM();
        static void buildAntIHM();
        static void buildAntSensitive();
        //static void initSS(void);
        //VARS STRINGS
        //static stringstream  str_wood;

    protected:

    private:
        static void TW_CALL makeBois(void * client);
        static void TW_CALL makeMetal(void * client);
        static void TW_CALL makePlastic(void * client);
        static void buildLabel();
        //VARS



};

#endif // ANTIHM_H
