/*! \file cocktail.c
* \author Rabus Jules
* \version 1
* \date 19/04/2021 Debut du travail en groupe
* \date 22/05/2021 Creation des commentaires doxygen.

* \brief Le fichier cocktail.c contient l'ensemble des fonctions pour la gestion des boissons et des cocktails.
*/



/*! \mainpage Presentation
* \section introduction Introduction
*
* Programme du bar a cocktail
*
* \section fonctions_procedures Fonctions et procédures
*
*/


/*! \file menu.h
* \section Presentation
* \brief Le fichier menu.h regroupe tous les prototypes de fonctions necessaires a l'affichage des menus et aux interactions utilisateur.
*/
/*! \file cocktail.h
* \section Presentation
* \brief Le fichier cocktail.h regroupe tous les prototypes de fonctions et les structures necessaires a la gestion des boissons et des cocktails.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cocktail.h"
#include "menu.h"


/*! \fn int taille_stock(char* data)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction taille_stock
*
*  \param data type d'element a lire
*
*  \return Retourne le nombre d'elements du type souhaite.
*
*  \remarks Cette fonction permet de calculer la taille du stock.
*/
int taille_stock(char* data){

    FILE* lecture = NULL;                                   // On initialise la lecture

    if( strcmp(data,"data_boisson") == 0){                  // On choisit quelle data on veut lire en fonction du parametre data
        lecture = fopen("../data/data_boisson.txt", "r");   // On ouvre le ficher
    }
    else if(strcmp(data,"data_cocktail") == 0){
        lecture = fopen("../data/data_cocktail.txt", "r");
    }
    else if(strcmp(data,"data_commande") == 0){
        lecture = fopen("../data/commande.txt", "r");
    }

    if (lecture != NULL)                    // On verifie que la fichier de lecture n'est pas nulle
    {
        int taille;                         // On initialise l'entier taille
        fscanf(lecture,"%d", &taille);      // On lit la valeur de l'entier present au debut du fichier lecture
        fclose(lecture);
        return taille;
    }
    else{                                   // La lecture est nulle, on ferme et quitte le programme
    fclose(lecture);
    exit(-1);
    }  

}

/*! \fn boisson_struc *remplirstock_boisson()
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction remplirstock_boisson
*
*  \return Retourne un poiteur vers un tableau de structure de boissons.
*
*  \remarks Cette fonction permet de remplir le stock de boissons pour l'initialisation du programme.
*/
boisson_struc *remplirstock_boisson(){

    FILE* lecture = NULL;                                   // On initialise la lecture
    lecture = fopen("../data/data_boisson.txt", "r");       // On ouvre le fichier des data de boisson
    if (lecture != NULL)
    {
        int taille;                                         // On initialise la taille
        int cocktail_id = 1;                                // On initialise cocktail id qui va servir plus tard a definir l'id de la boisson, on commence a 1 puis on l'incrementera
        fscanf(lecture,"%d", &taille);                      // On scanf la taille, pour apres allouer la taille, et pour passer la ligne
        boisson_struc boisson;                                                                //on initialise une structure boisson, qui va servir a recuperer les donnees
        boisson_struc *tab_boisson = malloc(taille * sizeof(boisson_struc) );                 // On alloue un tableau de structure de boisson, la taille est la lecture de la taille du fichier

    for( int i = 0; i<taille;i++ ){                                                                                                                                                             // On fait une boucle pour recuperer toutes les lignes
             fscanf(lecture, "%s%*c %f%*c %d%*c %d%*c %d%*c %s%*c %s",boisson.nom,&boisson.prix,&boisson.degre,&boisson.contenance,&boisson.quantite,boisson.type,boisson.categorie);           // On recupere les informations de la ligne qu'on stock dans la structure boisson

            if (strcmp(boisson.categorie,"boisson") == 0){                      // On verifie si il s'agit d'une boisson ou d'un cocktail
                boisson.id = i+1 ;                                              // Si c'est une boisson on lui attribue son idee via la boucle for +1
            }
            else{
                boisson.id = cocktail_id ;                              // On attribue la valeur de l'id pour les cocktails qui correspond a la ligne dans le fichier des cocktails
                cocktail_id ++;                                         // On incremente la valeur afin de se decaler d'une ligne pour la prochaine lecture d'un cocktail
            }
            tab_boisson[i] = boisson;                                   // On mets la structure de lecture des boissons dans le tableau de structure
        }

        fclose(lecture);                                                // On ferme le fichier de lecture car on n'a plus rien a lire
        return tab_boisson;                                             // On retourne le tableau de structure contenant le stock des boissons
    }
    else{
        fclose(lecture);                                                // La lecture est nulle, on ferme et quitte le programme
        exit(-1);
    }  
        
}

