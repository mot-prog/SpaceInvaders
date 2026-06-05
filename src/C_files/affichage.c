#include "../global.h"

void afficher_menu(text *text_affiche)
{
    tailleLutin(text_affiche->menu_texte, &largeur, &hauteur);
    afficherLutin(text_affiche->menu_texte, (SCREEN_LENGTH - largeur) / 2, SCREEN_HEIGHT * 0.1);
    tailleLutin(text_affiche->manette_texte, &largeur, &hauteur);
    afficherLutin(text_affiche->manette_texte, (SCREEN_LENGTH - largeur) / 2, SCREEN_HEIGHT - SCREEN_HEIGHT * 0.4);
    tailleLutin(text_affiche->clavier_texte, &largeur, &hauteur);
    afficherLutin(text_affiche->clavier_texte, (SCREEN_LENGTH - largeur) / 2, SCREEN_HEIGHT * 0.5);
    afficherLutin(text_affiche->exit_text, 20, SCREEN_HEIGHT - 50);
}

void afficher_waiting_screen(text *text_affiche)
{
    // TEXT CENTRAL
    tailleLutin(text_affiche->wait_screen_text, &largeur, &hauteur);
    afficherLutin(text_affiche->wait_screen_text, (SCREEN_LENGTH - largeur) / 2, (SCREEN_HEIGHT - (2 * hauteur + 20)) / 2);
    tailleLutin(text_affiche->press_to_start_text, &largeur, &hauteur);
    afficherLutin(text_affiche->press_to_start_text, (SCREEN_LENGTH - largeur) / 2, (SCREEN_HEIGHT - (hauteur)) / 2);
}

void afficher_commandes(text *text_affiche, entite ship, L_entite L_m)
{
    tailleLutin(ship.sprite, &largeur, &hauteur);
    // Je profite de cette fonction pour afficher la vie du vaisseau.
    if (ship.life > 0)
    {
        int largeur_barre = ship.life * 8;
        int x_barre = ship.x + (largeur / 2) - (largeur_barre / 2);
        int y_barre = ship.y - 12;
        rectanglePlein(x_barre, y_barre, largeur_barre, 5, COULEUR_VERT);
    }

    afficherLutin(ship.sprite, ship.x, ship.y);

    tailleLutin(text_affiche->exit_text, &largeur, &hauteur);
    afficherLutin(text_affiche->exit_text, 10, SCREEN_HEIGHT - 30);
    afficherLutin(text_affiche->go_to_menu_text, largeur + 50, SCREEN_HEIGHT - 30);
    tailleLutin(text_affiche->manip_text, &largeur, &hauteur);
    afficherLutin(text_affiche->manip_text, SCREEN_LENGTH - largeur - 10, SCREEN_HEIGHT - 30);
    afficherLutin(text_affiche->line_text, 0, SCREEN_HEIGHT - hauteur - 40);
    afficherLutin_liste(L_m, 1);
}

void afficher_win(void)
{
    // On génère les textes UNE SEULE FOIS avant la boucle pour ne pas saturer la mémoire vidéo
    int titre = lutinTexte("VICTOIRE !", COULEUR_VERT);
    int sous_titre = lutinTexte("La galaxie est sauvee.", COULEUR_BLANC);

    int w_titre, h_titre, w_sous, h_sous;
    tailleLutin(titre, &w_titre, &h_titre);
    tailleLutin(sous_titre, &w_sous, &h_sous);

    // Mini-boucle d'animation de 4 secondes (400 itérations de 10ms)
    for (int i = 0; i < 400; i++)
    {
        effacerSurface();

        // Effet de clignotement arcade pour le titre (visible 30 frames, caché 10 frames)
        if (i % 40 < 30)
        {
            afficherLutin(titre, (SCREEN_LENGTH - w_titre) / 2, SCREEN_HEIGHT / 2 - 50);
        }

        // Le sous-titre reste fixe
        afficherLutin(sous_titre, (SCREEN_LENGTH - w_sous) / 2, SCREEN_HEIGHT / 2 + 50);

        majSurface();
        pauseIHM(10);
    }
}

void afficher_lose(void)
{
    int titre = lutinTexte("GAME OVER", COULEUR_ROUGE);
    int sous_titre = lutinTexte("La Terre a ete detruite...", COULEUR_GRIS);

    int w_titre, h_titre, w_sous, h_sous;
    tailleLutin(titre, &w_titre, &h_titre);
    tailleLutin(sous_titre, &w_sous, &h_sous);

    for (int i = 0; i < 400; i++)
    {
        effacerSurface();

        // Effet de chute pour le GAME OVER
        int y_cible = SCREEN_HEIGHT / 2 - 50;
        // Il descend de 4 pixels par frame jusqu'à atteindre sa cible
        int y_actuel = (i * 4 < y_cible) ? i * 4 : y_cible;

        afficherLutin(titre, (SCREEN_LENGTH - w_titre) / 2, y_actuel);

        // Le sous-titre n'apparaît que lorsque le Game Over a fini sa chute
        if (y_actuel == y_cible)
        {
            afficherLutin(sous_titre, (SCREEN_LENGTH - w_sous) / 2, SCREEN_HEIGHT / 2 + 50);
        }

        majSurface();
        pauseIHM(10);
    }
}