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
    boisson_struc* stock = remplirstock();

    char quitter = 0;
    char arborescence[100] = {0};

     do {
         quitter = afficherMenu(stock,arborescence);
     } while (quitter != 'q');
    
    return 0;
}