/*! \fn boisson_struc *remplirstock_cocktail()
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction remplirstock_cocktail
*
*  \return Retourne un poiteur vers un tableau de structure de cocktails.
*
*  \remarks Cette fonction permet de remplir le stock de cocktails pour l'initialisation du programme.
*/
cocktail_struc *remplirstock_cocktail(){

    FILE* lecture = NULL;                                                   // On initialise la lecture
    lecture = fopen("../data/data_cocktail.txt", "r");                       // On ouvre le fichier des data
    if (lecture != NULL)
    {
        int taille;
        fscanf(lecture,"%d", &taille);
        cocktail_struc cocktail;                                                                    // On initialise un structure cocktail, qui va servir a recuperer les donnees des cocktails
        cocktail_struc *tab_cocktail = malloc(taille * sizeof(cocktail_struc) );                    // On alloue un tableau de structure de cocktail

        for( int i = 0; i<taille; i++ ){
            fscanf(lecture, "%s%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d%*c %d",cocktail.nom,&cocktail.id_boisson[0],&cocktail.id_boisson[1],&cocktail.id_boisson[2],&cocktail.id_boisson[3],&cocktail.id_boisson[4],&cocktail.id_boisson[5],&cocktail.contenance[0],&cocktail.contenance[1],&cocktail.contenance[2],&cocktail.contenance[3],&cocktail.contenance[4],&cocktail.contenance[5]);         // On recupere les informations de la ligne qu'on stock dans la structure cocktail
            tab_cocktail[i] = cocktail;                      // On mets la structure de lecture des cocktails dans le tableau de structure
        }

        fclose(lecture);
        return tab_cocktail;    //On retourne le tableau de structure contenant la liste des cocktails
    }
    else{
        fclose(lecture);
        exit(-1);
    }  
        
}

/*! \fn void commande(boisson_struc* stock,cocktail_struc* cocktail_liste,panier_struc panier,int id_personne)
*  \author Rabus Jules
*  \version 1
*  \date 21/05/2021 Commentaires doxygen
*
*  \brief Procedure commande
*
*  \param stock Tableau contenant le stock
*  \param cocktail_liste Tableau de cocktails
*  \param panier Affiche le panier
*  \param id_personne 0 : barman, 1 : client
*
*  \remarks Cette fonction permet de passer une commande et de la stocker dans l'historique.
*/
void commande(boisson_struc* stock,cocktail_struc* cocktail_liste,panier_struc panier,int id_personne){
                                                                                                            // 1ere partie on baisse la quantite disponible si besoin                                                                                                        
    for( int i = 0; i<panier.taille; i++){                                                                  // On parcourt tout le panier, la taille du panier est stocker dans sa structure panier.taille
        if( id_personne != 0){                                                                              // On baisse uniquement si la personne est un client , 1 = client , 0 Serveur
            if( strcmp(panier.stock[i].categorie,"cocktail") == 0){                                         // Si c'est un cocktail on parcours la structure panier.stock pour reduire la quantite des ingredients du cocktail
                for( int j = 0 ; j<6;j++){
                    if (cocktail_liste[ panier.stock[i].id-1].id_boisson[ j ] != -1){                                                               // On baisse uniquement si l'id est bien defini, -1 = pas defini, le reste oui
                        stock[ cocktail_liste[ panier.stock[i].id-1].id_boisson[ j ] ].quantite -= panier.stock[i].quantite;                        // Si l'id correspond a une boisson on baisse la quantite du nombre de cocktail commande
                    }
                }
            }
            else{
                stock[panier.stock[i].id-1].quantite -= panier.stock[i].quantite;                           // Si c'est une boisson on baisse la quantite du nombre de boisson commande
            }
        }
    }
                                                                                    // 2eme partie on lit les commandes deja enregistres
    int taille = taille_stock("data_commande");                                     // On utilise la fonction taille_stock afin de connaitre la taille avant de lire le ficher dans cette fonction
    boisson_struc *boisson = malloc(taille * sizeof(boisson_struc));                // On alloue un tableau de structure de boisson, la taille est la lecture de la taille du fichier
    int *id_personne_lecture = malloc(taille * sizeof(int));                        // On alloue un tableau d'entier pour stocker la lecture de l'id de la personne

    FILE* lecture = NULL;
    lecture = fopen("../data/commande.txt", "r");
    if (lecture != NULL){
        fscanf(lecture,"%d",&taille);

        for( int i = 0; i<taille; i++ ){
            fscanf(lecture,"%s%*c %f%*c %d%*c %d%*c %d%*c %s",boisson[i].nom ,&boisson[i].prix,&boisson[i].quantite,&id_personne_lecture[i],&boisson[i].id,boisson[i].categorie);    // On recupere les informations de la ligne qu'on stock dans la structure boisson et dans le tableau d'entier          
        }
    }
    else{
        fclose(lecture);
        exit(-1);
    }  


    FILE* ecriture = NULL;                                          // 3eme partie on ecrit les informations qu'on a lu, et on rajoute la commande

    ecriture = fopen("../data/commande.txt", "w");
    if (ecriture != NULL){
            fprintf(ecriture,"%d\n",taille+1);

            for( int i = 0; i<taille; i++){
                fprintf(ecriture,"%s %.2f %d %d %d %s\n",boisson[i].nom ,boisson[i].prix,boisson[i].quantite,id_personne_lecture[i],boisson[i].id,boisson[i].categorie);        // On ecrit ce qui etait dans le tableau de structure de boisson
            }
            free(boisson);
            free(id_personne_lecture);
            for( int i = 0; i<panier.taille; i++){
                fprintf(ecriture,"%s %.2f %d %d %d %s\n",panier.stock[i].nom ,panier.stock[i].prix,panier.stock[i].quantite,id_personne,panier.stock[i].id,panier.stock[i].categorie);          // On ecrit la commande qui est stocke dans le panier
            }
            fclose(ecriture);
        }
    else{
        fclose(ecriture);
        exit(-1);
    }
}

