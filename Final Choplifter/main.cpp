#include <stdio.h>
#include <Stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Nom : TRAORE Oumar
   Rôle Par défaut : Projet Manager
   Date de Création : 4/10/2013
   Date de dernier modif : 4/10/2013

   Motif :
   Rôle du Module : Fonction Main Principale
*/

#include <SDL.h>

/* Inclusion de bibliothèques supplementaires */

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fmod.h>
#include "constantes.h"

/* prototype des fonctions qui ne veulent pas suivre les phases "PM" */

void shot2();
void shot3();
void shot4();
void saveMap();
void reinitialiseMap();
void shot();
void trouverZoneHelicopter();
void collisionTirHelicopter(int x, int y);
void choixModeAvion();
void trouverZoneAvion();
void collisionDetected();
void collisionCrash();
void embarquerOtage();

/* Phase 1 d'initialisation */

void initiSprite()
{
    sprite.blanc = IMG_Load("graphics/blanc.png");
    sprite.sol = IMG_Load("graphics/Sprite/sol.png");
    sprite.arbreV = IMG_Load("graphics/Sprite/arbreV.png");
    SDL_SetColorKey(sprite.arbreV, SDL_SRCCOLORKEY, SDL_MapRGB(sprite.arbreV->format, 255, 255, 255));
    sprite.arbreM = IMG_Load("graphics/Sprite/arbreM.png");
    sprite.maison[1] = IMG_Load("graphics/Sprite/maison1.png");
    sprite.maison[0] = IMG_Load("graphics/Sprite/maison2.png");
    sprite.impact = IMG_Load("graphics/Sprite/impact.png");
    /* Fin charles content */
}

void initiChargementSprite()
{
    valeurSprite.Blanc = 0;
    valeurSprite.Base = 1;
    valeurSprite.Sol = 2;
    valeurSprite.ArbreV = 3;
    valeurSprite.ArbreM = 4;
    valeurSprite.Maison = 5;
    valeurSprite.Tank = 6;
    valeurSprite.Avion = 7;
    valeurSprite.Atterissage = 8;
    valeurSprite.MaisonD = 9;
    valeurSprite.Otage = 10;
    valeurSprite.Boss = 11;
    valeurSprite.Alien = 12;
}

/* Initialisation des balles */

void initiBalle()
{
    int i;
    for(i=0; i<3; i++)
    {
        balle[i].Bullet = IMG_Load("graphics/Balle/bullet.png");
        balle[i].shot = 0;
    }
}

void initiOtage() {
    civil.otage[otage1] = IMG_Load("graphics/Civil/civil1.png");
    civil.otage[otage2] = IMG_Load("graphics/Civil/civil2.png");
    civil.otage[otage3] = IMG_Load("graphics/Civil/civil3.png");
    civil.otage[otage4] = IMG_Load("graphics/Civil/civil4.png");
    civil.otage[otage5] = IMG_Load("graphics/Civil/civil5.png");

    civil.imgchopper = IMG_Load("graphics/Civil/imgchopper.png");
    civil.imgtue = IMG_Load("graphics/Civil/tue.png");
    civil.imgsauve = IMG_Load("graphics/Civil/sauv.png");

    civil.otageActuel = civil.otage[otage1];

    civil.x = 0;
    civil.y = 0;
    civil.direction = Droite;
    civil.zone = 0;
    civil.debutZone = 0;
    civil.finZone = 0;
    civil.tempsMort = 0;

    civil.vershelico = 0;
    civil.bougevers = 0;
    civil.MIA = 0;
    civil.saved = 0;

    civil.nombreBatiment = 0;
}


/* Initialisation du tank */

