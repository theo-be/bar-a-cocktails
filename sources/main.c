#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "cocktail.h"
#include "menu.h"



int main (int argc, char** argv) {
    // boisson_struc* stock = remplirstock();

    char quitter = 0;
    char arborescence[100] = {0};

    // do {
    //     quitter = afficherMenu(arborescence);
    // } while (quitter != 'q');


	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);

    afficherTableau();

    // printf("%c%c\n", "coucou"[0], "coucou"[4]);


    return 0;
}