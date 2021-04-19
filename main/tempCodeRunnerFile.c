#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cocktail.h"
#define TAILLE_LECTURE 50

int taille_lecture(FILE* fichier){

    char *lecture = malloc(TAILLE_LECTURE * sizeof(char));
    char *fin;
    int caractere = 0;
    int i = 0;
    int taille_lecture = 0;
        do{
            caractere = fgetc(fichier); 
            lecture[i] = caractere; 
            i++;

        }while(caractere != '\n');
        taille_lecture = (int) strtof(lecture,&fin);
    return taille_lecture;
}

void decomposition(char* lecture,int taille){

        printf("fait decompo");
    
  /*   int ordre = 0;
    int i = 0;
    boisson_struc boisson;
    char* fin;
    char *decomposition;
    boisson_struc *stock = (boisson_struc*) malloc(taille * sizeof(boisson) );

while(lecture[i] != '\0'){

    if (lecture[i] == ';'){
        switch (ordre)
        {
        case 0:
            boisson.nom = decomposition;
            break;
        case 1:
            boisson.prix = strtof(decomposition,&fin);
            break;
        case 2:
            boisson.degre = strtof(decomposition,&fin);
            break;
        case 3:
            boisson.type = decomposition;
            break;
        default:
            boisson.quantite = (int) strtof(decomposition,&fin);
            break;
        }
        ordre++;
    }
    else if(lecture[i] != '\n'){
        stock[i] = boisson;
    }
    else{
        sprintf(decomposition, "%c" ,lecture[i]);
    }
    i++;
}   
*/
}

void remplirstock(){

    FILE* fichier = NULL;
    fichier = fopen("data.txt", "r");
    if (fichier != NULL)
    {
        char *lecture;
        int taille = taille_lecture(fichier);
        do{
            printf("fait remplir");
            fgets(lecture, TAILLE_LECTURE, fichier);
            for(int i = 0; i<20;i++){
printf("lecture %c",lecture[i]);

            }

            decomposition(lecture,taille);
        }
        while(lecture != NULL);
        fclose(fichier);
        
    }
}