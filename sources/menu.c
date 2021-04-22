#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

char afficherMenu() {

	// system("clear");

	char retourFonction = 0;
	int erreurSaisie = 0;
	
	size_t bufsize = 2;
	char* buffer = NULL;
	buffer = (char*)malloc(bufsize * sizeof(char));
	int taille = 0;

	do {

		// on affiche le menu
		printf("Bonjour, bienvenue dans notre interface de commande de cocktails.\n");
		printf("Que souhaitez-vous faire ?\n\n");
		printf("\t1. Commander une boisson\n\n");
		printf("\t2. Administration\n\n");
		printf("\t3. Quitter\n\n");

		do {
			erreurSaisie = 0;
			printf("Votre option : ");

			taille = getline(&buffer, &bufsize, stdin);

			switch (buffer[0]) {
			case '1':
				retourFonction = foo();
				break;
			case '2':
				retourFonction = afficherInterfaceAdmin();
				break;
			case '3':
				retourFonction = 'q';
				break;
			
			default:
				printf("Erreur dans la saisie\n");
				erreurSaisie = 1;
				break;
			}

		} while (erreurSaisie == 1);

	} while (retourFonction != 'q');

	// printf("%s", buffer);

	// printf("%d", (int)taille);



	// int quitter = 0;
	// int erreur = 0;

	
	
	// afficherInterfaceAdmin();

    // si opt admin, demander le mdp

	return retourFonction;
}



char afficherInterfaceAdmin () {
	// afficher boissons -> les lister et pour plus de details les selectionner manu
	// modifier prix

	// afficher cocktails
	// creer cocktail
	// supprimer cocktail

	// system("clear");

	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

	size_t bufsize = 2;
	char* buffer = NULL;
	buffer = (char*)malloc(bufsize * sizeof(char));
	int taille = 0;

	do {

		printf("Bienvenue dans l'interface d\'administration.\n");
		printf("foo\n");
		printf("revenir\n");


		do{

			erreurSaisie = 0;
			printf("Votre option : ");

			taille = getline(&buffer, &bufsize, stdin);

			switch (buffer[0]) {
			case '1':
				retourFonction = foo();
				break;
			case '2':
				quittterMenu = 1;
				break;

			
			default:
				printf("Erreur dans la saisie\n");
				erreurSaisie = 1;
				break;
			}
		} while (erreurSaisie == 1);

	} while (!quittterMenu);

	return 'b';
}





char foo () {

	// system("clear");

	char retourFonction = 0;
	int erreurSaisie = 0;
	int quitterMenu = 0;

	size_t bufsize = 2;
	char* buffer = NULL;
	buffer = (char*)malloc(bufsize * sizeof(char));
	int taille = 0;

	do{

		printf("Menu foo\n\n");
		printf("admin\n\n");
		printf("revenir\n\n");
		do {

			erreurSaisie = 0;
			printf("Votre option : ");

			taille = getline(&buffer, &bufsize, stdin);

			switch (buffer[0]) {
			case '1':
				retourFonction = afficherInterfaceAdmin();
				break;
			case '2':
				quitterMenu = 1;
				break;
			
			default:
				printf("Erreur dans la saisie\n");
				erreurSaisie = 1;
				break;
			}


		} while (erreurSaisie == 1);

	} while (!quitterMenu);

	return 'b';
}


/*

idee : a chaque fois qu'on rentre dans les menus,
la fonction qui affiche tel menu va retourner un char 
pour savoir si on retourne dans le menu précédent
et donc le reafficher
donc chaque menu est un do while aver un system("clear");
avec une variable locale quitter

codes de retour des fonctions 
(idee : renvoyer des parametres si on a besoin 
d'afficher le menu differemment) :
	0 : rien, ne pas quitter, juste revenir au menu precedent
	b : 
	q : quitter



trucs a faire :

voir la securite des inputs
tenir compte de la valeur de retour des fonctions dans 
une autre variable que retourFonction (quitterMenu)




*/