void initiAvion()
{
    /* Ajouter les sprites pour avoir 13 sprites et réaliser un effet visuel plus clair "PM" */

    avion.plane[avion1] = IMG_Load("graphics/Avion/avion1.png");
    avion.plane[avion2] = IMG_Load("graphics/Avion/avion2.png");
    avion.plane[avion3] = IMG_Load("graphics/Avion/avion3.png");
    avion.plane[avion4] = IMG_Load("graphics/Avion/avion4.png");
    avion.plane[avion5] = IMG_Load("graphics/Avion/avion5.png");
    avion.plane[avion6] = IMG_Load("graphics/Avion/avion6.png");

    avion.plane[avion7] = IMG_Load("graphics/Avion/avion7.png");
    avion.plane[avion8] = IMG_Load("graphics/Avion/avion8.png");
    avion.plane[avion9] = IMG_Load("graphics/Avion/avion9.png");
    avion.plane[avion10] = IMG_Load("graphics/Avion/avion10.png");
    avion.plane[avion11] = IMG_Load("graphics/Avion/avion11.png");
    avion.plane[avion12] = IMG_Load("graphics/Avion/avion12.png");
    avion.plane[avion42] = IMG_Load("graphics/Avion/avion42.png");
    avion.plane[avion43] = IMG_Load("graphics/Avion/avion43.png");

    avion.planeActuel = avion.plane[avion1];

    if(avion.planeActuel == NULL )
    {
        fprintf(stderr, "Erreur d'initialisation de l'avion : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    avion.x = 0;
    avion.y = 10;
    avion.direction = Droite;
    avion.tir = 0;
    //avion.modeCombat = Bas;
    avion.zone = 0;
    avion.tempsMort = 0;
    avion.tempGeneration = 0;
    avion.tir = 0;

    avion.limiteZone = 5;
    avion.nombreVie = NOMBRE_VIE_AVION;
    avion.nombrePhase = 0;
}

void initiTank()
{
    int i;
    tank.BTank[tank1] = IMG_Load("graphics/Tank/droite.png");
    tank.BTank[tank5] = IMG_Load("graphics/Tank/gauche.png");
    tank.BTank[tank2] = IMG_Load("graphics/Tank/diagonale_haut_droite.png");
    tank.BTank[tank4] = IMG_Load("graphics/Tank/diagonale_haut_gauche.png");
    tank.BTank[tank3] = IMG_Load("graphics/Tank/haut.png");

    tank.tankActuel = tank.BTank[tank1];

    if(tank.tankActuel == NULL )
    {
        fprintf(stderr, "Erreur d'initialisation du tank[%d] : %s\n", i+1, SDL_GetError());
        exit(EXIT_FAILURE);
    }


    tank.x = 0;
    tank.y = 10;
    tank.direction = Droite;
    tank.tir = 0;
    tank.zone = 0;
    tank.tempsMort = 0;
    tank.tempGeneration = 0;
    tank.tirprec = 0;
    tank.nombreVie = NOMBRE_VIE_TANK;
}

/* Initialisation Soucoupe Volante */

void initiSoucoupe()
{
    soucoupe.alien = IMG_Load("graphics/Soucoupe/soucoupe.png");
    if(soucoupe.alien == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de la soucoupe %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    soucoupe.x = 0;
    soucoupe.y = 2;
    soucoupe.direction = Droite;
    soucoupe.zone = 0;
    soucoupe.tempsMort = 0;
    soucoupe.tempGeneration = 0;
}

/* initialiser le boss de fin */

void initiBoss()
{
    /* Ajouter les sprites pour avoir 13 sprites et réaliser un effet visuel plus clair "PM" */

    boss.sangohan[boss1] = IMG_Load("graphics/Boss/boss1.png");
    boss.sangohan[boss2] = IMG_Load("graphics/Boss/boss2.png");
    boss.sangohan[boss3] = IMG_Load("graphics/Boss/boss3.png");
    boss.sangohan[boss4] = IMG_Load("graphics/Boss/boss4.png");
    boss.sangohan[boss5] = IMG_Load("graphics/Boss/boss5.png");
    boss.sangohan[boss6] = IMG_Load("graphics/Boss/boss6.png");

    boss.sangohan[boss7] = IMG_Load("graphics/Boss/boss7.png");
    boss.sangohan[boss8] = IMG_Load("graphics/Boss/boss8.png");
    boss.sangohan[boss9] = IMG_Load("graphics/Boss/boss9.png");


    boss.sangohanActuel = boss.sangohan[boss9];

    if(boss.sangohanActuel == NULL )
    {
        fprintf(stderr, "Erreur d'initialisation de l'avion : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    boss.x = 0;
    boss.y = 10;
    boss.direction = Droite;
    boss.tir = 0;
    //avion.modeCombat = Bas;
    boss.zone = 0;
    boss.tempsMort = 0;
    boss.tir = 0;

    boss.limiteZone = 5;
    boss.nombreVie = NOMBRE_VIE_BOSS;
    boss.nombrePhase = 0;
}

/* Initialisation de notre zone safe */

void initibase()
{
    safe.atterissage = IMG_Load("graphics/Sprite/atterissage.png");
    safe.base = IMG_Load("graphics/Sprite/base.png");
    safe.debarquement = 0;
}

/* Initialisation de l'hélicopter */

void initiHelicopter()
{
    /* Charles content */

    choplifter.helicopter[gauche_avance] = IMG_Load("graphics/Heli/gauche-avance.png");
    choplifter.helicopter[gauche] = IMG_Load("graphics/Heli/gauche.png");
    choplifter.helicopter[gauche_recule] = IMG_Load("graphics/Heli/gauche-recule.png");
    choplifter.helicopter[centre_gauche] = IMG_Load("graphics/Heli/bas-gauche.png");
    choplifter.helicopter[centre] = IMG_Load("graphics/Heli/bas.png");
    choplifter.helicopter[centre_droite] = IMG_Load("graphics/Heli/bas-droite.png");
    choplifter.helicopter[droite_avance] = IMG_Load("graphics/Heli/droite-avance.png");
    choplifter.helicopter[droite] = IMG_Load("graphics/Heli/droite.png");
    choplifter.helicopter[droite_recule] = IMG_Load("graphics/Heli/droite-recule.png");

    choplifter.helicopter[latence_droite] = IMG_Load("graphics/Heli/droite_boum.png");
    choplifter.helicopter[latence_gauche] = IMG_Load("graphics/Heli/gauche_boum.png");
    choplifter.helicopter[latence_bas] = IMG_Load("graphics/Heli/bas_boum.png");

    /* On charge la premiere image de l'image "PM" */
    choplifter.heli = choplifter.helicopter[gauche];

    if(choplifter.heli == NULL )
    {
        fprintf(stderr, "Erreur d'initialisation de l'hélico : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* On initialise les cordonnée de départ "PM */
    choplifter.x = 495;
    choplifter.y = GROUND;
    choplifter.canon =0;
    choplifter.tirprec = 0;
    choplifter.zone = 0;
    choplifter.position = Gauche;
    choplifter.descends = 0;
    choplifter.poser = poser;
    choplifter.passagers = 0;
    choplifter.etatmort = 0;

    choplifter.nombreVie = NOMBRE_VIE_HELICOPTER;
    choplifter.vie = 3;
}

void initiStatus ()
{
    int i;

    for(i=0; i<NOMBRE_VIE_HELICOPTER; i++)
    {
        hp[i].pv = IMG_Load("graphics/Status/coeur.png");
        hp[i].y = 24;
        hp[i].x = i * 24;
    }

    for(i=0; i<3; i++)
    {
        life[i].vie = IMG_Load("graphics/Status/vie.png");
        life[i].y = 0;
        life[i].x = i * 24;
    }
}

/* initialisation de l'image de fong (Background) "PM" */

void initiBackground()
{
    map.background = IMG_Load("graphics/Background/background1.png");
    // initialise menu;
    map.coeur = IMG_Load("graphics/Status/coeur.png");
}

/* initialisation du menu principale */

void initiMenuPrincipale()
{
    fenetre.hand = IMG_Load ("graphics/Menu/curseur.gif");

    fenetre.menuPrincipale = IMG_Load("graphics/Menu/Menu.png");
}

void initiGameOver()
{
    fenetre.gameOver = IMG_Load("graphics/Menu/gameOver.png");
    fenetre.timeOver = 0;
    fenetre.terminer = 0;
}

void initiMapVide()
{
    int i;
    int j;

    sprite.objetActuel = valeurSprite.Blanc;
    SDL_SetColorKey(sprite.blanc, SDL_SRCCOLORKEY, SDL_MapRGB((sprite.blanc)->format, 255, 255, 255));


    for(i=0; i<LARGEUR_TOTAL_MAP; i++)
    {
        for(j=0; j<(LONGEUR_TOTAL_MAP * NOMBRE_ZONE_LONGEUR); j++)
        {
            map.sprite[i][j] = sprite.objetActuel;
        }
    }
}

/* initialisation de la police d'écriture */

void initiTexte()
{
    fenetre.font = TTF_OpenFont("texte/texte.ttf", 25);
    if(fenetre.font == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de fichier texte %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }

}

void initiMusique()
{
    /* Initialisation de notre objet système pour le son du jeu */
    FMOD_System_Create(&fenetre.system);
    FMOD_System_Init(fenetre.system, 13, FMOD_INIT_NORMAL, NULL);

    /* Initialisation des différentes musique de notre jeu */

    // Init bruit hélico
    if(FMOD_System_CreateSound(fenetre.system, "sound/heli.wav", FMOD_CREATESAMPLE | FMOD_LOOP_NORMAL , 0, &choplifter.vole) != FMOD_OK) {
        fprintf(stderr, "Impossible de lire heli.wav\n");
        exit(EXIT_FAILURE);
    }

    // Init bruits tirs
    if(FMOD_System_CreateSound(fenetre.system, "sound/shot.wav", FMOD_CREATESAMPLE, 0, &channel.tir)!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire shot.wav (hélico)\n");
        exit(EXIT_FAILURE);
    }

    if(FMOD_System_CreateSound(fenetre.system, "sound/shot2.wav", FMOD_CREATESAMPLE, 0, &channel.tir2)!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire shot.wav (tank)\n");
        exit(EXIT_FAILURE);
    }

    if(FMOD_System_CreateSound(fenetre.system, "sound/shot3.wav", FMOD_CREATESAMPLE, 0, &channel.tir3)!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire shot.wav (avion)\n");
        exit(EXIT_FAILURE);
    }

    if(FMOD_System_CreateSound(fenetre.system, "sound/shot4.wav", FMOD_CREATESAMPLE, 0, &channel.tir4)!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire shot.wav (avion)\n");
        exit(EXIT_FAILURE);
    }


    // Init explosions
    if(FMOD_System_CreateSound(fenetre.system, "sound/explo.wav", FMOD_CREATESAMPLE, 0, &choplifter.explose)!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire explo.wav (hélico)\n");
        exit(EXIT_FAILURE);
    }

    if(FMOD_System_CreateSound(fenetre.system, "sound/explo.wav", FMOD_CREATESAMPLE, 0, &tank.explose)!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire explo.wav (tank)\n");
        exit(EXIT_FAILURE);
    }

    if(FMOD_System_CreateSound(fenetre.system, "sound/explo.wav", FMOD_CREATESAMPLE, 0, &avion.explose)!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire explo.wav (avion)\n");
        exit(EXIT_FAILURE);
    }

    if(FMOD_System_CreateSound(fenetre.system, "sound/explo.wav", FMOD_CREATESAMPLE, 0, &soucoupe.explose)!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire explo.wav (soucoupe)\n");
        exit(EXIT_FAILURE);
    }

    //Init Musiques
    if(FMOD_System_CreateSound(fenetre.system, "sound/menu.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL , 0, &fenetre.musicmenu)!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire menu.mp3\n");
        exit(EXIT_FAILURE);
    }

    if(FMOD_System_CreateSound(fenetre.system, "sound/jeu.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM  | FMOD_LOOP_NORMAL , 0, &fenetre.musicgame)!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire jeu.mp3\n");
        exit(EXIT_FAILURE);
    }

    // Init batiment explosion
    if(FMOD_System_CreateSound(fenetre.system, "sound/explo_batiment.wav", FMOD_CREATESAMPLE, 0, &fenetre.batisplosion )!= FMOD_OK) {
        fprintf(stderr, "Impossible de lire shot.wav (hélico)\n");
        exit(EXIT_FAILURE);
    }

    if(FMOD_System_CreateSound(fenetre.system, "sound/cdie.wav", FMOD_CREATESAMPLE, 0, &fenetre.civildown) != FMOD_OK) {
        fprintf(stderr, "Impossible de lire cdie.wav\n");
        exit(EXIT_FAILURE);
    }

    if(FMOD_System_CreateSound(fenetre.system, "sound/bos.mp3", FMOD_CREATESAMPLE, 0, &boss.tirCanon) != FMOD_OK) {
        fprintf(stderr, "Impossible de lire bos.mp3\n");
        exit(EXIT_FAILURE);
    }

    // Activation de la répétition des musiques de fond
    FMOD_Sound_SetLoopCount(fenetre.musicgame, -1);
    FMOD_Sound_SetLoopCount(fenetre.musicmenu, -1);
    FMOD_Sound_SetLoopCount(choplifter.vole, -1);

    // Création des channels de controle des sons
    FMOD_System_GetChannel(fenetre.system, 1 , &channel.channelmusic);
    FMOD_System_GetChannel(fenetre.system, 2 , &channel.channelfly);

    FMOD_System_GetChannel(fenetre.system, 3 , &channel.channeltir_helico);
    FMOD_System_GetChannel(fenetre.system, 4 , &channel.channeltir_tank);
    FMOD_System_GetChannel(fenetre.system, 5 , &channel.channeltir_avion);

    FMOD_System_GetChannel(fenetre.system, 6 , &channel.channelexplo_helico);
    FMOD_System_GetChannel(fenetre.system, 7 , &channel.channelexplo_tank);
    FMOD_System_GetChannel(fenetre.system, 8 , &channel.channelexplo_avion);
    FMOD_System_GetChannel(fenetre.system, 9 , &channel.channelexplo_soucoupe);

    FMOD_System_GetChannel(fenetre.system, 10 , &channel.channelexplo_batiment);

    FMOD_System_GetChannel(fenetre.system, 11 , &channel.channelcivildown);
    FMOD_System_GetChannel(fenetre.system, 12 , &channel.channeltirboss);



    /* Création des Channelgroup
    FMOD_Channel_SetChannelGroup (channel.channeltir_helico, channel.groupshot);
    FMOD_Channel_SetChannelGroup (channel.channeltir_tank, channel.groupshot);
    FMOD_Channel_SetChannelGroup (channel.channeltir_avion, channel.groupshot);

    FMOD_Channel_SetChannelGroup (channel.channelexplo_helico, channel.groupexplo);
    FMOD_Channel_SetChannelGroup (channel.channelexplo_tank, channel.groupexplo);
    FMOD_Channel_SetChannelGroup (channel.channelexplo_avion, channel.groupexplo);
    FMOD_Channel_SetChannelGroup (channel.channelexplo_soucoupe, channel.groupexplo);

*/

}

void initiConstante()
{
    map.debutX = LONGEUR_TOTAL_MAP * (NOMBRE_ZONE_LONGEUR - 1);
    map.finX = LONGEUR_TOTAL_MAP * NOMBRE_ZONE_LONGEUR;
    map.spriteX = 0;

    // Gestion de la boucle principale du jeu "PM" -> Merci de ne pas en utiliser d'autre dans vos programme
    fenetre.continuer = 1;
    fenetre.menu = 0;
    fenetre.jeu = 0;
    fenetre.nombreTank = 0;
    fenetre.nombreAvion = 0;
    fenetre.nombreSoucoupe = 0;
    fenetre.nombreOtage = 0;
    fenetre.nombreBoss = 0;

    fenetre.timeOver = 0;
    fenetre.terminer = 0;

    /* On initialise les cordonnée de départ "PM */
    choplifter.x = 495;
    choplifter.y = GROUND;
    choplifter.canon =0;
    choplifter.tirprec = 0;
    choplifter.zone = 0;
    choplifter.position = Gauche;
    choplifter.descends = 0;
    choplifter.poser = poser;
    choplifter.passagers = 0;
    choplifter.etatmort = 0;

    choplifter.nombreVie = NOMBRE_VIE_HELICOPTER;
    choplifter.vie = 3;

    boss.x = 0;
    boss.y = 10;
    boss.direction = Droite;
    boss.tir = 0;
    //avion.modeCombat = Bas;
    boss.zone = 0;
    boss.tempsMort = 0;
    boss.tir = 0;

    boss.limiteZone = 5;
    boss.nombreVie = NOMBRE_VIE_BOSS;
    boss.nombrePhase = 0;

    soucoupe.x = 0;
    soucoupe.y = 2;
    soucoupe.direction = Droite;
    soucoupe.zone = 0;
    soucoupe.tempsMort = 0;
    soucoupe.tempGeneration = 0;

    tank.x = 0;
    tank.y = 10;
    tank.direction = Droite;
    tank.tir = 0;
    tank.zone = 0;
    tank.tempsMort = 0;
    tank.tempGeneration = 0;
    tank.tirprec = 0;
    tank.nombreVie = NOMBRE_VIE_TANK;

    avion.x = 0;
    avion.y = 10;
    avion.direction = Droite;
    avion.tir = 0;
    //avion.modeCombat = Bas;
    avion.zone = 0;
    avion.tempsMort = 0;
    avion.tempGeneration = 0;
    avion.tir = 0;

    avion.limiteZone = 5;
    avion.nombreVie = NOMBRE_VIE_AVION;
    avion.nombrePhase = 0;
}

void initiDebutPartie()
{
    civil.x = 0;
    civil.y = 0;
    civil.direction = Droite;
    civil.zone = 0;
    civil.debutZone = 0;
    civil.finZone = 0;
    civil.tempsMort = 0;

    civil.vershelico = 0;
    civil.bougevers = 0;
    civil.MIA = 0;
    civil.saved = 0;

    civil.nombreBatiment = 0;
}

void initiGenerale()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Erreur lors du chargement de la SDL %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Choplifter", NULL);
    fenetre.ecran = SDL_SetVideoMode(LONGEUR_ECRAN - SPRITE_RESOLUTION, LARGEUR_ECRAN, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);

    SDL_ShowCursor(SDL_DISABLE);
    /* Initialise SDL_TTF */

    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());

        exit(1);
    }

    //SDL_ShowCursor(SDL_ENABLE);

    map.debutX = LONGEUR_TOTAL_MAP * (NOMBRE_ZONE_LONGEUR - 1);
    map.finX = LONGEUR_TOTAL_MAP * NOMBRE_ZONE_LONGEUR;
    map.spriteX = 0;

    // Gestion de la boucle principale du jeu "PM" -> Merci de ne pas en utiliser d'autre dans vos programme
    fenetre.continuer = 1;
    fenetre.menu = 0;
    fenetre.jeu = 0;
    fenetre.nombreTank = 0;
    fenetre.nombreAvion = 0;
    fenetre.nombreSoucoupe = 0;
    fenetre.nombreOtage = 0;
    fenetre.nombreBoss = 0;

    initiSprite();
    initiMapVide();
    initiChargementSprite();
    initiBackground();
    initiBalle();
    initiHelicopter();
    initiTank();
    initiAvion();
    initiOtage();
    initiBoss();
    initiSoucoupe();
    initiMenuPrincipale();
    initiGameOver();
    initiStatus();
    initibase();
    initiTexte();
    initiMusique();
}

/* Fin phase d'initialisation */

/* Phase 2 de chargement */

void chargementNiveau()
{
    FILE *fichier = NULL;
    int caractereActuel = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    if((fichier = fopen("map0.txt", "r")) == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement du niveau %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    for(i=0; i<LARGEUR_TOTAL_MAP; i++)
    {
        for(j=0; j<LONGEUR_TOTAL_MAP * NOMBRE_ZONE_LONGEUR; j++)
        {
            caractereActuel = fgetc(fichier);
            if(caractereActuel != EOF)
            {
                switch(caractereActuel)
                {
                    case '0':
                        map.sprite[i][j] = valeurSprite.Blanc;
                        break;
                    case '1':
                        map.sprite[i][j] = valeurSprite.Base;
                        safe.xB = j;
                        safe.yB = i;
                        break;
                    case '2':
                        map.sprite[i][j] = valeurSprite.Sol;
                        break;
                    case '3':
                        map.sprite[i][j] = valeurSprite.ArbreV;
                        break;
                    case '4':
                        map.sprite[i][j] = valeurSprite.ArbreM;
                        break;
                    case '5':
                        map.sprite[i][j] = valeurSprite.Maison;
                        if(k < NOMBRES_BATIMENT)
                        {
                            civil.batiment[k][0] = i;
                            civil.batiment[k][1] = j;
                            civil.batiment[k][2] = 15; // Il faut toucher le batiment 5 fois pour qu'il soit détruit
                            civil.batiment[k][3] = valeurSprite.Maison;
                            civil.nombreOtage[k] = 0;
                            civil.totalCivil[k] = NOMBRE_PASSAGER_MAX; // Dans chaque batiment nous avons 16 Otages
                            civil.nombreBatiment++;
                            k++;
                        }
                        break;
                    case '6':
                        map.sprite[i][j] = valeurSprite.Tank;
                        break;
                    case '7':
                        map.sprite[i][j] = valeurSprite.Avion;
                        break;
                    case '8':
                        map.sprite[i][j] = valeurSprite.Atterissage;
                        safe.xA = j;
                        safe.yA = i;
                        break;
                    case '9':
                        map.sprite[i][j] = valeurSprite.MaisonD;
                        break;
                }
            }
        }
    }

    fclose(fichier);
}

/* Fin phase de chargement */

/* Phase 3 Mise à jour Map */

/* Mise à jour des coordonnée map.debutX et map.finX */

void miseAJour()
{
    map.bouge = 0;
    if(clavier.Left == 1 && choplifter.x <= ((fenetre.ecran->w)/2)-((choplifter.heli->w)/2)
        && map.debutX >0 && choplifter.poser==decolle && (choplifter.latence != 1))
    {
        map.bouge = 1;
        if(map.spriteX == 0)
        {
            map.debutX--;
            map.finX--;
            map.spriteX = SPRITE_RESOLUTION;
        }
        else
        {
            if(map.spriteX == (SPRITE_RESOLUTION % VITESSE_SCROLLING))
                map.spriteX = map.spriteX - (SPRITE_RESOLUTION % VITESSE_SCROLLING);
            else
                map.spriteX -= VITESSE_SCROLLING;
        }
    }

    if(clavier.Right == 1 && choplifter.x >= ((fenetre.ecran->w)/2)-((choplifter.heli->w)/2)
        && map.finX < (LONGEUR_TOTAL_MAP * NOMBRE_ZONE_LONGEUR) && choplifter.poser==decolle && (choplifter.latence != 1))
    {
        map.bouge = 1;
        if(map.spriteX == SPRITE_RESOLUTION)
        {
            map.debutX++;
            map.finX++;
            map.spriteX = 0;
            map.spriteX += VITESSE_SCROLLING;
        }
        else
        {
            if(map.spriteX == SPRITE_RESOLUTION - (SPRITE_RESOLUTION % VITESSE_SCROLLING))
                map.spriteX = map.spriteX + (SPRITE_RESOLUTION % VITESSE_SCROLLING);
            else
                map.spriteX += VITESSE_SCROLLING;
        }
    }
    // Si on peut tirer avec le canon
    if(choplifter.canon == 1)
        shot();
    /*if(choplifter.poser == poser)
        FMOD_System_PlaySound(fenetre.system, FMOD_CHANNEL_FREE, choplifter.vole, 0, NULL); */
}
/* Phase 4 d'affichage */

/* affichage du background */

void affichageBackground()
{
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    SDL_BlitSurface(map.background, NULL, fenetre.ecran, &pos);
}

/* affichage fin du jeu */

void affichageGameOver()
{
    unsigned int time = SDL_GetTicks();

    SDL_Rect pos;
    if(fenetre.terminer == 1)
    {
        SDL_FillRect(fenetre.ecran, NULL, SDL_MapRGB(fenetre.ecran->format, 255, 255, 255));

        pos.x = 0;
        pos.y = 0;

        SDL_BlitSurface(fenetre.gameOver, NULL, fenetre.ecran, &pos);
        SDL_Flip(fenetre.ecran);
        if(time - fenetre.timeOver > 200)
        {
            fenetre.terminer = 2; // On sort du Game Overs
        }
    }
}

/* affichage du menu principale */

void affichageMenuPrincipale()
{
    if (FMOD_Channel_IsPlaying (channel.channelmusic, 0 ) != FMOD_OK )
        FMOD_System_PlaySound(fenetre.system,(FMOD_CHANNELINDEX)1, fenetre.musicmenu, 0, NULL); // musique menu

    SDL_Event event;
    SDL_Rect pos;
    int continuer= 1;
    int menu = 0;

    pos.x= 0;
    pos.y=0;

    SDL_BlitSurface(fenetre.menuPrincipale, NULL, fenetre.ecran, &pos);

    pos.x=170;
    pos.y=350;
    SDL_BlitSurface(fenetre.hand, NULL, fenetre.ecran, &pos);


    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                fenetre.continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        continuer = 0;
                        FMOD_Channel_SetPaused(channel.channelfly, 0);
                        FMOD_Channel_Stop (channel.channelmusic) ;
                        break;

                    case SDLK_UP:
                        if(menu > 0)
                            menu--;
                        break;

                    case SDLK_DOWN:
                        if(menu < 2)
                            menu++;
                        break;

                    case SDLK_ESCAPE:
                        menu = 2;
                        continuer = 0;
                        break;

                }
            break;
        }

        pos.x=0;
        pos.y=0;
        SDL_BlitSurface(fenetre.menuPrincipale, NULL, fenetre.ecran, &pos);

        switch(menu)
        {
            case 0:
                pos.x=170;
                pos.y=350;
                fenetre.menu = 0;
                fenetre.continuer = 1;
                SDL_BlitSurface(fenetre.hand, NULL, fenetre.ecran, &pos);
                break;
            case 1:
                pos.x=170;
                pos.y=390;
                fenetre.menu = 1;
                SDL_BlitSurface(fenetre.hand, NULL, fenetre.ecran, &pos);
                break;


            case 2:
                pos.x=170;
                pos.y=430;
                fenetre.menu = 2;
                fenetre.continuer = 0;
                SDL_BlitSurface(fenetre.hand, NULL, fenetre.ecran, &pos);
                break;
        }

        SDL_Flip(fenetre.ecran);
    }
}

void affichageSprite(SDL_Surface *image, int x, int y)
{
    SDL_Rect pos;
    SDL_Rect src;

    pos.x = (y * SPRITE_RESOLUTION) - map.spriteX;
    pos.y = x * SPRITE_RESOLUTION;
    pos.w = image->w;
    pos.h = image->h;

    if(x == 0 || x == map.finX)
        src.x = map.spriteX;
    else
        src.x = 0;
    src.y = 0;
    src.h = SPRITE_RESOLUTION;
    src.w = SPRITE_RESOLUTION - (map.spriteX * VITESSE_SCROLLING);

    SDL_BlitSurface(image, &src, fenetre.ecran, &pos);
}

/* affichage de la map */

void affichageMap()
{
    int i;
    int j;
    int z;
    for(i=0; i<LARGEUR_TOTAL_MAP; i++)
    {
        z = 0;
        for(j=map.debutX; j<map.finX; j++)
        {
            map.mapEnCours[i][z] = map.sprite[i][j];
            z++;
        }
    }

    for(i=0; i<LARGEUR_TOTAL_MAP; i++)
    {
        for(j=0; j<LONGEUR_TOTAL_MAP; j++)
        {
            switch(map.mapEnCours[i][j])
            {
                case 0:
                    sprite.spriteActuel = sprite.blanc;
                    break;
                case 1:
                    sprite.spriteActuel = safe.base;
                    break;
                case 2:
                    sprite.spriteActuel = sprite.sol;
                    break;
                case 3:
                    sprite.spriteActuel = sprite.arbreV;
                    break;
                case 4:
                    sprite.spriteActuel = sprite.arbreM;
                    break;
                case 5:
                    sprite.spriteActuel = sprite.maison[1];
                    break;
                case 6:
                    sprite.spriteActuel = tank.tankActuel;
                    break;
                case 7:
                    sprite.spriteActuel = avion.planeActuel;
                    break;
                case 8:
                    sprite.spriteActuel = safe.atterissage;
                    break;
                case 9:
                    sprite.spriteActuel = sprite.maison[0];
                    break;
                case 10:
                    sprite.spriteActuel = civil.otageActuel;
                    break;
                case 11:
                    sprite.spriteActuel = boss.sangohanActuel;
                    break;
                case 12:
                    sprite.spriteActuel = soucoupe.alien;
                    break;
            }
            affichageSprite(sprite.spriteActuel, i, j);
        }
    }
}


/* affichage de l'hélicopter */

void affichageHelicopter()
{
    SDL_Rect pos;

    pos.x = choplifter.x;
    pos.y = choplifter.y;

    pos.w = choplifter.heli->w;
    pos.h = choplifter.heli->h;

    SDL_BlitSurface(choplifter.heli, NULL, fenetre.ecran, &pos);
}

void affichageBullet()
{
    SDL_Rect pos;

    if(balle[0].shot == 1)
    {
        if((balle[0].x < 0) || (balle[0].x > LONGEUR_ECRAN) || (balle[0].y > LARGEUR_ECRAN))
            balle[0].shot=0;

        if (balle[0].direction == vers_gauche)
            balle[0].x -= VITESSE_BALLE;

        if (balle[0].direction == vers_gauche_bas)
        {
            balle[0].x -= VITESSE_BALLE;
            balle[0].y += VITESSE_BALLE;
        }

        if(balle[0].direction == vers_bas)
            balle[0].y += VITESSE_BALLE;

        if(balle[0].direction == vers_droite_bas)
        {
            balle[0].x += VITESSE_BALLE;
            balle[0].y += VITESSE_BALLE;
        }

        if (balle[0].direction == vers_droite)
            balle[0].x += VITESSE_BALLE;

        pos.x = balle[0].x;
        pos.y = balle[0].y;

        pos.w = balle[0].Bullet->w;
        pos.h = balle[0].Bullet->h;

        SDL_BlitSurface(balle[1].Bullet, NULL, fenetre.ecran, &pos);
    }
}

void affichageBulletTank()
{
    SDL_Rect pos;

    if(balle[1].shot == 1)
    {
        if(balle[1].y <= 0 || balle[1].x <= 0 || balle[1].x >= LONGEUR_ECRAN)
            balle[1].shot = 0;

        if (balle[1].direction == vers_gauche_haut)
        {
            balle[1].x -= VITESSE_B_ENNEMI;
            balle[1].y -= VITESSE_B_ENNEMI;
        }

        if(balle[1].direction == vers_haut)
            balle[1].y -= VITESSE_B_ENNEMI;

        if(balle[1].direction == vers_haut_droite)
        {
            balle[1].x += VITESSE_B_ENNEMI;
            balle[1].y -= VITESSE_B_ENNEMI;
        }

        pos.x = balle[1].x;
        pos.y = balle[1].y;

        pos.w = balle[1].Bullet->w;
        pos.h = balle[1].Bullet->h;

        SDL_BlitSurface(balle[1].Bullet, NULL, fenetre.ecran, &pos);
    }
}

void affichageBulletAvion()
{
    SDL_Rect pos;

    if(balle[2].shot == 1)
    {
        if((balle[2].x < 0) || (balle[2].x > LONGEUR_ECRAN) || (balle[2].y < 0))
            balle[2].shot = 0;

        if (balle[2].direction == vers_gauche)
            balle[2].x -= VITESSE_B_ENNEMI;

        if (balle[2].direction == vers_gauche_haut)
        {
            balle[2].x -= VITESSE_B_ENNEMI;
            balle[2].y -= VITESSE_B_ENNEMI;
        }

        if(balle[2].direction == vers_haut)
            balle[2].y -= VITESSE_B_ENNEMI;

        if(balle[2].direction == vers_haut_droite)
        {
            balle[2].x += VITESSE_B_ENNEMI;
            balle[2].y -= VITESSE_B_ENNEMI;
        }

        if (balle[2].direction == vers_droite)
            balle[2].x += VITESSE_B_ENNEMI;

        if (balle[2].direction == vers_droite_bas) {
            balle[2].x += VITESSE_B_ENNEMI;
            balle[2].y += VITESSE_B_ENNEMI;
        }

        if (balle[2].direction == vers_bas)
            balle[2].y += VITESSE_B_ENNEMI;

        if (balle[2].direction == vers_gauche_bas) {
            balle[2].x -= VITESSE_B_ENNEMI;
            balle[2].y += VITESSE_B_ENNEMI;
        }

        pos.x = balle[2].x;
        pos.y = balle[2].y;

        pos.w = balle[2].Bullet->w;
        pos.h = balle[2].Bullet->h;

        SDL_BlitSurface(balle[2].Bullet, NULL, fenetre.ecran, &pos);
    }
}

/* affichage du status du joueur (Helicopter | CIVIL SAUVER | CIVIL TUER) */

void affichageStatus() {
    // Affichage des vies/coeurs, des civils sauvés ect...
    int i;
    SDL_Rect pos;
        // Chaine de charactères qu'on affichera à l'écran.
    char civchop[6]; // civils dans l'hélico
    char civdie[7]; // civils mort
    char civsauv[7]; // civils sauvés
    SDL_Color color={5,5,5};

    for(i=0; i<choplifter.nombreVie; i++) {
        pos.x = hp[i].x;
        pos.y = hp[i].y;
        SDL_BlitSurface(hp[i].pv, NULL, fenetre.ecran, &pos);
    }

     for(i=0;i<choplifter.vie;i++) {
        pos.x = life[i].x;
        pos.y = life[i].y;
        SDL_BlitSurface(life[i].vie, NULL, fenetre.ecran, &pos);
    }

    // blitz les images qui indiquerons l'état des civils
    pos.x = 600;
    pos.y = 0;
    SDL_BlitSurface(civil.imgchopper, NULL, fenetre.ecran, &pos);

    pos.x = 595;
    pos.y = 45;
    SDL_BlitSurface(civil.imgsauve, NULL, fenetre.ecran, &pos);

    pos.x = 580;
    pos.y = 95;
    SDL_BlitSurface(civil.imgtue, NULL, fenetre.ecran, &pos);
    // fin


    // écriture à l'écran
    // ca ca marche
        //écriture nb passagers
    sprintf (civchop, ": %d", choplifter.passagers);
    civil.civilchopper = TTF_RenderText_Solid(fenetre.font, civchop, color);
    pos.x = 650;
    pos.y = 0;
    SDL_BlitSurface(civil.civilchopper, NULL, fenetre.ecran, &pos);

    // me faut une variable pour les civils dans la base ici
        //écriture nb civil sauvé
    sprintf (civsauv, ": %d", civil.saved);
    civil.civilsauve = TTF_RenderText_Solid(fenetre.font, civsauv, color);
    pos.y = 50;
    SDL_BlitSurface(civil.civilsauve, NULL, fenetre.ecran, &pos);

    // me faut une variable qui marche ici
        //écriture nb civil tué
    sprintf (civdie, ": %d", civil.MIA);
    civil.civiltue = TTF_RenderText_Solid(fenetre.font, civdie, color);
    pos.y = 100;
    SDL_BlitSurface(civil.civiltue, NULL, fenetre.ecran, &pos);
}

void affichageCollision(int x, int y)
{
    SDL_Rect pos;

    pos.x = x;
    pos.y = y;

    pos.w = sprite.impact->w;
    pos.h = sprite.impact->h;

    SDL_BlitSurface(sprite.impact, NULL, fenetre.ecran, &pos);
}

void affichageGenerale()
{
    SDL_FillRect(fenetre.ecran, NULL, SDL_MapRGB(fenetre.ecran->format, 255, 255, 255));

    /* background */

    affichageBackground();

    affichageMap();

    collisionCrash();

    affichageHelicopter();

    affichageBullet();

    affichageBulletTank();

    affichageBulletAvion();

    /******************** Colision !Not **************/

    collisionDetected();

    affichageStatus();

    SDL_Flip(fenetre.ecran);
}

/* Fin phase d'affichage */

/* Phase 5 de liberation */

void liberation()
{
    int i;
    int j;
    SDL_FreeSurface(sprite.blanc);
    SDL_FreeSurface(sprite.arbreV);
    SDL_FreeSurface(sprite.arbreM);

    /* Liberation des Surfaces de la safe base */

    SDL_FreeSurface(safe.base);
    SDL_FreeSurface(safe.atterissage);

    /* Liberation des Surfaces des tanks et avion "PM" */

    for(j=0; j<2; j++)
    {
        /* Liberation des sprites maison et balle */
        SDL_FreeSurface(sprite.maison[i]);
    }

    //Libération des 3 structures bullet
    for(i=0; i<3; i++)
        SDL_FreeSurface(balle[i].Bullet);

    SDL_FreeSurface(tank.tankActuel);
    for(i=0; i<5; i++)
        SDL_FreeSurface(tank.BTank[i]);

    /* Liberation des Surfaces des avions "PM" */

    SDL_FreeSurface(avion.planeActuel);
    for(i=0; i<14; i++)
        SDL_FreeSurface(avion.plane[i]);

    /* Liberation du Boss */

    SDL_FreeSurface(boss.sangohanActuel);
    for(i=0; i<9; i++)
        SDL_FreeSurface(boss.sangohan[i]);


    /* Liberation des helicopters "PM" */

    SDL_FreeSurface(choplifter.heli);
    for(i=0; i<11; i++)
        SDL_FreeSurface(choplifter.helicopter[i]);

    /* Libération de nos otage */

    SDL_FreeSurface(civil.otageActuel);
    for(i=0; i<5; i++)
        SDL_FreeSurface(civil.otage[i]);

    //liberation des images de status
    for (i=0;i<3;i++)
        SDL_FreeSurface(life[i].vie);

    for(i=0; i<NOMBRE_VIE_HELICOPTER; i++)
        SDL_FreeSurface(life[i].vie);

    /* Libération de la soucoupe */

    SDL_FreeSurface(soucoupe.alien);

    SDL_FreeSurface(map.background);
    SDL_FreeSurface(fenetre.menuPrincipale);
    SDL_FreeSurface(fenetre.hand);

    SDL_FreeSurface(civil.imgtue);
    SDL_FreeSurface(civil.imgchopper);
    SDL_FreeSurface(civil.imgsauve);
    SDL_FreeSurface(civil.civiltue);
    SDL_FreeSurface(civil.civilchopper);
    SDL_FreeSurface(civil.civilsauve);


    /* Close the font */
    if(fenetre.font != NULL)
    {
        TTF_CloseFont(fenetre.font);
    }

    TTF_Quit();

    /* Fermeture du son */

    FMOD_Sound_Release(choplifter.tirCanon);
    FMOD_Sound_Release(choplifter.vole);
    FMOD_Sound_Release(choplifter.explose);
    FMOD_Sound_Release(tank.tirCanon);
    FMOD_Sound_Release(tank.explose);
    FMOD_Sound_Release(avion.tirCanon);
    FMOD_Sound_Release(avion.explose);
    FMOD_Sound_Release(soucoupe.explose);
    FMOD_Sound_Release(fenetre.batisplosion);
    FMOD_Sound_Release(boss.tirCanon);

    FMOD_System_Close(fenetre.system);
    FMOD_System_Release(fenetre.system);

    SDL_FreeSurface(fenetre.ecran);
    SDL_Quit(); // Arrêt de la SDL
}

/* Fin phase de liberation */

/* Phase 6 Editeur de niveau */

/* Sauvegarde l'etat de la Map */

void saveMap()
{
    int i, j;
    FILE *fichier;

    fichier = fopen("map0.txt", "w");

    /* Si on ne peut pas charger la map, on quitte */

    if(fichier == NULL)
        exit(EXIT_FAILURE);


    /* Sauvegarde la map */

    for (i=0; i<LARGEUR_TOTAL_MAP; i++)
    {
        for (j=0; j<(LONGEUR_TOTAL_MAP * NOMBRE_ZONE_LONGEUR); j++)
        {
            fprintf(fichier, "%d", map.sprite[i][j]);
        }
    }

    /* On referme le fichier */

    fclose(fichier);
}

void reinitialiseMap()
{
    /* Pour réinitialiser la map à vide */

    /* On va d'abord initialise une map vide de blanc */
    initiMapVide();

    /* Et on va ensuite save cette map */

    saveMap();
}

void editeurMap()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT:
            fenetre.continuer = 1;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                map.sprite[event.button.y/SPRITE_RESOLUTION][(event.button.x/SPRITE_RESOLUTION) + map.debutX] = sprite.objetActuel;
                souris.clickGauche = 1;
            }
            if(event.button.button == SDL_BUTTON_RIGHT)
            {
                map.sprite[event.button.y/SPRITE_RESOLUTION][event.button.x/SPRITE_RESOLUTION + map.debutX] = valeurSprite.Blanc;
                souris.clickDroit = 1;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT)
                souris.clickGauche = 0;
            if(event.button.button == SDL_BUTTON_RIGHT)
                souris.clickDroit = 0;
            break;
        case SDL_MOUSEMOTION:
            if(souris.clickGauche)
            {
                map.sprite[event.button.y/SPRITE_RESOLUTION][event.button.x/SPRITE_RESOLUTION + map.debutX] = sprite.objetActuel;
            }
            else if(souris.clickDroit)
            {
                map.sprite[event.button.y/SPRITE_RESOLUTION][event.button.x/SPRITE_RESOLUTION + map.debutX] = valeurSprite.Blanc;
            }
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    fenetre.continuer = 1;
                    break;
                /* Pour le Scrolling sur la map */
                case SDLK_LEFT:
                    clavier.Left = 1;
                    break;
                case SDLK_RIGHT:
                    clavier.Right = 1;
                    break;
                /* Fin du scrolling sur la map */
                case SDLK_s:
                    fenetre.save = 1;
                    saveMap();
                    break;
                case SDLK_r:
                    fenetre.reinitialise = 1;
                    break;
                case SDLK_KP0:
                    sprite.objetActuel = valeurSprite.Blanc;
                    break;
                case SDLK_KP1:
                    sprite.objetActuel = valeurSprite.Base;
                    break;
                case SDLK_KP2:
                    sprite.objetActuel = valeurSprite.Sol;
                    break;
                case SDLK_KP3:
                    sprite.objetActuel = valeurSprite.ArbreV;
                    break;
                case SDLK_KP4:
                    sprite.objetActuel = valeurSprite.ArbreM;
                    break;
                case SDLK_KP5:
                    sprite.objetActuel = valeurSprite.Maison;
                    break;
                case SDLK_KP6:
                    sprite.objetActuel = valeurSprite.Atterissage;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    clavier.Left = 0;
                    break;
                case SDLK_RIGHT:
                    clavier.Right = 0;
                    break;
                case SDLK_s:
                    fenetre.save = 0;
            }
        break;
    }
}

