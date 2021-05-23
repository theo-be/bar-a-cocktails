/*! \file main.c
* \author Rabus Jules
* \author Belliere Theo
* \version 1
* \date 19/04/2021 Debut du travail en groupe
* \date 21/05/2021 Creation des commentaires doxygen.
*  \brief Programme principal du bar a cocktails.
*/
 
 
/*! \mainpage Presentation
* \section introduction Introduction
*
* Programme du bar a cocktail
*
* \section fonctions_procedures Fonctions et procédures
*
*/

 
/*! \file menu.h
* \section Presentation
* \brief Le fichier menu.h regroupe tous les prototypes de fonctions necessaires a l'affichage des menus et aux interactions utilisateur.
*/
/*! \file cocktail.h
* \section Presentation
* \brief Le fichier cocktail.h regroupe tous les prototypes de fonctions et les structures necessaires a la gestion des boissons et des cocktails.
*/
/*! \file cryptage.h
* \section Presentation
* \brief Le fichier cryptage.h regroupe tous les prototypes de fonctions necessaires au cryptage du mot de passe du barman.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "cocktail.h"
#include "menu.h"
#include "cryptage.h"


/*! \fn int main (int argc, char** argv)
* \author Belliere Theo
* \author Rabus Jules
* \version 1
* \date 19/04/2021 Debut de la programmation
*
* \brief Fonction principale
*
* \param argc : Nombre d'argument
* \param argv : Tableau des arguments
* \return 0   : le programme doit se terminer normalement
*
* \remarks La fonction appelle la fonction d'affichage du menu principal.
*/

/* La fonction main est la fonction principale. L'execution d'un programme entraine automatiquement l'appel de la fonction main. */
int main (int argc, char** argv) {
    boisson_struc* stock = remplirstock_boisson();
    cocktail_struc* cocktail_liste = remplirstock_cocktail();

    char quitter = 0;
    char arborescence[100] = {0};

    do {
        quitter = afficherMenu(stock,cocktail_liste,arborescence);
    } while (quitter != 'q');


    return 0;
}