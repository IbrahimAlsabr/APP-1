#include <stdio.h>
#include <stdbool.h>

/*
 *  Auteur(s) : Alsabr Ibrahim
 *  Date : 16/09/2021
 */

char LettreMaj(char lettreLue, int cle){

    if (lettreLue + cle > 'Z')
    {
        return(cle - ('Z' - lettreLue) + 'A' - 1) ;
    }

    return lettreLue + cle ;
}

char LettreMin(char lettreLue, int cle){

    if (lettreLue + cle > 'z')
    {
        return(cle - ('z' - lettreLue) + 'a' - 1) ;
    }

    return lettreLue + cle ;
}

bool EST_MAJSCULE(char lettre){
    return(lettre >= 'A' && lettre <= 'Z');
}

bool EST_MINUSCULE(char lettre){
    return(lettre >= 'a' && lettre <= 'z');
}

int main (void)
{
    char lettreLue;
    char lettreSuivante3;

    printf ("Donner une lettre \n");
    scanf ("%c",&lettreLue);


    if (EST_MINUSCULE(lettreLue))
    {
        lettreSuivante3 = LettreMin(lettreLue,3);
        printf("\n%c\n",lettreSuivante3);
    }  

    else if (EST_MAJSCULE(lettreLue))
    {
        lettreSuivante3 = LettreMaj(lettreLue, 3);
        printf("\n%c\n",lettreSuivante3);
    }

    else
    {
        printf("\n%c\n",lettreLue);
    }
    
    return 0;
}