/* Fin phase d'editeur de niveau */

/* Phase 7 jouer "PM" */

/* Generer une soucoupe volante */

void genererSoucoupe()
{
    int time = SDL_GetTicks();

    trouverZoneHelicopter();
    if(fenetre.nombreSoucoupe < 1)
    {
        if(time - soucoupe.tempGeneration > FREQUENCE_SOUCOUPE)
        {
            if(choplifter.zone == 3 || choplifter.zone == 4)
            {
                if(map.debutX > 10 && map.finX < (LONGEUR_TOTAL_MAP * (NOMBRE_ZONE_LONGEUR - 2)))
                {
                    soucoupe.debutZone = map.debutX - 2;
                    soucoupe.x = soucoupe.debutZone;
                    // On spawn l'abscisse en longeur de l'hélicopter si on n'est dans les air
                    if((choplifter.y / SPRITE_RESOLUTION) < 6)
                        soucoupe.y = choplifter.y / SPRITE_RESOLUTION;
                    soucoupe.finZone = map.finX + 2;
                    soucoupe.direction = Droite;
                    soucoupe.nombreVie = 5;
                    map.sprite[soucoupe.y][soucoupe.x] = valeurSprite.Alien;
                    fenetre.nombreSoucoupe++;
                    soucoupe.tempGeneration = 0;
                    choplifter.toucheSoucoupe = 0;
                }
            }

            if(choplifter.zone == 1 || choplifter.zone == 2)
            {
                if(map.debutX > 10 && map.finX < (LONGEUR_TOTAL_MAP * (NOMBRE_ZONE_LONGEUR - 2)))
                {
                        soucoupe.finZone = map.debutX - 1;
                        soucoupe.debutZone = map.finX + 1;
                        soucoupe.x = soucoupe.debutZone;
                        // On spawn l'abscisse en longeur de l'hélicopter si on n'est dans les air
                        if((choplifter.y / SPRITE_RESOLUTION) < 6)
                            soucoupe.y = choplifter.y / SPRITE_RESOLUTION;
                        soucoupe.direction = Gauche;
                        soucoupe.nombreVie = 5;
                        map.sprite[soucoupe.y][soucoupe.x] = valeurSprite.Alien;
                        fenetre.nombreSoucoupe++;
                        soucoupe.tempGeneration = 0;
                        choplifter.toucheSoucoupe = 0;
                }
            }
        }
        if(soucoupe.tempGeneration == 0)
            soucoupe.tempGeneration = SDL_GetTicks();
    }
}