/*! \fn char**tableau_type(boisson_struc *stock)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction tableau_type
*
*  \param stock Tableau contenant le stock
*
*  \return Retourne le panier
*
*  \remarks Cette fonction permet de generer un tableau de chaine de caractere, dans lequel on va mettre chaque type qu'on a trouve dans le stock
*/
char**tableau_type(boisson_struc *stock){

    int taille = taille_stock("data_boisson");      // On recupere la taille
    char** chaine;                                  // On fait un tableau de chaine
    chaine = calloc(taille, sizeof(int*));          // On alloue le tableau

    for(int i = 0 ; i< taille; i++){
         chaine[i] = calloc(30, sizeof(char));      // On alloue les chaines dans le tableau
    }

    for (int i = 0; i< taille; i++){

        if(stock[i].quantite > 0 ){                 // On verifie si la quantite disponible de la boisson est superieur a 0 

            strcat(chaine[i], stock[i].type);       // Si la taille est superieur a 0, on concatene le type de la boisson dans le tableau de chaine
        }

    }

    return chaine;
}

/*! \fn char * message_type(boisson_struc *stock)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction message_type
*
*  \param stock Tableau contenant le stock
*
*  \return Retourne 
*
*  \remarks Cette fonction permet de retourner une chaine contenant tout les types disponible dans le stock, sans double
*/
char * message_type(boisson_struc *stock){

    char** tableau = tableau_type(stock);       // On recupere le tableau de caractere de la fonction tableau_type
    int taille = taille_stock("data_boisson");
    char* chaine = calloc(30 * taille, sizeof(char));    // On alloue une chaine de 8 caracteres avec un calloc pour eviter des problemes lors de la concatenation, et stocker le message

    for(int i =0; i<taille;i++){

           if( strstr(chaine,tableau[i]) == 0){         // On regarde si on a deja le type qui est dans le tableau de caractere a deja ete mis dans la chaine du message

                strcat(chaine,tableau[i]);          // Si elle n'a pas ete mise on l'ajoute, en concatenant
                strcat(chaine, " ");                // On ajoute un espace
        }

    }
    strcat(chaine, " : ");          // On ajoute un deux points a la fin du message
    free(tableau);                  // On libere la memoire du tableau de type
    return chaine;                  // On retourne la chaine contenant le message avec les types
}

/*! \fn int verification_type(boisson_struc *stock,char* type)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction verification_type
*
*  \param stock Tableau contenant le stock
*  \param type nom du type a verifier
*
*  \return Retourne 1 pour un bon type, 0 sinon.
*
*  \remarks Cette fonction sert a verifier si le type existe
*/
int verification_type(boisson_struc *stock,char* type){

    char** tableau = tableau_type(stock);                // On recupere le tableau de caractere de la fonction tableau_type
    int taille = taille_stock("data_boisson");

    for(int i =0; i<taille; i++){

        if (strcmp(type,tableau[i]) == 0){              // On compare le type du tableau , et le type rentrer en parametre
            free(tableau);                              // Si on trouve le type dans le tableau on libere le
            return 1;                                   // Et on retourne 1 car on a trouve le type
        }
    }
    free(tableau);  // On libere le tableau 
    return 0;       // On retourne qu'on a pas trouve type
}

/*! \fn int verification_id(boisson_struc *stock,char* type,long id)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction verification_id
*
*  \param stock Tableau contenant le stock
*  \param type nom de l'id a verifier
*
*  \return Retourne 1 pour un bon id, 0 sinon.
*
*  \remarks Cette fonction sert a verifier si l'id existe, et si l'id existe et si le type de l'id correspond
*/
int verification_id(boisson_struc *stock,char* type,long id){

    int taille = taille_stock("data_boisson");

    for(int i = 0; i<taille; i++){
        if ( ( i+1 == id && strcmp(stock[i].type,type) == 0) || ( i+1 == id && strcmp(type,"tout") == 0) ){         // On regarde si l'id correspond existe et si le type correspond bien, ou si l'id est bien present dans le tableau . Le ou permet de globaliser la fonction avec un parametre
            return 1;                                                                                               // Si on trouve une correspondance on retourne 1 car l'id existe et le type correspond, ou juste l'id correspond
        }
    }
    return 0;       // On retourne 0 car on n'a pas trouve une correspondance
}

