#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "cocktail.h"
#include "menu.h"
#include "cryptage.h"



int main (int argc, char** argv) {
    boisson_struc* stock = remplirstock_boisson();
    cocktail_struc* cocktail_liste = remplirstock_cocktail();

  /* for(int i = 0;i<taille;i++){
        
        printf("%s",stock[i].nom);

        if(strcmp(stock[i].categorie,"cocktail") == 0){

            printf(", sa composition :");

            for(int x = 0; x<5 ; x++){
                    if (cocktail_liste[stock[i].id-1].id_boisson[x] != 0){
                    printf(" %s ",stock[cocktail_liste[stock[i].id-1].id_boisson[x]].nom);
                    }
            }
        }
        printf("\n");
    }

*/

    char quitter = 0;
    char arborescence[100] = {0};

    do {
        quitter = afficherMenu(stock,cocktail_liste,arborescence);
    } while (quitter != 'q');


    return 0;
}