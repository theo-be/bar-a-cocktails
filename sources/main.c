#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include "cocktail.h"
#include "cocktail.c"
#include <windows.h>


int main(int argc, char** argv) {
 boisson_struc* stock = remplirstock();
    //printf("%d\n",stock[0].quantite);
    //commande(stock,0,2,0);

   //affichage();
   affichage_type(122,2,stock);
    return 0;
}