/*! \fn int* tableau_id(boisson_struc *stock,char* type)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction tableau_id
*
*  \param stock Tableau contenant le stock
*  \param type nom du type
*
*  \return Retourne un pointeur vers un tableau d'entiers.
*
*  \remarks Cette fonction cree un tableau qui regroupe les id des elements dans le stock correspondant au type ou un tableau qui retroupe tout les id des elements dans le stock
*/
int* tableau_id(boisson_struc *stock,char* type){

    int taille = taille_stock("data_boisson");
    int* tableau_id = calloc(taille, sizeof(int));              // On alloue un tableau d'entier
    for(int i = 0; i<taille; i++){

        if(strcmp(type,"tout") == 0){                           // On compare si le type est egale a tout
            tableau_id[i] = i+1;                                // Si oui on ajoute l'id au tableau d'entier

        }
        else if(strcmp(stock[i].type,type) == 0){               // On compare si le type est dans le stock
            tableau_id[i] = i+1;                                // Si oui on ajoute l'id au tableau d'entier
            }
    }
    return tableau_id;                  // On retourne le tableau d'entier

}

/*! \fn char* message_id(boisson_struc *stock,char* type)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction message_id
*
*  \param stock Tableau contenant le stock
*  \param type nom du type
*
*  \return Retourne un pointeur vers une chaine de caracteres.
*
*  \remarks Cette fonction permet de faire un message structure pour afficher l'id des boissons
*/
char* message_id(boisson_struc *stock,char* type){

    int* tableau = tableau_id(stock,type);                  // On recupere le tableau d'entier de tableau_id
    int taille = taille_stock("data_boisson");
    char* chaine = calloc(40 * taille, sizeof(char));        // On alloue une chaine de 40 caracteres avec un calloc pour eviter des problemes lors de la concatenation, et stocker le message
    char* conversion = calloc(10, sizeof(char));             // On alloue une chaine de 10 caracteres avec un calloc pour eviter des problemes lors de la concatenation, et avoir une chaine pour convertir les entiers en chaine
    for (int i = 0; i< taille; i++){
        
        if(tableau[i] != 0 ){                                   // On verifie que l'entier dans le tableau n'est pas egal a 0

                strcat(chaine, stock[tableau[i]-1].nom);        // Si il n'est pas egal a 0, on concatene le nom de la boisson en la recuperant via le tableau de structure des boissons et le tableau d'entier(le rang du tableau)
                strcat(chaine, " : ");                          
                sprintf(conversion,"%d",tableau[i]);            // On converti l'entier(id) en chaine
                strcat(chaine, conversion);                     // On concatene la chaine et la chaine avec la conversion
                strcat(chaine, " : ");
        }
    }
    free(conversion);                   // On libere la chaine conversion
    return chaine;                      // On retourne la chaine avec le message avec les id

}

/*! \fn char* message_quantite(boisson_struc *stock,cocktail_struc *cocktail_liste,int id)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction message_quantite
*
*  \param stock Tableau contenant le stock
*  \param cocktail_liste Tableau de cocktails
*  \param id z
*
*  \return Retourne un pointeur vers une chaine de caracteres.
*
*  \remarks Cette fonction permet de faire un message structure pour afficher la quantite disponible de l'id
*/
char* message_quantite(boisson_struc *stock,cocktail_struc *cocktail_liste,int id){

    int taille = taille_stock("data_boisson");
    char* chaine = calloc(40 * taille, sizeof(char));      // On alloue une chaine de 40 caracteres avec un calloc pour eviter des problemes lors du concatenage, et stocker le message 

    char* conversion = calloc(10, sizeof(char));           // On alloue une chaine de 10 caracteres avec un calloc pour eviter des problemes lors du concatenage, et avoir une chaine pour convertir les entiers en chaine
    id --;                                                 // On descend l'id de 1 , car le tableau de structure de boisson commence a 0 , et l'id que rentre l'utilisateur est decale de 1

    int quantite = 0;

    if( strcmp(stock[id].categorie,"cocktail") == 0){                               //On regarde dans le tableau de structure de boisson , au rang qui correspond a l'id
        quantite = quantite_cocktail(stock,cocktail_liste[stock[id].id-1]);         // Si oui on calcule la quantite disponible via la fonction quantite_cocktail
    }
    else{
        quantite = stock[id].quantite;                                              // Sinon c'est une boisson, donc la quantite est disponible dans le tableau de structure
    }

    strcat(chaine,"Quantite disponible de ");       // On concatene le tout

    strcat(chaine, stock[id].nom);

    strcat(chaine," ");

    sprintf(conversion,"%d",quantite);
    strcat(chaine, conversion);
    strcat(chaine, " : ");
    free(conversion);
    return chaine;          

}

