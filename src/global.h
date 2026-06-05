#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include "Graphique-2.0/libgraph.h"
#include "inc/struct.h"
#include "inc/entite.h"
#include "inc/fonctions.h"
#include "inc/collisions.h"
#include "inc/affichage.h"

// DISPLAY
#define SCREEN_LENGTH 1500
#define SCREEN_HEIGHT 1000
#define BORD_GAUCHE 10
#define BORD_DROIT SCREEN_LENGTH - 10

// INVADERS
#define NB_INVADERS 80
#define LIGNES 10
#define INVADERS_LIVES 3
#define VITESSE_ANIMATION 50
#define FRAMES_PAR_BOUCLES 1
#define VITESSE_INVADERS 1
#define VITESSE_BOMBES 5
#define DEATH_ANIMATION_FRAMES 15

// ID
#define ID_CLAVIER 1
#define ID_MANETTE 2

// SHIP
#define SHIP_LIVES 5
#define VITESSE 10
#define VITESSE_MISSILES 5
#define CADENCE_DE_TIRE 25
#define SHIP_ANIMATION_FRAMES 25
// #define NB_MISSILES 100

// SHIELDS
#define SPACE_BETWEEN_SHIELDS 200
#define SHIELDS_LIVES 5

// MANETTE
#define A 0
#define B 1
#define C 2
#define D 3
#define K 4

extern int largeur, hauteur;
extern SDL_Joystick *manette;
