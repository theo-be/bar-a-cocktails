#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cocktail.h"
#include "menu.h"

int taille_stock(char* data){

    FILE* lecture = NULL;

    if( strcmp(data,"data_boisson") == 0){
        lecture = fopen("../data/data_boisson.txt", "r");
    }
    else if(strcmp(data,"data_cocktail") == 0){
        lecture = fopen("../data/data_cocktail.txt", "r");
    }
    else{
        exit(-1);
    }

    if (lecture != NULL)
    {
        int taille;
        fscanf(lecture,"%d", &taille);
        fclose(lecture);
        return taille;
    }
    else{
    fclose(lecture);
    exit(-1);
    }  

}

boisson_struc *remplirstock_boisson(){

    FILE* lecture = NULL;
    lecture = fopen("../data/data_boisson.txt", "r");
    if (lecture != NULL)
    {
        int taille;
        int cocktail_id = 1;
        fscanf(lecture,"%d", &taille);
        boisson_struc boisson;
        boisson_struc *tab_boisson = malloc(taille * sizeof(boisson_struc) );

        for( int i = 0; i<taille;i++ ){
             fscanf(lecture, "%s%*c %f%*c %d%*c %d%*c %d%*c %s%*c %s",boisson.nom,&boisson.prix,&boisson.degre,&boisson.contenance,&boisson.quantite,boisson.type,boisson.categorie);

            if (strcmp(boisson.categorie,"boisson") == 0){
                boisson.id = i+1 ;
            }
            else{
                boisson.id = cocktail_id ;
                cocktail_id ++;
            }

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

cocktail_struc *remplirstock_cocktail(){

    FILE* lecture = NULL;
    lecture = fopen("../data/data_cocktail.txt", "r");
    if (lecture != NULL)
    {
        int taille;
        fscanf(lecture,"%d", &taille);
        cocktail_struc cocktail;
        cocktail_struc *tab_cocktail = malloc(taille * sizeof(cocktail_struc) );

        for( int i = 0; i<taille; i++ ){
            fscanf(lecture, "%s%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c",cocktail.nom,&cocktail.id_boisson[0],&cocktail.id_boisson[1],&cocktail.id_boisson[2],&cocktail.id_boisson[3],&cocktail.id_boisson[4],&cocktail.id_boisson[5],&cocktail.contenance);
            tab_cocktail[i] = cocktail;
        }

        fclose(lecture);
        return tab_cocktail;
    }
    else{
        fclose(lecture);
        exit(-1);
    }  
        
}

char commande(boisson_struc *stock,long boisson_id,long quantite,int id_personne){

        FILE* ecriture = NULL;
        ecriture = fopen("../data/commande.txt", "a");
        if (ecriture != NULL){

                boisson_id -= 1;
                stock[boisson_id].quantite -= quantite;

                fprintf(ecriture,"%s %.2f %ld %d %s \n",stock[boisson_id].nom ,stock[boisson_id].prix * quantite ,quantite ,id_personne,stock[boisson_id].categorie);
                fclose(ecriture);
                return 'v';
            }
        else{
            fclose(ecriture);
            exit(-1);
        }
}

char**tableau_type(boisson_struc *stock){

    int taille = taille_stock("data_boisson");
    char** chaine;
    chaine = calloc(taille, sizeof(int*));

    for(int i = 0 ; i< taille; i++){
         chaine[i] = calloc(30, sizeof(char));
    }

    for (int i = 0; i< taille; i++){

        if(stock[i].quantite > 0 ){

            strcat(chaine[i], stock[i].type);
        }

    }

    return chaine;
}

char * message_type(boisson_struc *stock){

    char** tableau = tableau_type(stock);
    int taille = taille_stock("data_boisson");
    char* chaine = calloc(8 * taille, sizeof(char));

    for(int i =0; i<taille;i++){

           if( strstr(chaine,tableau[i]) == 0){

                strcat(chaine,tableau[i]);
                strcat(chaine, " ");     
        }

    }
    strcat(chaine, " : ");
    return chaine;
}

int verification_type(boisson_struc *stock,char* type){

    char** tableau = tableau_type(stock);
    int taille = taille_stock("data_boisson");

    for(int i =0; i<taille; i++){

        if (strcmp(type,tableau[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int verification_id(boisson_struc *stock,char* type,long id){

    int taille = taille_stock("data_boisson");

    for(int i = 0; i<taille; i++){
        if ( (stock[i].id == id && strcmp(stock[i].type,type) == 0) || (stock[i].id == id && strcmp(type,"tout") == 0) ){
            return 1;
        }
    }
    return 0;
}

int* tableau_id(boisson_struc *stock,char* type){

    int taille = taille_stock("data_boisson");
    int* tableau_id = calloc(taille, sizeof(int));
    for(int i = 0; i<taille; i++){

        if(strcmp(type,"tout") == 0){
            tableau_id[i] = i+1;

        }
        else if(strcmp(stock[i].type,type) == 0){
            tableau_id[i] = i+1;
            }
    }
    return tableau_id;

}

char* message_id(boisson_struc *stock,char* type){

    int* tableau = tableau_id(stock,type);
    int taille = taille_stock("data_boisson");
    char* chaine = calloc(40 * taille, sizeof(char));
    char* conversion = calloc(10, sizeof(char));
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

    int taille = taille_stock("data_boisson");
    char* chaine = calloc(40 * taille, sizeof(char));

    char* conversion = calloc(10, sizeof(char));
    id --;

    strcat(chaine,"Quantite disponible de ");

    strcat(chaine, stock[id].nom);

    strcat(chaine," ");

    sprintf(conversion,"%d",stock[id].quantite);
    strcat(chaine, conversion);
    strcat(chaine, " : ");

    return chaine;

}

int verification_nom(boisson_struc *stock,char* nom){

    int taille = taille_stock("data_boisson");

    for(int i = 0; i<taille; i++){

        if(strcmp(stock[i].nom,nom) == 0){
            return i+1;
        }
    }
    return -1;
}

char* recherche_boisson(boisson_struc *stock,char* recherche){

    int taille = taille_stock("data_boisson");
    char* chaine = calloc(40 * taille, sizeof(char));
    char* conversion = calloc(10, sizeof(char));
    int vide = 0;

    for (int i = 0; i< taille; i++){
        if ( strstr(stock[i].nom,recherche)){
                strcat(chaine, stock[i].nom);
                strcat(chaine, " : ");
                sprintf(conversion,"%d",i+1);
                strcat(chaine, conversion);
                strcat(chaine, " ");
                vide++;
        }
    }

    if(vide == 0){
        return "Il n'existe pas de boisson qui correspond à votre recherche";
    }
    return chaine;

}

char* affichage_boisson(boisson_struc *stock){

    int taille = taille_stock("data_boisson");
    char* chaine = calloc(40 * taille, sizeof(char));

    for (int i = 0; i< taille; i++){

        strcat(chaine,stock[i].nom);
        strcat(chaine," ");
    }
    strcat(chaine,"\n");
    return chaine;

}

long conversion_long(char* chaine){

    char* fin_pointeur;

    return strtol(chaine, &fin_pointeur,0);
}

boisson_struc *ajouterBoisson(boisson_struc *stock){


    boisson_struc boisson = saisie_boisson(stock);

    if ( boisson.id != -2){

            FILE* ecriture = NULL;
            int taille = taille_stock("data_boisson");

            ecriture = fopen("../data/data_boisson.txt", "w");
            if (ecriture != NULL){

                    if(boisson.id == -1){
                        fprintf(ecriture,"%d\n",taille+1);                 
                    }
                    else{
                        fprintf(ecriture,"%d\n",taille);
                    }

                    for(int i = 0 ;i<taille; i++){
                        if(boisson.id == i){
                            fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",stock[i].nom , ((float) (stock[i].degre * stock[i].contenance)) ,stock[i].degre,stock[i].quantite+boisson.quantite,stock[i].contenance,stock[i].type,stock[i].categorie);
                        }
                        else{
                            fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",stock[i].nom , ((float) (stock[i].degre * stock[i].contenance) * 0.01) ,stock[i].degre,stock[i].quantite,stock[i].contenance,stock[i].type,stock[i].categorie);
                        }
                    }
                    if(boisson.id == -1){
                        fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",boisson.nom , ((float) (boisson.degre*boisson.contenance)),boisson.degre,boisson.quantite,boisson.contenance,boisson.type,"boisson");
                    }
                    fclose(ecriture);
                }
            else{
                fclose(ecriture);
                exit(-1);
            }  

        free(stock);
        stock = remplirstock_boisson();
    }
    return stock;
    
}

cocktail_struc *ajouterCocktail(boisson_struc *stock,cocktail_struc *cocktail_liste){

    cocktail_struc cocktail = saisie_cocktail(stock,cocktail_liste);

    if( strcmp(cocktail.nom,"") != 0){

    FILE* ecriture = NULL;
    int taille = taille_stock("data_cocktail");
    ecriture = fopen("../data/data_cocktail.txt", "w");

        if (ecriture != NULL){

                fprintf(ecriture,"%d\n",taille+1);

                for(int i = 0 ;i<taille; i++){
                fprintf(ecriture,"%s %d %d %d %d %d %d \n",cocktail_liste[i].nom,cocktail_liste[i].id_boisson[0],cocktail_liste[i].id_boisson[1],cocktail_liste[i].id_boisson[2],cocktail_liste[i].id_boisson[3],cocktail_liste[i].id_boisson[4],cocktail_liste[i].id_boisson[5]);
                }

                 fprintf(ecriture,"%s %d %d %d %d %d %d \n",cocktail.nom,cocktail.id_boisson[0],cocktail.id_boisson[1],cocktail.id_boisson[2],cocktail.id_boisson[3],cocktail.id_boisson[4],cocktail.id_boisson[5]);
                 fclose(ecriture);
            }
        else{
            fclose(ecriture);
            exit(-1);
        }

    ecriture = fopen("../data/data_boisson.txt", "w");

        if (ecriture != NULL){

                fprintf(ecriture,"%d\n",taille+1);

                for(int i = 0 ;i<taille; i++){
                    fprintf(ecriture,"%s %.2f %d %d %s %s\n",stock[i].nom ,stock[i].prix ,stock[i].degre,stock[i].quantite,stock[i].type,stock[i].categorie);
                }

                int degre_cocktail = stock[cocktail.id_boisson[0]].degre;
                char* type_cocktail = calloc( 30, sizeof(char));
                strcat(type_cocktail,"sans-alcool");
                for(int i = 0 ; i<taille; i++){
                    if (stock[cocktail.id_boisson[i]].degre < degre_cocktail){
                        degre_cocktail = stock[cocktail.id_boisson[i]].degre;
                    }
                    if( strcmp(stock[cocktail.id_boisson[i]].type,"alcool") == 0){
                        strcpy(type_cocktail,"alcool");
                    }
                }

                fprintf(ecriture,"%s %.2f %d %d %s %s\n",cocktail.nom ,cocktail.prix ,degre_cocktail,0,type_cocktail,"cocktail");
            }
        else{
            fclose(ecriture);
            exit(-1);
        }

    free(cocktail_liste);
    cocktail_liste = remplirstock_cocktail();
    }

    return cocktail_liste;
    
}