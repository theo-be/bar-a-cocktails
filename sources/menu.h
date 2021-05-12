#ifndef _MENU_
#define _MENU_


char afficherMenu(boisson_struc *stock);
char afficherInterfaceAdmin(boisson_struc *stock);
char afficherListe(char *typeAjout,boisson_struc *stock);
char afficherListeAdmin(char *typeAjout,boisson_struc *stock);
// char afficherDetailsBoisson();
//char commanderBoisson();
char* saisie();
char inputMenu();
char saisie_commande(boisson_struc *stock);
char afficherStocks(boisson_struc *stock,char* categorie);

#endif