/*! \fn int verification_nom(boisson_struc *stock,char* nom)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction verification_nom 
*
*  \param stock Tableau contenant le stock
*  \param nom nom de la boissson
*
*  \return Retourne 1 : si le nom correspond, 0 : sinon.
*
*  \remarks Cette fonction permet de rechercher une boisson d'une certaine categorie (si precise) dans le stock.
*/
int verification_nom(boisson_struc *stock,char* nom){

    int taille = taille_stock("data_boisson");

    for(int i = 0; i<taille; i++){

        if(strcmp(stock[i].nom,nom) == 0){              // On cherche dans le tableau de structure de boisson si il y a le nom qui correspond
            return i;                                 // On retourne le rang de le tableau si on trouve un nom qui correspond
        }
    }
    return -1;      // On retourne -1 si on trouve aucune correspondance
}

/*! \fn char* recherche_boisson(boisson_struc *stock,char* recherche,char *categorie)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction recherche_boisson 
*
*  \param stock Tableau contenant le stock
*  \param recherche boisson ou cocktail rechreche
*  \param categorie categorie de la boisson (facultatif)
*
*  \return Retourne un pointeur vers une chaine de caracteres qui est le nom de la boisson recherchee.
*
*  \remarks Cette fonction permet de rechercher une boisson d'une certaine categorie (si precise) dans le stock.
*/
char* recherche_boisson(boisson_struc *stock,char* recherche,char *categorie){

    int taille = taille_stock("data_boisson");
    char* chaine = calloc(40 * taille, sizeof(char));
    char* conversion = calloc(10, sizeof(char));
    int vide = 0;                                   // On initialise vide un entier, pour savoir si on trouve une une boisson via la recherche

    for (int i = 0; i< taille; i++){
        if ( (strstr(stock[i].nom,recherche) && strcmp(stock[i].categorie,categorie) == 0) || (strstr(stock[i].nom,recherche) && strcmp(categorie,"tout") == 0)  ){             // On cherche une sous-chaine de recherche dans le nom des boissons dans le tableau de structure, et on verifie la categorie si voulu,
                strcat(chaine, stock[i].nom);
                strcat(chaine, " : ");
                sprintf(conversion,"%d",i+1);
                strcat(chaine, conversion);
                strcat(chaine, " ");
                vide++;
        }
    }

    if(vide == 0){
        return "Il n'existe pas de boisson qui correspond a votre recherche";    // On retourne le message disant que la recherche n'a rien donnee
    }
    return chaine;          // On retourne le message avec les id qui correspondent au nom des boissons trouve
}

/*! \fn char* affichage_boisson(boisson_struc *stock)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction affichage_boisson 
*
*  \param stock Tableau contenant le stock
*
*  \return Retourne un pointeur vers une chaine de caracteres qui est le nom de la boisson.
*
*  \remarks Cette fonction permet d'afficher le nom d'une boisson avec un certain format.
*/
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

/*! \fn long conversion_long(char* chaine)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction conversion_long 
*
*  \param chaine chaine a convertir
*
*  \return Retourne un long.
*
*  \remarks Cette fonction sert a convertir une chaine en type long.
*/
long conversion_long(char* chaine){

    char* fin_pointeur;

    return strtol(chaine, &fin_pointeur,0);     // On utilise la strlol pour convertir une chaine en long
}

/*! \fn int verification_cocktail(boisson_struc *stock,int id)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction verification_cocktail 
*
*  \param stock Tableau contenant le stock
*  \param id id dans le stock
*
*  \return Retourne 1 : si l'element est un cocktail, 0 : l'element n'est pas un cocktail.
*
*  \remarks Cette fonction sert a verifier si l'element est un cocktail ou non.
*/
int verification_cocktail(boisson_struc *stock,int id){

    if( strcmp(stock[id].categorie,"cocktail") == 0 ){      // On cherche si l'id correspond bien a un cocktail
        return 1;                                           // Si c'est un cocktail on retoure oui
    }
    return 0;               // Sinon on retourne non
}

/*! \fn int contenance_cocktail(cocktail_struc cocktail)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction contenance_cocktail 
*
*  \param cocktail cocktail
*
*  \return Retourne la contenance du cocktail.
*
*  \remarks Cette fonction donne la contenance d'un cocktail en cL.
*/
int contenance_cocktail(cocktail_struc cocktail){

    int contenance = 0;

    for(int i = 0; i< 6;i++){
        if ( cocktail.id_boisson[i] != -1){             // On va jusqu'a 6, qui correspond au nombre de composant maximale que peux avoir un cocktail, (taille max defini dans la structure)
           contenance += cocktail.contenance[i];        // On additionne la contenance de tout les composants de la boisson
        }
    }
    return contenance;
}

