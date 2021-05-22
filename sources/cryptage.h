/*! \file cryptage.h
* \section Presentation
* \brief Le fichier cryptage.h contient les fonctions necessaires pour le cryptage et la verifictation des du mot de passe.
*/


#ifndef H_cryptage
#define H_cryptage

/*!
*  \brief Prototype de la fonction vigenere
*/
char* vigenere(char* mes);

/*!
*  \brief Prototype de la fonction verification_mdp
*/
int verification_mdp(char *saisie);


#endif
