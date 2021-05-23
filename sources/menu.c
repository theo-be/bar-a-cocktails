/*! \file menu.c
* \author Belliere Theo
* \author Rabus Jules
* \version 1
* \date 19/04/2021 Debut du travail en groupe
* \date 21/05/2021 Creation des commentaires doxygen.
* \brief Le fichier menu.c contient l'ensemble des fonctions pour l'affichage des menus et les interactions utilisateur.
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
* \brief Le fichier cryptage.h contient les fonctions necessaires pour le cryptage et la verifictation des du mot de passe.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "cocktail.h"
#include "menu.h"
#include "cryptage.h"



/*! \fn char afficherMenu (boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence)
*  \author Belliere Theo
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Fonction afficherMenu
*
*  \param stock Tableau de boissons
*  \param cocktail_liste Tableau de cocktails
*  \param arborescence Arborescence 
*
*  \return Retourne 'q' pour quitter le programme
*
*  \remarks Cette fonction permet de afficher le menu principal.
*/
 
/* Cette fonction fonctionne comme toutes les fonctions d'affichage de menus :
 l'arborescence est modidifiee
 une premiere boucle do while est executee pour afficher le menu
 une deuxieme boucle do while est executee pour demander a l'utilisateur d'entrer une option
*/
char afficherMenu (boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence) {
	char retourFonction = 0;
	int erreurSaisie = 0;

	// Mise a jour de l'arborescence
	char *menuActuel = "Accueil";
	strcat(arborescence, menuActuel);

	// Affichage du menu
	do {
		system("clear");
		affichageCentre(arborescence);
		printf("\n");

		// On affiche les options disponibles
		affichageCentre("Bonjour, bienvenue dans notre interface de commande de cocktails.");
		affichageCentre("Etes-vous un client ou bien un barman ?\n");
		affichageMarge("1. Client\n", 48);
		affichageMarge("2. Barman\n", 48);
		affichageMarge("3. Quitter\n", 48);

		// Interaction utilisateur
		do {
			erreurSaisie = 0;
			printf("Votre option : ");

			// On regarde le premier caractere demande par l'utilisateur
			switch (inputMenu()) {
			case '1':
				retourFonction = afficherMenuClient(stock,cocktail_liste, arborescence);
				break;
			case '2':
				retourFonction = afficherInterfaceBarman(stock,cocktail_liste, arborescence);
				break;
			case '3':
				retourFonction = quitter(stock);
				break;
			default:
				printf("Erreur dans la saisie\n");
				erreurSaisie = 1;
				break;
			}
		} while (erreurSaisie == 1);
	} while (retourFonction != 'q');

	// On supprime de dernier elemant de l'arborescence
	supprimerAPartirDe(arborescence, menuActuel);
	return retourFonction;
}

