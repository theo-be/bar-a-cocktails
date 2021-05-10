#ifndef _MENU_
#define _MENU_


char afficherMenu(boisson_struc *stock);
char afficherInterfaceAdmin(boisson_struc *stock);
char afficherListe(char *typeAjout,boisson_struc *stock);
char afficherListeAdmin(char *typeAjout,boisson_struc *stock);
char ajouterBoisson();
char ajouterCocktail();
// char afficherDetailsBoisson();
char commanderBoisson();
char* saisie();
char inputMenu();
//char foo();
char saisie_commande(boisson_struc *stock);
char afficherStocks(boisson_struc *stock,char* categorie);

#endif
