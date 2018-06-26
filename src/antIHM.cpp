#include "antIHM.h"
#include "main.h"

TwBar *  mainBar =  TwNewBar("~ Archimède - Menu ~");
TwBar *  sensitiveBar =  TwNewBar("~ Archimède - Sensibilité ~");

//LABEL PERS
stringstream stream_vitesse; char * string_vitesse;
stringstream stream_masse;  char * string_masse;
stringstream stream_rayon;   char * string_rayon;
stringstream stream_densite; char * string_densite;

//LABEL MATERIAUX
stringstream stream_wood;   char * string_wood;
stringstream stream_metal;  char * string_metal;
stringstream stream_plastique; char * string_plastique;

//LABEL SOURIS
stringstream stream_scroll; char * string_scroll;
stringstream stream_mouse;  char * string_mouse;
stringstream stream_translation;    char * string_translation;


antIHM::antIHM()
{
}

void antIHM::buildLabel()
{
    //INIT STREAM
    initSS();

    //BUILD LABELS PERS
    stream_vitesse << "label='Vitesse' min=" << SPEED_MIN << " max=" << SPEED_MAX << " step=" << SPEED_STEP << " keyIncr=o keyDecr=l help='Redéfinir la vitesse.' ";
    stream_masse << "label='Masse' min=" << MASSE_MIN << " max=" << MASSE_MAX << " step=" << MASSE_STEP << " keyIncr=p keyDecr=m help='Redéfinir la masse.' ";
    stream_rayon << "label='Rayon' min="<< RAYON_MIN << " max="<< RAYON_MAX << " step="<< RAYON_STEP << " keyIncr=i keyDecr=k help='Redéfinir le rayon.' ";
    stream_densite << "label='Densité' min="<< DENSITE_MIN << " max=" << DENSITE_MAX << " step=" << DENSITE_STEP << " keyIncr=u keyDecr=j help='Redéfinir la densité du liquide.' ";

    //BUILDL LABELS MAT
    stream_wood << "label='Bois' key=1 help='Default Masse : " << WOOD_DEFAULT_MASSE << "' ";
    stream_metal << "label='Metal' key=2 help='Default Masse : " << METAL_DEFAULT_MASSE << "' ";
    stream_plastique << "label='Plastique' key=3 help='Default Masse : " << PLASTIC_DEFAULT_MASSE << "' ";

    //BUILD SOURIS
    stream_scroll << "label='Scroll' min=" << SCROLL_MIN << " max=" << SCROLL_MAX << " step=" << SCROLL_STEP << " keyIncr=y keyDecr=h help='Modifier la sensibilité du scroll.' ";
    stream_mouse << "label='Mouse' min=" << MOUSE_MIN << " max=" << MOUSE_MAX << " step=" << MOUSE_STEP << " keyIncr=t keyDecr=g help='Modifier la sensibilité de la souris.' ";
    stream_translation << "label='Translation' min=" << TRANS_MIN << " max=" << TRANS_MAX << " step=" << TRANS_STEP << " keyIncr=r keyDecr=f help='Modifier la sensibilité de la translation.' ";

    //CONVERT VITESSE
    string s_vitesse = stream_vitesse.str();
    string_vitesse = new char[s_vitesse.size() + 1];
    std::copy(s_vitesse.begin(), s_vitesse.end(), string_vitesse);
    string_vitesse[s_vitesse.size()] = '\0';

    //CONVERT MASSE
    string s_masse = stream_masse.str();
    string_masse = new char[s_masse.size() + 1];
    std::copy(s_masse.begin(), s_masse.end(), string_masse);
    string_masse[s_masse.size()] = '\0';

    //CONVERT RAYON
    string s_rayon = stream_rayon.str();
    string_rayon = new char[s_rayon.size() + 1];
    std::copy(s_rayon.begin(), s_rayon.end(), string_rayon);
    string_rayon[s_rayon.size()] = '\0';

    //CONVERT DENSITE
    string s_densite = stream_densite.str();
    string_densite = new char[s_densite.size() + 1];
    std::copy(s_densite.begin(), s_densite.end(), string_densite);
    string_densite[s_densite.size()] = '\0';

    //CONVERT METAL
    string s_metal = stream_metal.str();
    string_metal = new char[s_metal.size() + 1];
    std::copy(s_metal.begin(), s_metal.end(), string_metal);
    string_metal[s_metal.size()] = '\0';

    //CONVERT PLASTIQUE
    string s_plastic = stream_plastique.str();
    string_plastique = new char[s_plastic.size() + 1];
    std::copy(s_plastic.begin(), s_plastic.end(), string_plastique);
    string_plastique[s_plastic.size()] = '\0';

    //CONVERT BOIS
    string s_wood = stream_wood.str();
    string_wood = new char[s_wood.size() + 1];
    std::copy(s_wood.begin(), s_wood.end(), string_wood);
    string_wood[s_wood.size()] = '\0';

    //CONVERT SCROOL
    string s_scroll = stream_scroll.str();
    string_scroll = new char[s_scroll.size() + 1];
    std::copy(s_scroll.begin(), s_scroll.end(), string_scroll);
    string_scroll[s_scroll.size()] = '\0';

    //CONVERT MOUSE
    string s_mouse = stream_mouse.str();
    string_mouse = new char[s_mouse.size() + 1];
    std::copy(s_mouse.begin(), s_mouse.end(), string_mouse);
    string_mouse[s_mouse.size()] = '\0';

    //CONVERT TRANSLATION
    string s_trans = stream_translation.str();
    string_translation = new char[s_trans.size() + 1];
    std::copy(s_trans.begin(), s_trans.end(), string_translation);
    string_translation[s_trans.size()] = '\0';

}

