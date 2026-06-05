#pragma once
#include "../global.h"

void afficher_monstre(void);
void initialisation(listes_chainees *listes, entite *ship, charger_sprite sprites);
void animation_monstres(L_entite L_m, int *incr, int compteur, charger_sprite sprites);
void animation_ship(entite *ship, charger_sprite sprites, int *ship_last_life);
void mouvements(commandes *com, entite *ship, int *touches_pressees, int y_enable, L_entite *missiles, charger_sprite sprites, int compteur, SDL_Joystick *manette, char *touche);
void maj_touches(int *touchePresse, char *touche, evenement evt);
