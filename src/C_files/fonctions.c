#include "../global.h"

void afficher_monstre(void)
{
    creerSurface(500, 500, "test");
    int lutin1 = chargerLutin("Lutins/invader_monstre2_1.bmp", 3);
    int lutin2 = chargerLutin("Lutins/invader_monstre2_2.bmp", 3);
    for (int i = 0; i < 10; i++)
    {
        afficherLutin(lutin1, 200, 200);
        majSurface();
        pauseIHM(500);
        effacerSurface();
        majSurface();
        afficherLutin(lutin2, 200, 200);
        majSurface();
        pauseIHM(500);
        effacerSurface();
        majSurface();
    }
}

void initialisation(listes_chainees *listes, entite *ship, charger_sprite sprites)
{
    entite invader1 = {
        .x = BORD_GAUCHE,
        .y = BORD_GAUCHE,
        .sprite = sprites.monstre2_1,
        .life = INVADERS_LIVES,
        .timer_anim = 0,
    };
    entite shield1 = {
        .x = SPACE_BETWEEN_SHIELDS,
        .y = SCREEN_HEIGHT - 200,
        .sprite = sprites.bouclier,
        .life = SHIELDS_LIVES,
        .timer_anim = 0,
    };
    fabriquer_liste_invaders(invader1, &(listes->L_m));
    fabriquer_liste_shields(shield1, &(listes->shields));
    afficherLutin_liste(listes->L_m, 1);
    ship->x = (SCREEN_LENGTH - 30) / 2;
    ship->y = (SCREEN_HEIGHT - SCREEN_HEIGHT / 10);
    ship->sprite = sprites.canon;
    ship->life = SHIP_LIVES;
    majSurface();
}

void animation_monstres(L_entite L_m, int *incr, int compteur, charger_sprite sprites)
{
    int touche_bord = 0;
    L_entite courant = L_m;
    static int changer = 0;
    // Vérifier si l'essaim touche un bord de l'écran
    while (courant != NULL)
    {
        // Si on va vers la droite
        if (*incr > 0 && courant->E.x >= BORD_DROIT - largeur)
        {
            touche_bord = 1;
            break;
        }
        // Si on va vers la gauche
        if (*incr < 0 && courant->E.x <= BORD_GAUCHE)
        {
            touche_bord = 1;
            break;
        }
        courant = courant->next;
    }

    // Si un bord est touché : inversion et descente
    if (touche_bord)
    {
        *incr = -(*incr); // Inverser la direction

        // Descendre tous les monstres d'un cran
        courant = L_m;
        while (courant != NULL)
        {
            courant->E.y += 20; // Descend d'une ligne (50 pixels)
            courant = courant->next;
        }
    }

    // Deplacement
    if (compteur % VITESSE_INVADERS == 0)
        deplacer_entitees(L_m, *incr, 0);

    // Animation
    if (compteur % VITESSE_ANIMATION == 0) // soit toutes les 0.5s
    {
        if (changer)
        {
            changer_entite(L_m, sprites.monstre2_2);
            changer = 0;
        }
        else
        {
            changer_entite(L_m, sprites.monstre2_1);
            changer = 1;
        }
    }
}

void animation_ship(entite *ship, charger_sprite sprites, int *ship_last_life)
{
    // S'il a perdu de la vie
    if (ship->life < *ship_last_life)
    {
        ship->timer_anim = SHIP_ANIMATION_FRAMES;
        ship->sprite = sprites.canon_feraille;
        *ship_last_life = ship->life;
    }

    // Si le chronomètre d'animation est en cours
    if (ship->timer_anim > 0)
    {
        ship->timer_anim--;
        // Quand c'est fini, on remet le sprite normal
        if (ship->timer_anim == 0 && ship->life > 0)
        {
            ship->sprite = sprites.canon;
        }
    }
}

void mouvements(commandes *com, entite *ship, int *touches_pressees, int y_enable, L_entite *missiles, charger_sprite sprites, int compteur, SDL_Joystick *manette, char *touche)
{
    tailleLutin(ship->sprite, &largeur, &hauteur);
    static int dernier_tir = -CADENCE_DE_TIRE; // le moins pour lancer directement le premier missile

    if (com->id == ID_CLAVIER)
    {
        // DEPLACEMENT
        if (touches_pressees[com->LEFT] && ship->x > BORD_GAUCHE)
            ship->x -= VITESSE;
        if (touches_pressees[com->RIGHT] && ship->x < BORD_DROIT - largeur)
            ship->x += VITESSE;

        if (y_enable)
        {
            if (touches_pressees[com->UP] && ship->y > 50 - hauteur)
                ship->y -= VITESSE;
            if (touches_pressees[com->DOWN] && ship->y < SCREEN_HEIGHT)
                ship->y += VITESSE;
        }
        if (touches_pressees[com->tire] && (compteur - dernier_tir >= CADENCE_DE_TIRE))
        {
            tirer(missiles, sprites, *ship);
            dernier_tir = compteur;
        }
    }
    if (com->id == ID_MANETTE)
    {
        int exit = SDL_JoystickGetButton(manette, com->altf4);
        int start = SDL_JoystickGetButton(manette, com->autre);
        int fire = SDL_JoystickGetButton(manette, com->tire);
        if (exit)
        {
            *touche = 'W';
        }
        if (start)
        {
            *touche = 'A';
        }

        int axe_x = SDL_JoystickGetAxis(manette, 0);
        if (axe_x < -8000 || axe_x > 8000)
        {
            int deplacement_x = (axe_x * VITESSE) / 32767;
            if (deplacement_x < 0 && ship->x > 50)
            {
                ship->x += deplacement_x;
            }
            else if (deplacement_x > 0 && ship->x < SCREEN_LENGTH - 150)
            {
                ship->x += deplacement_x;
            }
        }
        if (y_enable)
        {
            int axe_y = -SDL_JoystickGetAxis(manette, 1);
            if (axe_y < -800 || axe_y > 800)
            {
                int deplacement_y = (axe_y * VITESSE) / 32767;

                if (deplacement_y < 0 && ship->y > 50)
                {
                    ship->y += deplacement_y;
                }
                else if (deplacement_y > 0 && ship->y < SCREEN_HEIGHT - 150)
                {
                    ship->y += deplacement_y;
                }
            }
        }
        if (fire && (compteur - dernier_tir >= CADENCE_DE_TIRE))
        {
            tirer(missiles, sprites, *ship);
            dernier_tir = compteur;
        }
    }
}

void maj_touches(int *touches_pressees, char *touche, evenement evt)
{
    if (evt == touchePresse && *touche != 0)
    {
        touches_pressees[(int)*touche] = 1; // On active la touche
    }
    else if (evt == toucheRelache && *touche != 0)
    {
        touches_pressees[(int)*touche] = 0; // On desactive la touche
    }
}
