#ifndef H_cocktail
#define H_cocktail

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

typedef struct cocktail_struc cocktail_struc;
struct cocktail_struc
{
    char nom[30];
    int id_boisson[6];
    int contenance[6];
    float prix;
};

typedef struct bdd bdd;
struct bdd
{
    cocktail_struc *cocktail_liste;
    boisson_struc *stock;

};

typedef struct panier_struc panier_struc;
struct panier_struc
{
    boisson_struc stock[20];
    int taille;

};

int taille_stock(char* data);
boisson_struc *remplirstock_boisson();
cocktail_struc *remplirstock_cocktail();
int commande(boisson_struc* stock,panier_struc panier,int id_personne);

char**tableau_type(boisson_struc *stock);
char* message_type(boisson_struc *stock);
int verification_type(boisson_struc *stock,char* type);
int verification_id(boisson_struc *stock,char* type,long id);
int* tableau_id(boisson_struc *stock,char* type);
char* message_id(boisson_struc *stock,char* type);
char* message_quantite(boisson_struc *stock,int id);
int verification_nom(boisson_struc *stock,char* nom);
char* recherche_boisson(boisson_struc *stock,char* recherche,char *categorie);
char* affichage_boisson(boisson_struc *stock);

long conversion_long(char* chaine);

int contenance_cocktail(cocktail_struc cocktail);
int quantite_cocktail(boisson_struc *stock,cocktail_struc cocktail);
char* type_cocktail(boisson_struc *stock,cocktail_struc cocktail);
int degre_cocktail(boisson_struc *stock,cocktail_struc cocktail);
float prix_cocktail(boisson_struc *stock,cocktail_struc cocktail);

float prix_boisson(int degre, int contenance);

boisson_struc *ajouterBoisson(boisson_struc *stock);
bdd ajouterCocktail(boisson_struc *stock,cocktail_struc *cocktail_liste);

panier_struc ajouterPanier(panier_struc panier,boisson_struc commande,int id_personne);


#endif