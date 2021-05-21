#ifndef H_cocktail
#define H_cocktail

typedef struct boisson_struc boisson_struc;
struct boisson_struc
{
    char categorie[30];
    char nom[30];
    float prix;
    int degre;
    int quantite;
    int contenance;
    char type[30];
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

int taille_stock(char* data);
boisson_struc *remplirstock_boisson();
cocktail_struc *remplirstock_cocktail();

char commande(boisson_struc *stock,long boisson_id,long quantite,int id_client);
char**tableau_type(boisson_struc *stock);
char* message_type(boisson_struc *stock);
int verification_type(boisson_struc *stock,char* type);
int verification_id(boisson_struc *stock,char* type,long id);
int* tableau_id(boisson_struc *stock,char* type);
char* message_id(boisson_struc *stock,char* type);
char* message_quantite(boisson_struc *stock,int id);
int verification_nom(boisson_struc *stock,char* nom);
char* recherche_boisson(boisson_struc *stock,char* recherche);

char* affichage_boisson(boisson_struc *stock);

long conversion_long(char* chaine);

int contenance_cocktail(cocktail_struc cocktail);
int quantite_cocktail(boisson_struc *stock,cocktail_struc cocktail);
char* type_cocktail(boisson_struc *stock,cocktail_struc cocktail);
int degre_cocktail(boisson_struc *stock,cocktail_struc cocktail);
float prix_cocktail(boisson_struc *stock,cocktail_struc cocktail);

boisson_struc *ajouterBoisson(boisson_struc *stock);
cocktail_struc *ajouterCocktail(boisson_struc *stock,cocktail_struc *cocktail_liste);

#endif