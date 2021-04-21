#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int afficherMenu() {

	int option = 0;
	int retour =  0;

	// on affiche le menu
	printf("Bonjour, bienvenue dans notre interface de commande de cocktails.\n");
	printf("Que souhaitez-vous faire ?\n\n");

	printf("\t1. Commander une boisson\n\n");
	printf("\t2. Administration\n\n");
	printf("\t3. Quitter\n\n");

	do {
		retour = scanf("Votre option : %d\n", &option);

	} while (option > 0 && option < 4);





	int quitter = 0;
	int erreur = 0;

	int bufsize = 2;

	char* buffer = NULL;

	buffer = (char*)malloc(bufsize * sizeof(char));

	do {
		printf("Voulez-vous quitter ? ");
		getline(&buffer, &bufsize, stdin);

		// analyser la chaine
	} while (erreur == 1);





	
	
	afficherInterfaceAdmin();

    // si opt admin, demander le mdp



	// return demanderQuitter();
	return 1;
}

// idee : a chaque fois qu'on rentre dans les menus,
// la fonction qui affiche tel menu va retourner un char 
// pour savoir si on retourne dans le menu précédent
// et donc le reafficher
// donc chaque menu est un do while

char afficherInterfaceAdmin () {
	// afficher boissons -> les lister et pour plus de details les selectionner manu
	// modifier prix

	// afficher cocktails
	// creer cocktail
	// supprimer cocktail


	printf("Bienvenue dans l'interface d\'administration.\n");



	return 'o';
}








/*



voir la securite des inputs















*/