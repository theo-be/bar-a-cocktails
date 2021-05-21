#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* vigenere(char* saisie){

    char* cleVigenere = "barman";
    int valeurCryptage;
    int i = 0;
    int longCle = strlen(cleVigenere)-1;

    while (saisie[i] != '\0' && strlen(saisie) > i)
    {
        if((int)saisie[i] < 48 || ((int)saisie[i] > 57 && (int)saisie[i] < 65) || ((int)saisie[i] > 90 && (int)saisie[i] < 97) || ((int)saisie[i] > 122 && (int)saisie[i] <= 126))
        {
            i++;
        }else{
            if( ((int)saisie[i] > 64 && (int)saisie[i] < 91) && ((int)cleVigenere[i % longCle] > 64 && (int)cleVigenere[i % longCle] < 91)){
                valeurCryptage = ((int)saisie[i] - 65 + ((int)cleVigenere[i % longCle] - 65)) % 26 + 65;

            }else if( ((int)saisie[i] > 96 && (int)saisie[i] < 123) && ((int)cleVigenere[i % longCle] > 96 && (int)cleVigenere[i % longCle] < 123)){
                valeurCryptage = ((int)saisie[i] - 97 + ((int)cleVigenere[i % longCle] - 97)) % 26 + 97;

            }else if( ((int)saisie[i] > 47 && (int)saisie[i] < 58) ){
                valeurCryptage = (((int)saisie[i] - 48) + ((int)cleVigenere[i % longCle] - 48)) % 10 + 48;

            }else{
                valeurCryptage = ((int)saisie[i] + ((int)cleVigenere[i % longCle]));
            }
            saisie[i] = (char) valeurCryptage;
            i++;
        }
        
    }
    return saisie;
    
}

int verification_mdp(char *saisie){

    char* mot_de_passe = malloc( 20 * sizeof(char));

    FILE* lecture = NULL;
    lecture = fopen("../data/mot_de_passe.txt", "r");
    if (lecture != NULL){
        fscanf(lecture, "%s",mot_de_passe);
        fclose(lecture);
    }
    else{
        fclose(lecture);
        exit(-1);
    }  

    if (strcmp(mot_de_passe,vigenere(saisie)) == 0){
        free(mot_de_passe);
        return 1;
    }
    else{
        free(mot_de_passe);
        return 0;

    }

}