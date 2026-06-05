#include <stdio.h>
#include "../Graphique-2.0/libgraph.h"

int main()
{
    char touche;
    evenement evt = aucun;
    creerSurface(1000, 1000, "test");
    majSurface();
    while (evt != quitter)
    {
        lireEvenement(&evt, &touche);
        printf("Touche : %c\n", touche);
        pauseIHM(200);
    }
    return 0;
}