/*! \fn char afficherMenuClient (boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence)
*  \author Belliere Theo
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Fonction afficherMenuClient
*
*  \param stock Tableau de boissons
*  \param cocktail_liste Tableau de cocktails
*  \param arborescence Arborescence 
*
*  \return Retourne 'p' pour revenir au menu precedent
*
*  \remarks Cette fonction permet de afficher le menu du client.
*/
char afficherMenuClient (boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence) {
	char retourFonction = 0;
	int erreurSaisie = 0;

	bdd base_de_donne;
	panier_struc panier;
	panier.taille = 0;

	// Mise a jour de l'arborescence
	char *menuActuel = "/client";
	strcat(arborescence, menuActuel);

	
	char menuActuel_tableau[30];

	// Affichage du menu
	do {
		system("clear");
		affichageCentre(arborescence);
		printf("\n");
	
		// On affiche les options disponibles
		affichageCentre("Que souhaitez-vous faire ?\n");
		affichageMarge("1. Commander une boisson\n", 45);
		affichageMarge("2. Afficher le panier\n", 45);
		affichageMarge("3. Afficher les boissons\n", 45);
		affichageMarge("4. Afficher les cocktails\n", 45);
		affichageMarge("5. Ajouter un cocktail\n", 45);
		affichageMarge("Appuyez sur \'p\' pour revenir au menu precedent\n", 45);

		do {
			erreurSaisie = 0;
			printf("Votre option : ");

			// On regarde le premier caractere demande par l'utilisateur
			switch (inputMenu()) {
			case '1':
				panier = saisie_commande(stock,cocktail_liste,panier,arborescence,1);
			break;
			case '2':
				panier = panier_affichage(stock,cocktail_liste,arborescence,panier,1);
			break;
			case '3':
				strcpy(menuActuel_tableau,"/afficher_tableau_boisson");
				strcat(arborescence, menuActuel_tableau);
				afficherTableau (stock,cocktail_liste,arborescence,"boisson",taille_stock("data_boisson"),1);
				supprimerAPartirDe(arborescence, menuActuel_tableau);
			break;
			case '4':
				afficher_Cocktail(stock,cocktail_liste,arborescence);
			break;
			case '5':
				base_de_donne = ajouterCocktail(stock,cocktail_liste,arborescence);
				stock = base_de_donne.stock;
				cocktail_liste = base_de_donne.cocktail_liste;
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

	// On supprime de dernier elemant de l'arborescence
	supprimerAPartirDe(arborescence, menuActuel);
	return retourFonction;
}

/*! \fn char afficherInterfaceBarman (boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence)
*  \author Belliere Theo
*  \author Rabus Jules
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Fonction afficherInterfaceBarman
*
*  \param stock Tableau de boissons
*  \param cocktail_liste Tableau de cocktails
*  \param arborescence Arborescence 
*
*  \return Retourne 'p' pour revenir au menu precedent
*
*  \remarks Cette fonction permet de afficher le menu du barman.
*/
char afficherInterfaceBarman (boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence) {
	panier_struc panier;
	panier.taille = 0;

	// On demande la mot de passe avant de rentrer dans l'interface barman
	do {
		system("clear");
		affichageCentre(arborescence);
		printf("\n");
		affichageCentre("Veuillez saisir le mot de passe pour acceder a l\'interface barman .\n");
	} while(verification_mdp(saisie()) == 0);


	int erreurSaisie = 0;
	int quittterMenu = 0;

	bdd base_de_donne;

	// Mise a jour de l'arborescence
	char menuActuel[] = "/barman";
	strcat(arborescence, menuActuel);

	char menuActuel_tableau[30];
	// Affichage du menu
	do {
		system("clear");
		affichageCentre(arborescence);
		printf("\n");
	
		// On affiche les options disponibles
		affichageCentre("Bienvenue dans l\'interface Barman .\n");
		affichageCentre("Que souhaitez-vous faire ?\n\n");
		affichageMarge("\t1. Afficher les stocks.\n\n", 30);
		affichageMarge("\t2. Afficher les boissons.\n\n", 30);
		affichageMarge("\t3. Ajouter une boisson.\n\n", 30);
		affichageMarge("\t4. Afficher les cocktails.\n\n", 30);
		affichageMarge("\t5. Ajouter un cocktail.\n\n", 30);
		affichageMarge("\t6. Ajouter une boisson au plateau du serveur.\n\n", 30);
		affichageMarge("\t7. Servir le plateau.\n\n", 30);
		affichageMarge("\t8. Administration.\n\n", 30);
		affichageMarge("\t9. Revenir au menu principal.\n\n", 30);

		do{
			erreurSaisie = 0;
			printf("Votre option : ");

			// On regarde le premier caractere demande par l'utilisateur
			switch (inputMenu()) {
			case '1':
				strcpy(menuActuel_tableau,"/afficher_tableau");
				strcat(arborescence, menuActuel_tableau);
				afficherTableau (stock,cocktail_liste,arborescence,"tout",taille_stock("data_boisson"),1);
				supprimerAPartirDe(arborescence, menuActuel_tableau);
			break;
			case '2':
				strcpy(menuActuel_tableau,"/afficher_tableau_boisson");
				strcat(arborescence, menuActuel_tableau);
				afficherTableau (stock,cocktail_liste,arborescence,"boisson",taille_stock("data_boisson"),1);
				supprimerAPartirDe(arborescence, menuActuel_tableau);
			break;
			case '3':
				stock = ajouterBoisson(stock,arborescence);
			break;
			case '4':
				afficher_Cocktail(stock,cocktail_liste,arborescence);
			break;
			case '5':
				base_de_donne = ajouterCocktail(stock,cocktail_liste,arborescence);
				stock = base_de_donne.stock;
				cocktail_liste = base_de_donne.cocktail_liste;
			break;
			case '6':
				panier = saisie_commande(stock,cocktail_liste,panier,arborescence,0);
			break;
			case '7':
				panier = panier_affichage(stock,cocktail_liste,arborescence,panier,0);
			break;
			case '8':
				administration(arborescence);
			break;
			case '9':
				quittterMenu = 1;
			break;
			
			default:
				printf("Erreur dans la saisie\n");
				erreurSaisie = 1;
				break;
			}
		} while (erreurSaisie == 1);
	} while (!quittterMenu);


	// On supprime de dernier elemant de l'arborescence
	supprimerAPartirDe(arborescence, menuActuel);
	return 'p';
}

/*! \fn void remplirEspaces (char tab[], int debut, int fin)
*  \author Belliere Theo
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Fonction remplirEspaces
*
*  \param tab Tableau de caracteres
*  \param debut Indice de debut (inclus)
*  \param fin Indice de fin (non inclus)
*
*  \remarks Cette fonction permet de remplir le tableau envoye de caracteres ' ' entre le debut inclus et la fin non incluse.
*/
void remplirEspaces (char tab[], int debut, int fin) {
	// fin non incluse
	for (int i = debut; i < fin; i++) {
		tab[i] = ' ';
	}
} 

/*! \fn void separerColonnes (char *ligne, int nbColonnes, int *taillesColonnes)
*  \author Belliere Theo
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Procedure separerColonnes
*
*  \param ligne Ligne du terminal
*  \param nbColonnes Nombre de colonnes
*  \param taillesColonnes Tableau des tailles de chaque colonne dans le bon ordre
*
*  \remarks Cette fonction permet de mettre les barres verticales pour separer les colonnes.
*/
void separerColonnes (char *ligne, int nbColonnes, int *taillesColonnes) {
	int indiceSeparation = -1;
	for (int i = 0; i < nbColonnes - 1; i++) {
		indiceSeparation += (taillesColonnes[i] + 1);
		ligne[indiceSeparation] = '|';
	}
}

/*! \fn void afficherEntete (char *ligne, int *taillesColonnes, int nbColonnes, int largeur)
*  \author Belliere Theo
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Procedure afficherEntete
*
*  \param ligne Ligne du terminal
*  \param taillesColonnes Tableau des tailles de colonnes
*  \param nbColonnes Nombre de colonnes
*  \param largeur Largeur du terminal
*
*  \remarks Cette fonction permet de mettre les barres verticales pour separer les colonnes.
*/
void afficherEntete (char *ligne, int *taillesColonnes, int nbColonnes, int largeur) {
	// Recuperation de la taille du terminal
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	// Initialisation de la ligne
	remplirEspaces(ligne, 0, w.ws_col);
	separerColonnes(ligne, nbColonnes, taillesColonnes);

	// Incice de debut de chaque colonne dans la ligne
	// Est incremente a chaque nouvelle colonne
	int indiceDebutCol = 0;
	int colonne = 0;
	int tailleChaineAAjouter = 0;
	char entetes[8][11] = {
		"id",
		"nom",
		"prix",
		"contenance",
		"degre",
		"type",
		"categorie",
		"quantite"
	};

	for (int i = 0; i < 8; i++) {
		tailleChaineAAjouter = (int)strlen(entetes[i]);
		for (int j = 0; j < tailleChaineAAjouter; j++) {
			ligne[indiceDebutCol + j] = entetes[i][j]; // <- Nom du tableau qui contient les infos a afficher
		}
		indiceDebutCol += (taillesColonnes[colonne] + 1);
		colonne++;
	}

	// On affiche l'entete
	printf("%s\n", ligne);

	remplirEspaces(ligne, 0, w.ws_col);

	// On separe l'entete du tableau par une ligne de caracteres
	for (int i = 0; i < largeur; i++) {
		ligne[i] = '=';
	}
	separerColonnes(ligne, nbColonnes, taillesColonnes);
	printf("%s\n", ligne);
}

/*! \fn void afficherTableau (boisson_struc *stock,cocktail_struc *cocktail_liste,char* categorie)
*  \author Belliere Theo
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Fonction afficherTableau
*
*  \param stock Tableau de boissons
*  \param cocktail_liste Tableau de cocktails
*  \param arborescence Arborescence 
*  \param categorie Nom de la categorie a afficher ("tout" pour tout afficher)
*  \param taille_tableau Nombre de lignes du tableau
*  \param pause Indique si l'utilisateur doit agir pour ne plus afficher le tableau
*
*  \remarks Cette fonction permet d'afficher le tableau qui affiche les details des elements voulus (boisson, cocktail ou tout).
*/
void afficherTableau (boisson_struc *stock,cocktail_struc *cocktail_liste,char * arborescence,char* categorie,int taille_tableau,int pause) {

	system("clear");
	affichageCentre(arborescence);

	// Recuperation de la taille du terminal
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    // printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);

	// Premiere partie de la procedure, on calcule le nombre et la taille des colonnes

	int tailleColId = 3;
	int tailleColPrix = 4;
	int tailleColContenance = 10;
	int tailleColDegre = 5;
	int tailleColQuantite = 8;

	int tailleMaxColFlex = 30;

	int tailleTotaleColStatiques =  tailleColId + tailleColPrix + tailleColContenance + tailleColDegre + tailleColQuantite;

	int nombreColonnesFlex = 3;
	int nombreColonnesTotal = nombreColonnesFlex + 5;

	// Une colonne flexible est une colonne qui peut prendre une taille variable en fonction de la place disponible dans le terminal
	int tailleColonnesFlex = (w.ws_col - tailleTotaleColStatiques - nombreColonnesTotal + 1) / nombreColonnesFlex;
	if (tailleColonnesFlex > tailleMaxColFlex) tailleColonnesFlex = tailleMaxColFlex;

	int tailleTotaleTableau = tailleTotaleColStatiques + tailleColonnesFlex * nombreColonnesFlex + nombreColonnesTotal;
	

	//printf("taille colonnes flexibles : %d\n", tailleColonnesFlex);

	// Tableau de tailles de colonnes
	int taillesColonnes[] = {tailleColId, tailleColonnesFlex, tailleColPrix, tailleColContenance, tailleColDegre, tailleColonnesFlex, tailleColonnesFlex};

	// Ligne du tableau
	char *ligne = malloc((w.ws_col + 1) * sizeof(char));

	ligne[w.ws_col] = '\0';

	// Taille du texte dans la chaine temporaire
	int tailleChaineAAjouter = 0;

	// Incice de debut de chaque colonne dans la ligne
	// Est incremente a chaque nouvelle colonne
	int indiceDebutCol = 0;
	int colonne = 0;


	// La chaine temporaire sert pour la conversion de int ou float en char
	char chaineTemporaire[10] = {0};

	afficherEntete(ligne, taillesColonnes, nombreColonnesTotal, tailleTotaleTableau);

	for (int id = 0; id < taille_tableau; id++) {

		if (strcmp(stock[id].categorie, categorie) == 0 || strcmp("tout", categorie) == 0){

			// Initialisation de la ligne
			remplirEspaces(ligne, 0,  w.ws_col);
			separerColonnes(ligne, nombreColonnesTotal, taillesColonnes);

			indiceDebutCol = 0;
			colonne = 0;

			// ID
			// On regarde si on affiche l'element
			if ( strcmp(stock[id].categorie,"cocktail") == 0 ){
				sprintf(chaineTemporaire, "%d", id);
			}
			else{
				sprintf(chaineTemporaire, "%d", stock[id].id);
			}
			tailleChaineAAjouter = (int)strlen(chaineTemporaire);
			// On copie caractere par caractere les elements a afficher
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = chaineTemporaire[j]; // <- Nom du tableau qui contient les infos a afficher
			}
			// On passe a la colonne suivante
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// NOM
			tailleChaineAAjouter = (int)strlen(stock[id].nom);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = stock[id].nom[j]; // <- Nom du tableau qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// PRIX
			sprintf(chaineTemporaire, "%f", stock[id].prix);
			for (int j = 0; j < 4; j++) {
				ligne[indiceDebutCol + j] = chaineTemporaire[j]; // <- Nom du tableau qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// CONTENANCE
			sprintf(chaineTemporaire, "%d", stock[id].contenance);
			tailleChaineAAjouter = (int)strlen(chaineTemporaire);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = chaineTemporaire[j]; // <- Nom du tableau qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// DEGRE
			sprintf(chaineTemporaire, "%d", stock[id].degre);
			tailleChaineAAjouter = (int)strlen(chaineTemporaire);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = chaineTemporaire[j]; // <- Nom du tableau qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// TYPE
			tailleChaineAAjouter = (int)strlen(stock[id].type);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = stock[id].type[j]; // <- Nom du tableau qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// CATEGORIE
			tailleChaineAAjouter = (int)strlen(stock[id].categorie);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = stock[id].categorie[j]; // <- Nom du tableau qui contient les infos a afficher
			}
			indiceDebutCol += (taillesColonnes[colonne] + 1);
			colonne++;

			// QT
			sprintf(chaineTemporaire, "%d", stock[id].quantite);
			tailleChaineAAjouter = (int)strlen(chaineTemporaire);
			for (int j = 0; j < tailleChaineAAjouter; j++) {
				ligne[indiceDebutCol + j] = chaineTemporaire[j]; // <- Nom du tableau qui contient les infos a afficher
			}
			// indiceDebutCol += (taillesColonnes[colonne] + 1);
			// colonne++;


			// Ensuite on affiche la ligne
			printf("%s\n", ligne);
		}
	}

	if( pause ){
		getchar();
	}

	// On libere l'espace cree par malloc
	free(ligne);
}

/*! \fn void affichageCentre (char *chaine)
*  \author Belliere Theo
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Procedure affichageCentre
*
*  \param chaine Chaine a centrer
*
*  \remarks Cette fonction permet de centrer du texte dans le terminal.
*/
void affichageCentre (char *chaine) {

    // Recuperation de la taille du terminal
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

/*! \fn void affichageMarge (char *chaine, int ratio)
*  \author Belliere Theo
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Procedure affichageMarge
*
*  \param chaine Chaine a centrer
*  \param ratio Pourcentage de marge
*
*  \remarks Cette fonction permet d'afficher du texte dans le terminal avec une certaine marge a gauche.
*/
void affichageMarge (char *chaine, int ratio) {
	// Recuperation de la taille du terminal
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

/*! \fn char inputMenu ()
*  \author Belliere Theo
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Fonction inputMenu
*
*  \return Retourne le premier caractere entre par l'utilisateur
*
*  \remarks Cette fonction permet a l'utilisateur d'entrer du contenu.
*/
char inputMenu () {
	size_t bufsize = 2;
	char* buffer = NULL;
	buffer = (char*)malloc(bufsize * sizeof(char));

	// getline sert a vider le buffer
	getline(&buffer, &bufsize, stdin);
	
	// On retourne uniquement le premier caractere
	char caractere = buffer[0];
	free(buffer);
	return caractere;
}

/*! \fn void supprimerAPartirDe (char *chaine, char* sousChaine)
*  \author Belliere Theo
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Procedure supprimerAPartirDe
*
*  \param chaine Chaine principale
*  \param sousChaine Sous chaine a localiser
*
*  \remarks Cette fonction permet de mettre un \0 sur la chaine a l'emplacement de la premiere occurence de la sous chaine dans la chaine.
*/
void supprimerAPartirDe (char *chaine, char* sousChaine) {
	size_t longueurChaine = strlen(chaine);
	size_t longueurSupp = strlen(sousChaine);
	// On verifie que la sous-chaine est plus petite que la chaine principale
	if (longueurChaine < longueurSupp) return;

	char *occurence = strstr(chaine, sousChaine);

	// On place un caractere de fin de ligne a l'endroit de la sous-chaine pour ne plus l'afficher
	if (occurence != NULL) occurence[0] = '\0';
}

/*! \fn char* saisie()
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction saisie
*
*  \return Retourne un pointeur qui pointe vers la chaine saisie par l'utilisateur
*
*  \remarks Cette fonction permet a l'utilisateur de saisir du texte.
*/
char* saisie() {
    
	char* chaine = malloc(30 * sizeof(char));		 // On alloue la mémoire a la chaine, pour 30 caractres
	scanf("%s",chaine);								 // On fait saisir a l'utilisateur une chaine de caracteres

	return chaine;

}

/*! \fn panier_struc panier_affichage(boisson_struc *stock,cocktail_struc *cocktail_liste,panier_struc panier,int id_personne)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction panier_affichage
*
*  \param stock Tableau de boissons
*  \param cocktail_liste Tableau de cocktails
*  \param arborescence Arborescence
*  \param panier Affiche le panier
*  \param id_personne 0 : barman, 1 : client
*
*  \return Retourne le panier
*
*  \remarks Cette fonction permet d'afficher le panier.
*/
panier_struc panier_affichage(boisson_struc *stock,cocktail_struc *cocktail_liste,char *arborescence,panier_struc panier,int id_personne){
	
	char *menuActuel;

	if( id_personne){
		menuActuel = "/Panier";
	}
	else{
		menuActuel = "/Plateau";
	}

	strcat(arborescence, menuActuel);
	affichageCentre(arborescence);
	
	char* interraction = calloc(10,sizeof(char));
	afficherTableau(panier.stock,cocktail_liste,arborescence,"tout",panier.taille,0);    // On affiche le tableau de la fonction afficherTableau

	if (panier.taille > 0){ 						// On regarde si le panier a quelques choses a l'interieur sinon on passe
		float prix_total;

		for(int i = 0 ; i<panier.taille; i++){
			prix_total += panier.stock[i].prix;			// On calcule le prix total du panier , en additionnant le prix de tout ce qu'il y a l'interieur
		}
		printf("Le prix total est de : %.2f € \n",prix_total);
		if( id_personne){																																	// On regarde si c'est un barman ou un client, client = 1 , serveur = 0
			printf("\nSi vous souhaitez revenir en arriere entrer \'p\', si vous souhaitez : valider votre panier entrer \'v\', l'annuler \'a\'  ");		// On affiche pour le client
		}
		else{
			printf("\nSi vous souhaitez revenir en arriere entrer \'p\', si vous souhaitez : servir le plateau entrer \'v\', l'annuler \'a\'  ");		// On affiche pour le serveur
		}
		interraction = saisie();
		if(strcmp(interraction,"v") == 0){
			commande(stock,cocktail_liste,panier,id_personne);		// On envoie le panier a la fonction commande
			panier.taille = 0;										// On remets le panier.taille a 0 , pour le remettre comme si il etait vide
		}
		if(strcmp(interraction,"a") == 0){
			panier.taille = 0;										// On annule panier , en remettant panier.taille a 0
		}

	}
	else{
		if( id_personne){
			printf("Votre panier est vide");			// On affiche pour le client
		}
		else{
			printf("Le plateau est vide");				// On affiche pour le serveur
		}
		getchar();	// On fait une pause, l'utilisateur doit presser une touche pour avancer
	}
	supprimerAPartirDe(arborescence, menuActuel);
	return panier;
}

/*! \fn panier_struc saisie_commande(boisson_struc *stock,cocktail_struc *cocktail_liste,panier_struc panier,char *arborescence,int id_personne)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction saisie_commande
*
*  \param stock Tableau de boissons
*  \param cocktail_liste Tableau de cocktails
*  \param panier Affiche le panier
*  \param arborescence Arborescence dans les menus
*  \param id_personne 0 : barman, 1 : client
*
*  \return Retourne le panier de la commande
*
*  \remarks Cette fonction permet a l'utilisateur de prendre une commande.
*/
panier_struc saisie_commande(boisson_struc *stock,cocktail_struc *cocktail_liste,panier_struc panier,char *arborescence,int id_personne){

	char menuActuel[] = "/commander";
	strcat(arborescence, menuActuel);

	char* interraction = calloc(30,sizeof(char));
	char* type = calloc(30, sizeof(char));
	long id;
	long quantite;
	int etape = 0;
	boisson_struc commande_boisson;

	if ( panier.taille > 18){																		// On regarde si le panier n'a pas atteint sa taille maximale (20 boisson/cocktail), si oui on passe
		system("clear");
		affichageCentre(arborescence);
		affichageCentre("\tSi vous souhaitez revenir en arriere entrer \'p\'\n");
		affichageCentre("\tVotre panier est plein, veuillez le vider ou le commander \'p\'\n");
	}
	else{
		do{																							// On lance le do while de la saisie
			system("clear");																		// On efface le terminal
			affichageCentre(arborescence);
			printf("\n");

			affichageCentre("\tSi vous souhaitez revenir en arriere entrer \'p\'\n");

			switch (etape)																			// On fait un switch pour faire des etapes pour la saisie
			{
			case 0:																							// Etape 0 : saisie du type de recherche
				printf("\t Veuillez choisir le type de recherche, par type 0 ou par mots-clés 1 :\n");			
				interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape --;
				}
				else if( conversion_long(interraction) == 0 ){												// 0 : Recherche par type
					etape ++;
				}
				else if( conversion_long(interraction) == 1){												// 0 : Recherche par sous chaine 
					etape = 3;
				}
			break;

			case 1:																// Etape 1 : saisie du type de boisson , recherche par type
				printf("\t Veuillez choisir le type de boisson :\n");		
				printf("\t %s", message_type(stock));
				type = saisie();
				if (strcmp(type,"p") == 0){
					etape --;
				}
				else if(verification_type(stock,type)){
					etape = 2;
				}
			break;

			case 2:																// Etape 2 : saisie de l'id de la boisson , recherche par type
				printf("\t Veuillez choisir l'id de la boisson :\n");
				printf("\t %s", message_id(stock,type));						// Affichage du message avec les id des boisson correspondant au type rentrer dans etape 1
				interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape --;
				}
				else{
					id = conversion_long(interraction);
					if(verification_id(stock,type,id)){							// On vérifie si le type existe bien avec la fonction verification_id
						etape = 4;
					}
				}
			break;

			case 3:																// Etape 3 : saisie de l'id de la boisson , recherche par sous chaine
				printf("\t Veuillez choisir l'id de la boisson :\n");
				printf("\nFaire une recherche :");
				printf("%s\n",recherche_boisson(stock,saisie(),"tout"));		// Affichage du message de la recherche avec la fonction_recherche_boisson
				interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = 0;
				}
				else{
					id = conversion_long(interraction);
					if(verification_id(stock,"tout",id)){						// On vérifie si le type existe bien avec la fonction verification_id, type = "tout", car on ne cherche pas avec le type	
						etape ++;
					}
				}
			break;

			case 4:																// Etape 4 : saisie de la quantite
				printf("\t Veuillez choisir la quantite : \n");
				printf("%s", message_quantite(stock,cocktail_liste,id));		// Affichage du message disant la disponibilite des boissons / cocktails avec la fonction message_quantite
				interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = 0;
				}
				else{
					quantite = (int) conversion_long(interraction);
					if( stock[id-1].quantite >= quantite || id_personne == 0 ||( quantite_cocktail(stock,cocktail_liste[stock[id-1].id-1]) >=  quantite && quantite > 0) ){		// On verifie la quantite si la commande est faite par un client, on passe si elle faite par un serveur
						etape ++;
					}
				}
			break;

			case 5:																																											// Etape 5 : Confirmation de la commande
				printf(" Votre commande : %s, Quantite : %d, Prix : %.2f€ , Type : %s\n",stock[id-1].nom,((int) quantite) ,stock[id-1].prix * quantite,stock[id-1].type);
				printf("Taper \'v\' pour mettre votre commande au panier, sinon taper \'p\' ");
				interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape --;
				}
				if (strcmp(interraction,"v") == 0){											// Si la commande est 'v', valider On mets toutes les informations de la boisson dans la structure boisson
					commande_boisson = stock[id-1];
					commande_boisson.quantite = quantite;
					commande_boisson.prix = stock[id-1].prix * quantite;
					panier = ajouterPanier(panier,commande_boisson);						// On ajoute la commande au panier avec la fonction ajouterPanier
					etape = 8;																// On sort du do while avec etape = 8
				}
			break;

			default:
				supprimerAPartirDe(arborescence, menuActuel);
				return panier;			// En cas de defaut on retourne le panier
				break;
			}

		}
		while(etape != 8);
	}
	supprimerAPartirDe(arborescence, menuActuel);
	return panier;
}

