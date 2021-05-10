#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sources/cocktail.h"
#include "../sources/menu.h"


char afficherMenu(boisson_struc *stock) {

	char retourFonction = 0;
	int erreurSaisie = 0;

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

			switch (inputMenu()) {
			case '1':
			retourFonction = saisie_commande(stock);
				break;
			case '2':
			    // si opt admin, demander le mdp
				retourFonction = afficherInterfaceAdmin(stock);
				
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

	return retourFonction;
}

char commanderBoisson (boisson_struc *stock) {
	
	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

	do {
		system("clear");
		printf("Tapez l\'id de la boisson que vous souhaitez commander.\n");
		printf("Que souhaitez-vous faire ?\n\n");

		afficherListe("boisson",stock);

		printf("Entrez \'a\' pour annuler la commande\n\n");

		do{
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

	return 'b';
}

char afficherInterfaceAdmin (boisson_struc *stock) {
	// afficher boissons
	// -> les lister et pour plus de details les selectionner manuellement
	// afficher cocktails
	// creer cocktail

	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

	do {
		system("clear");
		printf("Bienvenue dans l'interface d\'administration.\n");
		printf("Que souhaitez-vous faire ?\n\n");
		printf("\t1. Afficher les stocks.\n\n");
		printf("\t2. Afficher les boissons.\n\n");
		printf("\t3. Ajouter une boisson.\n\n");
		printf("\t4. Afficher les cocktails.\n\n");
		printf("\t5. Ajouter un cocktail.\n\n");
		printf("\t6. Revenir au menu principal.\n\n");

		do{
			erreurSaisie = 0;
			printf("Votre option : ");

			switch (inputMenu()) {
			case '1':
				retourFonction = afficherStocks(stock,"tout");
				break;
			case '2':
				retourFonction = afficherStocks(stock,"boisson");
				break;
			case '3':
				retourFonction = ajouterBoisson();
				break;
			case '4':
				retourFonction = afficherStocks(stock,"cocktail");
				break;
			case '5':
				retourFonction = ajouterCocktail();
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

	return 'b';
}

char afficherListeAdmin (char *typeAjout,boisson_struc *stock) {

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

		printf("\t %s",message_id("tout",stock));
		printf("\n");

		do{
			erreurSaisie = 0;
			printf("Votre option : ");
			

			switch (inputMenu()) {
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

	return 'b';
}

char afficherListe (char *typeAjout,boisson_struc *stock) {

	char retourFonction = 0;
	int erreurSaisie = 0;
	int quittterMenu = 0;

	do {
		system("clear");
		printf("Que souhaitez-vous faire ?\n\n");
		printf("\tEntrez l\'id d\'une boisson pour connaitre plus de details.\n\n");
		printf("\tEntrez \'p\' pour revenir au menu precedent.\n\n");

		printf("Voici les boissons enregistrees :\n");

		printf("\t %s",message_id("tout",stock));
		printf("\n");

		do {
			erreurSaisie = 0;
			printf("Votre option : ");
			
			switch (inputMenu()) {
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

char* saisie(){
    

    size_t bufsize = 30;
	char* chaine = malloc(bufsize * sizeof(char));
	scanf("%s",chaine);

	return chaine;

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
/*
char foo (bac) {

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
				retourFonction = afficherInterfaceAdmin(stock);
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
}*/

char saisie_commande(boisson_struc *stock){

	char* interraction= calloc(30, sizeof(char));
	long id;
	long quantite;
	int etape = 0;

	do{
		system("clear");

		switch (etape)
		{
		case 0:

			printf("\t Veuillez choisir le type de boisson :\n");
			printf("\t %s", message_type(stock));
			interraction = saisie();
			if (strstr(interraction,"-1") != NULL){
				etape = -1;
			}
			else{
			etape = 1;
			}

			break;

		case 1:
			printf("\t Veuillez choisir l'id de la boisson :\n");
			printf("\t %s", message_id(interraction,stock));
			id = conversion_long(saisie());
			if (id == -1){
				etape = 0;
			}
			else{
			etape = 2;
			}
			break;

		case 2:
			printf("\t Veuillez choisir la quantite : \n");
			printf("\t %s", message_quantite(stock,id));
			quantite = conversion_long(saisie());
			if (quantite == -1){
				etape = 1;
			}
			else if( stock[id-1].quantite >= quantite){
			etape = 3;
			}
			break;
		
		default:
			return 'q';
			break;
		}

	}
	while(etape != 3);

	if(etape == 3){
	return commande(stock,id,quantite,0);
	}
	else{
		return 'q';
	}
}

char afficherStocks(boisson_struc *stock,char* categorie){

	int taille = taille_stock();
	system("clear");
	printf("Si vous souhaitez quitter, faite entrer\n\n");

	printf("\tVoici l'état des stocks :\n\n");
	for(int i = 0; i<taille; i++){

			if( categorie == "boisson" && strcmp(stock[i].categorie,"boisson") == 0 || categorie == "tout" && strcmp(stock[i].categorie,"boisson") == 0){
				printf("Boisson : %s, Quantite : %d, Id : %d\n",stock[i].nom,stock[i].quantite, stock[i].id);

			}
			else if( categorie == "cocktail" && strcmp(stock[i].categorie,"cocktail") == 0 || categorie == "tout" && strcmp(stock[i].categorie,"cocktail") == 0){
				printf("Cocktail : %s, Quantite : %d, Id : %d\n",stock[i].nom,stock[i].quantite, stock[i].id);
			}
	}
	getchar();


	return('0');
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

