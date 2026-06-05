#pragma once
#include "../global.h"

int Contact(entite E1, entite E2);
void Contact_liste_liste(L_entite L1, L_entite L2);
void Contact_entite_liste(entite *E, L_entite L);
void nettoyer_morts(L_entite *L, int sprite_mort);