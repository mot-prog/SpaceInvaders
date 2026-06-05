#include "../global.h"
#include "../inc/jeu.h"

int largeur, hauteur;
SDL_Joystick *manette = NULL;

int main()
{
    // afficher_monstre();
    listes_chainees listes = {
        .bombes = NULL,
        .L_m = NULL,
        .missiles = NULL,
        .shields = NULL,
    };
    entite ship;
    commandes com;
    evenement evt = aucun;
    char touche = 0;
    int compteur = 0;

    creerSurface(SCREEN_LENGTH, SCREEN_HEIGHT, "Space Invader");

    char line[SCREEN_LENGTH];
    charger_sprite sprites = {
        .bombe = chargerLutin("Lutins/invader_bombe.bmp", COULEUR_BLANC),
        .bouclier = chargerLutin("Lutins/invader_bouclier.bmp", COULEUR_ROUGE),
        .canon = chargerLutin("Lutins/invader_canon.bmp", COULEUR_VERT),
        .canon_feraille = chargerLutin("Lutins/invader_canon_ferraille.bmp", COULEUR_VERT),
        .missile = chargerLutin("Lutins/invader_missile.bmp", COULEUR_BLANC),
        .monstre1_1 = chargerLutin("Lutins/invader_monstre1_1.bmp", COULEUR_BLANC),
        .monstre2_1 = chargerLutin("Lutins/invader_monstre2_1.bmp", COULEUR_VERT),
        .monstre2_2 = chargerLutin("Lutins/invader_monstre2_2.bmp", COULEUR_VERT),
        .monstre3_1 = chargerLutin("Lutins/invader_monstre3_1.bmp", COULEUR_ROSE),
        .ovni = chargerLutin("Lutins/invader_ovni.bmp", COULEUR_ROUGE),
        .explosion = chargerLutin("Lutins/invader_monstre_bouillie.bmp", COULEUR_ROUGE),
    };
    initialisation(&listes, &ship, sprites);

    effacerSurface();

    // TEXT ON THE SCREEN
    text text_affiche = {
        .exit_text = lutinTexte("Quitter : W", COULEUR_ROUGE),
        .clavier_texte = lutinTexte("Clavier : C", COULEUR_BLANC),
        .go_to_menu_text = lutinTexte("MENU : M", COULEUR_GRIS),
        .manette_texte = lutinTexte("Manette : J", COULEUR_BLANC),
        .manip_text = 0,
        .menu_texte = lutinTexte("MENU", COULEUR_ROSE),
        .press_to_start_text = 0,
        .line_text = lutinTexte("_", COULEUR_BLANC),
        .wait_screen_text = lutinTexte("WAITING SCREEN", COULEUR_ROSE)};

    tailleLutin(text_affiche.line_text, &largeur, &hauteur);
    // Taille de la ligne
    for (int i = 0; i < SCREEN_LENGTH; i++)
    {
        line[i] = '_';
    }
    changerLutinTexte(line, COULEUR_BLANC, text_affiche.line_text);
    menu(&text_affiche, evt, touche, &com);
    int incr = FRAMES_PAR_BOUCLES;
    waiting_screen(&text_affiche, evt, &touche, &com, ship, incr, sprites, &compteur, listes);
    if (touche == 'A')
    {
        play(&text_affiche, evt, &touche, &com, ship, incr, sprites, &compteur, listes);
    }
    fermerSurface();
    return 0;
}

// TODO: JOYSTICK
// BUG : garde l'état précédent de la manette
// Améliorer la précision du joystick. Pouvoir choisir avec le joystick dans le menu (mettre higlight sur le choix)

// TODO: animation de win et lose -> règle de lose si les invaders arrives à la fin.
// TODO: voir comment augmenter la vitesse des invaders car bloqué au minimum à 1 (logique inverse à régler).