/*! \fn int quantite_cocktail(boisson_struc *stock,cocktail_struc cocktail)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction quantite_cocktail 
*
*  \param stock Tableau contenant le stock
*  \param cocktail cocktail
*
*  \return Retourne la quantite de cocktails.
*
*  \remarks Cette fonction permet de calculer la quantite d'un cocktail.
*/
int quantite_cocktail(boisson_struc *stock,cocktail_struc cocktail){

    int quantite = stock[cocktail.id_boisson[0]].quantite;      // On prend la quantite disponible du 1er composant du cocktail, on va la chercher dans le tableau de structure, le rang est le 1er id contenu dans la structure cocktail

    for(int i = 1; i< 6;i++){
        if ( cocktail.id_boisson[i] != -1 && stock[cocktail.id_boisson[i]].quantite < quantite){        // On regarde si la quantite du composant suivant est inferieur a celle precedente
           quantite = stock[cocktail.id_boisson[i]].quantite;                                           // Si oui la nouvelle valeur de quantite est celle du tableau de structure
        }

    }
    return quantite;    
}

/*! \fn char* type_cocktail(boisson_struc *stock,cocktail_struc cocktail)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction type_cocktail 
*
*  \param stock Tableau contenant le stock
*  \param cocktail cocktail
*
*  \return Retourne un pointeur vers une chaine de caracteres.
*
*  \remarks Cette fonction donne le type d'un cocktail.
*/
char* type_cocktail(boisson_struc *stock,cocktail_struc cocktail){

    char* type = calloc(20, sizeof(char));
    strcpy(type,"sans-alcool");                     // On mets la chaine "sans alcool" dans la chaine type

    for(int i = 0; i< 6;i++){
        if ( cocktail.id_boisson[i] != -1 && strcmp(stock[cocktail.id_boisson[i]].type,"alcool") == 0){         // On regarde si le composant existe, et si le composant a le type alcool
           strcpy(type,"alcool");                                                                               // Si oui le type du cocktail est alcool
        }
    }
    return type;            // On retourne le type
}

/*! \fn int degre_cocktail(boisson_struc *stock,cocktail_struc cocktail)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction degre_cocktail 
*
*  \param stock Tableau contenant le stock
*  \param cocktail cocktail
*
*  \return Retourne le degre du cocktail.
*
*  \remarks Cette fonction permet de calculer le degre d'un cocktail.
*/
int degre_cocktail(boisson_struc *stock,cocktail_struc cocktail){

    int quantite_degre = 0;
    int degre;

    for(int i = 0; i< 6;i++){
        if ( cocktail.id_boisson[i] != -1 && strcmp("alcool",type_cocktail(stock,cocktail)) == 0 && strcmp(stock[cocktail.id_boisson[i]].type,"alcool") == 0 ){     // On regarde si le composant existe, et si c'est un cocktail avec alcool
           quantite_degre += cocktail.contenance[i] * stock[cocktail.id_boisson[i]].degre;                                                                          // Si oui on additionne les degres d'alcool
        }
        else if( cocktail.id_boisson[i] != -1 && strcmp("alcool",type_cocktail(stock,cocktail)) != 0 && strcmp(stock[cocktail.id_boisson[i]].type,"alcool") != 0){          // On regarde si le composant existe, et si c'est un cocktail avec sans-alcool
            quantite_degre += cocktail.contenance[i] * stock[cocktail.id_boisson[i]].degre;                                                                                 // Si oui on additionne les degres de sucre
        }
    }

    degre = quantite_degre / contenance_cocktail(cocktail);                 // On calcule le degre final

    return degre;
}

/*! \fn int disponibilite_cocktail(boisson_struc *stock,cocktail_struc *cocktail_liste,int id_cocktail)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction disponibilite_cocktail 
*
*  \param stock Tableau contenant le stock
*  \param cocktail Tableau de cocktails
*  \param id_cocktail id du cocktail
*
*  \return Retourne le nombre de cocktails disponibles.
*
*  \remarks Cette fonction permet de calculer la disponibilite d'un cocktail.
*/
int disponibilite_cocktail(boisson_struc *stock,cocktail_struc *cocktail_liste,int id_cocktail){
                                                                                            // La difference avec quantite_cocktail est que ici on ne prend pas les meme parametres
    int quantite = stock[cocktail_liste[stock[id_cocktail].id].id_boisson[0]].quantite;   // On prend la quantite disponible du 1er composant du cocktail, on va la chercher dans le tableau de structure, le rang est le 1er id contenu dans la structure cocktail

    for(int i = 1; i< 6;i++){
        if ( stock[cocktail_liste[stock[id_cocktail].id].id_boisson[i]].quantite < quantite ){       // On regarde si la quantite du composant suivant est inferieur a celle precedente
            quantite = stock[cocktail_liste[stock[id_cocktail].id].id_boisson[i]].quantite;          // Si oui la nouvelle valeur de quantite est celle du tableau de structure
        }
    }
    return quantite;
}

