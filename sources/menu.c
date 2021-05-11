#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "menu.h"

char afficherMenu (char *arborescence) {

	char retourFonction = 0;
	int erreurSaisie = 0;

	char *menuActuel = "Accueil";
	strcat(arborescence, menuActuel);


	do {
		// on affiche le menu
		system("clear");
		printf("\t%s\n\n", arborescence);
		// printf("Bonjour, bienvenue dans notre interface de commande de cocktails.\n");
		// printf("Que souhaitez-vous faire ?\n\n");
		// printf("\t1. Commander une boisson\n\n");
		// printf("\t2. Administration\n\n");
		// printf("\t3. Quitter\n\n");

		affichageCentre("Bonjour, bienvenue dans notre interface de commande de cocktails.");
		affichageCentre("Que souhaitez-vous faire ?\n");
		affichageMarge("1. Commander une boisson\n", 45);
		affichageMarge("2. Administration\n", 45);
		affichageMarge("3. Quitter\n", 45);

		do {
			erreurSaisie = 0;
			printf("Votre option : ");

			switch (inputMenu()) {
			case '1':
				retourFonction = commanderBoisson(arborescence);
				break;
			case '2':
			    // si opt admin, demander le mdp
				retourFonction = afficherInterfaceAdmin(arborescence);
				
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

	return retourFonction;
}

char commanderBoisson (char arborescence[]) {
	
	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

	char menuActuel[] = "/commander";
	strcat(arborescence, menuActuel);

	do {
		system("clear");
		printf("\t%s\n\n", arborescence);
		printf("Tapez l\'id de la boisson que vous souhaitez commander.\n");
		printf("Que souhaitez-vous faire ?\n\n");

		printf("Entrez \'a\' pour annuler la commande\n\n");

		do {
			erreurSaisie = 0;
			printf("Votre option : ");

			switch (inputMenu()) {
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

	supprimerAPartirDe(arborescence, menuActuel);

	return 'p';
}

char afficherInterfaceAdmin (char arborescence[]) {
	// afficher boissons
	// -> les lister et pour plus de details les selectionner manuellement
	// afficher cocktails
	// creer cocktail



	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

		
	char menuActuel[] = "/administration";
	strcat(arborescence, menuActuel);

	do {
		system("clear");
		printf("\t%s\n\n", arborescence);
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

			switch (inputMenu()) {
			case '1':
				retourFonction = afficherListeAdmin("boisson");
				break;
			case '2':
				retourFonction = ajouterBoisson("/");
				break;
			case '3':
				retourFonction = afficherListeAdmin("cocktail");
				break;
			case '4':
				retourFonction = ajouterCocktail("/");
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

	supprimerAPartirDe(arborescence, menuActuel);

	return 'p';
}

char afficherListeAdmin (char *typeAjout) {

	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

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
			

			switch (inputMenu()) {
			case 'a':
				retourFonction = ajouterBoisson("/");
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

	return 'p';
}

char afficherListe (char *typeAjout) {

	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

	do {
		system("clear");
		printf("Que souhaitez-vous faire ?\n\n");
		printf("\tEntrez l\'id d\'une boisson pour connaitre plus de details.\n\n");
		printf("\tEntrez \'p\' pour revenir au menu precedent.\n\n");

		printf("Voici les boissons enregistrees :\n");

		// afficher les boissons

		do {
			erreurSaisie = 0;
			printf("Votre option : ");
			
			switch (inputMenu()) {
			case 'a':
				retourFonction = ajouterBoisson("/");
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

	return 'b';
}



char ajouterBoisson (char *arborescence) {
	
	char *menuActuel = "/ajout boisson";
	strcat(arborescence, menuActuel);

	printf("Ajout.\n");
	return 0;
}
char ajouterCocktail (char *arborescence) {
	
	char *menuActuel = "/ajout cocktail";
	strcat(arborescence, menuActuel);

	printf("Ajout.\n");
	return 0;
}

void affichageCentre (char *chaine) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    // printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);

	int longueurChaine = (int)strlen(chaine);

	// Si la longueur de la console est plus petite 
	// que la taille de la chaine a afficher,
	// alors un affichage de base sera fait.

	if (longueurChaine <= w.ws_col) {

		int longueurEspaces = (w.ws_col - (int)longueurChaine) / 2;
		char *espaceVide = malloc(longueurEspaces * sizeof(char));

		for (int i = 0; i < longueurEspaces - 1; i++) {
			espaceVide[i] = ' ';
		}
		espaceVide[longueurEspaces - 1] = '\0';

		printf("%s", espaceVide);

		free(espaceVide);
	}
	printf("%s\n", chaine);
}

void affichageMarge (char *chaine, int ratio) {
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    // printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);

	int longueurChaine = (int)strlen(chaine);

	// Si la longueur de la console est plus petite 
	// que la taille de la chaine a afficher,
	// alors un affichage de base sera fait.

	if (longueurChaine <= w.ws_col) {

		int longueurEspaces = w.ws_col * ratio / 100;

		// si la marge est trop a droite, on centre a droite
		// en ajustant le nombre d'espaces

		if (longueurEspaces + longueurChaine > w.ws_col) {
			longueurEspaces = w.ws_col - longueurChaine;
		}





		char *espaceVide = malloc(longueurEspaces * sizeof(char));

		for (int i = 0; i < longueurEspaces - 1; i++) {
			espaceVide[i] = ' ';
		}
		espaceVide[longueurEspaces - 1] = '\0';

		printf("%s", espaceVide);

		free(espaceVide);
	}
	printf("%s\n", chaine);
}

char inputMenu () {
	size_t bufsize = 2;
	char* buffer = NULL;
	buffer = (char*)malloc(bufsize * sizeof(char));
	int taille = 0;

	taille = getline(&buffer, &bufsize, stdin);
	
	char caractere = buffer[0];
	free(buffer);
	return caractere;
}

void supprimerAPartirDe (char *chaine, char* sousChaine) {
	size_t longueurChaine = strlen(chaine);
	size_t longueurSupp = strlen(sousChaine);
	if (longueurChaine < longueurSupp) return;
		
	char *occurence = strstr(chaine, sousChaine);

	if (occurence != NULL) occurence[0] = '\0';

	// printf("%s\n", occurence);
	// printf("%s\n", chaine);
}

char foo () {
	char retourFonction = 0;
	int erreurSaisie = 0;
	int quitterMenu = 0;
	do {
		system("clear");
		printf("Menu foo\n\n");
		printf("admin\n\n");
		printf("revenir\n\n");
		do {
			erreurSaisie = 0;
			printf("Votre option : ");
			switch (inputMenu()) {
			case '1':
				retourFonction = afficherInterfaceAdmin("/");
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
	0 : rien
	p : juste revenir au menu precedent
	q : quitter


trucs a faire :

voir la securite des inputs


idée arborescence : 

faire une fonction qui ajoute une chaine à une autre /
et qui supprime la chaine apres le dernier

idée dans les fonctions : /
ajout /<menu> 

fin de la fonction : 
supprime /<menu>

*/