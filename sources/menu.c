#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "cocktail.h"
#include "menu.h"
#include "cryptage.h"

char afficherMenu (boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence) {
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
				retourFonction = afficherMenuClient(stock,cocktail_liste, arborescence);
				break;
			case '2':
				retourFonction = afficherInterfaceBarman(stock,cocktail_liste, arborescence);
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

char afficherMenuClient (boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence) {
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
		affichageMarge("Appuyez sur \'p\' pour revenir au menu precedent\n", 45);

		do {
			erreurSaisie = 0;
			printf("Votre option : ");

			switch (inputMenu()) {
			case '1':
				retourFonction = saisie_commande(stock,cocktail_liste,arborescence,0);
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

char afficherInterfaceBarman (boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence) {
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
				afficherTableau (stock,cocktail_liste,"tout");
				break;
			case '2':
				afficherTableau (stock,cocktail_liste,"boisson");
				break;
			case '3':
				stock = ajouterBoisson(stock);
				break;
			case '4':
				afficherTableau (stock,cocktail_liste,"cocktail");
				break;
			case '5':
				ajouterCocktail(stock,cocktail_liste);
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

void afficherEntete (char *ligne, int *taillesColonnes, int nbColonnes, int largeur) {
	// initialisation
	remplirEspaces(ligne, 0,  largeur);

	int indiceSeparation = -1;
	for (int i = 0; i < nbColonnes - 1; i++) {
		indiceSeparation += (taillesColonnes[i] + 1);
		ligne[indiceSeparation] = '|';
	}

	// incice de colonne global
	int indiceDebutCol = 0;
	int colonne = 0;
	int tailleChaineAAjouter = 0;
	char entetes[6][9] = {
		"id",
		"nom",
		"prix",
		"degre",
		"type",
		"quantite"
	};

	for (int i = 0; i < 6; i++) {
		tailleChaineAAjouter = (int)strlen(entetes[i]);
		for (int j = 0; j < tailleChaineAAjouter; j++) {
			ligne[indiceDebutCol + j] = entetes[i][j]; // <- nom de l'array qui contient les infos a afficher
		}
		indiceDebutCol += (taillesColonnes[colonne] + 1);
		colonne++;
	}
	printf("%s\n", ligne);
}

void afficherTableau (boisson_struc *stock,cocktail_struc *cocktail_liste,char* categorie) {

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

	//printf("taille colonnes flexibles : %d\n", tailleColonnesFlex);

	int taillesColonnes[] = {tailleColId, tailleColonnesFlex, tailleColPrix, tailleColDegre, tailleColonnesFlex};

	// tableau de ligne
	char *ligne = malloc((w.ws_col + 1) * sizeof(char));

	ligne[w.ws_col] = '\0';


	int tailleChaineAAjouter = 0;
	int indiceSeparation = -1;
	int indiceDebutCol = 0;
	int colonne = 0;

	char chaineTemporaire[10] = {0};

	int tailleStock = taille_stock("data_boisson");

	afficherEntete(ligne, taillesColonnes, nombreColonnesTotal, w.ws_col);

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

	getline(&buffer, &bufsize, stdin);
	
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

char saisie_commande(boisson_struc *stock,cocktail_struc *cocktail_liste,char *arborescence,int id_personne){

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

		affichageCentre("\tSi vous souhaitez revenir en arriere entrer \'p\'\n");

		switch (etape)
		{
		case 0:

			printf("\t Veuillez choisir le type de boisson :\n");
			printf("\t %s", message_type(stock));
			type = saisie();
			if (strcmp(type,"p") == 0){
				etape = -1;
			}
			else if(verification_type(stock,type)){
				etape = 1;
			}
		break;

		case 1:
			printf("\t Veuillez choisir l'id de la boisson :\n");
			printf("\nFaire une recherche :");
			printf("%s\n",recherche_boisson(stock,saisie()));
			interraction = saisie();
			if (strcmp(interraction,"p") == 0){
				etape = 0;
			}
			else if(strcmp(interraction,"") != 0 ){
				id = conversion_long(interraction);
				if(verification_id(stock,type,id)){
					etape = 2;
				}
			}
		break;

		case 2:
			printf("\t Veuillez choisir la quantite de %s : \n"),stock[id-1].nom;
			printf("\t %s", message_quantite(stock,id));
			interraction = saisie();
			if (strcmp(interraction,"p") == 0){
				etape = 1;
			}
			else if(strcmp(interraction,"") != 0 ){
				quantite = (int) conversion_long(interraction);
				if( stock[id-1].quantite >= quantite || id_personne == 0){
					etape = 3;
				}
			}
		break;

		case 3:
			printf(" Votre commande : %s, Quantite : %d, Prix : %.2f€ , Type : %s\n",stock[id-1].nom,((int) quantite) ,stock[id-1].prix * quantite,stock[id-1].type);
			printf("Taper \'v\' pour valider la commande, sinon taper \'p\' ");
			interraction = saisie();
			if (strcmp(interraction,"p") == 0){
				etape = 2;
			}
			if (strcmp(interraction,"v") == 0){
				etape = 4;
			}
		break;
		
		case 4:
			retourFonction = commande(stock,id,quantite,id_personne);
			if(retourFonction == 'v'){
				printf("Taper sur entrer pour continuer\n\n");
				printf("\tVotre commande de %d %s au prix de %.2f€ a bien ete enregistre \n\n",((int) quantite),stock[id-1].nom,stock[id-1].prix * quantite);
				getchar();
				etape = 4;
				}
			else{
				etape = 0;
				printf("\tIl y a eu un problème dans la saisie de votre commande. \n\n");
				getchar();
			}
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
		affichageCentre("\tSi vous souhaitez revenir en arriere entrer \'p\'\n");

		switch (etape)
		{
		case 0:
			printf("\tVeuillez entrer le nom de la boisson :\n");
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = -1;
				}
				else if( verification_nom(stock,interraction) == -1 && strcmp(interraction,"") != 0){				
					strcpy(boisson.nom,interraction);
					etape = 1;
				}
				else if(verification_nom(stock,interraction) != -1){
					etape = 10;
				}
		break;

		case 1:
			printf("\tVeuillez entre le type de boisson (ex: sucre / alcool) : \n");
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = 0;
				}
				else if( strcmp(interraction,"") != 0){
					etape = 2;
					strcpy(boisson.type,interraction);
				}
			break;
			
		case 2:
			printf("\tVeuillez entre le degre ");
			if (strcmp(interraction,"alcool") == 0 ){
				printf("d'alcool de %s :\n",boisson.nom);
			}
			else{
				printf("de sucre de %s :\n",boisson.nom);
			}
			interraction = saisie();
			if (strcmp(interraction,"p") == 0){
				etape = 1;
			}
			else if(strcmp(interraction,"") != 0 ){
			interraction_chiffre = conversion_long(interraction);
				if( interraction_chiffre >= 0){
					etape = 3;
					boisson.degre = (int) interraction_chiffre;
				}
				if(boisson.degre == 0){
					etape = 7;
				}
			}
		break;

		case 3:
			printf("\tVeuillez entre la quantite disponible de %s :\n",boisson.nom);
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = 2;
				}
				else if(strcmp(interraction,"") != 0 ){
					interraction_chiffre = conversion_long(interraction);
					if( interraction_chiffre > 0){
						etape = 4;
						boisson.quantite= (int) interraction_chiffre;
					}
				}
		break;

		case 4:
			printf("\tVeuillez entre la contenance en cl de %s :\n",boisson.nom);
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = 3;
				}
				else if(strcmp(interraction,"") != 0 ){
					interraction_chiffre = conversion_long(interraction);
					if( interraction_chiffre > 0){
						etape = 5;
						boisson.contenance= (int) interraction_chiffre;
					}
				}
		break;

		case 5:
			printf("\t Veuillez entrer \'p\' si il y a un probleme de saisie, sinon entrer \'v\'\n");
			printf("\tNom : %s, Prix : %.2f, Quantite : %d, Degre : %d, Type : %s, Contenance :  %d\n",boisson.nom ,boisson.prix ,boisson.quantite,boisson.degre,boisson.type,boisson.contenance);
			interraction = saisie();
			if(strcmp(interraction,"p") == 0){
				etape = 0;
			}
			else if(strcmp(interraction,"v") == 0){
				etape = 8;
				boisson.id = -1;
			}
		break;

		case 7:	
			printf("\tVeuillez entrer le prix de %s :\n",boisson.nom);
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = 2;
				}
				else if(strcmp(interraction,"") != 0 ){
					interraction_chiffre = (float) conversion_long(interraction);
					if( interraction_chiffre > 0){
						etape = 3;
						boisson.prix = interraction_chiffre;
					}
				}
		break;

		case 10:
			id = verification_nom(stock,interraction) -1;
			printf("\t Cette boisson est deja enregistre\n, si vous souhaitez changer la quantite en stock entrer la quantite à ajouter/enlever\n Sinon taper \'p\' \n\n");
			printf("\tNom : %s, Prix : %.2f, Quantite : %d, Degre : %d, Type : %s\n",stock[id].nom ,stock[id].prix,stock[id].quantite,stock[id].degre,stock[id].type);
			interraction = saisie();
			if(strcmp(interraction,"p") == 0){
				etape = 0;
			}
			else if(strcmp(interraction,"") != 0){
				interraction_chiffre = (int) conversion_long(interraction);
				etape = 11;
			}
		break;

		case 11:
			boisson.id = id;
			printf("\tLa quantite de %s sera de : %d\n",stock[id].nom,stock[id].quantite+boisson.quantite);
			getchar();
			etape = 8;
		break;
		
		default:
			boisson.id = -2;
			return boisson;
			break;
		}
	}
	while(etape != 8);

	return boisson;
}

cocktail_struc saisie_cocktail(boisson_struc *stock,cocktail_struc *cocktail_liste){

	char* interraction = calloc(30,sizeof(char));
	int id;
	int compteur_id = 0;
	int etape = 0;
	cocktail_struc cocktail;

	do{
		system("clear");
		affichageCentre("\tSi vous souhaitez revenir en arriere entrer \'p\'\n");

		switch (etape)
		{
		case 0:

			printf("\tVeuillez entrer le nom du cocktail :\n");
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = -1;
				}
				else if( verification_nom(stock,interraction) == -1 && strcmp(interraction,"") != 0){				
					strcpy(cocktail.nom,interraction);
					etape = 1;
					compteur_id = 0;
				}
				else if(verification_nom(stock,interraction) != -1 && strcmp(interraction,"") != 0){
					etape = 5;
				}
		break;

		case 1:
			printf("\t Veuillez entrer l\' id de la boisson qui va etre ajouter au cocktail, si vous avez fini entrer \'v\' \n");
			if (compteur_id >0){
				printf("La composition : ");
				for(int i = 0; i<compteur_id;i++){
					printf("%s ",stock[cocktail.id_boisson[i]].nom);
				}
			}

			if ( compteur_id < 6 ){
				printf("\nFaire une recherche :");
				printf("%s\n",recherche_boisson(stock,saisie()));
				interraction = saisie();
					if( verification_id(stock,"tout",conversion_long(interraction)) != 0 && strcmp(interraction,"") != 0){
						cocktail.id_boisson[compteur_id] = conversion_long(interraction)-1;
						compteur_id ++;
					}
			}

			else{
				printf("\n Vous ne pouvez pas ajouter plus de composant à votre cocktail :");
				printf("\n Entrer \'v\' si vous souhaitez valider sa composition, sinon entrer \'p\' \n");
				if(strcmp(saisie(),"p") == 0){
					compteur_id = 0;
			}
			}
			if(strcmp(interraction,"p") == 0){
				etape = 0;
			}
			else if( strcmp(interraction,"v") == 0 && compteur_id > 1){
				etape = 2;
				for( int i = compteur_id; i< 5; i++){
					cocktail.id_boisson[i] = -1;
				}
			}
		break;

		case 2: 
			printf("\t Veuillez entrer \'v\', si la saisie de votre cocktail est correcte,, sinon entrer \'p\' \n");
			printf("La composition du cocktail : ");
			for(int i = 0; i<5; i++){
				if(cocktail.id_boisson[i] != -1){
				printf("%s ",stock[cocktail.id_boisson[i]].nom);
				}
			}
			interraction = saisie();
				if(strcmp(interraction,"p") == 0){
					etape = 1;
					compteur_id = 0;
				}
				else if( strcmp(interraction,"v") == 0 ){
					etape = 3;
				}
		break;

		case 3:
			printf("\t Veuillez entrer \'p\' si il y a un probleme de saisie, sinon entrer \'v\'\n");
			int quantite = stock[cocktail.id_boisson[0]].quantite;
			int contenance = 0;
			int degre;
			char* type = calloc(20, sizeof(char));
			strcpy(type,"sans-alcool");

			for(int i = 0; i<5; i++){
				if(cocktail.id_boisson[i] != -1 && stock[cocktail.id_boisson[i]].quantite < quantite){
					quantite = stock[cocktail.id_boisson[i]].quantite;
				}
				if(cocktail.id_boisson[i] != -1){
					cocktail.prix += stock[cocktail.id_boisson[i]].prix *1.10;
				}
				if(cocktail.id_boisson[i] != -1){
					degre = stock[cocktail.id_boisson[i]].degre ;
				}
				if(cocktail.id_boisson[i] != -1){
					contenance += stock[cocktail.id_boisson[i]].contenance ;
				}
				if(cocktail.id_boisson[i] != -1 && strcmp(stock[cocktail.id_boisson[i]].type,"alcool") ){
					strcpy(type,"alcool") ;
				}
			}
			printf("\tNom : %s, Prix : %.2f, Quantite : %d, Degre : %d, Type : %s, Contenance :  %d\n",cocktail.nom ,cocktail.prix ,quantite,degre,type,contenance);
			printf("\t Veuillez entrer le prix du cocktail\n");
			interraction = saisie();
				if(strcmp(interraction,"p") == 0){
					etape = 2;
					compteur_id = 0;
				}
				else if( strcmp(interraction,"") != 0 ){
					cocktail.prix = conversion_long(interraction);
					if( cocktail.prix > 0){
						etape = 4;
					}
				}


		case 5:
			id = verification_nom(stock,interraction) -1;
			printf("\t Ce nom de %s est déja en stock \n",stock[id].categorie);
			printf("\t Elle correspond à Nom : %s, Prix : %.2f, Quantite : %d, Degre : %d, Type : %s\n",stock[id].nom ,stock[id].prix ,stock[id].quantite,stock[id].degre,stock[id].type);

			if ( strcmp(stock[id].categorie,"cocktail") == -1){
				printf("\t La composition du cocktail est :");
				for ( int i = 0; i<5 ; i++){
					if (cocktail_liste[stock[id].id].id_boisson[i] != 0){
                    printf(" %s ",stock[cocktail_liste[stock[id].id].id_boisson[i]].nom);
                    }
				}

			}
			getchar();
			etape = 0;
		break;
		
		default:
			strcpy(cocktail.nom,"");
			return cocktail;
			break;
		}
	}
	while(etape != 6);

	return cocktail;

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

différencier cocktail et boisson /

faire les entetes de tbl /
faire des fonctions différentes pour chaque entete /



*/