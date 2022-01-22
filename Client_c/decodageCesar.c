#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "decodageCesar.h"
#include "client.h"

// bool EST_MAJSCULE(char lettre){
//     return(lettre >= 'A' && lettre <= 'Z');
// }

// bool EST_MINUSCULE(char lettre){
//     return(lettre >= 'a' && lettre <= 'z');
// }

// char DecodageLetrMaj(char lettreLue, int cle){

//     if (lettreLue - cle < 'A')
//     {
//         return('Z' - (cle - (lettreLue -'A')) + 1);
// 	}

//     return lettreLue - cle ;
// }

// char DecodageLetrMinusc(char lettreLue, int cle){

//     if (lettreLue - cle < 'a')
//     {
//         return('z' - (cle - (lettreLue -'a')) + 1);
// 	}

//     return lettreLue - cle ;
// }

// char* decodageCesar(char SRC[], int cle) {

//     for (unsigned long i = 0; i < strlen(SRC); i++)
//     {
//         if (EST_MINUSCULE(SRC[i]))
//         {
//             SRC[i] = DecodageLetrMinusc(SRC[i], cle);
//             //printf("%c",DecodageLetrMinusc(SRC[i], cle));
//         }

//         else if (EST_MAJSCULE(SRC[i]))
//         {
//             SRC[i] = DecodageLetrMaj(SRC[i], cle);
//             //printf("%c",DecodageLetrMaj(SRC[i], cle));
//         }

//         else
//         {
//             SRC[i] = SRC[i];
//             //printf("%c",SRC[i]);
//         }
//     }
//     return (char*) SRC;
// }

    

// int main()
// {
//     char *filename = "MessageSecret.txt";
//     FILE *fp = fopen(filename, "r");

//     const unsigned MAX_LENGTH = 256;
//     char buffer[MAX_LENGTH];

//     while (fgets(buffer, MAX_LENGTH, fp))
//     {
//        decodageCesar(buffer,5);
//     }

//     fclose(fp);

//     return 0;
// }

