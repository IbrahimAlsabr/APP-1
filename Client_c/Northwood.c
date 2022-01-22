#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXMSG MAXREP

/* 
 * fonction pour savoir l'indice d'une lettre dans chaine de cacatere  
 */ 
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


/*
 * fonction pour ajouter une lettre au debut d'une chaine de caractere
 */
void ajoutAuDebut(char str[], char lettre){
	for (unsigned long i = strlen(str); i > 0; i--)
    {
        str[i] =  str[i-1];
    }   str[0] = lettre; 
}


/*
 * fonction pour extraire le mot de passe de chaine
 */
char* motDePasse(char str[]){
    static char mdp[25];

    int  i = 0;
	while( i <= 29)
	{
		if(i >= 10)
		{
			ajoutAuDebut(mdp, str[strlen(str)-i]);
		}   i++;
	}
    return (char*) mdp;
}

void deplacerLettreVersFin(char str[], unsigned long indice){
    char lettre = str[indice];
    for (unsigned long i = indice; i < strlen(str); i++)
    {
        str[i] = str[i+1];
    }   str[strlen(str)] = lettre;
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

/*
 * fonction principale de 'DecrypteSeq'
 */
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
    envoyer_recevoir("load Northwoods", reponse);
    envoyer_recevoir("start", reponse);
    envoyer_recevoir(" hasta la victoria siempre", reponse);
   
    
    char str[MAXREP] = {0};
    strcpy(str,DecryptSeq(reponse));
    strcpy(str, motDePasse(str));
    envoyer_recevoir(str, reponse);
    envoyer_recevoir("Therh wiliebrlnoeNwebtntioENgTNy-FbuT", reponse);
    
    //lire_clavier(message);   // message tapé au clavier
    
    //envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur
    
    //printf ("Réponse du serveur: %s",(char*) DecryptSeq(reponse));
    //printf ("Fin de la connection au serveur\n");
    return 0;
    
}
