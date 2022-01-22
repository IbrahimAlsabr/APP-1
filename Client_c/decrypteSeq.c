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


int lettreDansSeq(char str[], char lettre){
    for (unsigned long i = 0; i < strlen(str); i++)
    {
        if (str[i] == lettre)
        {
            return 1;
        }
    } return 0;
}

void ajoutLettreAlaFin(char str[], char lettre){
    str[strlen(str)] = lettre;
}

void indiceLettres(int *D, int *C, char str[], char lettre){

    if (str[0] == lettre)
    {
        *D = strlen(str) - 1;;
        *C = 0; 
    } else {
        for (unsigned long i = 0; i < strlen(str); i++)
        {
            if (str[i] == lettre)
            {
                *D = i-1;
                *C = i;
                break;
                i = strlen(str);
            }
        }  
    }
}

void deplacerLettreVersFin(char str[], unsigned long indice){
    char lettre = str[indice];
    for (unsigned long i = indice; i < strlen(str); i++)
    {
        str[i] = str[i+1];
    }   str[strlen(str)] = lettre;
}

char* crypteSeq(char str[]){
    int C = 0,D = 0;
    char seq[MAXREP];
    static char messageCrypte[MAXREP];

    for (unsigned long i = 0; i < strlen(str); i++)
    {
        if(lettreDansSeq(seq, str[i]) == 0)
        {
            ajoutLettreAlaFin(seq, str[i]);
            ajoutLettreAlaFin(messageCrypte, str[i]);
        }

        else
        {
            indiceLettres(&D, &C, seq, str[i]);
            ajoutLettreAlaFin(messageCrypte, seq[D]);
            deplacerLettreVersFin(seq, C);
        }
    }

    return (char*) messageCrypte; 
}

int indiceLettre(char str[], char lettre){
    if (str[strlen(str)-1] == lettre)
    {
       return 0;
    }
    
    for (unsigned long i = 0; i < strlen(str); i++)
    {
        if (str[i] == lettre)
        {
            return i+1;
        }  
    } return 0;
}


char* DecryptSeq(char str[]){
    static char mes[MAXREP];
    char seq[MAXREP];
    int indiceLettreSuiv;
    for (unsigned long i = 0; i < strlen(str); i++)
    {
        if (lettreDansSeq(seq,str[i]) == 0)
        {
            ajoutLettreAlaFin(mes, str[i]);
            ajoutLettreAlaFin(seq, str[i]);
        }
        else
        {
            indiceLettreSuiv = indiceLettre(seq,str[i]);
            ajoutLettreAlaFin(mes,seq[indiceLettreSuiv]);
            deplacerLettreVersFin(seq,indiceLettreSuiv);
        }
    }   return (char*) mes;
}


int main() {

    // char str[] = "Alice, nous avons besoin de toi de toute urgence.";
    // printf("%s\n",(char*)crypteSeq(str));



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
    envoyer_recevoir("load crypteSeq", reponse);
    envoyer_recevoir("start", reponse);
    
    char str[MAXREP] = {0};
    strcpy(str,BayOfPigs(reponse));
    strcpy(str,crypteSeq(str));
    envoyer_recevoir(str, reponse);


    strcpy(str,DecryptSeq(reponse));
    printf("%s\n",reponse);
    envoyer_recevoir(str, reponse);

    //lire_clavier(message);   // message tapé au clavier
    //envoyer_recevoir(str, reponse); // on envoie message, et on reçoit la réponse du serveur
    
    printf ("Réponse du serveur: %s", reponse);
    printf ("Fin de la connection au serveur\n");
    return 0;
    
}
