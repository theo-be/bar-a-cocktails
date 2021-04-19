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
    int id;
};
boisson_struc *remplirstock();
int commande(boisson_struc *stock,int boisson_id,int quantite,int id_client);
void affichage(boisson_struc *stock);
void centrage(int colonne);
void affichage_emplacement(int colonne,char* affichage_ecran, int emplacement);
int saisie_int(int colonne,char* affichage_message);
int taille_stock();

#endif