/**** Bibliotheque graphique (definitions) ****/
#include <stdbool.h>

/** Types */
typedef enum
{
    quitter,
    touchePresse,
    toucheRelache,
    aucun
} evenement;

/** Constantes **/
#define COULEUR_BLANC 0
#define COULEUR_NOIR 1
#define COULEUR_ROUGE 2
#define COULEUR_VERT 3
#define COULEUR_BLEU 4
#define COULEUR_ROSE 5
#define COULEUR_GRIS 6

#define TAILLE_POLICE_DEFAUT 20

static const char nomPoliceDefaut[] = "Lutins/DejaVuSans.ttf";

/**
 * @brief cree une fenetre 2D
 *
 * @param largeur en pixels de la fenetre
 * @param hauteur en pixels de la fenetre
 * @param titre   de la fenetre (chaine de caractere)
 * @return true si ok, false sinon
 */
bool creerSurface(int largeur, int hauteur, char *titre);

/**
 * @brief libere la surface d'affichage
 *        a faire lors de la fermeture
 *        du programme
 */
void fermerSurface(void);

/**
 * @brief   dessine un rectange de taille (l,h) aux coordonnêes
 *          (x,y) et de couleur c
 *
 * @param x 0 <= x <= l_surface
 * @param y 0 <= y <= h_surface
 * @param l largeur en pixels
 * @param h longueur en pixels
 * @param c indice de couleur
 */
void rectanglePlein(int x, int y, int l, int h, int c);

/**
 * @brief   efface le contenu de la surface d'affichage
 */
void effacerSurface(void);

/**
 * @brief rafraichit la surface d'affichage
 */
void majSurface(void);

/**
 * @brief attend pendant un temps donné
 *
 * @param ms le temps à attendre, en millisecondes
 */
void pauseIHM(int ms);

/**
 * @brief charge un lutin à partir du fichier
 *
 * @param fichier image bitmap du lutin à charger
 * @param couleur la couleur à utiliser pour le lutin
 * @return numero de lutin
 * ou -1 si échec
 */
int chargerLutin(char *fichier, int couleur);

/**
 * @brief afficher un lutin aux coordonnées (x,y)
 *
 * @param lutin numero du lutin à afficher (< MAX_LUTINS)
 * @param x     abscisse de départ
 * @param y     ordonnée de départ
 */
void afficherLutin(int lutin, int x, int y);

/**
 * @brief crée un lutin à partir d'un texte
 *
 * @param texte le texte
 * @param couleur la couleur à utiliser pour le lutin
 * @return numero de lutin
 *  ou -1 si échec
 */
int lutinTexte(char *texte, int couleur);

/**
 * @brief met à jour un lutin de texte existant ; plus rapide que de
 * créer un nouveau texte
 *
 * @param texte le nouveau texte
 * @param couleur la couleur à utiliser pour le lutin
 * @param lutin le numéro de lutin existant
 */
void changerLutinTexte(char *texte, int couleur, int lutin);

/**
 * @brief calcule la taille (largeur,hauteur) d'un lutin
 *
 * @param lutin     index du lutin
 * @param largeur   pointeur sur la largeur
 * @param hauteur   pointeur sur la hauteur
 */
void tailleLutin(int lutin, int *largeur, int *hauteur);

/**
 * @brief libère l'espace utilisé par les lutins
 */
void nettoyerLutins();

/**
 * @brief lire une touche au clavier
 *
 * @param evt    pointeur sur evenement
 * @param touche pointeur sur la touche pressée
 */
void lireEvenement(evenement *evt, char *touche);