/*! \fn boisson_struc saisie_boisson(boisson_struc *stock)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction saisie_boisson
*
*  \param stock Tableau de boissons
*  \param arborescence Arborescence dans les menus
*
*  \return Retourne une structure de boisson
*
*  \remarks Cette fonction permet au barman d'ajouter une boisson.
*/
boisson_struc saisie_boisson(boisson_struc *stock, char* arborescence){

	char* interraction = calloc(30,sizeof(char));
	long interraction_chiffre;
	int id;
	int etape = 0;
	boisson_struc boisson;

		char *menuActuel = "/Saisie_boisson";
		strcat(arborescence, menuActuel);

	do{
		system("clear");
		affichageCentre(arborescence);
		
		affichageCentre("\tSi vous souhaitez revenir en arriere entrer \'p\'\n");

		switch (etape)
		{
		case 0:																	// Etape 0 : saisie du nom de la boisson
			printf("\tVeuillez entrer le nom de la boisson :\n");
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape --;
				}
				else if( verification_nom(stock,interraction) == -1){			// On verifie que le nom n'existe pas encore avec la fonction verifation_nom, -1 elle pas de correspondance		
					strcpy(boisson.nom,interraction);							// Si il existe pas, on mets le nom dans la structure boisson
					etape ++;													// Et on passe a l'etape suivante
				}
				else if( verification_nom(stock,interraction) != -1 && strcmp(stock[verification_nom(stock,interraction)].categorie,"boisson") == 0 ){			// Si le nom existe on va a l'étape 10, la fonction verification_nom qui retourne l'id de la boisson, != -1 une correspondance
					etape = 10;
				}
		break;

		case 1:																			// Etape 1 : saisie du type de la boisson
			printf("\tVeuillez entre le type de boisson (ex: sucre / alcool) : \n");
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape --;
				}
				else{
					etape ++;
					strcpy(boisson.type,interraction);
				}
			break;
			
		case 2:																			// Etape 2 : saisie du type de la boisson
			printf("\tVeuillez entre le degre ");
			if (strcmp(interraction,"alcool") == 0 ){									// On demande le degre d'alcool si c'est une boisson alcoolise
				printf("d'alcool de %s :\n",boisson.nom);
			}
			else{
				printf("de sucre de %s :\n",boisson.nom);								// On demande le degre de sucre si c'est une boisson sans-alcool	
			}
			interraction = saisie();
			if (strcmp(interraction,"p") == 0){
				etape --;
			}
			else{
			interraction_chiffre = conversion_long(interraction);
				if( interraction_chiffre >= 0){
					etape ++;
					boisson.degre = (int) interraction_chiffre;
				}
				if(boisson.degre == 0){
					etape = 7;															// Si elle ne possade pas de degre, le prix serait de 0, donc on va etape 7 pour demander le prix
				}
			}
		break;

		case 3:																				// Etape 3 : saisie de la quantite disponible
			printf("\tVeuillez entre la quantite disponible de %s :\n",boisson.nom);	
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape --;
				}
				else{
					interraction_chiffre = conversion_long(interraction);
					if( interraction_chiffre > 0){
						etape ++;
						boisson.quantite= (int) interraction_chiffre;
					}
				}
		break;

		case 4:																				// Etape 4 : saisie de la contenance en cl de la boisson
			printf("\tVeuillez entre la contenance en cl de %s :\n",boisson.nom);
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape --;
				}
				else{
					interraction_chiffre = conversion_long(interraction);
					if( interraction_chiffre > 0){
						etape ++;
						boisson.contenance= (int) interraction_chiffre;
					}
				}
		break;

		case 5:																									// Etape 5 : Verifie si le demande est celle bien voulu
			printf("\t Veuillez entrer \'p\' si il y a un probleme de saisie, sinon entrer \'v\'\n");
			if(boisson.degre != 0){
				boisson.prix = prix_boisson(boisson.degre,boisson.contenance);									// On calcule le prix avec le degre et la contenance avec la fonction prix_boisson
			}

			printf("\tNom : %s, Prix : %.2f, Quantite : %d, Degre : %d, Type : %s, Contenance :  %d\n",boisson.nom ,boisson.prix,boisson.quantite,boisson.degre,boisson.type,boisson.contenance);
			interraction = saisie();
			if(strcmp(interraction,"p") == 0){
				etape = 0;
			}
			else if(strcmp(interraction,"v") == 0){
				etape = 8;									// On fait quitter le do while
				boisson.id = -1;							// On mets boisson.id -1 pour que la fonction ajoutBoisson ajoute la boisson
			}
		break;

		case 7:																			// Etape 7 : On demande le prix en cas de degre nulle
			printf("\tVeuillez entrer le prix de %s :\n",boisson.nom);
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = 2;
				}
				else{
					interraction_chiffre = (float) conversion_long(interraction);
					if( interraction_chiffre > 0){
						etape = 3;
						boisson.prix = (int) interraction_chiffre;
					}
				}
		break;

		case 10:																		// Etape 10 : On demande si il veut augmenter/diminuer la quantite disponible de la boisson
			id = verification_nom(stock,interraction) -1;
			printf("\t Cette boisson est deja enregistre\n, si vous souhaitez changer la quantite en stock entrer la quantite a ajouter/enlever\n Sinon taper \'p\' \n\n");
			printf("\tNom : %s, Prix : %.2f, Quantite : %d, Degre : %d, Type : %s\n",stock[id].nom ,stock[id].prix,stock[id].quantite,stock[id].degre,stock[id].type);
			interraction = saisie();
			if(strcmp(interraction,"p") == 0){
				etape = 0;
			}
			else{
				interraction_chiffre = (int) conversion_long(interraction);
				etape ++;
			}
		break;

		case 11:																			// Etape 11 : On affiche la quantite disponible apres augmentation/diminution de la quantite disponible de la boisson
			boisson.id = id;
			printf("\tLa quantite de %s sera de : %d\n",stock[id].nom,stock[id].quantite+boisson.quantite);
			getchar();
			etape = 8;
		break;
		
		default:
			boisson.id = -2;	// On mets boisson.id -2 pour que la fonction ajoutBoisson ne fasse rien car on est dans le defaut
			supprimerAPartirDe(arborescence, menuActuel);
			return boisson;
			break;
		}
	}
	while(etape != 8);
	supprimerAPartirDe(arborescence, menuActuel);
	return boisson;
}