/* deplacer soucoupe */

void deplacerSoucoupe()
{
    int time = SDL_GetTicks();
    int valeurSpriteTemporaire;

    /* Le faire déplaceer à droite */

    if(time - soucoupe.frameLimit > VITESSE_SOUCOUPE && soucoupe.direction == Droite)
    {
        soucoupe.x+=2;
        map.sprite[soucoupe.y][soucoupe.x] = valeurSprite.Alien;
        map.sprite[soucoupe.y][soucoupe.x - 2] = valeurSprite.Blanc;
        soucoupe.frameLimit = SDL_GetTicks();
    }

    /* le faire deplacer à gauche */

    if(time - soucoupe.frameLimit > VITESSE_SOUCOUPE && soucoupe.direction == Gauche)
    {
        soucoupe.x-=2;
        map.sprite[soucoupe.y][soucoupe.x] = valeurSprite.Alien;
        map.sprite[soucoupe.y][soucoupe.x + 2] = valeurSprite.Blanc;
        soucoupe.frameLimit = SDL_GetTicks();
    }


}

/* Trouver zone Soucoupe */

void trouverZoneSoucoupe()
{
    if(!(soucoupe.x > map.debutX && soucoupe.x < map.finX))
        soucoupe.zone = 0;
}

/* Libère la soucoupes si elle est dans la zone 0 */

void annulerSoucoupe()
{
    unsigned int time=SDL_GetTicks();

    trouverZoneSoucoupe();
    if(soucoupe.zone == 0)
    {
        if(time - tank.tempsMort > 300) // Si il fait 4 secondes dans la zone 0
        {
            map.sprite[soucoupe.y][soucoupe.x] = valeurSprite.Blanc;
            soucoupe.tempsMort = 0;
            fenetre.nombreSoucoupe--;
            soucoupe.nombreVie = 5;
        }
        if(soucoupe.tempsMort == 0)
            soucoupe.tempsMort = SDL_GetTicks();
    }
    if(soucoupe.nombreVie < 0)
    {
        map.sprite[soucoupe.y][soucoupe.x] = valeurSprite.Blanc;
        FMOD_System_PlaySound(fenetre.system, (FMOD_CHANNELINDEX)9, soucoupe.explose, 0, NULL);
        soucoupe.tempsMort = 0;
        fenetre.nombreSoucoupe--;
        soucoupe.nombreVie = 5;
        soucoupe.tempsMort = SDL_GetTicks();
    }
}


/* Bouger le Tank */

void deplacerTank()
{
    int time = SDL_GetTicks();
    int valeurSpriteTemporaire;
    if(time - tank.frameLimit > VITESSE_ENNEMIES_TANK && tank.direction == Droite)
    {
        tank.x++;
        map.sprite[tank.y][tank.x] = valeurSprite.Tank;
        map.sprite[tank.y][tank.x - 1] = valeurSprite.Sol;
        tank.frameLimit = SDL_GetTicks();
        if(tank.x == tank.finZone)
        {
            tank.direction = Gauche;
            tank.tankActuel = tank.BTank[tank5];
        }
    }
    if(time - tank.frameLimit > VITESSE_ENNEMIES_TANK && tank.direction == Gauche)
    {
        tank.x--;
        map.sprite[tank.y][tank.x] = valeurSprite.Tank;
        map.sprite[tank.y][tank.x + 1] = valeurSprite.Sol;
        tank.frameLimit = SDL_GetTicks();
        if(tank.x == tank.debutZone)
        {
            tank.direction = Droite;
            tank.tankActuel = tank.BTank[tank1];
        }
    }
}

void genererTank()
{
    int i;
    /* Pour generer un ennemie à gauche de l'écran */
    int time = SDL_GetTicks();
    if(fenetre.nombreTank < 1)
    {
        if(time - tank.tempGeneration > FREQUENCE_TANK)
        {
            if(choplifter.zone == 3 || choplifter.x == 4) // On n'est a gauche
            {
                if(map.finX < (LONGEUR_TOTAL_MAP * (NOMBRE_ZONE_LONGEUR - 2)))
                {
                    tank.finZone = map.finX + 3;
                    tank.x = tank.finZone;
                    tank.debutZone = map.finX - 10;
                    tank.direction = Gauche;
                    tank.tankActuel = tank.BTank[tank5];
                    map.sprite[tank.y][tank.x] = valeurSprite.Tank;
                    fenetre.nombreTank++;
                }
            }
            if(choplifter.zone == 1 || choplifter.zone == 2)
            {
                if(map.debutX > 10 && map.finX < (LONGEUR_TOTAL_MAP * (NOMBRE_ZONE_LONGEUR - 2)))
                {
                    tank.debutZone = map.debutX -3;
                    tank.x = tank.debutZone;
                    tank.finZone = map.debutX + 10;
                    tank.direction = Droite;
                    tank.tankActuel = tank.BTank[tank1];
                    map.sprite[tank.y][tank.x] = valeurSprite.Tank;
                    fenetre.nombreTank++;
                }
            }
        }
        if(tank.tempGeneration == 0)
            tank.tempGeneration = SDL_GetTicks();
    }
}

/* Trouver zone Tank */

void trouverZoneTank()
{
    if(tank.x > map.debutX && tank.x < map.finX)
    {
        if(tank.x <= (map.debutX + (LONGEUR_TOTAL_MAP / 2)))
            tank.zone = 1; // On n'est a gauche
        else
            tank.zone = 2; // On n'est a droite
    }
    else
        tank.zone = 0;
}

/* Choisir la position du tank en fonction de la zone du tank et de l'hélicopter */

void modeCombatTank()
{
    trouverZoneHelicopter();
    trouverZoneTank();
    if(tank.zone == 2)// On n'est donc à droite
    {
        switch(choplifter.zone)
        {
            case 1:  //Haut Gauche
                tank.position = tank5;
                tank.tankActuel = tank.BTank[tank5];
                break;
            case 2:  //Bas Gauche
                tank.position = tank4;
                tank.tankActuel = tank.BTank[tank4];
                break;
            case 3: // Haut Droite
                tank.position = tank3;
                tank.tankActuel = tank.BTank[tank3];
                break;
            case 4: // Bas Droite
                tank.position = tank3;
                tank.tankActuel = tank.BTank[tank3];
                break;
        }
    }
    if(tank.zone == 1)// On n'est donc à gauche
    {
        switch(choplifter.zone)
        {
            case 1: // Haut Gauche
                tank.position = tank3;
                tank.tankActuel = tank.BTank[tank3];
                break;
            case 2: // Bas Gauche
                tank.position = tank3;
                tank.tankActuel = tank.BTank[tank3];
                break;
            case 3: // Haut Droite
                tank.position = tank1;
                tank.tankActuel = tank.BTank[tank1];
                break;
            case 4: // Bas Droite
                tank.position = tank2;
                tank.tankActuel = tank.BTank[tank2];
                break;
        }
    }
    // inutile de le mettre en mode Combat si il est dans la zone 0 */
}

/* Libère le tank si il est dans la zone 0 */

