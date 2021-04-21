#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include "sources/cocktail.h"
#include "sources/cocktail.c"
#include <windows.h>


int main(int argc, char** argv) {
 boisson_struc* stock = remplirstock();
    //printf("%d\n",stock[0].quantite);
    //commande(stock,0,2,0);

   affichage(stock);
   //affichage_type("soda",stock);
    return 0;
}