#ifndef _MENU_
#define _MENU_


char afficherMenu(boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence);
char afficherMenuClient(boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence);
char afficherInterfaceBarman(boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence);

char inputMenu();
void supprimerAPartirDe (char *chaine, char* supp);

char* saisie();

panier_struc panier_affichage(boisson_struc *stock,cocktail_struc *cocktail_liste,panier_struc panier,int id_personne);

panier_struc saisie_commande(boisson_struc *stock,cocktail_struc *cocktail_liste,panier_struc panier, char *arborescence,int id_personne);

void affichageCentre(char *chaine);
void affichageMarge(char *chaine, int ratio);

void afficherTableau (boisson_struc *stock,cocktail_struc *cocktail_liste,char* categorie,int taille_tableau);
void afficherEntete (char *ligne, int *taillesColonnes, int nbColonnes, int largeur);
void remplirEspaces(char tab[], int debut, int fin);
void separerColonnes (char *ligne, int nbColonnes, int *taillesColonnes);


boisson_struc saisie_boisson(boisson_struc *stock);
cocktail_struc saisie_cocktail(boisson_struc *stock,cocktail_struc *cocktail_liste);

void administration();

#endif