void annulerTank()
{
    int time=SDL_GetTicks();
    if(tank.zone == 0)
    {
        if(time - tank.tempsMort > 4000) // Si il fait 4 secondes dans la zone 0
        {
            map.sprite[tank.y][tank.x] = valeurSprite.Sol;
            tank.tempsMort = 0;
            fenetre.nombreTank--;
            tank.nombreVie = 5;
        }
        if(tank.tempsMort == 0)
            tank.tempsMort = SDL_GetTicks();
    }
    if(tank.nombreVie <= 0)
    {
        FMOD_System_PlaySound(fenetre.system, (FMOD_CHANNELINDEX)7, tank.explose, 0, NULL);
        map.sprite[tank.y][tank.x] = valeurSprite.Sol;
        tank.tempsMort = 0;
        fenetre.nombreTank--;
        tank.nombreVie = 5;
        tank.tempGeneration = SDL_GetTicks();
        tank.tempsMort = SDL_GetTicks();
    }
}

/* Mode Ennemie avion */

void genererAvion()
{
    int i;
    int time = SDL_GetTicks();
    /* Pour generer un ennemie à gauche de l'écran */
    if(fenetre.nombreAvion < 1)
    {
        if(time - avion.tempGeneration > FREQUENCE_AVION)
        {
            if(choplifter.zone == 3 || choplifter.x == 4) // On n'est a gauche
            {
                if(map.finX < (LONGEUR_TOTAL_MAP * (NOMBRE_ZONE_LONGEUR - 4)))
                {
                    avion.y = 5;
                    avion.finZone = map.finX + 1;
                    avion.x = avion.finZone;
                    avion.debutZone = map.finX - 14;
                    avion.direction = Gauche;
                    avion.planeActuel = avion.plane[avion7];
                    map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                    avion.nombrePhase = 10;
                    fenetre.nombreAvion++;
                }
            }
            if(choplifter.zone == 1 || choplifter.zone == 2)
            {
                if(map.debutX > 10 && map.finX < (LONGEUR_TOTAL_MAP * (NOMBRE_ZONE_LONGEUR - 2)))
                {
                    avion.y = 5;
                    avion.debutZone = map.debutX -1;
                    avion.x = avion.debutZone;
                    avion.finZone = map.debutX + 14;
                    avion.direction = Droite;
                    avion.planeActuel = avion.plane[avion1];
                    map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                    avion.nombrePhase = 10;
                    fenetre.nombreAvion++;
                }
            }
        }
        if(avion.tempGeneration == 0)
            avion.tempGeneration = SDL_GetTicks();
    }
}

void trouverZoneAvion()
{
    if(avion.x > map.debutX && avion.x < map.finX)
    {
        if(avion.x <= (map.debutX + (LONGEUR_TOTAL_MAP / 2)))
            avion.zone = 1; // On n'est a gauche
        else
            avion.zone = 2; // On n'est a droite
    }
    else
        avion.zone = 0;
}

/* Bouger l'Avion */

void deplacerAvion()
{
    int time = SDL_GetTicks();
    int valeurSpriteTemporaire;
    if(time - avion.frameLimit > VITESSE_ENNEMIES_AVION && avion.direction == Droite)
    {
        switch(avion.nombrePhase)
        {
            case 10: // Haut Gauche
                avion.position = avion1;
                avion.planeActuel = avion.plane[avion1];
                avion.x++;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y][avion.x - 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 9: // Bas Gauche
                avion.position = avion2;
                avion.planeActuel = avion.plane[avion2];
                avion.x++;
                avion.y--;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y + 1][avion.x - 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 8: // Haut Droite
                avion.position = avion2;
                avion.planeActuel = avion.plane[avion2];
                avion.x++;
                avion.y--;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y + 1][avion.x - 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 7: // Haut Droite
                avion.position = avion2;
                avion.planeActuel = avion.plane[avion2];
                avion.x++;
                avion.y--;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y + 1][avion.x - 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 6: // Bas Droite
                avion.position = avion1;
                avion.planeActuel = avion.plane[avion1];
                avion.x++;
                avion.y--;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y + 1][avion.x - 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 5: // Haut Gauche
                avion.position = avion1;
                avion.planeActuel = avion.plane[avion1];
                avion.x++;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y][avion.x - 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 4: // Bas Gauche
                avion.position = avion6;
                avion.planeActuel = avion.plane[avion6];
                avion.x++;
                avion.y++;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y - 1][avion.x - 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 3: // Haut Droite
                avion.position = avion6;
                avion.planeActuel = avion.plane[avion6];
                avion.x++;
                avion.y++;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y - 1][avion.x - 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 2: // Haut Gauche
                avion.position = avion42;
                avion.planeActuel = avion.plane[avion42];
                avion.x--;
                avion.y++;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y - 1][avion.x + 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 1: // Bas Gauche
                avion.position = avion7;
                avion.planeActuel = avion.plane[avion7];
                avion.x--;
                avion.y++;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y - 1][avion.x + 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
        }
        avion.frameLimit = SDL_GetTicks();
        if(avion.nombrePhase == 0)  // J'ai mis 5 pour l'instant (voir image si on continue le combat
        {
            avion.direction = Gauche;
            avion.nombrePhase = 10;
        }
        shot3();
    }
    if(time - avion.frameLimit > VITESSE_ENNEMIES_AVION && avion.direction == Gauche)
    {
        switch(avion.nombrePhase)
        {
            case 10: // Gauche
                avion.position = avion7;
                avion.planeActuel = avion.plane[avion7];
                avion.x--;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y][avion.x + 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 9: // Diagonale Bas Gauche
                avion.position = avion8;
                avion.planeActuel = avion.plane[avion8];
                avion.x--;
                avion.y--;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y + 1][avion.x + 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 8: // Diagonale Bas Gauche
                avion.position = avion8;
                avion.planeActuel = avion.plane[avion8];
                avion.x--;
                avion.y--;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y + 1][avion.x + 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 7: // Diagonale Bas Gauche
                avion.position = avion8;
                avion.planeActuel = avion.plane[avion8];
                avion.x--;
                avion.y--;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y + 1][avion.x + 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 6: // Gauche
                avion.position = avion7;
                avion.planeActuel = avion.plane[avion7];
                avion.x--;
                avion.y--;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y + 1][avion.x + 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 5: // Gauche
                avion.position = avion7;
                avion.planeActuel = avion.plane[avion7];
                avion.x--;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y][avion.x + 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 4: // Gauche
                avion.position = avion12;
                avion.planeActuel = avion.plane[avion12];
                avion.x--;
                avion.y++;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y - 1][avion.x + 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 3: // Haut gauche
                avion.position = avion12;
                avion.planeActuel = avion.plane[avion12];
                avion.x--;
                avion.y++;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y - 1][avion.x + 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 2: // Bas Droite
                avion.position = avion43;
                avion.planeActuel = avion.plane[avion43];
                avion.x++;
                avion.y++;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y - 1][avion.x - 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
            case 1: // Bas Droite
                avion.position = avion1;
                avion.planeActuel = avion.plane[avion1];
                avion.x++;
                avion.y++;
                map.sprite[avion.y][avion.x] = valeurSprite.Avion;
                map.sprite[avion.y - 1][avion.x - 1] = valeurSprite.Blanc;
                avion.nombrePhase--;
                break;
        }
        avion.frameLimit = SDL_GetTicks();
        if(avion.nombrePhase == 0)
        {
            avion.direction = Droite;
            avion.nombrePhase = 10;
        }
    }
}

/* Libère l'avion si il est dans la zone 0 */

void annulerAvion()
{
    int time = SDL_GetTicks();

    trouverZoneAvion();
    if(avion.zone == 0)
    {
        if(time - avion.tempsMort > 4000) // Si il fait 4 secondes dans la zone 0
        {
            map.sprite[avion.y][avion.x] = valeurSprite.Blanc;
            avion.tempsMort = 0;
            fenetre.nombreAvion--;
        }
        if(avion.tempsMort == 0)
            avion.tempsMort = SDL_GetTicks();
    }
    if(avion.nombreVie <= 0)
    {
        FMOD_System_PlaySound(fenetre.system, (FMOD_CHANNELINDEX)8, avion.explose, 0, NULL);

        map.sprite[avion.y][avion.x] = valeurSprite.Blanc;
        avion.tempsMort = 0;
        fenetre.nombreAvion--;
        avion.nombreVie = 5;
        avion.tempsMort = SDL_GetTicks();
        avion.tempGeneration = SDL_GetTicks();
    }
}

/* Mode Ennemie Boss */

bool peutGenererBoss()
{
    int i;
    int cpt = 0;

    for(i=0; i<civil.nombreBatiment; i++)
    {
        if(civil.batiment[i][3] == valeurSprite.MaisonD && civil.totalCivil[i] == 0)
            cpt++;
    }
    if(cpt == civil.nombreBatiment)
        return true;
    else
        return false;
}

void genererBoss()
{
    int k = 0; // Variable Aléatoire entre

    /* Pour generer un ennemie à gauche de l'écran */ // On doit changer la condition d'appel du boss
    if(fenetre.nombreBoss < 1 && boss.nombreVie > 0)
    {
        if(choplifter.zone == 3 || choplifter.x == 4) // On n'est a droite
        {
            if(map.finX < (LONGEUR_TOTAL_MAP * (NOMBRE_ZONE_LONGEUR - 2)))
            {
                boss.y = 5;
                boss.x = map.debutX + 8;
                boss.direction = Droite;
                boss.sangohanActuel = boss.sangohan[avion9];
                boss.nombrePhase = 11;

                // On determine le nombre de phase Grace au random pour le Generer à 3 positions dans cette direction
                k = rand() % 3;
                switch(k)
                {
                    case 0:
                        boss.nombrePhase = 7;
                        boss.x = map.debutX + 9;
                        boss.y = 3;
                        break;
                    case 1:
                        boss.nombrePhase = 3;
                        boss.x = map.finX - 3;
                        boss.y = 3;
                        break;
                }

                fenetre.nombreBoss++;
                boss.apparition = 0;
            }
        }
        if(choplifter.zone == 1 || choplifter.zone == 2) // On n'est a gauche
        {
            if(map.debutX > 10)
            {
                boss.y = 5;
                boss.x = map.finX - 8;
                boss.direction = Gauche;
                boss.sangohanActuel = boss.sangohan[avion9];
                boss.nombrePhase = 11;

                // On determine le nombre de phase Grace au random pour le Generer à 3 positions dans cette direction
                k = rand() % 3;
                switch(k)
                {
                    case 0:
                        boss.nombrePhase = 7;
                        boss.x = map.finX - 7;
                        boss.y = 3;
                        break;
                    case 1:
                        boss.nombrePhase = 3;
                        boss.x = map.debutX + 3;
                        boss.y = 3;
                        break;
                }

                fenetre.nombreBoss++;
                boss.apparition = 0;
            }
        }
    }
}

void trouverZoneBoss()
{
    if(boss.x > map.debutX && boss.x < map.finX)
    {
        if(boss.x <= (map.debutX + (LONGEUR_TOTAL_MAP / 2)))
            boss.zone = 1; // On n'est a gauche
        else
            boss.zone = 2; // On n'est a droite
    }
    else
        boss.zone = 0;
}

/* Bouger l'Avion */

void deplacerBoss()
{
    int time = SDL_GetTicks();

    if(boss.apparition == 0)
    {
        boss.position = boss9;
        boss.sangohanActuel = boss.sangohan[boss9];
        boss.apparition++;
        map.sprite[boss.y][boss.x] = valeurSprite.Boss;
        map.sprite[boss.y][boss.x - 1] = valeurSprite.Blanc;
    }
    else
    {
        if(time - boss.frameLimit > VITESSE_ENNEMIE_BOSS && boss.direction == Droite)
        {
            switch(boss.nombrePhase)
            {
                case 11:
                    boss.position = boss9;
                    boss.sangohanActuel = boss.sangohan[boss9];
                    boss.x++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                case 10: // Haut Gauche
                    boss.position = boss1;
                    boss.sangohanActuel = boss.sangohan[boss1];
                    boss.x++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 9: // Bas Gauche
                    boss.position = boss1;
                    boss.sangohanActuel = boss.sangohan[boss1];
                    boss.x++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 8: // Haut Droite
                    boss.position = boss3;
                    boss.sangohanActuel = boss.sangohan[boss3];
                    boss.x++;
                    boss.y--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y + 1][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 7: // Haut Droite
                    boss.position = boss3;
                    boss.sangohanActuel = boss.sangohan[boss3];
                    boss.x++;
                    boss.y--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y + 1][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 6: // Bas Droite
                    boss.position = boss1;
                    boss.sangohanActuel = boss.sangohan[avion1];
                    boss.x++;
                    boss.y--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y + 1][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 5: // Haut Gauche
                    boss.position = boss1;
                    boss.sangohanActuel = boss.sangohan[boss1];
                    boss.x++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 4: // Bas Gauche
                    boss.position = boss8;
                    boss.sangohanActuel = boss.sangohan[boss8];
                    boss.x++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 3: // Haut Droite
                    boss.position = boss8;
                    boss.sangohanActuel = boss.sangohan[boss8];
                    boss.x++;
                    boss.y++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y - 1][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 2: // Haut Gauche
                    boss.position = boss8;
                    boss.sangohanActuel = boss.sangohan[boss8];
                    boss.x++;
                    boss.y++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y - 1][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 1: // Bas Gauche
                    boss.position = boss6;
                    boss.sangohanActuel = boss.sangohan[boss6];
                    boss.x++;
                    boss.y++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y - 1][boss.x - 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
            }
            boss.frameLimit = SDL_GetTicks();
            if(boss.nombrePhase == 0)  // J'ai mis 5 pour l'instant (voir image si on continue le combat
            {
                boss.direction = Gauche;
                boss.nombrePhase = 10;
            }
            shot4();
        }
        if(time - boss.frameLimit > VITESSE_ENNEMIE_BOSS && boss.direction == Gauche)
        {
            switch(boss.nombrePhase)
            {
                case 11:
                    boss.position = boss9;
                    boss.sangohanActuel = boss.sangohan[boss9];
                    boss.x--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                case 10: // Gauche
                    boss.position = boss2;
                    boss.sangohanActuel = boss.sangohan[boss2];
                    boss.x--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 9: // Diagonale Bas Gauche
                    boss.position = boss2;
                    boss.sangohanActuel = boss.sangohan[boss2];
                    boss.x--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y ][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 8: // Diagonale Bas Gauche
                    boss.position = boss4;
                    boss.sangohanActuel = boss.sangohan[boss8];
                    boss.x--;
                    boss.y--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y + 1][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 7: // Diagonale Bas Gauche
                    boss.position = boss4;
                    boss.sangohanActuel = boss.sangohan[boss4];
                    boss.x--;
                    boss.y--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y + 1][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 6: // Gauche
                    boss.position = boss2;
                    boss.sangohanActuel = boss.sangohan[boss2];
                    boss.x--;
                    boss.y--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y + 1][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 5: // Gauche
                    boss.position = boss2;
                    boss.sangohanActuel = boss.sangohan[boss2];
                    boss.x--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 4: // Gauche
                    boss.position = boss7;
                    boss.sangohanActuel = boss.sangohan[boss7];
                    boss.x--;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 3: // Haut gauche
                    boss.position = boss7;
                    boss.sangohanActuel = boss.sangohan[boss7];
                    boss.x--;
                    boss.y++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y - 1][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 2: // Bas Droite
                    boss.position = boss7;
                    boss.sangohanActuel = boss.sangohan[boss7];
                    boss.x--;
                    boss.y++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y - 1][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
                case 1: // Bas Droite
                    boss.position = boss5;
                    boss.sangohanActuel = boss.sangohan[boss5];
                    boss.x--;
                    boss.y++;
                    map.sprite[boss.y][boss.x] = valeurSprite.Boss;
                    map.sprite[boss.y - 1][boss.x + 1] = valeurSprite.Blanc;
                    boss.nombrePhase--;
                    break;
            }
            shot4();
            boss.frameLimit = SDL_GetTicks();
            if(boss.nombrePhase == 0)
            {
                boss.direction = Droite;
                boss.nombrePhase = 10;
            }
        }
    }
}


