#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/* Constantes de charles */

#define GROUND 416
#define OUTSCREEN 672

#define TEMPS_LATENCE 600

#define TEMPS_TIR_ENNEMI 1000

#define TEMPS_TIR_BOSS 500

enum {vers_gauche, vers_gauche_bas, vers_bas, vers_droite_bas,
        vers_droite, vers_haut_droite, vers_gauche_haut, vers_haut};

enum {tank1, tank2, tank3, tank4, tank5};

enum {avion1, avion2, avion3, avion4, avion5, avion6, avion7,
        avion8, avion9, avion10, avion11, avion12, avion42, avion43};

enum {poser, decolle};

enum {Gauche, Bas, Droite, Haut};

enum {gauche_avance, gauche, gauche_recule, centre_gauche,
        centre, centre_droite, droite_avance, droite,
        droite_recule, latence_droite, latence_bas, latence_gauche};

enum {otage1, otage2, otage3, otage4, otage5};

enum {boss1, boss2, boss3, boss4, boss5, boss6, boss7, boss8, boss9};

/* Fin constante et définition de charles */


/* Constante et definition de charle de charles a detailer par lui même */
/* Fin des constantes et definition de charles */

/* Resolution d'ecran */

#define LARGEUR_ECRAN 600
#define LONGEUR_ECRAN 800

/* Resolution des Tiles */

#define SPRITE_RESOLUTION 50

/* Nombres de Sprites */

#define NOMBRE_ZONE_LONGEUR 10

/* Resolution de la Grande map */

#define LONGEUR_TOTAL_MAP (LONGEUR_ECRAN / SPRITE_RESOLUTION)
#define LARGEUR_TOTAL_MAP (LARGEUR_ECRAN / SPRITE_RESOLUTION)

/* Defintiion des Zone de combat */

#define ZONE_BASSE (LARGEUR_ECRAN / 2)
#define ZONE_HAUTE (LARGEUR_ECRAN / 2)

/* Definition de la vitesse de jeu */

#define VITESSE_HELICOPTER 7

#define VITESSE_BALLE 45

#define VITESSE_B_ENNEMI 30

#define VITESSE_SCROLLING 10

#define VITESSE_ENNEMIES_AVION 350

#define VITESSE_ENNEMIES_TANK 400

#define VITESSE_CIVIL 150

#define VITESSE_SOUCOUPE 100

#define VITESSE_ENNEMIE_BOSS 150

#define NOMBRES_ENEMIES 10

#define NOMBRES_BATIMENT 12

#define NOMBRE_VIE_BOSS 30

#define NOMBRE_VIE_HELICOPTER 5

#define NOMBRE_PASSAGER_MAX 16

#define FREQUENCE_SOUCOUPE 15000 // Faire generer les soucoupes toutes les 15000ms = 15 secs

#define FREQUENCE_AVION 8000 // Faire generer les avions toutes les 8000 ms = 8s

#define FREQUENCE_TANK 5000 // Faire generer les tanks toutes les 5000 ms = 5s

#define NOMBRE_VIE_AVION 5

#define NOMBRE_VIE_TANK 5

/* les differents parametres sur l'écran */

typedef struct Ecran
{
    SDL_Surface *ecran;
    SDL_Surface *menuPrincipale;
    SDL_Surface *gameOver;
    SDL_Surface *hand;

    /* Déclaration de notre police de caractères */
    TTF_Font *font;
    /* Déclaration de notre objet systeme */
    FMOD_SYSTEM *system;

    int save;
    int reinitialise;
    int continuer; // Boucle menu Principale
    int menu; // Variable qui sert à rien juste pour choisir le menu au debut (switch)
    int jeu; // Boucle principale du jeu
    int menuPause;

    int nombreTank;
    int nombreAvion;
    int nombreSoucoupe;
    int nombreOtage;
    int nombreBoss;
    int collision;
    int rejouer;

    unsigned int frameLimit;

    // Temps d'affichage du Game Over
    int terminer;
    unsigned int timeOver;

    // SONS
    FMOD_SOUND *musicmenu;
    FMOD_SOUND *musicgame;
    FMOD_SOUND *batisplosion;
    FMOD_SOUND *civildown;
}Ecran;

    //Channel de FMOD
    //Channel de FMOD
