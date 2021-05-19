#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "cocktail.h"
#include "menu.h"
#include "cryptage.h"

char afficherMenu (boisson_struc *stock, char *arborescence) {
	char retourFonction = 0;
	int erreurSaisie = 0;

	char *menuActuel = "Accueil";
	strcat(arborescence, menuActuel);

	do {
		// on affiche le menu
		system("clear");
		affichageCentre(arborescence);
		printf("\n");

		affichageCentre("Bonjour, bienvenue dans notre interface de commande de cocktails.");
		affichageCentre("Etes-vous un client ou bien un barman ?\n");
		affichageMarge("1. Client\n", 48);
		affichageMarge("2. Barman\n", 48);
		affichageMarge("3. Quitter\n", 48);

		do {
			erreurSaisie = 0;
			printf("Votre option : ");

			switch (inputMenu()) {
			case '1':
				retourFonction = afficherMenuClient(stock, arborescence);
				break;
			case '2':
				retourFonction = afficherInterfaceBarman(stock, arborescence);
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

char afficherMenuClient (boisson_struc *stock, char *arborescence) {
	char retourFonction = 0;
	int erreurSaisie = 0;

	char *menuActuel = "/client";
	strcat(arborescence, menuActuel);

	do {
		system("clear");
		affichageCentre(arborescence);
		printf("\n");
	
		affichageCentre("Que souhaitez-vous faire ?\n");
		affichageMarge("1. Commander une boisson\n", 45);
		affichageMarge("2. Commander un cocktail\n", 45);
		affichageMarge("Appuyez sur \'p\' pour revenir au menu precedent\n", 45);

		do {
			erreurSaisie = 0;
			printf("Votre option : ");

			switch (inputMenu()) {
			case '1':
				retourFonction = saisie_commande(stock,arborescence,0);
				break;
			case '2':
				retourFonction = saisie_commande(stock,arborescence,0);
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

char afficherInterfaceBarman (boisson_struc *stock, char *arborescence) {
	// afficher boissons
	// -> les lister et pour plus de details les selectionner manuellement
	// afficher cocktails
	// creer cocktail

	do {
		system("clear");
		affichageCentre(arborescence);
		printf("\n");
		affichageCentre("Veuillez saisir le mot de passe pour acceder à l\'interface barman .\n");


	}
	while(verification_mdp(saisie()) == 0);


	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

		
	char menuActuel[] = "/Barman";
	strcat(arborescence, menuActuel);

	do {
		system("clear");
		affichageCentre(arborescence);
		printf("\n");

		affichageCentre("Bienvenue dans l\'interface Barman .\n");
		affichageCentre("Que souhaitez-vous faire ?\n\n");
		affichageMarge("\t1. Afficher les stocks.\n\n", 30);
		affichageMarge("\t2. Afficher les boissons.\n\n", 30);
		affichageMarge("\t3. Ajouter une boisson.\n\n", 30);
		affichageMarge("\t4. Afficher les cocktails.\n\n", 30);
		affichageMarge("\t5. Ajouter un cocktail.\n\n", 30);
		affichageMarge("\t6. Revenir au menu principal.\n\n", 30);

		do{
			erreurSaisie = 0;
			printf("Votre option : ");

			switch (inputMenu()) {
			case '1':
				afficherTableau (stock,"tout");
				retourFonction = 0;
				break;
			case '2':
				afficherTableau (stock,"boisson");
				retourFonction = 0;
				break;
			case '3':
				stock = ajouterBoisson(stock);
				retourFonction = 0;
				break;
			case '4':
				afficherTableau (stock,"cocktail");
				break;
			case '5':
				ajouterCocktail(stock);
				retourFonction = 0;
				break;
			case '6':
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


void remplirEspaces (char tab[], int debut, int fin) {
	// fin non incluse
	for (int i = debut; i < fin; i++) {
		tab[i] = ' ';
	}
} 

void afficherTableau (boisson_struc *stock,char* categorie) {

	system("clear");
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

	//printf("taille col flex : %d\n", tailleColonnesFlex);

	int taillesColonnes[] = {tailleColId, tailleColonnesFlex, tailleColPrix, tailleColDegre, tailleColonnesFlex};

	// affichage ligne
	char *ligne = malloc(w.ws_col * sizeof(char));

	ligne[w.ws_col - 1] = '\0';


	int tailleChaineAAjouter = 0;
	int indiceSeparation = -1;
	int indiceDebutCol = 0;
	int colonne = 0;

	char chaineTemporaire[10] = {0};

	int tailleStock = taille_stock("data_boisson");


	for (int id = 0; id < tailleStock; id++) {

		if(strcmp(stock[id].categorie,categorie) == 0 || strcmp("tout",categorie) == 0  ){

			// initialisation
			remplirEspaces(ligne, 0,  w.ws_col - 1);

			indiceSeparation = -1;
			for (int i = 0; i < nombreColonnesTotal - 1; i++) {
				indiceSeparation += (taillesColonnes[i] + 1);
				ligne[indiceSeparation] = '|';
			}

			// incice de colonne global
			indiceDebutCol = 0;
			colonne = 0;


			// ID
			sprintf(chaineTemporaire, "%d", stock[id].id);
			tailleChaineAAjouter = (int)strlen(chaineTemporaire);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = chaineTemporaire[j]; // <- nom de l'array qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// NOM
			tailleChaineAAjouter = (int)strlen(stock[id].nom);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = stock[id].nom[j]; // <- nom de l'array qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// PRIX
			sprintf(chaineTemporaire, "%f", stock[id].prix);
			for (int j = 0; j < 4; j++) {
				ligne[indiceDebutCol + j] = chaineTemporaire[j]; // <- nom de l'array qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// DEGRE
			sprintf(chaineTemporaire, "%d", stock[id].degre);
			tailleChaineAAjouter = (int)strlen(chaineTemporaire);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = chaineTemporaire[j]; // <- nom de l'array qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// TYPE
			tailleChaineAAjouter = (int)strlen(stock[id].type);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = stock[id].type[j]; // <- nom de l'array qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// QT
			sprintf(chaineTemporaire, "%d", stock[id].quantite);
			tailleChaineAAjouter = (int)strlen(chaineTemporaire);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = chaineTemporaire[j]; // <- nom de l'array qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;
			printf("%s\n", ligne);

		}
	}


	// affichage
	// exemple : 1 coca 1.50 0 boisson 20

	// ORDRE :
	// ID NOM PRIX DEGRE TYPE QT
	// 3   30  4     5    30   8



	getchar();
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

void supprimerAPartirDe (char *chaine, char* sousChaine) {
	size_t longueurChaine = strlen(chaine);
	size_t longueurSupp = strlen(sousChaine);
	if (longueurChaine < longueurSupp) return;
		
	char *occurence = strstr(chaine, sousChaine);

	if (occurence != NULL) occurence[0] = '\0';

	// printf("%s\n", occurence);
	// printf("%s\n", chaine);
}


char* saisie() {
    
    size_t bufsize = 30;
	char* chaine = malloc(bufsize * sizeof(char));
	scanf("%s",chaine);

	return chaine;

}

char saisie_commande(boisson_struc *stock,char *arborescence,int id_personne){

	char menuActuel[] = "/commander";
	strcat(arborescence, menuActuel);

	char* type = calloc(30, sizeof(char));
	char* interraction = calloc(30,sizeof(char));
	long id;
	long quantite;
	int etape = 0;
	char retourFonction;

	do{
		system("clear");
		affichageCentre(arborescence);
		printf("\n");

		affichageCentre("\tSi vous souhaitez quitter entrer \'p\' \n");

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
				if(verification_id(stock,type,id)){
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
				if( stock[id-1].quantite >= quantite || id_personne == 0){
				etape = 3;
				}

			break;

		case 3:
			retourFonction = commande(stock,id,quantite,id_personne);
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
	supprimerAPartirDe(arborescence, menuActuel);
	return 'v';
}

boisson_struc saisie_boisson(boisson_struc *stock){

	char* interraction = calloc(30,sizeof(char));
	long interraction_chiffre;
	int id;
	int etape = 0;
	boisson_struc boisson;

	do{
		system("clear");
		printf("Si vous souhaitez quitter entrer \'p\' \n");

		switch (etape)
		{
		case 0:

			printf("\tVeuillez entrer le nom de la boisson :\n");
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = -1;
					break;
				}
				else if( verification_nom(stock,interraction) == -1 && strcmp(interraction,"") != 0){				
					strcpy(boisson.nom,interraction);
					etape = 1;
					break;
				}
				else if(verification_nom(stock,interraction) != -1){
					etape = 10;
				}

			break;

		case 1:
			printf("\tVeuillez entrer le prix de %s :\n",boisson.nom);
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = -1;
					break;
				}
			
				interraction_chiffre = (float) conversion_long(interraction);
				if( interraction_chiffre > 0){
				etape = 2;
				boisson.prix = interraction_chiffre;
				}

			break;

		case 2:
			printf("\tVeuillez entre le type de boisson (ex: sucre / alcool) : \n");
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = -1;
					break;
				}
				else if( strcmp(interraction,"") != 0){
				etape = 3;
				strcpy(boisson.type,interraction);
				}

			break;
			
		case 3:
			printf("\tVeuillez entre le degre ");
			if (strcmp(interraction,"alcool") == 0 ){
				printf("d'alcool de %s :\n",boisson.nom);
			}
			else{
				printf("de sucre de %s :\n",boisson.nom);
			}
			interraction = saisie();
			if (strcmp(interraction,"p") == 0){
				etape = -1;
				break;
			}
			interraction_chiffre = conversion_long(interraction);
			if( interraction_chiffre >= 0){
			etape = 4;
			boisson.degre = (int) interraction_chiffre;
			}

			break;

		case 4:
			printf("\tVeuillez entre la quantite disponible de %s :\n",boisson.nom);
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = -1;
					break;
				}
				interraction_chiffre = conversion_long(interraction);
				if( interraction_chiffre > 0){
				etape = 5;
				boisson.quantite= (int) interraction_chiffre;
				}

			break;

		case 5:
			printf("\t Veuillez entrer \'p\' si il y a un probleme de saisie, sinon entrer \'v\'\n");
			printf("\tNom : %s, Prix : %.2f, Quantite : %d, Degre : %d, Type : %s\n",boisson.nom ,boisson.prix ,boisson.quantite,boisson.degre,boisson.type);
			interraction = saisie();
			if(strcmp(interraction,"p") == 0){
				etape = 0;
				break;
			}
			else if(strcmp(interraction,"v") == 0){
				etape = 6;
				boisson.id = -1;
			}
			break;

		case 10:
			id = verification_nom(stock,interraction) -1;
			printf("\t Cette boisson est deja enregistre\n, si vous souhaitez changer la quantite en stock entrer la quantite à ajouter/enlever\n Sinon taper \'p\' \n\n");
			printf("\tNom : %s, Prix : %.2f, Quantite : %d, Degre : %d, Type : %s\n",stock[id].nom ,stock[id].prix,stock[id].quantite,stock[id].degre,stock[id].type);
			interraction = saisie();
			if(strcmp(interraction,"p") == 0){
				etape = 0;
				break;
			}
			else if(strcmp(interraction,"") != 0){
				boisson.quantite = (int) conversion_long(interraction);
				etape = 11;
			}
			break;

		case 11:
			boisson.id = id;
			printf("\tLa quantite de %s sera de : %d\n",stock[id].nom,stock[id].quantite+boisson.quantite);
			rewind(stdin);
			getchar();
			etape = 6;
			break;
		
		default:
			boisson.id = -2;
			return boisson;
			break;
		}
	}
	while(etape != 6);

	return boisson;
}

char afficherStocks(boisson_struc *stock,char* categorie){

	int taille = taille_stock("data_boisson");
	system("clear");
	printf("Si vous souhaitez quitter, faite entrer\n\n");

	printf("\tVoici l'etat des stocks :\n\n");
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