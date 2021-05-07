#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>

#include "../sources/cocktail.h"
#include "../sources/menu.h"

int main(int argc, char** argv) {

    boisson_struc* stock = remplirstock();
    //commande(stock,0,2,0);

    // affichage();
    // affichage_type(122,2,stock);

    char quitter = 0;


    do {
        quitter = afficherMenu(stock);
    } while (quitter != 'q');

    return 0;
}