void annulerBoss()
{
    int time = SDL_GetTicks();

    trouverZoneBoss();
    if(boss.zone == 0)
    {
        if(time - boss.tempsMort > 4000) // Si il fait 4 secondes dans la zone 0
        {
            map.sprite[boss.y][boss.x] = valeurSprite.Blanc;
            boss.tempsMort = 0;
            fenetre.nombreBoss--;
        }
        if(boss.tempsMort == 0)
            boss.tempsMort = SDL_GetTicks();
    }
    if(boss.nombreVie < 0)
    {
        map.sprite[boss.y][boss.x] = valeurSprite.Blanc;
        boss.tempsMort = 0;
        fenetre.nombreBoss--;
        boss.tempsMort = SDL_GetTicks();
    }
}

/* Gestion des civils */

void genererCivil()
{
    int k;
    /* On teste Pour voir si le batiment est detruit */

    trouverZoneHelicopter();
    for(k=0; k<=civil.nombreBatiment; k++)
    {
        if(civil.nombreOtage[k] < 1 && civil.totalCivil[k] > 0)
        {
            if((civil.batiment[k][1] >= map.debutX && civil.batiment[k][1] <= map.finX)
               &&(civil.batiment[k][2] <= 0) && map.debutX > 1)
            {
                map.sprite[civil.batiment[k][0] + 1][civil.batiment[k][1]] = valeurSprite.Otage;

                civil.x = civil.batiment[k][1];
                civil.y = civil.batiment[k][0] + 1;

                civil.finZone = civil.batiment[k][1] + 3;
                civil.debutZone = civil.batiment[k][1] - 3;

                civil.nombreVie[k] = 5; // c'est la vie de chaque otage qui apparait touché 2 fois il meurre

                if(choplifter.zone == 3 || choplifter.x == 4) // On n'est a gauche
                    civil.direction = Droite;
                if(choplifter.zone == 1 || choplifter.x == 2) // On n'est a gauche
                    civil.direction = Gauche;
                civil.otageActuel = civil.otage[otage1];
                fenetre.nombreOtage = k;
                civil.nombreOtage[fenetre.nombreOtage]++;
            }
        }
    }
}

/* Faire deplacer les civils dans des directions pour qu'il monte dans l'hélicopter */

void deplacerCivil()
{
    int time = SDL_GetTicks();
    int valeurSpriteTemporaire;
    int k;

    civil.bougevers = 0;
    if(choplifter.poser == poser
       && (choplifter.x >= (civil.debutZone - map.debutX)*SPRITE_RESOLUTION)
       &&(choplifter.x <= (civil.finZone - map.debutX)*SPRITE_RESOLUTION)
       && map.debutX > 1)
    {
       civil.bougevers = 1;
    }

    if ((civil.x - map.debutX) * SPRITE_RESOLUTION <= choplifter.x )
        civil.vershelico = 1;

    if ((civil.x - map.debutX) * SPRITE_RESOLUTION >= choplifter.x + 100)
        civil.vershelico = 2;

    if (((civil.x - map.debutX) * SPRITE_RESOLUTION > choplifter.x)
        && ((civil.x - map.debutX) * SPRITE_RESOLUTION < choplifter.x + 100)
        && (choplifter.passagers < NOMBRE_PASSAGER_MAX))
    {
        civil.vershelico = 3;
        // Une premier phase de teste pour vérifier si il y a de la place
        // dans notre hélicopter sinon on fait passer bougerver à 0
    }


    if(civil.nombreOtage[fenetre.nombreOtage] > 0)
    {
        if(time - civil.frameLimit > VITESSE_CIVIL && civil.direction == Droite && civil.bougevers == 0)
        {
            civil.x++;
            civil.otageActuel = civil.otage[otage3];
            map.sprite[civil.y][civil.x] = valeurSprite.Otage;
            map.sprite[civil.y][civil.x - 1] = valeurSprite.Sol;
            civil.frameLimit = SDL_GetTicks();
            if(civil.x == civil.finZone)
            {
                civil.direction = Gauche;
                civil.otageActuel = civil.otage[otage5];
            }
        }

        if(time - civil.frameLimit > VITESSE_CIVIL && civil.direction == Gauche && civil.bougevers == 0 )
        {
            civil.x--;
            civil.otageActuel = civil.otage[otage5];
            map.sprite[civil.y][civil.x] = valeurSprite.Otage;
            map.sprite[civil.y][civil.x + 1] = valeurSprite.Sol;
            civil.frameLimit = SDL_GetTicks();
            if(civil.x == civil.debutZone)
            {
                civil.direction = Droite;
                civil.otageActuel = civil.otage[otage3];
            }
        }

        if(time - civil.frameLimit > VITESSE_CIVIL && civil.bougevers == 1)
        {
            if (civil.vershelico == 1) {
                civil.x++;
                civil.otageActuel = civil.otage[otage3];
                map.sprite[civil.y][civil.x] = valeurSprite.Otage;
                map.sprite[civil.y][civil.x - 1] = valeurSprite.Sol;
                civil.frameLimit = SDL_GetTicks();
            }

            if (civil.vershelico == 2) {
                civil.x--;
                civil.otageActuel = civil.otage[otage5];
                map.sprite[civil.y][civil.x] = valeurSprite.Otage;
                map.sprite[civil.y][civil.x + 1] = valeurSprite.Sol;
                civil.frameLimit = SDL_GetTicks();
            }

            if (civil.vershelico == 3)
            {
                civil.y++;
                civil.otageActuel = civil.otage[otage1];
                map.sprite[civil.y][civil.x] = valeurSprite.Otage;
                map.sprite[civil.y - 1][civil.x ] = valeurSprite.Sol;
                embarquerOtage();
                civil.frameLimit = SDL_GetTicks();
            }
        }
    }

    if(safe.debarquement == 1 && time - civil.frameLimit > VITESSE_CIVIL)
    {
        // On verifie que cet otage est entrée
        if(civil.x >= safe.xB && civil.x <= safe.xB + 1
           && civil.y >= safe.yB && civil.y <= safe.yB)
        {
            safe.debarquement = 0;
            map.sprite[civil.y][civil.x] = valeurSprite.Sol;
        }
        else
        {
            civil.x--;
            civil.otageActuel = civil.otage[otage5];
            map.sprite[civil.y][civil.x] = valeurSprite.Otage;
            map.sprite[civil.y][civil.x + 1] = valeurSprite.Sol;
            civil.frameLimit = SDL_GetTicks();
        }
    }

}

void trouverZoneOtage()
{
    if(civil.x > map.debutX && civil.x < map.finX && map.debutX > 1)
    {
        if(civil.x <= (map.debutX + (LONGEUR_TOTAL_MAP / 2)))
            civil.zone = 1; // On n'est a gauche
        else
            civil.zone = 2; // On n'est a droite
    }
    else
        civil.zone = 0;
}

/* Libère l'avion si il est dans la zone 0 */

void annulerOtage()
{
    int time = SDL_GetTicks();
    int k;

    trouverZoneOtage();

    if(civil.zone == 0 && map.debutX > 1)
    {
        if(time - civil.tempsMort > 400 && civil.batiment[fenetre.nombreOtage][3] == valeurSprite.MaisonD) // Si il fait 4 secondes dans la zone 0
        {
            map.sprite[civil.y][civil.x] = valeurSprite.Sol;
            civil.tempsMort = 0;
            civil.nombreOtage[fenetre.nombreOtage]--;
        }
        if(civil.tempsMort == 0)
            civil.tempsMort = SDL_GetTicks();
    }
}

void embarquerOtage()
{
    if(map.debutX > 1 && civil.nombreOtage[fenetre.nombreOtage] > 0) // Pour ne pas prendre plus de 16 Otages
    {
        civil.nombreOtage[fenetre.nombreOtage]--;
        civil.totalCivil[fenetre.nombreOtage]--;
        choplifter.passagers++;
        map.sprite[civil.y][civil.x] = valeurSprite.Sol;
    }
}

void debarquerOtage()
{
    int i;
    int j;
    if(safe.xA >= map.debutX && safe.xA <= map.finX && choplifter.passagers > 0
       && safe.debarquement == 0 && choplifter.poser == poser)
    {
        i = (safe.xA - map.debutX) * SPRITE_RESOLUTION;
        j = safe.yA * SPRITE_RESOLUTION;

        if(i >= choplifter.x  &&  i <= (choplifter.x + SPRITE_RESOLUTION)
           && (j >= choplifter.y && j <= (choplifter.y + SPRITE_RESOLUTION)))
        {
            choplifter.passagers--;
            civil.saved++;
            safe.debarquement = 1;
            civil.x = safe.xA - 1;
            civil.y = safe.yA;
        }
    }
}

void trouverZoneHelicopter()
{
    if(choplifter.x <= (fenetre.ecran->w)/2) // On n'est à Gauche
    {
        if(choplifter.y <= (fenetre.ecran->h)/2)
            choplifter.zone = 1;
        else
            choplifter.zone = 2;
    }
    else
    {
        if(choplifter.y <= (fenetre.ecran->h)/2)
            choplifter.zone = 3;
        else
            choplifter.zone = 4;
    }
}

void shot()
{
    int time = SDL_GetTicks();
    int randt = rand()%2;

        switch (randt) {
            case 0 :
            choplifter.tirCanon = channel.tir;
            break;

            case 1 :
            choplifter.tirCanon = channel.tir2;
            break;
        }

    if((time - choplifter.tirprec > 100) && (balle[0].shot == 0) && (choplifter.position == Gauche))
    {
        FMOD_System_PlaySound(fenetre.system,(FMOD_CHANNELINDEX)3, choplifter.tirCanon, 0, NULL); // son du tir
        balle[0].direction = vers_gauche;
        balle[0].x = choplifter.x;
        balle[0].y = choplifter.y + VITESSE_BALLE;
        balle[0].shot = 1;
        choplifter.tirprec = SDL_GetTicks();
    }

    if((time - choplifter.tirprec > 100) && (choplifter.position == Bas) && (balle[0].shot == 0))
    {
        if (clavier.Left)
            balle[0].direction = vers_gauche_bas;
        else if (clavier.Right)
            balle[0].direction = vers_droite_bas;
        else
            balle[0].direction = vers_bas;

        FMOD_System_PlaySound(fenetre.system, FMOD_CHANNEL_FREE, choplifter.tirCanon, 0, NULL); // On fait jouer de la musique

        balle[0].x = choplifter.x + VITESSE_BALLE;
        balle[0].y = choplifter.y + VITESSE_BALLE;
        balle[0].shot = 1;
        choplifter.tirprec = SDL_GetTicks();
    }

    if((time - choplifter.tirprec > 100) && (choplifter.position == Droite) && (balle[0].shot == 0))
    {

        FMOD_System_PlaySound(fenetre.system, FMOD_CHANNEL_FREE, choplifter.tirCanon, 0, NULL); // On fait jouer de la musique

        balle[0].direction = vers_droite;
        balle[0].x = choplifter.x + VITESSE_BALLE;
        balle[0].y = choplifter.y + VITESSE_BALLE;
        balle[0].shot = 1;
        choplifter.tirprec = SDL_GetTicks();
    }
}

/* Tir du tank */

void shot2()
{
    int time = SDL_GetTicks();

    int randt = rand() % 2;
    int i;
    int j;

    if(time - tank.tirprec > TEMPS_TIR_ENNEMI && balle[1].shot == 0)
    {
        i = (tank.x - map.debutX) * SPRITE_RESOLUTION;
        j = tank.y * SPRITE_RESOLUTION;
        balle[1].shot = 1;
        tank.tirprec = SDL_GetTicks();

        switch (randt) {
            case 0 :
            tank.tirCanon = channel.tir3;
            break;

            case 1 :
            tank.tirCanon = channel.tir4;
            break;
            }

        FMOD_System_PlaySound(fenetre.system,(FMOD_CHANNELINDEX)4 , tank.tirCanon, 0, NULL); // On fait jouer de la musique


        switch(tank.position)
        {
            case tank2:
                balle[1].direction = vers_haut_droite;
                balle[1].x = i + 35;
                balle[1].y = j;
                break;

            case tank3:
                balle[1].direction = vers_haut;
                balle[1].x = i + 25;
                balle[1].y = j;
                break;

            case tank4:
                balle[1].direction = vers_gauche_haut;
                balle[1].x = i + 15;
                balle[1].y = j;
                break;
        }
    }
}

/* Tir avion */

