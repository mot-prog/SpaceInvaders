#pragma once
#include "../global.h"

L_entite cons(entite e, L_entite next);
void addAfter(entite i, L_entite p);
void addHead(entite i, L_entite *l);
void deleteHead(L_entite *l);
void deleteAfter(L_entite p);
void fabriquer_liste_invaders(entite m, L_entite *l_e);
void fabriquer_liste_shields(entite m, L_entite *l_e);
void afficherLutin_liste(L_entite L, int barre_de_vie);
void deplacer_entitees(L_entite L, int incrX, int incrY);
void changer_entite(L_entite L_m, int sprite);
void tirer(L_entite *missiles, charger_sprite sprites, entite ship);
void lacher_bombes(L_entite *bombes, L_entite invaders, charger_sprite sprites, int compteur);
void nettoyer_hors_ecran(L_entite L);