/*! \fn cocktail_struc saisie_cocktail(boisson_struc *stock,cocktail_struc *cocktail_liste)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction saisie_cocktail
*
*  \param stock Tableau de boissons
*  \param cocktail_liste Tableau de cocktails
*  \param arborescence Arborescence dans les menus
*
*  \return Retourne une structure de cocktail
*
*  \remarks Cette fonction permet au barman d'ajouter un cocktail.
*/
cocktail_struc saisie_cocktail(boisson_struc *stock,cocktail_struc *cocktail_liste, char* arborescence){

	char* interraction = calloc(30,sizeof(char));
	int id;
	int compteur_id = 0;
	int compteur_contenance;
	int etape = 0;
	cocktail_struc cocktail;

	char *menuActuel = "/Saisie_boisson";
	strcat(arborescence, menuActuel);

	do{
		system("clear");
		affichageCentre(arborescence);
		affichageCentre("\tSi vous souhaitez revenir en arriere entrer \'p\'\n");

		switch (etape)
		{
		case 0:																		// Etape 0 : saisie du nom du cocktail
			printf("\tVeuillez entrer le nom du cocktail :\n");
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape --;
				}
				else if( verification_nom(stock,interraction) == -1){				
					strcpy(cocktail.nom,interraction);
					etape ++;
					compteur_id = 0;
				}
				else if(verification_nom(stock,interraction) != -1){
					etape = 8;
				}
		break;

		case 1:																		// Etape 1 : saisie de l'id des composants du cocktail
			printf("\t Veuillez entrer l\' id de la boisson qui va etre ajouter au cocktail, si vous avez fini entrer \'v\' \n");
			if (compteur_id >0){
				printf("La composition : ");
				for(int i = 0; i<compteur_id;i++){								//	On va de 0 jusqu'a la composition du cocktail saisie
					printf("%s ",stock[cocktail.id_boisson[i]].nom);			//  On affiche la composition du cocktail
				}
			}

			if ( compteur_id < 6 ){										// On verifie que compteur_id reste dans la limite maxime du nombre de composant d'un cocktail
				printf("\nFaire une recherche :");
				interraction = saisie();
				if(strcmp(interraction,"p") == 0){
					etape --;
				}
				else if(strcmp(interraction,"v") == 0 && compteur_id > 1){
					etape ++;													// On passe a l'etape suivante
					compteur_contenance = 0;
					for( int i = compteur_id; i< 6; i++){						// On complete la suite des composants du cocktail non saisie
						cocktail.id_boisson[i] = -1;							// On mets -1 au id des composants non défini
					}
					break;
				}
				else{
					printf("%s\n",recherche_boisson(stock,interraction,"boisson"));		// On affichage la recherche par sous chaine
				}

				interraction = saisie();
					if( verification_id(stock,"tout",conversion_long(interraction)) != 0 && strcmp(stock[conversion_long(interraction)-1].categorie,"boisson") == 0){			// On verifie que la boisson existe et qu'il s'agit bien d'une boisson
						cocktail.id_boisson[compteur_id] = conversion_long(interraction)-1;																					// Si oui on ajoute l'id de la boisson au cocktail
						compteur_id ++;																																		// On incrémente pour changer le rang de la prochaine saisie de boisson
					}
			}							
			else{
				printf("\n Vous ne pouvez pas ajouter plus de composant a votre cocktail :");								// On affiche le message quand la composition maximale est atteinte
				printf("\n Entrer \'v\' si vous souhaitez valider sa composition, sinon entrer \'p\' \n");
				if(strcmp(saisie(),"p") == 0){
					compteur_id = 0;																						// Si la saisie est incorrecte on reinitialiser la saisie des id des boissons
			}
			}
			if(strcmp(interraction,"p") == 0){
				etape --;
			}
			else if( strcmp(interraction,"v") == 0 && compteur_id > 1){
				etape ++;
				compteur_contenance = 0;
				for( int i = compteur_id; i< 6; i++){											// On complete la suite des composants du cocktail non saisie			
					cocktail.id_boisson[i] = -1;
				}
				if( verification_id(stock,"tout",conversion_long(interraction)) != 0 && strcmp(stock[conversion_long(interraction)-1].categorie,"boisson")){	// On verifie que la boisson existe et qu'il s'agit bien d'une boisson
					cocktail.id_boisson[compteur_id] = conversion_long(interraction)-1;
					compteur_id ++;
				}
			}
		break;

		case 2:																		// Etape 2 : saisie de la contenance des composants
			if(compteur_id > compteur_contenance){
				printf("\t Veuillez entrer la contenance de %s en cl \n",stock[cocktail.id_boisson[compteur_contenance]].nom);
				interraction = saisie();
				if(strcmp(interraction,"p") == 0){
					etape = 0;
					compteur_id = 0;
					compteur_contenance = 0;
				}
				cocktail.contenance[compteur_contenance] = conversion_long(interraction);
				if( cocktail.contenance[compteur_contenance] > 0){
						compteur_contenance ++;
					}
			}
			else{
				for( int i = compteur_id; i< 6 ;i++){ 						// On complete la suite des composants du cocktail non saisie
					cocktail.contenance[i] = 0;								// On mets 0 au contenances des composants non défini
				}
				etape++;
			}
		break;


		case 3: 																										// Etape 3 : Verifie si la saisie des composants est correcte
			printf("\t Veuillez entrer \'v\', si la saisie de votre cocktail est correcte, sinon entrer \'p\' \n");
			printf("La composition du cocktail : ");
			for(int i = 0; i<6; i++){
				if(cocktail.id_boisson[i] != -1){
				printf("%dcl %s, ",cocktail.contenance[i],stock[cocktail.id_boisson[i]].nom);			// On affiche la compostion
				}
			}
			interraction = saisie();
				if(strcmp(interraction,"p") == 0){
					etape --;
					compteur_id = 0;
				}
				else if( strcmp(interraction,"v") == 0 ){
					etape ++;
				}
		break;

		case 4: 																										// Etape 4 : Verifie si la saisie est correcte
			printf("\t Veuillez entrer \'p\' si il y a un probleme de saisie, sinon entrer \'v\'\n");
			int quantite = quantite_cocktail(stock,cocktail);
			int contenance = contenance_cocktail(cocktail);
			int degre = degre_cocktail(stock,cocktail);
			cocktail.prix = prix_cocktail(stock,cocktail);
			char* type = type_cocktail(stock,cocktail);

			printf("\tNom : %s, Prix : %.2f, Quantite disponible actuellement : %d, Degre : %d, Type : %s, Contenance :  %d\n",cocktail.nom ,cocktail.prix ,quantite,degre,type,contenance);
			interraction = saisie();
				if(strcmp(interraction,"p") == 0){
					etape --;
					compteur_id = 0;
				}
				else if (strcmp(interraction,"v") == 0){
					etape = 6;
				}
		break;

		case 8: 																					// Etape 8 : Affiche la compostion d'un cocktail deja enregistre
			id = verification_nom(stock,interraction) -1;
			printf("\t Ce nom de %s est déja en stock \n",stock[id].categorie);
			printf("\t Elle correspond a Nom : %s, Prix : %.2f, Quantite : %d, Degre : %d, Type : %s\n",stock[id].nom ,stock[id].prix ,stock[id].quantite,stock[id].degre,stock[id].type);

			if ( strcmp(stock[id].categorie,"cocktail") == 0){
				printf("\t La composition du cocktail est :");
				for ( int i = 0; i<6 ; i++){
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
			supprimerAPartirDe(arborescence, menuActuel);
			return cocktail;
			break;
		}
	}
	while(etape != 6);

	supprimerAPartirDe(arborescence, menuActuel);
	return cocktail;

}

/*! \fn void afficher_Cocktail(boisson_struc* stock,cocktail_struc* cocktail_liste)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction afficher_Cocktail
*
*  \param stock Tableau de boissons
*  \param cocktail_liste Tableau de cocktails
*  \param arborescence Arborescence dans les menus
*
*  \remarks Cette fonction permet d'afficher les ingredients d'un cocktail et leurs details.
*/
void afficher_Cocktail(boisson_struc* stock,cocktail_struc* cocktail_liste,char *arborescence){

	int etape = 0;
	int id ;
	char* interraction = calloc(10,sizeof(char));

	char *menuActuel = "/Affichage_cocktail";
	strcat(arborescence, menuActuel);

	do{
		system("clear");
		affichageCentre(arborescence);
		if (taille_stock("data_cocktail")){																// On verifie qu"il y est bien des cocktails
			afficherTableau (stock,cocktail_liste,arborescence,"cocktail",taille_stock("data_boisson"),0);			// On affiche le tableau sans pause
			printf("\n\tSi vous souhaitez quitter entrez \'p\'\n");
			printf("\n\tSi vous voulez plus d'information sur un cocktail entrer son id :\n");
			interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = 1;
				}
				id = (int) conversion_long(interraction);
				if( verification_cocktail(stock,id) ){
					printf("La composition de %s est :",stock[id].nom);				// On affiche le nom du cocktail
					for(int i = 0; i<6; i++){
						if(cocktail_liste[stock[id].id-1].id_boisson[i] != -1){
						printf("%d cl de %s, ",cocktail_liste[stock[id].id-1].contenance[i], stock[ cocktail_liste[stock[id].id-1].id_boisson[i] ].nom);		// On affiche sa compostion
						}
					}
					printf("\n");
				if (strcmp(saisie(),"p") == 0){
					etape = 1;
				}
				}
			}
			else{
				affichageCentre("Il n'y a pas de cocktail enregistre\n");			// On affichage le message quand il n'y a pas de cocktail dans la base de donnee
				interraction = saisie();
				if (strcmp(interraction,"p") == 0){
					etape = 1;
				}
			}
		}
	while(etape != 1);
	
	supprimerAPartirDe(arborescence, menuActuel);

}

