#ifndef H_cocktail
#define H_cocktail

typedef struct boisson_struc boisson_struc;
struct boisson_struc
{
    char* nom[30];
    float prix;
    float degre;
    int quantite;
    char* type[30];
    int id;
};
boisson_struc *remplirstock();
int commande(boisson_struc *stock,int boisson_id,int quantite,int id_client);
void affichage();
void centrage(int colonne);
void affichage_centre(int colonne,char* affichage);

#endif