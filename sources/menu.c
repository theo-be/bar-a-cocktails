#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "cocktail.h"
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
		affichageCentre("Etes-vous un client ou bien un administrateur ?\n");
		affichageMarge("1. Client\n", 45);
		affichageMarge("2. Administrateur\n", 45);
		affichageMarge("3. Quitter\n", 45);

		do {
			erreurSaisie = 0;
			printf("Votre option : ");

			switch (inputMenu()) {
			case '1':
				retourFonction = afficherMenuClient(arborescence);
				break;
			case '2':
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

char afficherMenuClient (char *arborescence) {
	char retourFonction = 0;
	int erreurSaisie = 0;

	char *menuActuel = "/client";
	strcat(arborescence, menuActuel);

	do {
		system("clear");
		printf("\t%s\n\n", arborescence);
	
		affichageCentre("Que souhaitez-vous faire ?\n");
		affichageMarge("1. Commander une boisson\n", 45);
		affichageMarge("2. Commander un cocktail\n", 45);
		affichageMarge("Appuyez sur \'p\' pour revenir au menu precedent\n", 45);

		do {
			erreurSaisie = 0;
			printf("Votre option : ");

			switch (inputMenu()) {
			case '1':
				retourFonction = commanderBoisson(arborescence);
				break;
			case '2':
				retourFonction = commanderBoisson(arborescence);
				break;
			case 'p':
				retourFonction = 'p';
				break;
			default:
				printf("Erreur dans la saisie\n");
				erreurSaisie = 1;
				break;
			}
		} while (erreurSaisie == 1);
	} while (retourFonction != 'p');

	supprimerAPartirDe(arborescence, menuActuel);
	return retourFonction;
}

char afficherInterfaceAdmin (char *arborescence) {
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
		affichageCentre("Bienvenue dans l'interface d\'administration.");
		affichageCentre("Que souhaitez-vous faire ?");
		affichageMarge("\t1. Afficher les boissons.\n", 40);
		affichageMarge("\t2. Ajouter une boisson.\n", 40);
		affichageMarge("\t3. Afficher les cocktails.\n", 40);
		affichageMarge("\t4. Ajouter un cocktail.\n", 40);
		affichageMarge("\t5. Revenir au menu principal.\n", 40);

		do{
			erreurSaisie = 0;
			printf("Votre option : ");

			switch (inputMenu()) {
			case '1':
				retourFonction = afficherListeAdmin("boisson");
				break;
			case '2':
				// retourFonction = ajouterBoisson("/");
				break;
			case '3':
				retourFonction = afficherListeAdmin("cocktail");
				break;
			case '4':
				// retourFonction = ajouterCocktail("/");
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

char commanderBoisson (char *arborescence) {
	
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
				// retourFonction = ajouterBoisson("/");
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
				// retourFonction = ajouterBoisson("/");
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

void remplirEspaces (char tab[], int debut, int fin) {
	for (int i = debut; i < fin; i++) {
		tab[i] = ' ';
	}
} 

void afficherTableau () {
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    // printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);

	int tailleColId = 3;
	int tailleColPrix = 4;
	int tailleColDegre = 5;
	int tailleColQuantite = 8;
	int tailleMaxColFlex = 30;

	int tailleTotaleColSatiques =  tailleColId + tailleColPrix + tailleColDegre + tailleColQuantite;

	int nombreColonnesFlex = 2;
	int nombreColonnesTotal = nombreColonnesFlex + 4;

	int tailleColonnesFlex = (w.ws_col - tailleTotaleColSatiques - nombreColonnesTotal + 1) / nombreColonnesFlex;
	if (tailleColonnesFlex > tailleMaxColFlex) tailleColonnesFlex = tailleMaxColFlex;

	printf("taille col flex : %d\n", tailleColonnesFlex);

	int taillesColonnes[] = {tailleColId, tailleColonnesFlex, tailleColPrix, tailleColDegre, tailleColonnesFlex};

	// affichage ligne
	char *ligne = malloc(w.ws_col * sizeof(char));

	ligne[w.ws_col - 1] = '\0';

	for (int id = 0; id < 10; id++) {
		// initialisation
		remplirEspaces(ligne, 0,  w.ws_col - 1);

		char *exemple = "023";

		int indiceSeparation = -1;
		for (int i = 0; i < nombreColonnesTotal - 1; i++) {
			indiceSeparation += (taillesColonnes[i] + 1);
			ligne[indiceSeparation] = '|';
		}	

		int indiceDebutCol = 0;
		for (int i = 0; i < nombreColonnesTotal; i++) {
			int tailleChaineAAjouter = (int)strlen(exemple);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = exemple[j]; // <- nom de l'array qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[i] + 1);
		}
		printf("%s\n", ligne);
	}


	// affichage
	// exemple : 1 coca 1.50 0 boisson 20

	// ORDRE :
	// ID NOM PRIX DEGRE TYPE QT
	// 3   30  4     5    30   8




	free(ligne);

	// si moins de 5 cols par colonne, demander d'agrandir la fenetre
	// si pas assez de place pour tout afficher dans une col,
	// separer la chaine avec les espaces et l'afficher dans la ligne de dessous
	//	-> 2 arrays : 1 avec les chaines a remettre, 1 avec l'emplacement de ces chaines
	// separer les colonnes par | /

	// COLONNES TOTALES : 6

	/*
	{
    char nom[30];
    float prix;
    float degre;
    int quantite;
    char type[30];
    char categorie[30];
    int id;
	};
	*/

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

char* saisie() {
    size_t bufsize = 30;
	char* chaine = malloc(bufsize * sizeof(char));
	scanf("%s",chaine);

	return chaine;
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

char saisie_commande(boisson_struc *stock) {

	char* type = calloc(30, sizeof(char));
	char* interraction = calloc(30,sizeof(char));
	long id;
	long quantite;
	int etape = 0;
	char retourFonction;

	do{
		system("clear");

		switch (etape)
		{
		case 0:

			printf("\t Veuillez choisir le type de boisson :\n");
			printf("\t %s", message_type(stock));
			type = saisie();
				if (strcmp(type,"p") == 0){
					etape = -1;
					break;
				}
				else if(verification_type(stock,type)){
				etape = 1;
				}

			break;

		case 1:
			printf("\t Veuillez choisir l'id de la boisson :\n");
			printf("\t %s", message_id(stock,type));
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = -1;
					break;
				}
			
				id = conversion_long(interraction);
				if (id == -1){
					etape = 0;
				}
				else if(verification_id(stock,type,id)){
				etape = 2;
				}

			break;

		case 2:
			printf("\t Veuillez choisir la quantite : \n");
			printf("\t %s", message_quantite(stock,id));
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = -1;
					break;
				}
			quantite = conversion_long(interraction);
				if (quantite == -1){
					etape = 1;
				}
				else if( stock[id-1].quantite >= quantite){
				etape = 3;
				}

			break;

		case 3:
			retourFonction = commande(stock,id,quantite,0);
				if(retourFonction == 'v'){
						printf("Taper sur entrer pour continuer\n\n");
						printf("\tVotre commande de %d %s au prix de %.2f€ a bien ete enregistre \n\n",quantite,stock[id-1].nom,stock[id-1].prix * quantite);
						getchar();
						etape = 4;
					}
					else{
						etape = 0;
						printf("\tIl y a eu un pronlème dans la saisie de votre commande. \n\n");
					}
					
			getchar();
			break;
		
		default:
			return 0;
			break;
		}

	}
	while(etape != 4);

	return 'v';
}

char afficherStocks(boisson_struc *stock,char* categorie) {

	int taille = taille_stock();
	system("clear");
	printf("Si vous souhaitez quitter, faite entrer\n\n");

	printf("\tVoici l'état des stocks :\n\n");
	for(int i = 0; i<taille; i++){

			if( categorie == "boisson" && strcmp(stock[i].categorie,"boisson") == 0 || categorie == "tout" && strcmp(stock[i].categorie,"boisson") == 0){
				printf("Boisson : Id %d, Nom : %s, Quantite : %d\n",stock[i].id,stock[i].nom,stock[i].quantite);
			}
			else if( categorie == "cocktail" && strcmp(stock[i].categorie,"cocktail") == 0 || categorie == "tout" && strcmp(stock[i].categorie,"cocktail") == 0){
				printf("Cocktail : Id %d, Nom : %s, Quantite : %d\n",stock[i].id,stock[i].nom,stock[i].quantite);
			}
	}
	getchar();

	return 0;
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

*/