typedef struct Chan {
    FMOD_CHANNEL *channelmusic;
    FMOD_CHANNEL *channelfly;

    FMOD_CHANNEL *channeltir_helico;
    FMOD_CHANNEL *channeltir_tank;
    FMOD_CHANNEL *channeltir_avion;

    FMOD_CHANNEL *channelexplo_helico;
    FMOD_CHANNEL *channelexplo_tank;
    FMOD_CHANNEL *channelexplo_avion;
    FMOD_CHANNEL *channelexplo_soucoupe;
    FMOD_CHANNEL *channelexplo_batiment;

    FMOD_CHANNEL *channelcivildown;

    FMOD_CHANNEL *channeltirboss;

    FMOD_CHANNELGROUP *groupshot;
    FMOD_CHANNELGROUP *groupexplo;
    FMOD_CHANNELGROUP *groupimpact;


    FMOD_SOUND *tir;
    FMOD_SOUND *tir2;
    FMOD_SOUND *tir3;
    FMOD_SOUND *tir4;


}Chan;

/* les touches du clavier */

typedef struct Clavier
{
    int Centre;
    int Left;
    int Right;
    int tir;
    int bouttonE, bouttonR, bouttonT;
}Clavier;

typedef struct Souris
{
    int clickGauche;
    int clickDroit;
}Souris;

/* Nos Sprites */

typedef struct Sprite
{
    SDL_Surface *blanc;
    SDL_Surface *sol;
    SDL_Surface *arbreV;
    SDL_Surface *arbreM;
    SDL_Surface *maison[2];

    SDL_Surface *impact;

    SDL_Surface *spriteActuel;

    int objetActuel;
}Sprite;

typedef struct Chargement
{
    int Blanc;
    int Base;
    int Sol;
    int ArbreV;
    int ArbreM;
    int Maison;
    int MaisonD;
    int Atterissage;
    int Tank;
    int Avion;
    int Alien;
    int Otage;
    int Boss;
}Chargement;

typedef struct Helicopter
{
    SDL_Surface *helicopter[11];

    /* Image de l'hélicopter courant */
    SDL_Surface *heli;

    int position;

    int passagers;
    int poser;

    int canon;
    int tirprec;
    int descends;
    int nombreVie;
    int vie;

    /* Variable token pour la collision avec les soucoupes volantes */

    int toucheSoucoupe;

    int tpscollision;
    int latence;
    int latencemort;
    int etatmort;

    int zone; // C'est pour savoir dans quelle partie de l'ecran on n'est (voir fontion trouverZoneHelicopter()) "PM"
    /* Cordonnée de l'hélicopter */
    int x;
    int y;

    // Sons
    FMOD_SOUND *tirCanon;
    FMOD_SOUND *vole;
    FMOD_SOUND *explose;
}Helicopter;

typedef struct Life {
    SDL_Surface *vie;
    int x;
    int y;
}Life;

typedef struct Hp {
    SDL_Surface *pv;
    int x;
    int y;
}Hp;

/* Structures qui contient les ennemies */

typedef struct CTank
{
    SDL_Surface *BTank[5];
    SDL_Surface *tankActuel;
    int x;
    int y;
    int debutZone;
    int finZone;
    int zone;
    int direction;
    int position;
    unsigned int frameLimit;
    unsigned int tempGeneration;
    unsigned int tempsMort;
    int tir;

    unsigned int tirprec;
    int nombreVie;

    //Sons
 	FMOD_SOUND *tirCanon;
    FMOD_SOUND *explose;
}CTank;

