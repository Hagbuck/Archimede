#ifndef ANTIHM_H
#define ANTIHM_H

#include <AntTweakBar.h>
#include <stdio.h>
#include "main.h"

/******************************************************************/
/************* CONFIG DEFAULT VALS FOR PREDEF OBJECTS *************/
/******************************************************************/
#define SPEED_DEFAULT 20
#define DENSITE_DEFAULT 20
#define RAYON_DEFAULT 20

#define SPEED_MAX 200
#define SPEED_MIN 10
#define SPEED_STEP 0.5

#define WOOD_DEFAULT_MASSE 15
#define METAL_DEFAULT_MASSE 50
#define CUIVRE_DEFAULT_MASSE 43

void initSS(void);

class antIHM
{
    public:
        antIHM();
        static void buildAntIHM();
        static void buildAntMaterial();
        //static void initSS(void);
        //VARS STRINGS
        //static stringstream  str_wood;

    protected:

    private:
        static void TW_CALL makeBois(void * client);
        static void TW_CALL makeMetal(void * client);
        static void TW_CALL makeCuivre(void * client);
        static void buildLabel();
        //VARS



};

#endif // ANTIHM_H
