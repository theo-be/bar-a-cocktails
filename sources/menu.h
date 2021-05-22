/*! \file menu.h
* \section Presentation
* \brief Le fichier menu.h regroupe tous les prototypes de fonctions necessaires a l'affichage des menus et aux interactions utilisateur.
*/


#ifndef _MENU_
#define _MENU_

#include "cocktail.h"

/*!
*  \brief Prototype de la fonction afficherMenu
*/
char afficherMenu(boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence);

/*!
*  \brief Prototype de la fonction afficherMenuClient
*/
char afficherMenuClient(boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence);

/*!
*  \brief Prototype de la fonction afficherInterfaceBarman
*/
char afficherInterfaceBarman(boisson_struc *stock,cocktail_struc *cocktail_liste, char *arborescence);

/*!
*  \brief Prototype de la fonction inputMenu
*/
char inputMenu();

/*!
*  \brief Prototype de la procedure supprimerAPartirDe
*/
void supprimerAPartirDe (char *chaine, char* supp);

/*!
*  \brief Prototype de la fonction saisie
*/
char* saisie();

/*!
*  \brief Prototype de la fonction panier_affichage
*/
panier_struc panier_affichage(boisson_struc *stock,cocktail_struc *cocktail_liste,panier_struc panier,int id_personne);

/*!
*  \brief Prototype de la fonction saisie_commande
*/
panier_struc saisie_commande(boisson_struc *stock, cocktail_struc *cocktail_liste, panier_struc panier, char *arborescence, int id_personne);

/*!
*  \brief Prototype de la procedure affichageCentre
*/
void affichageCentre(char *chaine);

/*!
*  \brief Prototype de la procedure affichageMarge
*/
void affichageMarge(char *chaine, int ratio);

/*!
*  \brief Prototype de la procedure afficherTableau
*/
void afficherTableau(boisson_struc *stock,cocktail_struc *cocktail_liste, char* categorie, int taille_tableau, int pause);

/*!
*  \brief Prototype de la procedure afficherEntete
*/
void afficherEntete(char *ligne, int *taillesColonnes, int nbColonnes, int largeur);
/*!
*  \brief Prototype de la procedure remplirEspaces
*/
void remplirEspaces(char *tab, int debut, int fin);

/*!
*  \brief Prototype de la procedure separerColonnes
*/
void separerColonnes(char *ligne, int nbColonnes, int *taillesColonnes);

/*!
*  \brief Prototype de la fonction saisie_boisson
*/
boisson_struc saisie_boisson(boisson_struc *stock);

/*!
*  \brief Prototype de la fonction saisie_cocktail
*/
cocktail_struc saisie_cocktail(boisson_struc *stock,cocktail_struc *cocktail_liste);

/*!
*  \brief Prototype de la procedure administration
*/
void administration();

#endif
