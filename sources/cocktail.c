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
            boisson.id = i +1 ;
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

char* commande(boisson_struc *stock,int boisson_id,int quantite,int id_client){

   boisson_id -= 1;

    if(stock[boisson_id].quantite >= quantite){

        stock[boisson_id].quantite -= quantite;


        FILE* ecriture = NULL;
        ecriture = fopen("data/commande.txt", "a");
        fprintf(ecriture,"%s %.2f %d %d\n",stock[boisson_id].nom ,stock[boisson_id].prix * quantite ,quantite ,id_client);
        fclose(ecriture);
        return "Votre commande a bien ete enregistre";
    }
    else{
        return "Votre commande n'a pas ete enregistre, quantite insuffisante";
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
    int saisie;

        printf("\n\n");

        for(int i = 0; i<cote; i++){
            printf(" ");
        }

        printf("%s",affichage_message);
        scanf("%d",&saisie);

    return saisie;

}

char* saisie_char(int colonne,char* affichage_message){
    
    int taille_affichage = strlen(affichage_message);
    int cote = ceil(colonne - taille_affichage)/2 ;
    char* saisie = calloc(30, sizeof(char));

        printf("\n\n");

        for(int i = 0; i<cote; i++){
            printf(" ");
        }

        printf("%s",affichage_message);
        scanf("%s",saisie);

    return saisie;

}

char* saisie_commande(int colonne,boisson_struc *stock){

        char* interraction= calloc(30, sizeof(char));
        char* affichage_ecran;
        int id = 0;
        int quantite;
        int etape = 0;

        while(etape != 3){

                system("cls"); // windows
                affichage_ligne(colonne);
                printf("\n\n");   

            switch (etape)
            {
            case 0:

                affichage_ecran = "Veuillez choisir le type de boisson :";
                affichage_emplacement(colonne,affichage_ecran,1);
                affichage_ecran = message_type(stock);
                interraction = saisie_char(colonne,affichage_ecran);
                if (strstr(interraction,"-1") != NULL){
                    etape = -1;
                }
                else{
                etape = 1;
                }

                break;

            case 1:
                affichage_ecran = "Veuillez choisir l'id de la boisson :";
                affichage_emplacement(colonne,affichage_ecran,1);
                affichage_ecran = message_id(interraction,stock);
                id = saisie_int(colonne,affichage_ecran);
                if (id == -1){
                    etape = 0;
                }
                else{
                etape = 2;
                }
                break;

            case 2:

                affichage_ecran = "Veuillez choisir la quantite : ";
                affichage_emplacement(colonne,affichage_ecran,1);
                affichage_ecran = message_quantite(stock,id);
                quantite = saisie_int(colonne,affichage_ecran);
                if (quantite == -1){
                    etape = 1;
                }
                else if( stock[id-1].quantite >= quantite){
                etape = 3;
                }
                break;
            
            default:
                return "Il y a eu un probleme avec la saisie de votre commande";
                break;
            }
                printf("\n\n");   
                affichage_ligne(colonne);

        }

        if(etape == 3){
        return commande(stock,id,quantite,0);
        }
        else{
            return "Retour au menu";
        }
}

char* message_type(boisson_struc *stock){

    int taille = taille_stock();
    char* chaine = calloc(8 * taille, sizeof(char)); //
    for (int i = 0; i< taille; i++){

        if( strstr(chaine,stock[i].type) == NULL && stock[i].quantite > 0 ){

                    strcat(chaine,stock[i].type);
                    strcat(chaine, " ");     
        }

    }
    strcat(chaine, " : ");

    return chaine;
}

char* message_id(char* type,boisson_struc *stock){

    int taille = taille_stock();
    char* chaine = calloc(40 * taille, sizeof(char)); 
    
    char* conversion = calloc(24 +40 * taille, sizeof(char)); //

    for (int i = 0; i< taille; i++){

        if( strcmp(stock[i].type,type) == 0 && stock[i].quantite > 0){

            strcat(chaine, stock[i].nom);

            strcat(chaine, " : ");

            sprintf(conversion,"%d",stock[i].id);
            strcat(chaine, conversion);

            strcat(chaine, " : ");
        }
    }
    return chaine;

}

char* message_quantite(boisson_struc *stock,int id){

    int taille = taille_stock();
    char* chaine = calloc(40 * taille, sizeof(char));

    char* conversion = calloc(10 * taille, sizeof(char)); //
    id --;

    strcat(chaine,"Quantite disponible de ");

    strcat(chaine, stock[id].nom);

    strcat(chaine," ");

    sprintf(conversion,"%d",stock[id].quantite);
    strcat(chaine, conversion);
    strcat(chaine, " : ");

    return chaine;

}

void affichage_ligne(int colonne){

        for( int i = 0; i < colonne; i++ ){
      printf("=");
    }

}

void affichage(boisson_struc *stock){

    CONSOLE_SCREEN_BUFFER_INFO csbi; // windows
    int colonne;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); // windows
    colonne = csbi.srWindow.Right - csbi.srWindow.Left + 1; // windows
    int terminal = 0;
    int etape = 0;
    char* affichage_ecran;
    char* affichage_debut = calloc(colonne, sizeof(char));


    do{

    system("cls"); // windows

    affichage_ligne(colonne);
    printf("\n\n");   

        if(etape != 0){
    affichage_emplacement(colonne,affichage_debut,1);
    }

    printf("\n\n");   
        
    switch (terminal){

    case 0: // début

        affichage_ecran = "Veuillez entrer l'interface a afficher :";
        affichage_emplacement(colonne,affichage_ecran,1);
        terminal = saisie_int(colonne,"Barman = 1, Client = 2 : ");

        break;
    case 1: // Barman
        /* code */
        break;
    case 2: // Client

        etape = 0;
        scanf("%d",&etape);
        affichage_debut = saisie_commande(colonne,stock);
        etape = 1;


        /* code */
        break;
    default: // fin
        break;
    }

    }while(terminal != -1);


    printf("\n\n");

    affichage_ligne(colonne);
    
}