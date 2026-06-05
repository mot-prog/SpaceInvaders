#include "../global.h"

void menu(text *text_affiche, evenement evt, char touche, commandes *com)
{
    int keep_menu;
    do
    {
        effacerSurface();
        afficher_menu(text_affiche);
        majSurface();
        lireEvenement(&evt, &touche);
        pauseIHM(10);
        if (touche == 'C')
        {
            com->id = ID_CLAVIER,
            com->LEFT = 'Q',
            com->RIGHT = 'D',
            com->UP = 'Z',
            com->DOWN = 'S',
            com->tire = 'P',
            com->pouvoir = 'A',
            com->altf4 = 'W',
            com->autre = 'E',
            text_affiche->manip_text = lutinTexte("Gauche : Q    Droite : D    Tire : P    Pouvoir : A", COULEUR_BLANC);
            text_affiche->press_to_start_text = lutinTexte("PRESS 'S' FOR START", COULEUR_ROSE);
        };
        if (touche == 'J')
        {
            if (SDL_NumJoysticks() < 1)
            {
                effacerSurface();
                int error = lutinTexte("Controller not detected", COULEUR_ROUGE);
                tailleLutin(error, &largeur, &hauteur);
                afficherLutin(error, (SCREEN_LENGTH - largeur) / 2, (SCREEN_HEIGHT - hauteur) / 2);
                touche = 0;
                majSurface();
                pauseIHM(2000);
            }
            else
            {
                manette = SDL_JoystickOpen(0); /// dev/input/js0
                // CHANGER EN FONCTION DE CE QUE RENVOIT LE JOY
                com->id = ID_MANETTE,
                com->LEFT = 0,
                com->RIGHT = 0,
                com->UP = 0,
                com->DOWN = 0,
                com->tire = A,
                com->pouvoir = B,
                com->altf4 = C,
                com->autre = D,
                text_affiche->manip_text = lutinTexte("Gauche : Joy gauche    Droite : Joy droite    Tire : A    Pouvoir : D", COULEUR_BLANC);
                text_affiche->press_to_start_text = lutinTexte("PRESS 'D' FOR START", COULEUR_ROSE);
                changerLutinTexte("Quitter : C", COULEUR_ROUGE, text_affiche->exit_text);
            }
        };
        keep_menu = touche != 'W' && touche != 'C' && touche != 'J' && evt != quitter;

    } while (keep_menu);
}

void waiting_screen(text *text_affiche, evenement evt, char *touche, commandes *com, entite ship, int incr, charger_sprite sprites, int *compteur, listes_chainees listes)
{
    int keep_waiting = *touche != 'W' && *touche != 'A' && evt != quitter;
    int last_color = COULEUR_ROSE;
    int touches_pressees[256] = {0};

    while (keep_waiting)
    {
        lireEvenement(&evt, touche);
        maj_touches(touches_pressees, touche, evt);
        effacerSurface();

        mouvements(com, &ship, touches_pressees, 0, &(listes.missiles), sprites, *compteur, manette, touche);
        if (*touche == 'M')
        {
            menu(text_affiche, evt, *touche, com);
        }

        afficher_waiting_screen(text_affiche);
        afficher_commandes(text_affiche, ship, listes.L_m);
        animation_monstres(listes.L_m, &incr, *compteur, sprites);
        deplacer_entitees(listes.missiles, 0, -VITESSE_MISSILES);
        afficherLutin_liste(listes.missiles, 0);
        afficherLutin_liste(listes.shields, 1);

        (*compteur)++;           //+ 10ms par boucle environ.
        if (*compteur % 50 == 0) // soit toutes les 0.5s
        {
            // TEXT CENTRAL
            if (com->id == ID_CLAVIER)
            {
                if (*touche == 'M')
                {
                    menu(text_affiche, evt, *touche, com);
                }
                if (last_color == COULEUR_ROSE)
                {
                    changerLutinTexte("PRESS 'A' FOR START", COULEUR_BLEU, text_affiche->press_to_start_text);
                    changerLutinTexte("WAITING SCREEN", COULEUR_BLEU, text_affiche->wait_screen_text);
                    last_color = COULEUR_BLEU;
                }
                else
                {
                    changerLutinTexte("PRESS 'A' FOR START", COULEUR_ROSE, text_affiche->press_to_start_text);
                    changerLutinTexte("WAITING SCREEN", COULEUR_ROSE, text_affiche->wait_screen_text);
                    last_color = COULEUR_ROSE;
                }
            }
            if (com->id == ID_MANETTE)
            {
                if (last_color == COULEUR_ROSE)
                {
                    changerLutinTexte("PRESS 'D' FOR START", COULEUR_BLEU, text_affiche->press_to_start_text);
                    changerLutinTexte("WAITING SCREEN", COULEUR_BLEU, text_affiche->wait_screen_text);
                    last_color = COULEUR_BLEU;
                }
                else
                {
                    changerLutinTexte("PRESS 'D' FOR START", COULEUR_ROSE, text_affiche->press_to_start_text);
                    changerLutinTexte("WAITING SCREEN", COULEUR_ROSE, text_affiche->wait_screen_text);
                    last_color = COULEUR_ROSE;
                }
            }
        }
        majSurface();
        pauseIHM(10);
        keep_waiting = *touche != 'W' && *touche != 'A' && evt != quitter;
    }
}

