/*! \file cocktail.h
* \author Rabus Jules
* \version 1
* \date 19/04/2021 Debut du travail en groupe
* \date 22/05/2021 Creation des commentaires doxygen.
* \brief Le fichier cocktail.h contient l'ensemble des fonctions necessaires pour la gestion des boissons et des cocktails.
*/

#ifndef H_cocktail
#define H_cocktail

/* Structures */

/*!
*  \class boisson_struc
*  \brief Declaration de la structure boisson_struc necessaire pour la gestion des boissons
*/
typedef struct boisson_struc boisson_struc;
struct boisson_struc
{
    char nom[30];
    float prix;
    int degre;
    int quantite;
    int contenance;
    char type[30];
    char categorie[30];
    int id;
};

/*!
*  \class cocktail_struc
*  \brief Declaration de la structure cocktail_struc necessaire pour la gestion des cocktails
*/
typedef struct cocktail_struc cocktail_struc;
struct cocktail_struc
{
    char nom[30];
    int id_boisson[6];
    int contenance[6];
    float prix;
};

/*!
*  \class bdd
*  \brief Declaration de la structure bdd qui represente une base de donnees
*/
typedef struct bdd bdd;
struct bdd
{
    cocktail_struc *cocktail_liste;
    boisson_struc *stock;

};

/*!
*  \class panier_struc
*  \brief Declaration de la structure panier_struc necessaire pour afficher l'historique des achats
*/
typedef struct panier_struc panier_struc;
struct panier_struc
{
    boisson_struc stock[20];
    int taille;

};

/* Fonctions et prototypes */

/*!
*  \brief Prototype de la fonction taille_stock
*/
int taille_stock(char* data);

/*!
*  \brief Prototype de la fonction remplirstock_boisson
*/
boisson_struc *remplirstock_boisson();

/*!
*  \brief Prototype de la fonction remplirstock_cocktail
*/
cocktail_struc *remplirstock_cocktail();

/*!
*  \brief Prototype de la procedure commande
*/
void commande(boisson_struc* stock,cocktail_struc* cocktail_liste,panier_struc panier,int id_personne);

/*!
*  \brief Prototype de la fonction tableau_type
*/
char**tableau_type(boisson_struc *stock);

/*!
*  \brief Prototype de la fonction message_type
*/
char* message_type(boisson_struc *stock);

/*!
*  \brief Prototype de la fonction verification_type
*/
int verification_type(boisson_struc *stock,char* type);

/*!
*  \brief Prototype de la fonction verification_id
*/
int verification_id(boisson_struc *stock,char* type,long id);

/*!
*  \brief Prototype de la fonction tableau_id
*/
int* tableau_id(boisson_struc *stock,char* type);

/*!
*  \brief Prototype de la fonction message_id
*/
char* message_id(boisson_struc *stock,char* type);

/*!
*  \brief Prototype de la fonction message_quantite
*/
char* message_quantite(boisson_struc *stock,cocktail_struc *cocktail_liste,int id);

/*!
*  \brief Prototype de la fonction verification_nom
*/
int verification_nom(boisson_struc *stock,char* nom);

/*!
*  \brief Prototype de la fonction recherche_boisson
*/
char* recherche_boisson(boisson_struc *stock,char* recherche,char *categorie);

/*!
*  \brief Prototype de la fonction affichage_boisson
*/
char* affichage_boisson(boisson_struc *stock);

/*!
*  \brief Prototype de la fonction conversion_long
*/
long conversion_long(char* chaine);

/*!
*  \brief Prototype de la fonction verification_cocktail
*/
int verification_cocktail(boisson_struc *stock,int id);

/*!
*  \brief Prototype de la fonction contenance_cocktail
*/
int contenance_cocktail(cocktail_struc cocktail);

/*!
*  \brief Prototype de la fonction quantite_cocktail
*/
int quantite_cocktail(boisson_struc *stock,cocktail_struc cocktail);

/*!
*  \brief Prototype de la fonction type_cocktail
*/
char* type_cocktail(boisson_struc *stock,cocktail_struc cocktail);

/*!
*  \brief Prototype de la fonction degre_cocktail
*/
int degre_cocktail(boisson_struc *stock,cocktail_struc cocktail);

/*!
*  \brief Prototype de la fonction prix_cocktail
*/
float prix_cocktail(boisson_struc *stock,cocktail_struc cocktail);

/*!
*  \brief Prototype de la fonction prix_boisson
*/
float prix_boisson(int degre, int contenance);

/*!
*  \brief Prototype de la fonction ajouterBoisson
*/
boisson_struc *ajouterBoisson(boisson_struc *stock,char *arborescence);

/*!
*  \brief Prototype de la fonction ajouterCocktail
*/
bdd ajouterCocktail(boisson_struc *stock,cocktail_struc *cocktail_liste,char *arborescence);

/*!
*  \brief Prototype de la fonction ajouterPanier
*/
panier_struc ajouterPanier(panier_struc panier,boisson_struc commande);

/*!
*  \brief Prototype de la fonction quitter
*/
char quitter(boisson_struc *stock);


#endif