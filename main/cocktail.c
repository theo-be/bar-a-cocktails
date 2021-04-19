#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cocktail.h"
#include <math.h>
#include <windows.h>
#define TAILLE_LECTURE 100
    
  
boisson_struc *remplirstock(){

    FILE* lecture = NULL;
    lecture = fopen("data/data.txt", "r");
    if (lecture != NULL)
    {
        int taille;
        rewind(lecture);
        fscanf(lecture, "%d", &taille);

        boisson_struc boisson;
        boisson_struc *tab_boisson = malloc(taille * sizeof(boisson_struc) );

        for( int i = 0; i<taille;i++ ){
            fscanf(lecture, "%s%*c %f%*c %f%*c %d%*c %s",boisson.nom,&boisson.prix,&boisson.degre,&boisson.quantite,boisson.type );
            boisson.id = i ;
            tab_boisson[i] = boisson;
        }

        fclose(lecture);
        return tab_boisson;
    }
    else{
        fclose(lecture);
        exit(-1);
    }  
        
}

int commande(boisson_struc *stock,int boisson_id,int quantite,int id_client){

    if(stock[boisson_id].quantite >= quantite){

        stock[boisson_id].quantite -= quantite;

        FILE* ecriture = NULL;
        ecriture = fopen("data/commande.txt", "a");
        fprintf(ecriture,"%s %.2f %d %d\n",stock[boisson_id].nom ,stock[boisson_id].prix * quantite ,quantite ,id_client);
        fclose(ecriture);
        return 1;
    }
    else{

        return 0;
    }
}

void affichage_centre(int colonne,char* affichage_ecran){
    
    int taille_affichage = strlen(affichage_ecran);
    int cote = ceil(colonne - taille_affichage)/2 ;
    for(int i = 0; i<cote; i++){
    printf(" ");
    }

    printf("%s",affichage_ecran);
        
    for( int i = 0; i<cote; i++){
    printf(" ");
    }
}

void affichage(){

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int colonne;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    colonne = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int marge = colonne * 0.03 ;
    int taille_affichage;
    int terminal = 0;
    char* affichage_ecran;

    for( int i = 0; i < colonne; i++ ){
      printf("=");
    }
    printf("\n\n");

    switch (terminal)
    {
    case 0:
        
        affichage_ecran = "Veuillez entrer l'interface a afficher :";
        affichage_centre(colonne,affichage_ecran);
        //printf("%s",affichage_ecran);

        break;
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;
    default:
        break;
    }



    printf("\n\n");

    for( int i = 0; i < colonne; i++ ){
      printf("=");
    }
    
}