typedef struct Plane
{
    SDL_Surface *plane[14];
    SDL_Surface *planeActuel;
    int x;
    int y;
    int zone;
    int debutZone;
    int finZone;
    int direction;
    int limiteZone;
    int position;
    unsigned int tempsMort;
    unsigned int tempGeneration;
    unsigned int frameLimit;
    unsigned int tirprec;

    /* Toute cette partie concerne l'IA "PM" */

    int nombreVie;
    int tir;

    int modeCombat;
    // On peut choisir un mode de combat entre 0 ou 1 et le nombre de phase
    int mode;
    int nombrePhase;

    // Sons
    FMOD_SOUND *tirCanon;
    FMOD_SOUND *explose;
}Plane;

typedef struct Alien
{
    SDL_Surface *alien;
    int x;
    int y;
    int debutZone;
    int finZone;
    int zone;
    int nombreVie;
    unsigned int tempsMort;
    unsigned int tempGeneration;
    unsigned int frameLimit;
    int direction;

    //Sons
    FMOD_SOUND *explose;
}Alien;


typedef struct Bullet
{
    SDL_Surface *Bullet;

    int shot;
    int direction;
    int x;
    int y;
}Bullet;

/* la map */

typedef struct Map
{
    SDL_Surface *background;
    SDL_Surface *coeur;

    int debutX;
    int finX;
    int spriteX;
    int sprite[LARGEUR_TOTAL_MAP][LONGEUR_TOTAL_MAP*NOMBRE_ZONE_LONGEUR];
    int mapEnCours[LARGEUR_TOTAL_MAP][LONGEUR_TOTAL_MAP];
    int bouge;
}Map;

/* structure qui gerer les otatges */

typedef struct Otage
{
    SDL_Surface *otage[5];
    SDL_Surface *otageActuel;

    int x;
    int y;
    /* On vas stocker les coordonnées de nos 10 batiments dans un tableau lors du chargement */
    int batiment[10][4];
    int nombreBatiment;
    int nombreOtage[10];
    int debutZone;
    int finZone;
    int zone;
    int direction;
    int position;

    int MIA; // compte les otages tués
    int saved;

    int vershelico;
    int bougevers;
    int totalCivil[10];
    int nombreVie[10]; // Il faut le mettre à la géneration chaque fois qu'un otage est generé pour que la même instance du batiment ait une vie pour chaque x16

    unsigned int frameLimit;
    unsigned int tempsMort;

    SDL_Surface *civilsauve;
    SDL_Surface *civiltue;
    SDL_Surface *civilchopper;

    SDL_Surface *imgsauve;
    SDL_Surface *imgtue;
    SDL_Surface *imgchopper;
}Otage;

typedef struct Mechant
{
    SDL_Surface *sangohan[9];
    SDL_Surface *sangohanActuel;
    int x;
    int y;
    int zone;
    int debutZone;
    int finZone;
    int direction;
    int limiteZone;
    int position;
    unsigned int tempsMort;
    unsigned int frameLimit;
    unsigned int tirprec;
    int apparition;
    //int tirCanon;
    /* Toute cette partie concerne l'IA "PM" */

    int nombreVie;
    int tir;

    int modeCombat;
    // On peut choisir un mode de combat entre 0 ou 1 et le nombre de phase
    int mode;
    int nombrePhase;

    FMOD_SOUND *tirCanon;
}Mechant;

typedef struct Base
{
    SDL_Surface *base;
    SDL_Surface *atterissage;
    int xA;
    int yA;
    int xB;
    int yB;

    int civilSauver;
    int debarquement;
}Base;


Ecran fenetre;
Clavier clavier;
Map map;
Sprite sprite;
Chargement valeurSprite;

Life life[3];
Hp hp[5];

Souris souris;
Helicopter choplifter;
Bullet balle[3];
CTank tank;
Plane avion;
Alien soucoupe;
Otage civil;
Mechant boss;
Base safe;
Chan channel;

#endif // CONSTANTES_H_INCLUDED
