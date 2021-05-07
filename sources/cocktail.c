#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../sources/cocktail.h"
#include "../sources/menu.h"

int taille_stock(){
    FILE* lecture = NULL;
    lecture = fopen("../data/data.txt", "r");
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
    lecture = fopen("../data/data.txt", "r");
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
        ecriture = fopen("../data/commande.txt", "a");
        fprintf(ecriture,"%s %.2f %d %d\n",stock[boisson_id].nom ,stock[boisson_id].prix * quantite ,quantite ,id_client);
        fclose(ecriture);
        return "Votre commande a bien ete enregistre";
    }
    else{
        return "Votre commande n'a pas ete enregistre, quantite insuffisante";
    }
}

char**tableau_type(boisson_struc *stock){

    int taille = taille_stock();
    char** chaine;
    chaine = calloc(taille, sizeof(int*));
    for(int i = 0 ; i< taille; i++){
    chaine[i] = calloc(30, sizeof(char));
    }

    for (int i = 0; i< taille; i++){

        if(stock[i].quantite > 0 ){

            strcpy(chaine[i], stock[i].type);
        }

    }

    return chaine;
}

char * message_type(boisson_struc *stock){

    char** tableau = tableau_type(stock);
    int taille = taille_stock();
    char* chaine = calloc(8 * taille, sizeof(char));

    for(int i =0; i<taille;i++){

           if( strstr(chaine,tableau[i]) == NULL){

                    strcat(chaine,tableau[i]);
                    strcat(chaine, " ");     
        }

    }
    strcat(chaine, " : ");
    return chaine;
}



int* tableau_id(char* type,boisson_struc *stock){

    int taille = taille_stock();
    int* tableau_id = calloc(taille, sizeof(int));
    int i = 0;
    for(int i = 0; i<taille; i++){


        if(strcmp(stock[i].type,type) == 0){
                tableau_id[i] = stock[i].id;
            }
    }
    return tableau_id;

}


char* message_id(char* type,boisson_struc *stock){

    int* tableau = tableau_id(type,stock);
    int taille = taille_stock();
    char* chaine = calloc(40 * taille, sizeof(char));
    char* conversion = calloc(8 * taille, sizeof(char));
    int i = 0;
    for (int i = 0; i< taille; i++){
        printf("%d",tableau[i]);
    }
    for (int i = 0; i< taille; i++){
        
        if(tableau[i] != 0 ){

                strcat(chaine, stock[tableau[i]-1].nom);
                strcat(chaine, " : ");
                sprintf(conversion,"%d",tableau[i]);
                strcat(chaine, conversion);
                strcat(chaine, " : ");
        }
    }
    return chaine;

}

char* message_quantite(boisson_struc *stock,int id){

    int taille = taille_stock();
    char* chaine = calloc(40 * taille, sizeof(char));

    char* conversion = calloc(8 * taille, sizeof(char));
    id --;

    strcat(chaine,"Quantite disponible de ");

    strcat(chaine, stock[id].nom);

    strcat(chaine," ");

    sprintf(conversion,"%d",stock[id].quantite);
    strcat(chaine, conversion);
    strcat(chaine, " : ");

    return chaine;

}

long conversion_long(char* chaine){

    char* fin_pointeur;

    return strtol(chaine, &fin_pointeur,0);
}