void shot3()
{
    int i;
    int j;
    int time = SDL_GetTicks();

    int randt = rand () % 2;

    if(time - avion.tirprec > TEMPS_TIR_ENNEMI)
    {
        i = (avion.x - map.debutX) * SPRITE_RESOLUTION;
        j = avion.y * SPRITE_RESOLUTION;
        avion.tirprec = SDL_GetTicks();
        balle[2].shot = 1;

        switch (randt) {
            case 0 :
            avion.tirCanon = channel.tir3;
            break;

            case 1 :
            avion.tirCanon = channel.tir4;
            break;
            }

        FMOD_System_PlaySound(fenetre.system, (FMOD_CHANNELINDEX)5, avion.tirCanon, 0, NULL); // On fait jouer de la musique


        switch (avion.position)
        {
            case avion1:
                 balle[2].direction = vers_droite;
                 balle[2].x = i + 50;
                 balle[2].y = j + 25;
                 break;

/*            case avion18:
                 balle[2].direction = vers_droite;
                 balle[2].x = i + 50;
                 balle[2].y = j + 25;
                 break;
*/
            case avion2:
                balle[2].direction = vers_haut_droite;
                balle[2].x = i + 50;
                balle[2].y = j;
                break;

            case avion3:
                balle[2].direction = vers_haut_droite;
                balle[2].x = i + 50;
                balle[2].y = j;
                break;

/*            case avion13:
                balle[2].direction = vers_haut;
                balle[2].x = i + 25;
                balle[2].y = j;
                break;

            case avion14:
                balle[2].direction = vers_haut;
                balle[2].x = i + 25;
                balle[2].y = j;
                break;

*/
            case avion8:
                balle[2].direction = vers_gauche_haut;
                balle[2].x = i;
                balle[2].y = j;
                break;

            case avion9:
                balle[2].direction = vers_gauche_haut;
                balle[2].x = i;
                balle[2].y = j;
                break;


            case avion7:
                balle[2].direction = vers_gauche;
                balle[2].x = i;
                balle[2].y = j + 25;
                break;

/*            case avion17:
                balle[2].direction = vers_gauche;
                balle[2].x = i;
                balle[2].y = j + 25;
                break;
*/
            case avion12:
                balle[2].direction = vers_gauche_bas;
                balle[2].x = i;
                balle[2].y = j + 50;
                break;

            case avion42:
                balle[2].direction = vers_gauche_bas;
                balle[2].x = i;
                balle[2].y = j + 50;
                break;

/*            case avion15:
                balle[2].direction = vers_bas;
                balle[2].x = i + 25;
                balle[2].y = j + 50;
                break;

            case avion16:
                balle[2].direction = vers_bas;
                balle[2].x = i + 25;
                balle[2].y = j + 50;
                break;
*/
            case avion43:
                balle[2].direction = vers_droite_bas;
                balle[2].x = i + 50;
                balle[2].y = j + 50;
                break;

            case avion6:
                balle[2].direction = vers_droite_bas;
                balle[2].x = i + 50;
                balle[2].y = j + 50;
                break;
        }
    }
}

/* Tir Boss */

void shot4()
{
    int i;
    int j;
    int time = SDL_GetTicks();

    int randt = rand () % 2;

    if(time - boss.tirprec > TEMPS_TIR_BOSS)
    {
        i = (boss.x - map.debutX) * SPRITE_RESOLUTION;
        j = boss.y * SPRITE_RESOLUTION;
        boss.tirprec = SDL_GetTicks();
        balle[2].shot = 1;
        FMOD_System_PlaySound(fenetre.system, (FMOD_CHANNELINDEX)12, boss.tirCanon, 0, NULL); // On fait jouer de la musique


//        FMOD_System_PlaySound(fenetre.system, (FMOD_CHANNELINDEX)5, boss.tirCanon, 0, NULL); // On fait jouer de la musique

        switch (boss.position)
        {
            case boss1:
                 balle[2].direction = vers_droite;
                 balle[2].x = i + 10;
                 balle[2].y = j;
                 break;

            case boss2:
                balle[2].direction = vers_gauche;
                balle[2].x = i - 10;
                balle[2].y = j;
                break;

            case boss3:
                balle[2].direction = vers_haut_droite;
                balle[2].x = i + 10;
                balle[2].y = j - 10;
                break;

            case boss4:
                balle[2].direction = vers_gauche_haut;
                balle[2].x = i - 10;
                balle[2].y = j - 10;
                break;

            case boss5:
                balle[2].direction = vers_droite;
                balle[2].x = i + 10;
                balle[2].y = j;
                break;

            case boss6:
                balle[2].direction = vers_gauche;
                balle[2].x = i + 10;
                balle[2].y = j;
                break;

            case boss7:
                balle[2].direction = vers_haut_droite;
                balle[2].x = i + 10;
                balle[2].y = j - 10;
                break;

            case boss8:
                balle[2].direction = vers_gauche_haut;
                balle[2].x = i - 10;
                balle[2].y = j - 10;
                break;
        }
    }
}

/* Procedure qui permet à l'hélicopter de se déplacer */

void deplacerHelicopeter()
{
    SDL_Event event;
    Uint8* keys = SDL_GetKeyState(NULL);

        if (FMOD_Channel_IsPlaying (channel.channelfly, 0 ) != FMOD_OK )
            FMOD_System_PlaySound(fenetre.system,(FMOD_CHANNELINDEX)2, choplifter.vole, 0, NULL); // son de l'helico

    // Test si l'hélico est posé
    if(choplifter.y < GROUND) {
        choplifter.poser = decolle;
        FMOD_Channel_SetPaused(channel.channelfly, 0);
    }
    else {
        choplifter.poser = poser;
        choplifter.y = GROUND;
        FMOD_Channel_SetPaused(channel.channelfly, 1);

        if(choplifter.position == Gauche)
            choplifter.heli = choplifter.helicopter[gauche];

        if(choplifter.position == Bas)
            choplifter.heli = choplifter.helicopter[centre];

        if(choplifter.position == Droite)
            choplifter.heli = choplifter.helicopter[droite];
    } //Fin test si hélico est posé

    //Cas touche gauche appuyée
    if((keys[SDLK_LEFT]==1) && (choplifter.poser == decolle) && (choplifter.latence != 1) && (choplifter.etatmort != 1) ) {
        if (map.bouge == 0) {
            if (choplifter.x > 0) {
                clavier.Left = 1;
                choplifter.x -= VITESSE_HELICOPTER;

                if(choplifter.position == Gauche)
                    choplifter.heli = choplifter.helicopter[gauche_avance];

                if(choplifter.position == Droite)
                    choplifter.heli = choplifter.helicopter[droite_recule];

                if(choplifter.position == Bas)
                    choplifter.heli = choplifter.helicopter[centre_gauche];
            }
        }

        if (map.bouge == 1) {
            if (choplifter.x  >= 150) {
            clavier.Left = 1;
            choplifter.x -= VITESSE_HELICOPTER;

            if(choplifter.position == Gauche)
                choplifter.heli = choplifter.helicopter[gauche_avance];

            if(choplifter.position == Droite)
                choplifter.heli = choplifter.helicopter[droite_recule];

            if(choplifter.position == Bas)
                choplifter.heli = choplifter.helicopter[centre_gauche];
            }
        }
    } //Fin touche gauche appuyée

    // Cas touche droite appuyée
    if((keys[SDLK_RIGHT] == 1) && (choplifter.poser == decolle) && (choplifter.latence != 1) && (choplifter.etatmort != 1))
    {
        if (map.bouge == 0) {
            if(choplifter.x < OUTSCREEN) {
                clavier.Right = 1;
                choplifter.x += VITESSE_HELICOPTER;
            }

            if(choplifter.position == Gauche)
                choplifter.heli = choplifter.helicopter[gauche_recule];
            if(choplifter.position == Droite)
                choplifter.heli = choplifter.helicopter[droite_avance];
            if(choplifter.position == Bas )
                choplifter.heli = choplifter.helicopter[centre_droite];
        }

        if (map.bouge == 1) {
            if (choplifter.x <= 450) {
                clavier.Right = 1;
                choplifter.x += VITESSE_HELICOPTER;
            }

            if(choplifter.position == Gauche)
                choplifter.heli = choplifter.helicopter[gauche_recule];
            if(choplifter.position == Droite)
                choplifter.heli = choplifter.helicopter[droite_avance];
            if(choplifter.position == Bas )
                choplifter.heli = choplifter.helicopter[centre_droite];
        }
    } //Fin touche droite appuyée

    //Cas 2 directions appuyées
    if (((keys[SDLK_LEFT]==1)&&(keys[SDLK_RIGHT]==1)) || choplifter.etatmort == 1) {
        map.bouge=0;
        clavier.Right=0;
        clavier.Left=0;

        if(choplifter.position == Gauche)
            choplifter.heli = choplifter.helicopter[gauche];

        if(choplifter.position == Droite)
            choplifter.heli = choplifter.helicopter[droite];

        if(choplifter.position == Bas )
            choplifter.heli = choplifter.helicopter[centre];
    } //Fin 2 directions appuyées

    //Cas touche haut appuyée
    if ((keys[SDLK_UP]==1) && (choplifter.latence != 1) && (choplifter.etatmort != 1)) {
        if(choplifter.y >0)
            choplifter.y -= VITESSE_HELICOPTER;
    } //Fin touche haut appuyée

    //Cas touche bas appuyée
    if ((keys[SDLK_DOWN]==1) && (choplifter.latence != 1) && (choplifter.etatmort != 1)) {
        if ((choplifter.y < GROUND ) && (choplifter.latence != 1))
            choplifter.y += VITESSE_HELICOPTER;
    } //Fin touche bas appuyée

    //Cas d'aucune direction appuyée
    if((keys[SDLK_LEFT]==0) && (keys[SDLK_RIGHT]==0)) {
        if(choplifter.position == Gauche )
            choplifter.heli = choplifter.helicopter[gauche];

        if(choplifter.position == Bas)
            choplifter.heli = choplifter.helicopter[centre];

        if(choplifter.position == Droite)
            choplifter.heli = choplifter.helicopter[droite];

        clavier.Left=0;
        clavier.Right=0;
    } //Fin aucune direction appuyée

    //Cas aucune touche appuyée
    if(((keys[SDLK_RIGHT] == 0) && (keys[SDLK_LEFT] == 0) && (keys[SDLK_UP] == 0) && (keys[SDLK_DOWN] == 0)) || (choplifter.latence == 1)) {
        if(choplifter.y < GROUND ) {
            if(choplifter.descends == 3) {
                choplifter.descends=0;
                choplifter.y += VITESSE_HELICOPTER - (VITESSE_HELICOPTER/2);
            }
            choplifter.descends++;
        }
    } // Fin aucune touche appuyée

    //Switch Keydown
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT :
            fenetre.jeu = 0;
            fenetre.continuer = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym )
            {
                case SDLK_PRINT:
                    SDL_SaveBMP(fenetre.ecran, "screenshot/img.bmp");
                    break;
                case SDLK_e:
                    if ((choplifter.poser == decolle) && (choplifter.latence != 1)) {
                        choplifter.heli = choplifter.helicopter[gauche];
                        choplifter.position = Gauche;
                    }
                    break;

                case SDLK_r:
                    if ((choplifter.poser == decolle) && (choplifter.latence != 1)) {
                        choplifter.heli = choplifter.helicopter[centre];
                        choplifter.position = Bas;
                    }
                    break;

                case SDLK_t:
                    if ((choplifter.poser == decolle) && (choplifter.latence != 1)) {
                        choplifter.heli = choplifter.helicopter[droite];
                        choplifter.position=Droite;
                    }
                    break;
                case SDLK_ESCAPE:
                    fenetre.jeu = 0;
                    fenetre.rejouer = 0;
                    FMOD_Channel_SetPaused (channel.channelfly, 1) ;
                    FMOD_Channel_Stop (channel.channelmusic) ;
                    break;
                case SDLK_SPACE:
                    choplifter.canon = 1;
                    break;
            } // Fin Switch de sélection de key appuyée
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    clavier.Left = 0;
                    break;
                case SDLK_RIGHT:
                    clavier.Right = 0;
                    break;
                case SDLK_SPACE:
                    choplifter.canon = 0;
                    break;
            }
            break;
    }

    // Ajout pour les collisions

    /* Pour les avions */
    if (choplifter.latence == 1) {

        switch(choplifter.position) {
                case Bas:
                    choplifter.heli = choplifter.helicopter[latence_bas];
                    break;

                case Droite:
                    choplifter.heli = choplifter.helicopter[latence_droite];
                    break;

                case Gauche:
                    choplifter.heli = choplifter.helicopter[latence_gauche];
                    break;
            }
    }

    if (choplifter.etatmort == 1) {
            switch(choplifter.position) {
                case Bas:
                    choplifter.heli = choplifter.helicopter[latence_bas];
                    break;

                case Droite:
                    choplifter.heli = choplifter.helicopter[latence_droite];
                    break;

                case Gauche:
                    choplifter.heli = choplifter.helicopter[latence_gauche];
                    break;
            }

    }
    /* Collision pour les soucoupes */
    if(choplifter.toucheSoucoupe > 0)
    {
        choplifter.nombreVie--;
        choplifter.toucheSoucoupe = 0;
    }
}

void annulerHelicopter () {

    int lat = SDL_GetTicks();

    if (choplifter.etatmort == 1) {
        if ( lat - choplifter.latencemort > 2000 ) {
            choplifter.etatmort = 0;
            civil.MIA = civil.MIA + choplifter.passagers;
            choplifter.passagers = 0;
            choplifter.nombreVie = NOMBRE_VIE_HELICOPTER;
            choplifter.vie --;

        }
    }

    if (choplifter.nombreVie < 1 ) {
        if (choplifter.vie > 0) {

            FMOD_System_PlaySound(fenetre.system, (FMOD_CHANNELINDEX)6, choplifter.explose, 0, NULL);
            choplifter.etatmort = 1;
            //choplifter.latencemort = SDL_GetTicks();
        }

        else {
            FMOD_System_PlaySound(fenetre.system, (FMOD_CHANNELINDEX)6, choplifter.explose, 0, NULL);
            FMOD_Channel_Stop (channel.channelmusic);
            FMOD_Channel_Stop (channel.channelfly);
            fenetre.jeu = 0;
            fenetre.continuer = 0;
        }
    }
}

/* Phase 8 Detection de collision */

