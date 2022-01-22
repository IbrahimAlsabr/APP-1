#include "client.h"
#include "crypteMove.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#define MAXMSG MAXREP

/* 
 * Supprimer premiere lettre de chaine de caractere 
 */ 
void SupprimerPremierLettre(char str[]){

    for (unsigned long i = 0; str[i] != '\0'; i++)
    {
        str[i] = str[i+1];
    }
}

/* 
 * Decaler un ensemble des lettres al fin de chaine de caractere  
 */ 
void decaleLettres (char str[], int nLetDecaler){

    for (int i = 0; i < nLetDecaler; i++) 
    {   
        char premLettre = str[0];
        SupprimerPremierLettre(str);
        str[strlen(str)] = premLettre;  
    }
}

/* 
 * Fonction principal de 'CrypteMove' 
 */ 
char* codageCrypteMove(char TXT[]){

    static char txtDecodeg[TAILLEMESSAGE];
    unsigned long mod, pas = 0;

    while (TXT[0] != '\0')
    {
        mod = TXT[0] % 8 ;
        txtDecodeg[pas] = TXT[0];
        SupprimerPremierLettre(TXT);

        /* Vérifier si le modulo de la lettre est plus grand que le nombre 
           de la séquence des symbole dans le TXT */ 
        if (mod < strlen(TXT))
        {
            decaleLettres(TXT,mod);
        }   pas++;
    }       
        return (char*)txtDecodeg;
}

int main() {

    char reponse[MAXREP]; // pour stocker la réponse du serveur
    //char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    //Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 11917197 \"ALSABR\"", reponse);
    envoyer_recevoir("load crypteMove", reponse);
    envoyer_recevoir("aide", reponse);

    char str[MAXREP] = {0};
    strcpy(str,codageCrypteMove(reponse));

    envoyer_recevoir("start", reponse);

    //lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(str, reponse); // on envoie message, et on reçoit la réponse du serveur
    
    printf ("Réponse du serveur: %s", reponse);
    printf ("Fin de la connection au serveur\n");
    return 0;
    
}
