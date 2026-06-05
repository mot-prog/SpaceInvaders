/**** Bibliotheque graphique ****/

/** Fichiers d'inclusion **/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "libgraph.h"

/** Types **/

/** Constantes **/

#define BITS_PAR_PIXEL 32
#define MAX_LUTINS 100

static const SDL_Color couleurs[] = {{255, 255, 255, 255}, {0, 0, 0, 255}, {255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}, {255, 105, 180, 255}, {150, 150, 150, 255}, {-1, -1, -1, 255}};

/** Variables globales **/

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *police;

SDL_Texture *lutins[MAX_LUTINS];
int lutins_nb = 0;

/** Fonctions **/
void choisirPolice(const char *chemin, int taille)
{
  police = TTF_OpenFont(chemin, taille);
  if (!police)
  {
    SDL_Log("TTF_OpenFont Error: %s", TTF_GetError());
    return;
  }
}

/* Appeler avant d'afficher du texte */
void initialiserTexte()
{
  TTF_Init();
  choisirPolice(nomPoliceDefaut, TAILLE_POLICE_DEFAUT);
}

/* Initialisation de la surface dessinable */
bool creerSurface(int largeur, int hauteur, char *titre)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0) // AJOUT
  {
    SDL_Log("Erreur lors de l'initialisation de SDL: %s", SDL_GetError());
    return 0;
  }

  window = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largeur, hauteur, SDL_WINDOW_SHOWN);
  if (!window)
  {
    SDL_Log("Erreur lors de la création de la fenêtre: %s", SDL_GetError());
    SDL_Quit();
    return 0;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
  {
    SDL_Log("Erreur lors de la création du renderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
  }

  SDL_SetWindowTitle(window, titre);
  initialiserTexte();

  return (window != NULL && renderer != NULL && police != NULL);
}

/* Fermeture de la surface dessinable */
void fermerSurface(void)
{
  if (renderer != NULL)
  {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
  }

  if (window != NULL)
  {
    SDL_DestroyWindow(window);
    window = NULL;
  }

  if (police != NULL)
    TTF_CloseFont(police);
  TTF_Quit();
  SDL_Quit();
}

void rectanglePlein(int x, int y, int l, int h, int c)
{
  SDL_Color color = couleurs[c];
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x, y, l, h};
  SDL_RenderFillRect(renderer, &rect);
}

void effacerSurface(void)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear screen with black
  SDL_RenderClear(renderer);
}

void majSurface(void)
{
  SDL_RenderPresent(renderer);
}

void pauseIHM(int ms)
{
  SDL_Delay(ms);
}

static void configurerLutin(SDL_Texture *texture, int couleur)
{
  SDL_Color c = couleurs[couleur];
  SDL_SetTextureColorMod(texture, c.r, c.g, c.b);
}

int chargerLutin(char *fichier, int couleur)
{
  if (lutins_nb >= MAX_LUTINS)
    return -2;

  SDL_Surface *surface = SDL_LoadBMP(fichier);
  if (!surface)
  {
    SDL_Log("Erreur: Impossible de charger l'image %s: %s", fichier, SDL_GetError());
    return -1;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture)
  {
    SDL_Log("Erreur: Impossible de créer une texture: %s", SDL_GetError());
    return -1;
  }

  lutins[lutins_nb++] = texture;

  if (couleur >= 0)
    configurerLutin(texture, couleur);

  return lutins_nb - 1;
}

void afficherLutin(int lutin, int x, int y)
{
  if (lutin < 0 || lutin >= lutins_nb || !lutins[lutin])
    return;

  SDL_Rect position = {x, y, 0, 0};

  tailleLutin(lutin, &position.w, &position.h);

  SDL_RenderCopy(renderer, lutins[lutin], NULL, &position);
}

void tailleLutin(int lutin, int *largeur, int *hauteur)
{
  SDL_QueryTexture(lutins[lutin], NULL, NULL, largeur, hauteur);
}

void lireEvenement(evenement *evt, char *touche)
{
  SDL_Event event;
  *evt = aucun;
  *touche = 0;

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      *evt = quitter;
    }
    else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
      *evt = (event.type == SDL_KEYDOWN) ? touchePresse : toucheRelache;

      const char *nom = SDL_GetKeyName(event.key.keysym.sym);
      if (strlen(nom) == 1 && nom[0] >= 32 && nom[0] < 128)
      {
        *touche = nom[0]; // Store the key character
      }
      else
      {
        *touche = 0;
      }
      break; // Un seul événement à la fois
    }
  }
}

SDL_Texture *textureTexte(char *texte, int couleur)
{
  if (!police)
    return NULL;
  SDL_Color color = couleurs[couleur];

  SDL_Surface *surface = TTF_RenderText_Solid(police, texte, color);
  if (!surface)
  {
    SDL_Log("Erreur: Impossible de créer une surface de texte: %s", TTF_GetError());
    return NULL;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture)
  {
    SDL_Log("Erreur: Impossible de créer une texture de texte: %s", SDL_GetError());
    return NULL;
  }

  return texture;
}

int lutinTexte(char *texte, int couleur)
{
  SDL_Texture *texture = textureTexte(texte, couleur);
  if (texture != NULL)
  {
    lutins[lutins_nb++] = texture;
    return lutins_nb - 1;
  }
  else
    return -1;
}

void changerLutinTexte(char *texte, int couleur, int lutin)
{
  SDL_Texture *texture = textureTexte(texte, couleur);
  if (texture != NULL)
  {
    SDL_DestroyTexture(lutins[lutin]);
    lutins[lutin] = texture;
  }
}

void nettoyerLutins()
{
  for (int i = 0; i < lutins_nb; i++)
    SDL_DestroyTexture(lutins[i]);
}