/*! \fn float prix_cocktail(boisson_struc *stock,cocktail_struc cocktail)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction prix_cocktail 
*
*  \param stock Tableau contenant le stock
*  \param cocktail cocktail
*
*  \return Retourne le prix du cocktail.
*
*  \remarks Cette fonction permet de calculer le prix d'un cocktail.
*/
float prix_cocktail(boisson_struc *stock,cocktail_struc cocktail){

    float prix = 0;

    for(int i = 0; i< 6;i++){
        if ( cocktail.id_boisson[i] != -1){
            prix += cocktail.contenance[i] * (stock[cocktail.id_boisson[i]].prix / stock[cocktail.id_boisson[i]].contenance) ;      // on calcule prix de chaque composant et on l'adittionne au precedant
        }
    }

    prix = prix * 1.10; // On augmente le prix de 10% car c'est un cocktail

    return prix;
}

/*! \fn float prix_boisson(int degre, int contenance)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction prix_boisson 
*
*  \param degre degre de sucre ou d'alcool
*  \param contenance contenance de la boisson en cL
*
*  \return Retourne le prix de la boisson.
*
*  \remarks Cette fonction permet de calculer le prix d'une boisson.
*/
float prix_boisson(int degre, int contenance){

    float prix = contenance * degre * 0.01;     // On calcule le prix de la boisson

    return prix;
}

/*! \fn boisson_struc *ajouterBoisson(boisson_struc *stock)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction ajouterBoisson 
*
*  \param stock Tableau contenant le stock
*  \param arborescence Arborescence 
*
*  \return Retourne un pointeur vers un tableau de structure de boissons.
*
*  \remarks Cette fonction permet d'ajouter une boisson dans le stock.
*/
boisson_struc *ajouterBoisson(boisson_struc *stock,char *arborescence){


    boisson_struc boisson = saisie_boisson(stock,arborescence);      // On fait saisir une boisson a l'utilisateur

    if ( boisson.id != -2){      // On ne fait rien car -2 correspond au defaut de la saisie de boisson

            FILE* ecriture = NULL;
            int taille = taille_stock("data_boisson");

            ecriture = fopen("../data/data_boisson.txt", "w");
            if (ecriture != NULL){

                    if(boisson.id == -1){
                        fprintf(ecriture,"%d\n",taille+1);                 // On augmente la car boisson.id -1 correspond a l'ajout d'une boisson
                    }
                    else{
                        fprintf(ecriture,"%d\n",taille);                    // On n'augmente pas car different de boisson.id -1
                    }

                    for(int i = 0 ;i<taille; i++){
                        if(boisson.id == i){                 // On regarde si le rang correspond au rang de la boisson qu'on veut augmenter la quantite disponible
                            fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",stock[i].nom ,stock[i].prix,stock[i].degre,stock[i].contenance,stock[i].quantite+boisson.quantite,stock[i].type,stock[i].categorie);   // On augmente la quantite disponible de la boisson     
                        }
                        else{
                            fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",stock[i].nom ,stock[i].prix ,stock[i].degre,stock[i].contenance,stock[i].quantite,stock[i].type,stock[i].categorie);     // On ecrit dans le ficher les anciennes donnees
                        }
                    }
                    if(boisson.id == -1){
                        fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",boisson.nom ,boisson.prix,boisson.degre,boisson.contenance,boisson.quantite,boisson.type,"boisson");     // On ecrit la nouvelle boisson dans le ficher data des boissons
                    }
                    fclose(ecriture);
                }
            else{
                fclose(ecriture);
                exit(-1);
            }  

        free(stock);                                    // On libere la memoire du tableau de structure des boissons
        stock = remplirstock_boisson();                 // On remplis le tableau de structure des boissons avec la nouvelle boisson
    }
    return stock;           // On retourne le tableau de structure des boissons pour qu'il soit mis a jour car on l'a free
    
}

