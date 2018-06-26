#include "antIHM.h"
#include "main.h"

TwBar *  mainBar =  TwNewBar("~ Archimède - Menu ~");
TwBar *  materialBar =  TwNewBar("~ Archimède - Materials ~");

//LABEL PERS
stringstream stream_vitesse; char * string_vitesse;
stringstream stream_masse;  char * string_masse;
stringstream stream_rayon;   char * string_rayon;
stringstream stream_densite; char * string_densite;

//LABEL MATERIAUX
stringstream stream_wood;   char * string_wood;
stringstream stream_metal;  char * string_metal;
stringstream stream_plastique; char * string_plastique;


antIHM::antIHM()
{
}

void antIHM::buildLabel()
{
    //INIT STREAM
    initSS();

    //BUILD LABELS
    stream_vitesse << "label='Vitesse' min=" << SPEED_MIN << " max=" << SPEED_MAX << " step=" << SPEED_STEP << " keyIncr=o keyDecr=l help='Redéfinir la vitesse.' ";
    stream_masse << "label='Masse' min=" << MASSE_MIN << " max=" << MASSE_MAX << " step=" << MASSE_STEP << " keyIncr=p keyDecr=m help='Redéfinir la masse.' ";
    stream_rayon << "label='Rayon' min="<< RAYON_MIN << " max="<< RAYON_MAX << " step="<< RAYON_STEP << " keyIncr=i keyDecr=k help='Redéfinir le rayon.' ";
    stream_densite << "label='Densité' min="<< DENSITE_MIN << " max=" << DENSITE_MAX << " step=" << DENSITE_STEP << " keyIncr=u keyDecr=j help='Redéfinir la densité du liquide.' ";

    //On les convertie en chaine de caractère

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

}

void antIHM::buildAntMaterial()
{
    //CREATION DES STRINGS

    //fontSize=3 position='180 16' size='270 440' valuesWidth=100 "
    materialBar =  TwNewBar("matBar");
    TwDefine("matBar label='~ Materials ~' position='475 40' size='150 150'");


    TwAddButton(materialBar, "Choississez un matériel", NULL, NULL, " label='Choississez un matériel' ");
    TwAddButton(materialBar, "Bois", makeBois, NULL, " label='Bois' key=1 help='Default Masse : 20' ");
    TwAddButton(materialBar, "Metal", makeMetal, NULL, " label='Metal' key=2 help='Default Masse : 100' ");
    TwAddButton(materialBar, "Cuivre", makeCuivre, NULL, " label='Cuivre' key=3 help='Default Masse : 43' ");
}

void initSS(void) {
    //Initialisation des streams
    stream_vitesse.clear(); stream_vitesse.str("");
    stream_masse.clear();   stream_masse.str("");
    stream_rayon.clear();    stream_rayon.str("");
    stream_densite.clear(); stream_densite.str("");
}


void TW_CALL antIHM::makeBois(void * client){default_val_masse = WOOD_DEFAULT_MASSE;}
void TW_CALL antIHM::makeMetal(void * client){default_val_masse = METAL_DEFAULT_MASSE;}
void TW_CALL antIHM::makeCuivre(void * client){default_val_masse = CUIVRE_DEFAULT_MASSE;}
