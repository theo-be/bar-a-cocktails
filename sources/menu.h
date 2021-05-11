#ifndef _MENU_
#define _MENU_


char afficherMenu(char arborescence[]);
char afficherInterfaceAdmin(char arborescence[]);
char afficherListe(char *typeAjout);
char afficherListeAdmin(char *typeAjout);
char ajouterBoisson(char *arborescence);
char ajouterCocktail(char *arborescence);
char commanderBoisson(char *arborescence);

char inputMenu();
void supprimerAPartirDe (char *chaine, char* supp);

void affichageCentre(char *chaine);
void affichageMarge(char *chaine, int ratio);

char foo();

#endif
