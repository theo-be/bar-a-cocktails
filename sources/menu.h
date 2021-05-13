#ifndef _MENU_
#define _MENU_


char afficherMenu(boisson_struc *stock);
char afficherInterfaceAdmin(boisson_struc *stock);
char afficherListe(char *typeAjout,boisson_struc *stock);
char afficherListeAdmin(char *typeAjout,boisson_struc *stock);
char* saisie();
char inputMenu();
char saisie_commande(boisson_struc *stock);
boisson_struc saisie_boisson(boisson_struc *stock);
char afficherStocks(boisson_struc *stock,char* categorie);


#endif
