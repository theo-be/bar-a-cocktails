#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cocktail.h"
#include <math.h>
#include <windows.h>
#define TAILLE_LECTURE 100
    
int taille_stock(){
    FILE* lecture = NULL;
    lecture = fopen("data/data.txt", "r");
    if (lecture != NULL)
    {
        int taille;
        rewind(lecture);
        fscanf(lecture,"%d", &taille);
        fclose(lecture);
        return taille;
    }
    else{
    fclose(lecture);
    exit(-1);
    }  
}

boisson_struc *remplirstock(){

    FILE* lecture = NULL;
    lecture = fopen("data/data.txt", "r");
    if (lecture != NULL)
    {
        int taille;
        rewind(lecture);
        fscanf(lecture,"%d", &taille);

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

void affichage_emplacement(int colonne,char* affichage_ecran, int emplacement){
    
    int taille_affichage = strlen(affichage_ecran);
    int cote = ceil(colonne - taille_affichage)/2 ;

    switch (emplacement)
    {
    case 0 : // gauche

        for(int i = 0; i<cote; i++){
            printf(" ");
        }

        printf("%s",affichage_ecran);

            break;


    case 1 :// milieu

        for(int i = 0; i<cote; i++){
            printf(" ");
        }

        printf("%s",affichage_ecran);

        for(int i = 0; i<cote; i++){
            printf(" ");
        }
             break;

    default: //droite

        printf("%s",affichage_ecran);

        for(int i = 0; i<cote; i++){
            printf(" ");
        }

        break;
    }

}

int saisie_int(int colonne,char* affichage_message){
    
    int taille_affichage = strlen(affichage_message);
    int cote = ceil(colonne - taille_affichage)/2 ;
    int saisie = 0;

        for(int i = 0; i<cote; i++){
            printf(" ");
        }

        printf("%s",affichage_message);
        printf("\n");
        scanf("%d",&saisie);

    return saisie;

}

void affichage_type(int colonne,int type,boisson_struc *stock){

    int taille_stock = taille_stock;
    char* chaine = malloc(60 * taille_stock * sizeof(char) );
    int x = 0;

    for (int i = 0; i< taille_stock; i++){

     for ( int l = 0; l<strlen(stock[i].nom); l++){
            chaine[x] = stock[i].nom[l];
            x++;
            }

    }
    printf("affichage %s", chaine);



    
}

void affichage(boisson_struc *stock){

    CONSOLE_SCREEN_BUFFER_INFO csbi; // windows
    int colonne;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); // windows
    colonne = csbi.srWindow.Right - csbi.srWindow.Left + 1; // windows
    int terminal = 0;
    int interraction = 0;
    int saisie = 0;
    char* affichage_ecran;


    do{

    system("cls"); // windows

    for( int i = 0; i < colonne; i++ ){
      printf("=");
    }
    printf("\n\n");   
        
    switch (terminal){

    case 0: // début

        affichage_ecran = "Veuillez entrer l'interface a afficher :";
        affichage_emplacement(colonne,affichage_ecran,1);
       /* affichage_ecran = "Barman = 1, Client = 2";
        affichage_emplacement(colonne,affichage_ecran,1);
        printf("\n");
        affichage_emplacement(colonne,"",0);
        scanf("%d",&terminal);*/
        interraction = saisie_int(colonne,"Barman = 1, Client = 2");

        break;
    case 1: // Barman
        /* code */
        break;
    case 2: // Client

        switch (saisie)
        {
        case 1:
            /* code */
            break;

        case 2:
                    /* code */
                    break;     
        default:
            break;
        }
        affichage_ecran = "Veuillez choisir la boisson :";
        affichage_emplacement(colonne,affichage_ecran,1);
        affichage_emplacement(colonne,"",0);
        scanf("%d",&interraction);

        /* code */
        break;
    default: // fin
        break;
    }

    }while(terminal != -1);


    printf("\n\n");

    for( int i = 0; i < colonne; i++ ){
      printf("=");
    }
    
}