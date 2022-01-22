#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

char To_Majuscule(char lettre){
    return lettre - 32;
}

char To_Minuscule(char lettre){
    return lettre + 32;
}


// char* ToMaj(char str[]){
    
//     for (int i = 0; str[i] != '\0'; i++)
//     {
//         if (isalpha(str[i]) != 0)
//         {
//             str[i] = toupper(str[i]);
//         } 
//     }       
//         return (char*) str;
// }

void afficher_txt_decodage(char SRC[], int cle) {

        for (int i = 0; i < strlen(SRC); i++)
        {
            if (EST_MINUSCULE(SRC[i]))
            {
                printf("%c",DecodageLetrMinusc(SRC[i], cle));
            }

            else if (EST_MAJSCULE(SRC[i]))
            {
                printf("%c",DecodageLetrMaj(SRC[i], cle));
            }

            else
            {
                printf("%c",SRC[i]);
            }
        }
  }

    

int main()
{
    //char *filename = "MessageSecret.txt";
    char *filename = "message.txt";
    FILE *fp = fopen(filename, "r");

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp))
    {
        afficher_txt_decodage(buffer,5);
    }

    fclose(fp);

    return 0;
}

