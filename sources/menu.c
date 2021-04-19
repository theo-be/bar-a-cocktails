#include <stdio.h>
#include <stdlib.h>


int afficherMenu() {

	// on affiche le menu
	printf("coucouu");

	

	
	return demanderQuitter();
}

int demanderQuitter() {
	int quitter = 0;
	int erreur = 0;

	int bufsize = 2;

	char* buffer = NULL;

	buffer = (char*)malloc(bufsize * sizeof(char));

	do {
		printf("Voulez-vous quitter ? ");
		getline(&buffer, &bufsize, stdin);

		// analyser la chaine
	} while (erreur == 1);
	return quitter;
}