#ifndef _MENU_
#define _MENU_


char afficherMenu(boisson_struc *stock, char *arborescence);
char afficherMenuClient(boisson_struc *stock, char *arborescence);
char afficherInterfaceBarman(boisson_struc *stock, char *arborescence);
char commanderBoisson(boisson_struc *stock, char *arborescence);

char inputMenu();
void supprimerAPartirDe (char *chaine, char* supp);

char* saisie();
char saisie_commande(boisson_struc *stock, char *arborescence,int id_personne);
char afficherStocks(boisson_struc *stock,char* categorie);
boisson_struc saisie_boisson(boisson_struc *stock);

void affichageCentre(char *chaine);
void affichageMarge(char *chaine, int ratio);

void afficherTableau();
void remplirEspaces(char tab[], int debut, int fin);


#endif
