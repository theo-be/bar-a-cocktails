#ifndef _MENU_
#define _MENU_

/*!
*  \brief Prototype de la fonction vigenere
*/
char afficherMenu(boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence);

/*!
*  \brief Prototype de la fonction vigenere
*/
char afficherMenuClient(boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence);

/*!
*  \brief Prototype de la fonction vigenere
*/
char afficherInterfaceBarman(boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence);

/*!
*  \brief Prototype de la fonction vigenere
*/
char inputMenu();

/*!
*  \brief Prototype de la fonction vigenere
*/
void supprimerAPartirDe (char *chaine, char* supp);

/*!
*  \brief Prototype de la fonction vigenere
*/
char* saisie();

/*!
*  \brief Prototype de la fonction vigenere
*/
panier_struc panier_affichage(boisson_struc *stock,cocktail_struc *cocktail_liste,panier_struc panier,int id_personne);

/*!
*  \brief Prototype de la fonction vigenere
*/
panier_struc saisie_commande(boisson_struc *stock,cocktail_struc *cocktail_liste,panier_struc panier, char *arborescence,int id_personne);

/*!
*  \brief Prototype de la fonction vigenere
*/
void affichageCentre(char *chaine);

/*!
*  \brief Prototype de la fonction vigenere
*/
void affichageMarge(char *chaine, int ratio);

/*!
*  \brief Prototype de la fonction vigenere
*/
void afficherTableau (boisson_struc *stock,cocktail_struc *cocktail_liste,char* categorie,int taille_tableau,int pause);

/*!
*  \brief Prototype de la fonction vigenere
*/
void afficherEntete (char *ligne, int *taillesColonnes, int nbColonnes, int largeur);

/*!
*  \brief Prototype de la fonction vigenere
*/
void remplirEspaces(char tab[], int debut, int fin);

/*!
*  \brief Prototype de la fonction vigenere
*/
void separerColonnes (char *ligne, int nbColonnes, int *taillesColonnes);

/*!
*  \brief Prototype de la fonction vigenere
*/
boisson_struc saisie_boisson(boisson_struc *stock);

/*!
*  \brief Prototype de la fonction vigenere
*/
cocktail_struc saisie_cocktail(boisson_struc *stock,cocktail_struc *cocktail_liste);

/*!
*  \brief Prototype de la fonction vigenere
*/
void afficher_Cocktail(boisson_struc* stock,cocktail_struc* cocktail_liste);

/*!
*  \brief Prototype de la fonction vigenere
*/
void administration();

#endif
