#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "menu.h"



int main(int argc, char** argv) {
    // boisson_struc* stock = remplirstock();

    char quitter = 0;
    char arborescence[100] = {0};

    do {
        quitter = afficherMenu(arborescence);
    } while (quitter != 'q');


    // char oui[] = "Je suis un papillon";
    // supprimerAPartirDe(oui, "un");
    // printf("%s\n", oui);
    // char chaine[] = "bonjour coucou";
    // affichageCentre(chaine);
    return 0;
}