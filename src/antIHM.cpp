#include "antIHM.h"
#include "main.h"

TwBar *  mainBar =  TwNewBar("~ Archimède - Menu ~");
TwBar *  materialBar =  TwNewBar("~ Archimède - Materials ~");

//VITESSE
stringstream  stream_vitesse; char * string_vitesse;


antIHM::antIHM()
{
}

void antIHM::buildLabel()
{
    //On initie nos objets
    initSS();
    //On construit nos labels
    stream_vitesse << "label='Vitesse' min=" << SPEED_MIN << " max=" << SPEED_MAX << " step=" << SPEED_STEP << " keyIncr=o keyDecr=l help='Redéfinir la vitesse.' ";

    //On les convertie en chaine de caractère

    //VITESSE
    string s_vitesse = stream_vitesse.str();
    string_vitesse = new char[s_vitesse.size() + 1];
    std::copy(s_vitesse.begin(), s_vitesse.end(), string_vitesse);
    string_vitesse[s_vitesse.size()] = '\0';


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
    TwAddVarRW(mainBar, "Masse : ", TW_TYPE_DOUBLE, &default_val_masse,
               "label='Masse' min=1 max=100 step=0.5 keyIncr=p keyDecr=m help='Redéfinir la masse.' ");
    //VITESSE
    TwAddVarRW(mainBar, "Vitesse : ", TW_TYPE_DOUBLE, &default_val_speed,
               string_vitesse);

    //RAYON
    TwAddVarRW(mainBar, "Rayon : ", TW_TYPE_DOUBLE, &default_val_rayon,
               "label='Rayon' min=1 max=100 step=0.5 keyIncr=i keyDecr=k help='Redéfinir le rayon.' ");


    TwAddButton(mainBar, "blank2", NULL, NULL, " label=' ' ");
    TwAddButton(mainBar, "Modifications Liquide", NULL, NULL, " label='Modifications Liquide' ");
    //DENSITE
    TwAddVarRW(mainBar, "Densité : ", TW_TYPE_DOUBLE, &default_val_densite,
               "label='Densité' min=1 max=100 step=0.5 keyIncr=u keyDecr=j help='Redéfinir la densité du liquide.' ");

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
}


void TW_CALL antIHM::makeBois(void * client){default_val_masse = WOOD_DEFAULT_MASSE;}
void TW_CALL antIHM::makeMetal(void * client){default_val_masse = METAL_DEFAULT_MASSE;}
void TW_CALL antIHM::makeCuivre(void * client){default_val_masse = CUIVRE_DEFAULT_MASSE;}
