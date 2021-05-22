#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cocktail.h"
#include "menu.h"

int taille_stock(char* data){

    FILE* lecture = NULL;                                   // On initialise la lecture

    if( strcmp(data,"data_boisson") == 0){                  // On choisit quelle data on veut lire en fonction du paramètre data
        lecture = fopen("../data/data_boisson.txt", "r");   // On ouvre le ficher
    }
    else if(strcmp(data,"data_cocktail") == 0){
        lecture = fopen("../data/data_cocktail.txt", "r");
    }
    else if(strcmp(data,"data_commande") == 0){
        lecture = fopen("../data/commande.txt", "r");
    }

    if (lecture != NULL)                    // On vérifie que la fichier de lecture n'est pas nulle
    {
        int taille;                         // On initialise l'entier taille
        fscanf(lecture,"%d", &taille);      // On lit la valeur de l'entier présent au début du fichier lecture
        fclose(lecture);
        return taille;
    }
    else{                                   // La lecture est nulle, on ferme et quitte le programme
    fclose(lecture);
    exit(-1);
    }  

}

boisson_struc *remplirstock_boisson(){

    FILE* lecture = NULL;                                   // On initialise la lecture
    lecture = fopen("../data/data_boisson.txt", "r");       // on ouvre le fichier des data
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
            fscanf(lecture, "%s%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d",cocktail.nom,&cocktail.id_boisson[0],&cocktail.id_boisson[1],&cocktail.id_boisson[2],&cocktail.id_boisson[3],&cocktail.id_boisson[4],&cocktail.id_boisson[5],&cocktail.contenance[0],&cocktail.contenance[1],&cocktail.contenance[2],&cocktail.contenance[3],&cocktail.contenance[4],&cocktail.contenance[5]);
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

int commande(boisson_struc* stock,cocktail_struc* cocktail_liste,panier_struc panier,int id_personne){

    for( int i = 0; i<panier.taille; i++){
        if( id_personne != 0){
            if( strcmp(panier.stock[i].categorie,"cocktail") == 0){
                for( int j = 0 ; j<6;j++){
                    if (cocktail_liste[ panier.stock[i].id-1].id_boisson[ j ] != -1){
                        stock[ cocktail_liste[ panier.stock[i].id-1].id_boisson[ j ] ].quantite -= panier.stock[i].quantite;
                    }
                }
            }
            else{
                stock[panier.stock[i].id-1].quantite -= panier.stock[i].quantite;
            }
        }
    }

    int taille = taille_stock("data_commande");
    boisson_struc *boisson = malloc(taille * sizeof(boisson_struc));
    int *id_personne_lecture = malloc(taille * sizeof(int));

    FILE* lecture = NULL;
    lecture = fopen("../data/commande.txt", "r");
    if (lecture != NULL){
        fscanf(lecture,"%d",&taille);

        for( int i = 0; i<taille; i++ ){
            fscanf(lecture,"%s%*c %f%*c %d%*c %d%*c %d%*c %s",boisson[i].nom ,&boisson[i].prix,&boisson[i].quantite,&id_personne_lecture[i],&boisson[i].id,boisson[i].categorie);
        }
    }
    else{
        fclose(lecture);
        exit(-1);
    }  


    FILE* ecriture = NULL;

    ecriture = fopen("../data/commande.txt", "w");
    if (ecriture != NULL){
            fprintf(ecriture,"%d\n",taille+1);

            for( int i = 0; i<taille; i++){
                fprintf(ecriture,"%s %.2f %d %d %d %s\n",boisson[i].nom ,boisson[i].prix,boisson[i].quantite,id_personne_lecture[i],boisson[i].id,boisson[i].categorie);
            }
            free(boisson);
            free(id_personne_lecture);
            for( int i = 0; i<panier.taille; i++){
                fprintf(ecriture,"%s %.2f %d %d %d %s\n",panier.stock[i].nom ,panier.stock[i].prix,panier.stock[i].quantite,id_personne,panier.stock[i].id,panier.stock[i].categorie);
            }
            fclose(ecriture);
            return 1;
        }
    else{
        fclose(ecriture);
        exit(-1);
    }
    return 0;
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
    free(tableau);
    return chaine;
}

int verification_type(boisson_struc *stock,char* type){

    char** tableau = tableau_type(stock);
    int taille = taille_stock("data_boisson");

    for(int i =0; i<taille; i++){

        if (strcmp(type,tableau[i]) == 0){
            free(tableau);
            return 1;
        }
    }
    free(tableau);
    return 0;
}

int verification_id(boisson_struc *stock,char* type,long id){

    int taille = taille_stock("data_boisson");

    for(int i = 0; i<taille; i++){
        if ( ( i+1 == id && strcmp(stock[i].type,type) == 0) || ( i+1 == id && strcmp(type,"tout") == 0) ){
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
    free(conversion);
    return chaine;

}

char* message_quantite(boisson_struc *stock,cocktail_struc *cocktail_liste,int id){

    int taille = taille_stock("data_boisson");
    char* chaine = calloc(40 * taille, sizeof(char));

    char* conversion = calloc(10, sizeof(char));
    id --;

    int quantite = 0;

    if( strcmp(stock[id].categorie,"cocktail") == 0){
        quantite = quantite_cocktail(stock,cocktail_liste[stock[id].id-1]);
    }
    else{
        quantite = stock[id].quantite;
    }

    strcat(chaine,"Quantite disponible de ");

    strcat(chaine, stock[id].nom);

    strcat(chaine," ");

    sprintf(conversion,"%d",quantite);
    strcat(chaine, conversion);
    strcat(chaine, " : ");
    free(conversion);
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

char* recherche_boisson(boisson_struc *stock,char* recherche,char *categorie){

    int taille = taille_stock("data_boisson");
    char* chaine = calloc(40 * taille, sizeof(char));
    char* conversion = calloc(10, sizeof(char));
    int vide = 0;

    for (int i = 0; i< taille; i++){
        if ( (strstr(stock[i].nom,recherche) && strcmp(stock[i].categorie,categorie) == 0) || (strstr(stock[i].nom,recherche) && strcmp(categorie,"tout") == 0)  ){
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

int verification_cocktail(boisson_struc *stock,int id){

    if( strcmp(stock[id].categorie,"cocktail") == 0 ){
           return 1;

    }
    return 0;
}

int contenance_cocktail(cocktail_struc cocktail){

    int contenance = 0;

    for(int i = 0; i< 6;i++){
        if ( cocktail.id_boisson[i] != -1){
           contenance += cocktail.contenance[i];
        }

    }
    return contenance;
}

int quantite_cocktail(boisson_struc *stock,cocktail_struc cocktail){

    int quantite = stock[cocktail.id_boisson[0]].quantite;

    for(int i = 1; i< 6;i++){
        if ( cocktail.id_boisson[i] != -1 && stock[cocktail.id_boisson[i]].quantite < quantite){
           quantite = stock[cocktail.id_boisson[i]].quantite;
        }

    }
    return quantite;
}

char* type_cocktail(boisson_struc *stock,cocktail_struc cocktail){

    char* type = calloc(20, sizeof(char));
    strcpy(type,"sans-alcool");

    for(int i = 0; i< 6;i++){
        if ( cocktail.id_boisson[i] != -1 && strcmp(stock[cocktail.id_boisson[i]].type,"alcool") == 0){
           strcpy(type,"alcool");
        }
    }

    return type;
}

int degre_cocktail(boisson_struc *stock,cocktail_struc cocktail){

    int quantite_degre = 0;
    int degre;

    for(int i = 0; i< 6;i++){
        if ( cocktail.id_boisson[i] != -1 && strcmp("alcool",type_cocktail(stock,cocktail)) == 0 && strcmp(stock[cocktail.id_boisson[i]].type,"alcool") == 0 ){
           quantite_degre += cocktail.contenance[i] * stock[cocktail.id_boisson[i]].degre;
        }
        else if( cocktail.id_boisson[i] != -1 && strcmp("alcool",type_cocktail(stock,cocktail)) != 0 && strcmp(stock[cocktail.id_boisson[i]].type,"alcool") != 0){
            quantite_degre += cocktail.contenance[i] * stock[cocktail.id_boisson[i]].degre;
        }
    }

    degre = quantite_degre / contenance_cocktail(cocktail);

    return degre;
}

int disponibilite_cocktail(boisson_struc *stock,cocktail_struc *cocktail_liste,int id_cocktail){

    int quantite = stock[cocktail_liste[stock[id_cocktail].id].id_boisson[0]].quantite;

    for(int i = 1; i< 6;i++){
        if ( stock[cocktail_liste[stock[id_cocktail].id].id_boisson[i]].quantite < quantite ){
            quantite = stock[cocktail_liste[stock[id_cocktail].id].id_boisson[i]].quantite;
        }
    }
    return quantite;
}

float prix_cocktail(boisson_struc *stock,cocktail_struc cocktail){

    float prix = 1;

    for(int i = 0; i< 6;i++){
        if ( cocktail.id_boisson[i] != -1){
            prix += cocktail.contenance[i] * (stock[cocktail.id_boisson[i]].prix / stock[cocktail.id_boisson[i]].contenance) ;
        }
    }

    prix = prix * 1.10;

    return prix;
}


float prix_boisson(int degre, int contenance){

    float prix = contenance * degre * 0.01;

    return prix;
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
                            fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",stock[i].nom ,stock[i].prix,stock[i].degre,stock[i].contenance,stock[i].quantite+boisson.quantite,stock[i].type,stock[i].categorie);
                        }
                        else{
                            fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",stock[i].nom ,stock[i].prix ,stock[i].degre,stock[i].contenance,stock[i].quantite,stock[i].type,stock[i].categorie);
                        }
                    }
                    if(boisson.id == -1){
                        fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",boisson.nom ,boisson.prix,boisson.degre,boisson.contenance,boisson.quantite,boisson.type,"boisson");
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

bdd ajouterCocktail(boisson_struc *stock,cocktail_struc *cocktail_liste){

    cocktail_struc cocktail = saisie_cocktail(stock,cocktail_liste);
    bdd base_de_donne ;


    if( strcmp(cocktail.nom,"") != 0){

    FILE* ecriture = NULL;
    int taille = taille_stock("data_cocktail");
    ecriture = fopen("../data/data_cocktail.txt", "w");

        if (ecriture != NULL){
                fprintf(ecriture,"%d\n",taille+1);

                for(int i = 0 ;i<taille; i++){
                fprintf(ecriture,"%s %d %d %d %d %d %d %d %d %d %d %d %d \n",cocktail_liste[i].nom,cocktail_liste[i].id_boisson[0],cocktail_liste[i].id_boisson[1],cocktail_liste[i].id_boisson[2],cocktail_liste[i].id_boisson[3],cocktail_liste[i].id_boisson[4],cocktail_liste[i].id_boisson[5],cocktail_liste[i].contenance[0],cocktail_liste[i].contenance[1],cocktail_liste[i].contenance[2],cocktail_liste[i].contenance[3],cocktail_liste[i].contenance[4],cocktail_liste[i].contenance[5]);
                }

                 fprintf(ecriture,"%s %d %d %d %d %d %d %d %d %d %d %d %d \n",cocktail.nom,cocktail.id_boisson[0],cocktail.id_boisson[1],cocktail.id_boisson[2],cocktail.id_boisson[3],cocktail.id_boisson[4],cocktail.id_boisson[5],cocktail.contenance[0],cocktail.contenance[1],cocktail.contenance[2],cocktail.contenance[3],cocktail.contenance[4],cocktail.contenance[5]);
                 fclose(ecriture);
            }
        else{
            fclose(ecriture);
            exit(-1);
        }

    taille = taille_stock("data_boisson");
    ecriture = fopen("../data/data_boisson.txt", "w");
        if (ecriture != NULL){
                fprintf(ecriture,"%d\n",taille+1);

                for(int i = 0 ;i<taille; i++){
                    fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",stock[i].nom ,stock[i].prix ,stock[i].degre,stock[i].contenance,stock[i].quantite,stock[i].type,stock[i].categorie);
                }

                fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",cocktail.nom ,prix_cocktail(stock,cocktail) ,degre_cocktail(stock,cocktail),contenance_cocktail(cocktail),0,type_cocktail(stock,cocktail),"cocktail");
                fclose(ecriture);
            }
        else{
            fclose(ecriture);
            exit(-1);
        }
    free(stock);
    stock = remplirstock_boisson();
    free(cocktail_liste);
    cocktail_liste = remplirstock_cocktail();

    base_de_donne.stock = stock; 
    base_de_donne.cocktail_liste = cocktail_liste;
    }

    return base_de_donne;
}

panier_struc ajouterPanier(panier_struc panier,boisson_struc commande){

	panier.stock[panier.taille] = commande;
    panier.taille ++;

	return panier;

}

char quitter(boisson_struc *stock){

    FILE* ecriture = NULL;
    int taille = taille_stock("data_boisson");
    ecriture = fopen("../data/data_boisson.txt", "w");
    if (ecriture != NULL){
        fprintf(ecriture,"%d\n",taille);

            for(int i = 0 ;i<taille; i++){
                fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",stock[i].nom ,stock[i].prix ,stock[i].degre,stock[i].contenance,,stock[i].quantite,stock[i].type,stock[i].categorie);
            }
            fclose(ecriture);
        }
    else{
        fclose(ecriture);
        exit(-1);
    }
    return 'q';
}
