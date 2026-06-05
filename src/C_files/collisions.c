#include "../global.h"

int Contact(entite E1, entite E2)
{
    if (E1.life <= 0 || E2.life <= 0)
        return 0;

    tailleLutin(E1.sprite, &largeur, &hauteur);
    int largeur_E1 = largeur;
    int hauteur_E1 = hauteur;
    tailleLutin(E2.sprite, &largeur, &hauteur);
    int largeur_E2 = largeur;
    int hauteur_E2 = hauteur;

    int collision_x;
    if (E1.x + largeur_E1 < E2.x || E2.x + largeur_E2 < E1.x)
    {
        collision_x = 0;
    }
    else
        collision_x = 1;

    int collision_y;
    if (E1.y + hauteur_E1 < E2.y || E2.y + hauteur_E2 < E1.y)
    {
        collision_y = 0;
    }
    else
        collision_y = 1;

    if (collision_x && collision_y)
        return 1;
    else
        return 0;
}

void Contact_liste_liste(L_entite L1, L_entite L2)
{
    if (L1 == NULL || L2 == NULL)
    {
        return;
    }
    else
    {
        Contact_entite_liste(&(L1->E), L2);
        Contact_liste_liste(L1->next, L2);
    }
    return;
}

void Contact_entite_liste(entite *E, L_entite L)
{
    if (L == NULL)
    {
        return;
    }
    else
    {
        if (Contact(*E, L->E))
        {
            L->E.life--;
            E->life--;
        }
        Contact_entite_liste(E, L->next);
    }
    return;
}

void nettoyer_morts(L_entite *L, int sprite_mort)
{
    // 1. Tête de liste
    while (*L != NULL && (*L)->E.life <= 0)
    {
        // Si l'entité vient de mourir et qu'on a prévu une animation
        if (sprite_mort != -1 && (*L)->E.timer_anim == 0)
        {
            (*L)->E.timer_anim = DEATH_ANIMATION_FRAMES; // L'animation dure 15 images
            (*L)->E.sprite = sprite_mort;
            break; // On sort de la boucle pour le laisser s'afficher
        }
        // Si l'animation est en cours
        else if ((*L)->E.timer_anim > 1)
        {
            (*L)->E.timer_anim--;
            break;
        }
        // Si le timer est à 1 (ou s'il n'y a pas d'animation prévue)
        else
        {
            deleteHead(L);
        }
    }

    // Même procédé pour le reste de la liste
    L_entite liste = *L;
    if (liste != NULL)
    {
        while (liste->next != NULL)
        {
            L_entite next = liste->next;
            if (next->E.life <= 0)
            {
                if (sprite_mort != -1 && next->E.timer_anim == 0)
                {
                    next->E.timer_anim = DEATH_ANIMATION_FRAMES;
                    next->E.sprite = sprite_mort;
                    liste = liste->next;
                }
                else if (next->E.timer_anim > 1)
                {
                    next->E.timer_anim--;
                    liste = liste->next;
                }
                else
                {
                    deleteAfter(liste);
                }
            }
            else
            {
                liste = liste->next;
            }
        }
    }
}