void antIHM::buildAntIHM()
{
    buildLabel();

    mainBar =  TwNewBar("~ Archimède - Menu ~");
    //DESIGN
    TwDefine(" GLOBAL help='Ce projet est une simulation 3D simplifié de la poussée d'Archimède. \n ");

    TwAddButton(mainBar, "blank", NULL, NULL, " label=' ' ");
    TwAddButton(mainBar, "Modifications Objet", NULL, NULL, " label='Modifications Objet' ");

    //MASSE
    TwAddVarRW(mainBar, "Masse : ", TW_TYPE_DOUBLE, &default_val_masse,string_masse);
    //VITESSE
    TwAddVarRW(mainBar, "Vitesse : ", TW_TYPE_DOUBLE, &default_val_speed, string_vitesse);
    //RAYON
    TwAddVarRW(mainBar, "Rayon : ", TW_TYPE_DOUBLE, &default_val_rayon, string_rayon);


    TwAddButton(mainBar, "blank2", NULL, NULL, " label=' ' ");
    TwAddButton(mainBar, "Modifications Liquide", NULL, NULL, " label='Modifications Liquide' ");

    //DENSITE
    TwAddVarRW(mainBar, "Densité : ", TW_TYPE_DOUBLE, &default_val_densite,string_densite);

    TwAddButton(mainBar, "blank3", NULL, NULL, " label=' ' ");

    //MATERIAL
    TwAddButton(mainBar, "Choississez un matériel", NULL, NULL, "label='Choississez un matériel' ");
    TwAddButton(mainBar, "Bois", makeBois, NULL, string_wood);
    TwAddButton(mainBar, "Metal", makeMetal, NULL, string_metal);
    TwAddButton(mainBar, "Plastique", makePlastic, NULL, string_plastique);

}

void antIHM::buildAntSensitive()
{
    //CREATION DES STRINGS
    sensitiveBar = TwNewBar("sensibi");
    TwDefine("sensibi label='~ Sensibilité ~' position='1000 40' size='200 150'");

    TwAddVarRW(sensitiveBar, "Scroll : ", TW_TYPE_DOUBLE, &default_scroll_sensivity,string_scroll);
    TwAddVarRW(sensitiveBar, "Mouse : ", TW_TYPE_DOUBLE, &default_mouse_sensitivity,string_mouse);
    TwAddVarRW(sensitiveBar, "Translation : ", TW_TYPE_DOUBLE, &default_translation_sensitivity,string_translation);

}



void initSS(void) {
    //Initialisation des streams
    stream_vitesse.clear(); stream_vitesse.str("");
    stream_masse.clear();   stream_masse.str("");
    stream_rayon.clear();    stream_rayon.str("");
    stream_densite.clear(); stream_densite.str("");
    stream_scroll.clear();  stream_scroll.str("");
    stream_mouse.clear();  stream_mouse.str("");
    stream_translation.clear(); stream_translation.str("");
}


void TW_CALL antIHM::makeBois(void * client){default_val_masse = WOOD_DEFAULT_MASSE;}
void TW_CALL antIHM::makeMetal(void * client){default_val_masse = METAL_DEFAULT_MASSE;}
void TW_CALL antIHM::makePlastic(void * client){default_val_masse = PLASTIC_DEFAULT_MASSE;}