/*! \fn void administration()
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*p
*  \brief Fonction administration
*  \param arborescence Arborescence dans les menus
*
*  \remarks Cette fonction affiche toutes les commandes et le chiffre d'affaires.
*/
void administration(char *arborescence){

	
	char *menuActuel = "/Administration";
	strcat(arborescence, menuActuel);

	system("clear");
	affichageCentre(arborescence);
    affichageCentre("Les commandes enregistrés :");
    FILE* lecture = NULL;
    int taille;
    float chiffre_daffaire = 0;

    lecture = fopen("../data/commande.txt", "r");

    if (lecture != NULL)
    {
        boisson_struc boisson;
        int id_personne;
        fscanf(lecture,"%d", &taille);

        for( int i = 0; i<taille;i++ ){
            fscanf(lecture, "%s %f %d %d %d %s",boisson.nom,&boisson.prix,&boisson.quantite,&id_personne,&boisson.id,boisson.categorie);
            if(id_personne){
                printf("\t%s : %d %s au prix de : %.2f€, %s par un client\n",boisson.categorie,boisson.quantite,boisson.nom,boisson.prix,boisson.type);
            }
            else{
                printf("\t%s : %d %s au prix de : %.2f€, %s par un serveur\n",boisson.categorie,boisson.quantite,boisson.nom,boisson.prix,boisson.type);
            }
            chiffre_daffaire += boisson.prix;
        }

        fclose(lecture);
    }
    else{
        fclose(lecture);
        exit(-1);
    }  

    printf("\n\t Nombre de commande %d, chiffre d'affaire : %.2f€",taille,chiffre_daffaire);
	getchar();
	supprimerAPartirDe(arborescence, menuActuel);
        
}
