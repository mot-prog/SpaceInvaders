#pragma once
#include "../global.h"

void menu(text *text_affiche, evenement evt, char touche, commandes *com);
void waiting_screen(text *text_affiche, evenement evt, char *touche, commandes *com, entite ship, int incr, charger_sprite sprites, int *compteur, listes_chainees listes);
void play(text *text_affiche, evenement evt, char *touche, commandes *com, entite ship, int incr, charger_sprite sprites, int *compteur, listes_chainees listes);