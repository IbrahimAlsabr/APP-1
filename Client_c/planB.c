#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "decodageCesar.h"
#define MAXMSG MAXREP

bool EST_MAJSCULE(char lettre){
    return(lettre >= 'A' && lettre <= 'Z');
}

bool EST_MINUSCULE(char lettre){
    return(lettre >= 'a' && lettre <= 'z');
}

char DecodageLetrMaj(char lettreLue, int cle){

    if (lettreLue - cle < 'A')
    {
        return('Z' - (cle - (lettreLue -'A')) + 1);
	}

    return lettreLue - cle ;
}

char DecodageLetrMinusc(char lettreLue, int cle){

    if (lettreLue - cle < 'a')
    {
        return('z' - (cle - (lettreLue -'a')) + 1);
	}

    return lettreLue - cle ;
}

char* decodageCesar(char SRC[], int cle) {

    for (unsigned long i = 0; i < strlen(SRC); i++)
    {
        if (EST_MINUSCULE(SRC[i]))
        {
            SRC[i] = DecodageLetrMinusc(SRC[i], cle);
        }

        else if (EST_MAJSCULE(SRC[i]))
        {
            SRC[i] = DecodageLetrMaj(SRC[i], cle);
        }

        else
        {
            SRC[i] = SRC[i];
        }
    }
    return (char*) SRC;
}


int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    //char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 11917197 \"ALSABR\"", reponse);
    envoyer_recevoir("load planB", reponse);
    envoyer_recevoir("start", reponse);
    envoyer_recevoir("42", reponse);
    envoyer_recevoir("aide", reponse);

    char str[MAXREP] = "hasta la revolucion";
    
    int cle = reponse[0] - 'C';
    envoyer_recevoir(decodageCesar(str,cle), reponse);

    strcpy(str,decodageCesar(reponse,cle));
    envoyer_recevoir(decodageCesar(str,cle), reponse);

    //lire_clavier(message);   // message tapé au clavier
   // envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
    
}
