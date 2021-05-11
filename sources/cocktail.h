#ifndef H_cocktail
#define H_cocktail

typedef struct boisson_struc boisson_struc;
struct boisson_struc
{
    char nom[30];
    float prix;
    float degre;
    int quantite;
    char type[30];
    char categorie[30];
    int id;
};

int taille_stock();
boisson_struc *remplirstock();
char commande(boisson_struc *stock,long boisson_id,long quantite,int id_client);
char**tableau_type(boisson_struc *stock);
char* message_type(boisson_struc *stock);
int verification_type(boisson_struc *stock,char* type);
int verification_id(boisson_struc *stock,char* type,long id);
int* tableau_id(boisson_struc *stock,char* type);
char* message_id(boisson_struc *stock,char* type);
char* message_quantite(boisson_struc *stock,int id);
char* affichage_boisson(boisson_struc *stock);
long conversion_long(char* chaine);

#endif
