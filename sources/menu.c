#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

char afficherMenu() {

	

	char retourFonction = 0;
	int erreurSaisie = 0;
	
	size_t bufsize = 2;
	char* buffer = NULL;
	buffer = (char*)malloc(bufsize * sizeof(char));
	int taille = 0;

	do {
		// on affiche le menu
		system("clear");
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
				retourFonction = commanderBoisson();
				break;
			case '2':
			    // si opt admin, demander le mdp
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
			// printf("%s", buffer);
			// printf("%d", (int)taille);
		} while (erreurSaisie == 1);
	} while (retourFonction != 'q');

	free(buffer);
	return retourFonction;
}

char commanderBoisson () {
	
	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

	size_t bufsize = 2;
	char* buffer = NULL;
	buffer = (char*)malloc(bufsize * sizeof(char));
	int taille = 0;

	do {
		system("clear");
		printf("Tapez l\'id de la boisson que vous souhaitez commander.\n");
		printf("Que souhaitez-vous faire ?\n\n");

		afficherListe("boisson");

		printf("Entrez \'a\' pour annuler la commande\n\n");

		do{
			erreurSaisie = 0;
			printf("Votre option : ");
			taille = getline(&buffer, &bufsize, stdin);

			switch (buffer[0]) {
			case 'a':
				quittterMenu = 1;
				break;
			
			default:
				printf("Erreur dans la saisie\n");
				erreurSaisie = 1;
				break;
			}
		} while (erreurSaisie == 1);
	} while (!quittterMenu);

	free(buffer);
	return 'b';
}

char afficherInterfaceAdmin () {
	// afficher boissons
	// -> les lister et pour plus de details les selectionner manuellement
	// afficher cocktails
	// creer cocktail

	
	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

	size_t bufsize = 2;
	char* buffer = NULL;
	buffer = (char*)malloc(bufsize * sizeof(char));
	int taille = 0;

	do {
		system("clear");
		printf("Bienvenue dans l'interface d\'administration.\n");
		printf("Que souhaitez-vous faire ?\n\n");
		printf("\t1. Afficher les boissons.\n\n");
		printf("\t2. Ajouter une boisson.\n\n");
		printf("\t3. Afficher les cocktails.\n\n");
		printf("\t4. Ajouter un cocktail.\n\n");
		printf("\t5. Revenir au menu principal.\n\n");

		do{
			erreurSaisie = 0;
			printf("Votre option : ");
			taille = getline(&buffer, &bufsize, stdin);

			switch (buffer[0]) {
			case '1':
				retourFonction = afficherListeAdmin("boisson");
				break;
			case '2':
				retourFonction = ajouterBoisson();
				break;
			case '3':
				retourFonction = afficherListeAdmin("cocktail");
				break;
			case '4':
				retourFonction = ajouterCocktail();
				break;
			case '5':
				quittterMenu = 1;
				break;
			
			default:
				printf("Erreur dans la saisie\n");
				erreurSaisie = 1;
				break;
			}
		} while (erreurSaisie == 1);
	} while (!quittterMenu);

	free(buffer);
	return 'b';
}

char afficherListeAdmin (char *typeAjout) {

	

	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

	size_t bufsize = 2;
	char* buffer = NULL;
	buffer = (char*)malloc(bufsize * sizeof(char));
	int taille = 0;

	do {
		system("clear");
		printf("Que souhaitez-vous faire ?\n\n");
		printf("\tEntrez l\'id d\'une boisson pour connaitre plus de details.\n\n");
		printf("\tEntrez \'a\' pour ajouter une boisson.\n\n");
		printf("\tEntrez \'p\' pour revenir au menu precedent.\n\n");

		printf("Voici les boissons enregistrees :\n");

		// afficher les boissons

		do{
			erreurSaisie = 0;
			printf("Votre option : ");
			taille = getline(&buffer, &bufsize, stdin);

			switch (buffer[0]) {
			case 'a':
				retourFonction = ajouterBoisson();
				break;
			case 'p':
				quittterMenu = 1;
				break;
			
			default:
				printf("Erreur dans la saisie\n");
				erreurSaisie = 1;
				break;
			}
		} while (erreurSaisie == 1);
	} while (!quittterMenu);

	free(buffer);
	return 'b';
}

char afficherListe (char *typeAjout) {



	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

	size_t bufsize = 2;
	char* buffer = NULL;
	buffer = (char*)malloc(bufsize * sizeof(char));
	int taille = 0;

	do {
		system("clear");
		printf("Que souhaitez-vous faire ?\n\n");
		printf("\tEntrez l\'id d\'une boisson pour connaitre plus de details.\n\n");
		printf("\tEntrez \'p\' pour revenir au menu precedent.\n\n");

		printf("Voici les boissons enregistrees :\n");

		// afficher les boissons

		do{
			erreurSaisie = 0;
			printf("Votre option : ");
			taille = getline(&buffer, &bufsize, stdin);

			switch (buffer[0]) {
			case 'a':
				retourFonction = ajouterBoisson();
				break;
			case 'p':
				quittterMenu = 1;
				break;
			
			default:
				printf("Erreur dans la saisie\n");
				erreurSaisie = 1;
				break;
			}
		} while (erreurSaisie == 1);
	} while (!quittterMenu);

	free(buffer);
	return 'b';
}



char ajouterBoisson () {
	printf("Ajout.\n");
	return 0;
}
char ajouterCocktail () {
	printf("Ajout.\n");
	return 0;
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

	do {

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

	free(buffer);
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
	0 : rien
	b : juste revenir au menu precedent
	q : quitter


trucs a faire :

voir la securite des inputs




*/