/*! \fn bdd ajouterCocktail(boisson_struc *stock,cocktail_struc *cocktail_liste)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction ajouterCocktail 
*
*  \param stock Tableau contenant le stock
*  \param cocktail_liste Tableau de cocktails
*  \param arborescence Arborescence 
*
*  \return Retourne un pointeur vers une base de donnees qui contient boissons et cocktail.
*
*  \remarks Cette fonction permet d'ajouter un cocktail dans le stock.
*/
bdd ajouterCocktail(boisson_struc *stock,cocktail_struc *cocktail_liste,char *arborescence){

    cocktail_struc cocktail = saisie_cocktail(stock,cocktail_liste,arborescence);            // On fait saisir un cocktail a l'utilisateur            
    bdd base_de_donne ;                                                         // On initialise la structure base de donnee

    if( strcmp(cocktail.nom,"") != 0){          // On ne fait rien car cocktail.nom "" correspond au defaut de la saisie de cocktail

    FILE* ecriture = NULL;
    int taille = taille_stock("data_cocktail");
    ecriture = fopen("../data/data_cocktail.txt", "w");

        if (ecriture != NULL){
                fprintf(ecriture,"%d\n",taille+1);

                for(int i = 0 ;i<taille; i++){
                fprintf(ecriture,"%s %d %d %d %d %d %d %d %d %d %d %d %d \n",cocktail_liste[i].nom,cocktail_liste[i].id_boisson[0],cocktail_liste[i].id_boisson[1],cocktail_liste[i].id_boisson[2],cocktail_liste[i].id_boisson[3],cocktail_liste[i].id_boisson[4],cocktail_liste[i].id_boisson[5],cocktail_liste[i].contenance[0],cocktail_liste[i].contenance[1],cocktail_liste[i].contenance[2],cocktail_liste[i].contenance[3],cocktail_liste[i].contenance[4],cocktail_liste[i].contenance[5]); // On recrit les cocktails dans le ficher des data des cocktail
                }

                 fprintf(ecriture,"%s %d %d %d %d %d %d %d %d %d %d %d %d \n",cocktail.nom,cocktail.id_boisson[0],cocktail.id_boisson[1],cocktail.id_boisson[2],cocktail.id_boisson[3],cocktail.id_boisson[4],cocktail.id_boisson[5],cocktail.contenance[0],cocktail.contenance[1],cocktail.contenance[2],cocktail.contenance[3],cocktail.contenance[4],cocktail.contenance[5]); // On ecrit les informations du nouveau cocktail dans le ficher des data des cocktail
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
                    fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",stock[i].nom ,stock[i].prix ,stock[i].degre,stock[i].contenance,stock[i].quantite,stock[i].type,stock[i].categorie); // On recrit les boissons dans le ficher des data des boissons
                }

                fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",cocktail.nom ,prix_cocktail(stock,cocktail) ,degre_cocktail(stock,cocktail),contenance_cocktail(cocktail),0,type_cocktail(stock,cocktail),"cocktail");  // On ecrit le nouveau cocktail dans le ficher des data des boissons
                fclose(ecriture);
            }
        else{
            fclose(ecriture);
            exit(-1);
        }
    free(stock);                                                           // On libere la memoire du tableau de structure des boissons
    stock = remplirstock_boisson();                                        // On remplis le tableau de structure des boissons avec le nouveau cocktail
    free(cocktail_liste);                                                  // On libere la memoire du tableau de structure des cocktails
    cocktail_liste = remplirstock_cocktail();                              // On remplis le tableau de structure des cocktails avec le nouveau cocktail

    base_de_donne.stock = stock;                                           // On mets les deux tableaux de structure dans la structure base de bdd
    base_de_donne.cocktail_liste = cocktail_liste;
    }

    return base_de_donne;                                                  // On retourne la base de donnee pour qu'ils soient mis a jour car on les free
}

/*! \fn panier_struc ajouterPanier(panier_struc panier,boisson_struc commande)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction ajouterPanier
*
*  \param panier panier de la commande
*  \param commande element commande
*
*  \return Retourne le panier.
*
*  \remarks Cette fonction permet d'ajouter l'element commande au panier.
*/
panier_struc ajouterPanier(panier_struc panier,boisson_struc commande){

	panier.stock[panier.taille] = commande;     // On ajoute la structure commande, au tableau de structure de boisson de la structure panier
    panier.taille ++;                           // On incremente panier.taille çar on a ajoute une commande

	return panier;  

}

/*! \fn char quitter(boisson_struc *stock)
*  \author Rabus Jules
*  \version 1
*  \date 22/05/2021 Commentaires doxygen
*
*  \brief Fonction quitter
*
*  \param stock Tableau contenant le stock
*
*  \return Retourne 'q' pour quitter.
*
*  \remarks Cette fonction permet de sauvegarder des donnees.
*/
char quitter(boisson_struc *stock){
                                                    // On sauvegarde le tableau de structure des boissons
    FILE* ecriture = NULL;
    int taille = taille_stock("data_boisson");
    ecriture = fopen("../data/data_boisson.txt", "w");
    if (ecriture != NULL){
        fprintf(ecriture,"%d\n",taille);

            for(int i = 0 ;i<taille; i++){
                fprintf(ecriture,"%s %.2f %d %d %d %s %s\n",stock[i].nom ,stock[i].prix ,stock[i].degre,stock[i].contenance,stock[i].quantite,stock[i].type,stock[i].categorie); // on ecrit le tableau de structure dans le fichier data des boissons afin de sauvegarder le stock
            }
            fclose(ecriture);
        }
    else{
        fclose(ecriture);
        exit(-1);
    }
    return 'q';
}
