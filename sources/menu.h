#ifndef _MENU_
#define _MENU_


char afficherMenu(char *arborescence);
char afficherMenuClient(char *arborescence);
char afficherInterfaceAdmin(char *arborescence);
char afficherListe(char *typeAjout);
char afficherListeAdmin(char *typeAjout);
char commanderBoisson(char *arborescence);

char inputMenu();
void supprimerAPartirDe (char *chaine, char* supp);

char* saisie();
char saisie_commande(boisson_struc *stock);
char afficherStocks(boisson_struc *stock,char* categorie);

void affichageCentre(char *chaine);
void affichageMarge(char *chaine, int ratio);

void afficherTableau();
void remplirEspaces(char tab[], int debut, int fin);

char foo();

#endif
