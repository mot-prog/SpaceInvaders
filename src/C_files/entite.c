#include "../global.h"
//////////////////////////////////////////////
//////////Fonctions utiles du cours
//////////////////////////////////////////////
L_entite cons(entite e, L_entite next)
{
    L_entite p = malloc(sizeof(Node));
    p->E = e;
    p->next = next;
    return p;
}
void addAfter(entite i, L_entite p)
{
    L_entite next = cons(i, p->next);
    p->next = next;
}

void addHead(entite i, L_entite *l)
{
    L_entite head = cons(i, *l);
    *l = head;
}

void deleteHead(L_entite *l)
{
    L_entite p = *l;
    *l = (*l)->next;
    free(p);
}
void deleteAfter(L_entite p)
{
    L_entite next = p->next;
    p->next = next->next;
    free(next);
}
//////////////////////////////////////////////

void fabriquer_liste_invaders(entite m, L_entite *l_e)
{
    for (int j = 0; j < NB_INVADERS / LIGNES; j++)
    {
        for (int i = 0; i < LIGNES; i++)
        {
            entite nouveau_monstre = {
                .x = m.x + (i * 50),
                .y = m.y + (j * 50),
                .sprite = m.sprite,
                .life = INVADERS_LIVES,
            };
            addHead(nouveau_monstre, l_e);
        }
    }
}

void fabriquer_liste_shields(entite m, L_entite *l_e)
{
    tailleLutin(m.sprite, &largeur, &hauteur);

    int number = SCREEN_LENGTH / (SPACE_BETWEEN_SHIELDS + largeur);
    int largeur_totale_bloc = (number * largeur) + ((number - 1) * SPACE_BETWEEN_SHIELDS);
    int marge_gauche = (SCREEN_LENGTH - largeur_totale_bloc) / 2;

    for (int i = 0; i < number; i++)
    {
        entite nouveau_shield = {
            .x = marge_gauche + i * (largeur + SPACE_BETWEEN_SHIELDS),
            .y = m.y,
            .sprite = m.sprite,
            .life = SHIELDS_LIVES,
        };
        addHead(nouveau_shield, l_e);
    }
}

void afficherLutin_liste(L_entite L, int barre_de_vie)
{
    if (L == NULL)
    {
        return;
    }
    else
    {
        if (barre_de_vie)
        {
            tailleLutin(L->E.sprite, &largeur, &hauteur);
            if (L->E.life > 0)
            {
                int largeur_barre = L->E.life * 8;
                int x_barre = L->E.x + (largeur / 2) - (largeur_barre / 2);
                int y_barre = L->E.y - 12;
                rectanglePlein(x_barre, y_barre, largeur_barre, 5, COULEUR_VERT);
            }
        }
        afficherLutin(L->E.sprite, L->E.x, L->E.y);
        afficherLutin_liste(L->next, barre_de_vie);
    }
}

void deplacer_entitees(L_entite L, int incrX, int incrY)
{
    if (L == NULL)
        return;
    else
    {
        (L->E).x += incrX;
        (L->E).y += incrY;
        deplacer_entitees(L->next, incrX, incrY);
    }
}

void changer_entite(L_entite L_m, int sprite)
{
    if (L_m == NULL)
        return;
    else
    {
        L_m->E.sprite = sprite;
        changer_entite(L_m->next, sprite);
    }
}

void tirer(L_entite *missiles, charger_sprite sprites, entite ship)
{
    tailleLutin(ship.sprite, &largeur, &hauteur);
    int milieu_vaisseau = ship.x + largeur / 2 - 4;
    entite missile = {
        .x = milieu_vaisseau,
        .y = ship.y,
        .life = 1,
        .sprite = sprites.missile,
    };
    addHead(missile, missiles);
}

void lacher_bombes(L_entite *bombes, L_entite invaders, charger_sprite sprites, int compteur)
{
    if (compteur % 20 != 0 || invaders == NULL)
        return;

    L_entite liste = invaders;
    while (liste != NULL)
    {
        if (rand() % 5 == 0)
        {
            tailleLutin(liste->E.sprite, &largeur, &hauteur);
            int milieu_invader = liste->E.x + (largeur / 2) - 5;
            entite bombe = {
                .x = milieu_invader,
                .y = liste->E.y + hauteur,
                .life = 1,
                .sprite = sprites.bombe,
            };
            addHead(bombe, bombes);
            break;
        }
        liste = liste->next;
    }
}

void nettoyer_hors_ecran(L_entite L)
{
    while (L != NULL)
    {
        if (L->E.y < -50 || L->E.y > 2000)
        {
            L->E.life = 0;
        }
        L = L->next;
    }
}