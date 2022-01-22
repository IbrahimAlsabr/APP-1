#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXMSG MAXREP

void supprimerDerniereLettre(char str[]){
    str[strlen(str)-1] = '\0';
}

void ajoutLettreAuDebut(char str[], char lettre ){
    for (int k = strlen(str)+1 ; k > 0 ; k--)
    {   
        str[k] = str[k-1];
    }   
        str[0] = lettre;
}

void decaleLettres(char str[], int nLetDecaler){
    for (int i = 0; i < nLetDecaler; i++)
    {
        char derLettre = str[strlen(str)-1];
        supprimerDerniereLettre(str);
        ajoutLettreAuDebut(str, derLettre);
    }
}

char* BayOfPigs(char ENC[]){

    static char TXT[TAILLEMESSAGE]; 
    while (ENC[0] != '\0')
    {
        /* Prendre la dernière lettre de ENC */
        char derLettre = ENC[strlen(ENC)-1];   

        /* Calculer le modulo avec code ascii de la dernière lettre dans ENC */
        unsigned long nLetDecaler = derLettre % 8; 

        /* Vérifier si le nombre des lettres à decaler est inférieur que le nombre 
            des caracteres dans le TXT */ 
        if (nLetDecaler < strlen(TXT))
        {
            decaleLettres(TXT, nLetDecaler);
        }

        /* Ajouter la dernier lettre (dans ENC) au debut de TXT */
        ajoutLettreAuDebut(TXT, derLettre);

        /* Supprimer la dernier lettre du ENC */
        supprimerDerniereLettre(ENC);
    }

    return (char*) TXT;
}


int main() {

    //char str[] = "Pee ct mosusriae.ttg";
    //char str[] = "CeeAi,l cher";

    //printf("\n\n%s\n\n",decrypteMove(str));


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
    envoyer_recevoir("load OneMillion", reponse);
    //envoyer_recevoir("aide", reponse);
    //envoyer_recevoir("start", reponse);
    
    
    char str[MAXREP] = {0};
    strcpy(str,BayOfPigs(reponse));
    printf("%s\n",BayOfPigs(reponse));
    
    // printf("\n\n\n");
    // printf("%s",(char*)str);
    //envoyer_recevoir("Par otuam eriet", reponse);


    // lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(str, reponse); // on envoie message, et on reçoit la réponse du serveur
    


    // printf ("Réponse du serveur: %s", reponse);
    // printf ("Fin de la connection au serveur\n");
    return 0;
    
}