void play(text *text_affiche, evenement evt, char *touche, commandes *com, entite ship, int incr, charger_sprite sprites, int *compteur, listes_chainees listes)
{
    int keep_playing = *touche != 'W' && evt != quitter;
    int touches_pressees[256] = {0};
    int y_enable = 0;
    int win = 0;
    int lose = 0;
    int ship_last_life = ship.life;

    while (keep_playing)
    {
        lireEvenement(&evt, touche);
        maj_touches(touches_pressees, touche, evt);
        effacerSurface();

        mouvements(com, &ship, touches_pressees, y_enable, &(listes.missiles), sprites, *compteur, manette, touche);
        if (*touche == 'M')
        {
            menu(text_affiche, evt, *touche, com);
        }

        lacher_bombes(&(listes.bombes), listes.L_m, sprites, *compteur);

        afficher_commandes(text_affiche, ship, listes.L_m);
        animation_monstres(listes.L_m, &incr, *compteur, sprites);
        animation_ship(&ship, sprites, &ship_last_life);
        deplacer_entitees(listes.missiles, 0, -VITESSE_MISSILES);
        deplacer_entitees(listes.bombes, 0, VITESSE_BOMBES);

        afficherLutin_liste(listes.missiles, 0);
        afficherLutin_liste(listes.shields, 1);
        afficherLutin_liste(listes.bombes, 0);

        Contact_liste_liste(listes.missiles, listes.bombes);
        Contact_liste_liste(listes.L_m, listes.missiles);
        Contact_liste_liste(listes.shields, listes.missiles);
        Contact_liste_liste(listes.shields, listes.bombes);
        Contact_entite_liste(&ship, listes.bombes);
        Contact_entite_liste(&ship, listes.L_m);

        nettoyer_hors_ecran(listes.missiles);
        nettoyer_hors_ecran(listes.bombes);

        nettoyer_morts(&(listes.L_m), sprites.explosion);
        nettoyer_morts(&(listes.missiles), -1);
        nettoyer_morts(&(listes.shields), -1);
        nettoyer_morts(&(listes.bombes), -1);

        if (listes.L_m == NULL)
        {
            afficher_win();
            win = 1;
        }
        if (ship.life == 0)
        {
            afficher_lose();
            lose = 1;
        }
        (*compteur)++; //+ 10ms par boucle environ.
        majSurface();
        pauseIHM(10);
        keep_playing = *touche != 'W' && evt != quitter && !lose && !win;
    }
}