/* Procedure qui verifie les collisions des tirs de notre hélicopter sur les ennemies */

void collisionDetected()
{
    int i;
    int j;
    int k;

    /* On teste d'abord les coordonnées des Avions */

    if(avion.x > map.debutX && avion.x < map.finX)
    {
        i = (avion.x - map.debutX) * SPRITE_RESOLUTION;
        j = avion.y * SPRITE_RESOLUTION;

        if((balle[0].x >= i && balle[0].x <= (i + SPRITE_RESOLUTION))
           && (balle[0].y >= j && balle[0].y <= (j + SPRITE_RESOLUTION)))
        {
            avion.nombreVie--;
            affichageCollision(i, j);
            balle[0].shot = 0;
        }
    }

    /* On teste les coordonnées des Soucoupes */

    if(soucoupe.x > map.debutX && soucoupe.x < map.finX)
    {
        i = (soucoupe.x - map.debutX) * SPRITE_RESOLUTION;
        j = soucoupe.y * SPRITE_RESOLUTION;

        if((balle[0].x >= i && balle[0].x <= (i + SPRITE_RESOLUTION))
           && (balle[0].y >= j && balle[0].y <= (j + SPRITE_RESOLUTION)))
        {
            soucoupe.nombreVie--;
            affichageCollision(i, j);
            balle[0].shot = 0;
        }
    }

    /* On teste les collisions sur les batiment */

    for(k=0; k<=civil.nombreBatiment; k++)
    {
        if(civil.batiment[k][1] >= map.debutX && civil.batiment[k][1] <= map.finX)
        {
            i = (civil.batiment[k][1] - map.debutX) * SPRITE_RESOLUTION;
            j = civil.batiment[k][0] * SPRITE_RESOLUTION;

            /* Permet aux tirs alliés de détruire les tentes */

            if((balle[0].x >= i - 30 && balle[0].x <= (i + SPRITE_RESOLUTION))
               && (balle[0].y >= j - 30 && balle[0].y <= (j + SPRITE_RESOLUTION))
               && (balle[0].shot == 1))
            {
                affichageCollision(i, j);
                civil.batiment[k][2]--;
                if(civil.batiment[k][2] < 0) {
                    civil.batiment[k][3] = valeurSprite.MaisonD;
                    FMOD_System_PlaySound(fenetre.system, (FMOD_CHANNELINDEX)10, fenetre.batisplosion, 0, NULL);

                }

                if(civil.batiment[k][2] == 0) {
                    map.sprite[civil.batiment[k][0]][civil.batiment[k][1]] = valeurSprite.MaisonD;
                    FMOD_System_PlaySound(fenetre.system, (FMOD_CHANNELINDEX)10, fenetre.batisplosion, 0, NULL);
                }

                balle[0].shot = 0;
            }

            /* Phase Pour permettre aux tirs ennemies de détruire les tentes */

            /* Permettre au tire des tanks de détruires les tentes */

            if((balle[1].x >= i - 30 && balle[1].x <= (i + SPRITE_RESOLUTION))
               && (balle[1].y >= j - 30 && balle[1].y <= (j + SPRITE_RESOLUTION))
               && (balle[1].shot == 1))
            {
                affichageCollision(i, j);
                civil.batiment[k][2]--;
                if(civil.batiment[k][2] < 0)
                    civil.batiment[k][3] = valeurSprite.MaisonD;
                if(civil.batiment[k][2] == 0)
                    map.sprite[civil.batiment[k][0]][civil.batiment[k][1]] = valeurSprite.MaisonD;
                balle[1].shot = 0;
            }

            /* Permettre au tire des avions de détruires les tentes */


            if((balle[2].x >= i - 30 && balle[2].x <= (i + SPRITE_RESOLUTION))
               && (balle[2].y >= j - 30 && balle[2].y <= (j + SPRITE_RESOLUTION))
               && (balle[2].shot == 1))
            {
                affichageCollision(i, j);
                civil.batiment[k][2]--;
                if(civil.batiment[k][2] < 0)
                    civil.batiment[k][3] = valeurSprite.MaisonD;
                if(civil.batiment[k][2] == 0)
                    map.sprite[civil.batiment[k][0]][civil.batiment[k][1]] = valeurSprite.MaisonD;
                balle[2].shot = 0;
            }
        }
    }

    /* Collisions sur les hotages */

    if(civil.nombreOtage[fenetre.nombreOtage] > 0  && civil.totalCivil[fenetre.nombreOtage] > 0)
    {
        /* Permettre aux tanks de tirer sur les Otages */
        i = (civil.x - map.debutX) * SPRITE_RESOLUTION;
        j = civil.y * SPRITE_RESOLUTION;
        if((balle[1].x >= i - 30 && balle[1].x <= (i + SPRITE_RESOLUTION))
           && (balle[1].y >= j - 30 && balle[1].y <= (j + SPRITE_RESOLUTION))
           && (balle[1].shot == 1))
        {
            affichageCollision(i, j);
            civil.nombreVie[fenetre.nombreOtage]--;
            civil.nombreOtage[fenetre.nombreOtage]--;
            civil.totalCivil[fenetre.nombreOtage]--;
            civil.MIA++;
            FMOD_System_PlaySound(fenetre.system,(FMOD_CHANNELINDEX)11, fenetre.civildown, 0, NULL);
            map.sprite[civil.y][civil.x] = valeurSprite.Sol;

            balle[1].shot = 0;
        }

        /* Permettre aux avions de tirer sur les Otages */

        if((balle[2].x >= i - 30 && balle[2].x <= (i + SPRITE_RESOLUTION))
           && (balle[2].y >= j - 30 && balle[2].y <= (j + SPRITE_RESOLUTION))
           && (balle[2].shot == 1))
        {
            affichageCollision(i, j);
            civil.nombreVie[fenetre.nombreOtage]--;
            civil.nombreOtage[fenetre.nombreOtage]--;
            civil.totalCivil[fenetre.nombreOtage]--;
            civil.MIA++;
            FMOD_System_PlaySound(fenetre.system,(FMOD_CHANNELINDEX)11, fenetre.civildown, 0, NULL);
            map.sprite[civil.y][civil.x] = valeurSprite.Sol;

            balle[2].shot = 0;
        }

        /* Permettre aux tirs alliés de tuer les civils */

        if((balle[0].x >= i - 30 && balle[0].x <= (i + SPRITE_RESOLUTION))
           && (balle[0].y >= j - 30 && balle[0].y <= (j + SPRITE_RESOLUTION))
           && (balle[0].shot == 1))
        {
            affichageCollision(i, j);
            civil.nombreVie[fenetre.nombreOtage]--;
            civil.nombreOtage[fenetre.nombreOtage]--;
            civil.totalCivil[fenetre.nombreOtage]--;
            civil.MIA++;
            FMOD_System_PlaySound(fenetre.system,(FMOD_CHANNELINDEX)11, fenetre.civildown, 0, NULL);
            map.sprite[civil.y][civil.x] = valeurSprite.Sol;

            balle[0].shot = 0;
        }
    }

    /* On teste les collisions sur les tanks */

    if(tank.x >= map.debutX && tank.x <= map.finX)
    {
        i = (tank.x - map.debutX) * SPRITE_RESOLUTION;
        j = tank.y * SPRITE_RESOLUTION;

        if((balle[0].x >= i && balle[0].x <= (i + SPRITE_RESOLUTION)) && (balle[0].y >= j && balle[0].y <= (j + SPRITE_RESOLUTION)))
        {
            tank.nombreVie--;
            affichageCollision(i, j);
            balle[0].shot = 0;
        }
    }

    /* On les collision sur le boss */

    if(boss.x > map.debutX && boss.x < map.finX)
    {
        i = (boss.x - map.debutX) * SPRITE_RESOLUTION;
        j = boss.y * SPRITE_RESOLUTION;

        if((balle[0].x >= i && balle[0].x <= (i + SPRITE_RESOLUTION))
           && (balle[0].y >= j && balle[0].y <= (j + SPRITE_RESOLUTION)))
        {
            boss.nombreVie--;
            affichageCollision(i, j);
            balle[0].shot = 0;
        }
    }

}

/* Procedure qui detecte si notre Hélicopter (Choplifter) entre en collision avec un Avion Ennemie */

void collisionCrash()
{
    int i;
    int j;
    int time=SDL_GetTicks();

    /* On teste d'abord les coordonnées des Avions */

    if(avion.x > map.debutX && avion.x < map.finX)
    {
        i = (avion.x - map.debutX) * SPRITE_RESOLUTION;
        j = avion.y * SPRITE_RESOLUTION;

        if((choplifter.x >= i && choplifter.x <= (i + SPRITE_RESOLUTION))
           && (choplifter.y >= j && choplifter.y <= (j + SPRITE_RESOLUTION)))
        {
            //choplifter.nombreVie--;
            choplifter.tpscollision = SDL_GetTicks();
            choplifter.latence = 1;
        }

        if (choplifter.tpscollision != 0) {
            if (time - choplifter.tpscollision > TEMPS_LATENCE ) {
                choplifter.tpscollision = 0;
                choplifter.latence = 0;
            }
        }
    }

    /* On teste la collision sur la soucoupe */

    if(soucoupe.x > map.debutX && soucoupe.x < map.finX)
    {
        i = (soucoupe.x - map.debutX) * SPRITE_RESOLUTION;
        j = soucoupe.y * SPRITE_RESOLUTION;

        if((choplifter.x >= i && choplifter.x <= (i + SPRITE_RESOLUTION))
           && (choplifter.y >= j && choplifter.y <= (j + SPRITE_RESOLUTION)))
        {
            choplifter.toucheSoucoupe++;
        }
    }


    /* On detecte si les tirs ennemies touche notre Hélicpter */
    if((balle[1].x >= choplifter.x && balle[1].x <= choplifter.x + SPRITE_RESOLUTION)
       && (balle[1].y >= choplifter.y && balle[1].y <= choplifter.y + SPRITE_RESOLUTION)
       && (balle[1].shot == 1))
    {
        i = balle[1].x;
        j = balle[1].y;
        if (choplifter.nombreVie == 1)
            choplifter.latencemort = SDL_GetTicks();
        choplifter.nombreVie --;
        affichageCollision(i, j);
        balle[1].shot = 0;
    }

    if((balle[2].x >= choplifter.x && balle[2].x <= choplifter.x + SPRITE_RESOLUTION)
       && (balle[2].y >= choplifter.y && balle[2].y <= choplifter.y + SPRITE_RESOLUTION)
       && (balle[2].shot == 1))
    {
        i = balle[2].x;
        j = balle[2].y;
        if (choplifter.nombreVie == 1)
            choplifter.latencemort = SDL_GetTicks();
        choplifter.nombreVie --;
        affichageCollision(i, j);
        balle[2].shot = 0;
    }
}

/* Phase 9 Fin de Partie */

void fin()
{
    if(fenetre.terminer == 0)
    {
        if(choplifter.vie == 0 && choplifter.nombreVie == 0)
        {
            fenetre.terminer = 1;
            fenetre.timeOver = SDL_GetTicks();
        }
    }
}

/* Phase 0 principale */

/* Procedure qui nous permet d'avoir 60 images/s */

void delay(unsigned int frameLimit)
{
    /* Gestion des 60 fps (images/stories/seconde) */

    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}


void jeu()
{
    int i;
    fenetre.frameLimit = SDL_GetTicks();
    while(fenetre.jeu)
    {
        if (FMOD_Channel_IsPlaying (channel.channelmusic, 0 ) != FMOD_OK )
            FMOD_System_PlaySound(fenetre.system,(FMOD_CHANNELINDEX)1, fenetre.musicgame, 0, NULL); // musique jeu

        deplacerHelicopeter();
        annulerHelicopter();
        trouverZoneHelicopter();
        if(peutGenererBoss())
            genererBoss();
        else
        {
            genererTank();
            genererAvion();
            genererSoucoupe();
        }

        if(fenetre.nombreBoss > 0)
        {
            deplacerBoss();
            annulerBoss();
        }
        if(fenetre.nombreSoucoupe > 0)
        {
            deplacerSoucoupe();
            annulerSoucoupe();
        }

        if(fenetre.nombreTank > 0)
        {
            modeCombatTank();
            shot2();
            deplacerTank();
            annulerTank();
        }
        if(fenetre.nombreAvion > 0)
        {
            deplacerAvion();
            shot3();
            annulerAvion();
        }

        genererCivil();
        deplacerCivil();
        debarquerOtage();
        annulerOtage();

        fin();
        miseAJour();
        if(fenetre.terminer == 1)
        {
            affichageGameOver();
            fenetre.continuer = 0;
        }
        else
            affichageGenerale();
        //delay(fenetre.frameLimit);
        fenetre.frameLimit = SDL_GetTicks() + 16;
    }
}

/* Commencer */

void commencer()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
                fenetre.menu = 0;
                fenetre.continuer = 0;
                fenetre.jeu = 0;
                fenetre.rejouer = 0;
                break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    fenetre.continuer = 0;
                    fenetre.rejouer = 0;
                    break;
            }
            break;
    }
    switch(fenetre.menu)
    {
        case 0:
            initiConstante();
            initiMapVide();
            initiDebutPartie();
            fenetre.terminer = 0;
            chargementNiveau();

            fenetre.jeu = 1;
            jeu();
            break;
        case 1:
            fenetre.jeu = 1;
            jeu();
            break;
        /*case 2:
            option();
            break;
        case SDLK_4:
            fenetre.continuer = 0;
            break;*/
    }
}

int main(int argc, char** argv)
{
    /* main "PM" */

    srand(time(NULL));

    fenetre.frameLimit = SDL_GetTicks() + 16;
    fenetre.rejouer = 1;

    initiGenerale();

    chargementNiveau();
    fenetre.terminer = 0;

    while(fenetre.continuer)
    {
        affichageMenuPrincipale();

        /* Boucle principale du jeu */
        if(fenetre.terminer == 2)
        {
            initiConstante();
            initiMapVide();
            initiDebutPartie();
            fenetre.terminer = 0;
            chargementNiveau();
        }
        commencer();

        // Pour faire le level éditor
        /*editeurMap();
        miseAJour();
        affichageGenerale();*/
    }

    liberation();

    return EXIT_SUCCESS;
}
