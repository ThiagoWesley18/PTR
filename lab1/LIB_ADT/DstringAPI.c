#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "Dstring.h"
#define DSTRING_TO_CHAR(dstring) (dstring.string)


// Cria uma Dstring
Dstring newDstring(char *string){
    Dstring str;
    str.string = malloc( strlen(string) + 1);
    if(str.string != NULL){
        strcpy(str.string, string);
    } else {
        printf("Falha na alocação de memória.\n");
        exit(1);
    }
    return str;
}

// Converte um tipo inteiro para Dstring
Dstring intToString(int num){
    Dstring str;
    int length = snprintf(NULL, 0, "%d", num);
    if (length < 0) {
        printf("Erro ao calcular o tamanho da string.\n");
        exit(1);
    }
    str.string = malloc(length + 1); // aloca memória baseado no tamanho da string
    if (str.string != NULL) {
        sprintf(str.string, "%d", num);  
    } else {
        printf("Falha na alocação de memória.\n");
        exit(1);  
    }
    return str;
}

// Converte um tipo float para Dstring
Dstring floatToString(float num){
    Dstring str;
    int length = snprintf(NULL, 0, "%f", num);
    if (length < 0) {
        printf("Erro ao calcular o tamanho da string.\n");
        exit(1);
    }
    str.string = malloc(length + 1); // aloca memória baseado no tamanho da string
    if (str.string != NULL) {
        sprintf(str.string, "%f", num);  
    } else {
        printf("Falha na alocação de memória.\n");
        exit(1);  
    }
    return str;
}

// Converte um tipo long para Dstring
Dstring longToString(long num){
    Dstring str;
    int length = snprintf(NULL, 0, "%ld", num);
    if (length < 0) {
        printf("Erro ao calcular o tamanho da string.\n");
        exit(1);
    }
    str.string = malloc(length + 1); // aloca memória baseado no tamanho da string
    if (str.string != NULL) {
        sprintf(str.string, "%ld", num);  
    } else {
        printf("Falha na alocação de memória.\n");
        exit(1);  
    }
    return str;
}

// Converte um tipo char para Dstring
Dstring charToString(char caractere){
    Dstring str;
    int length = snprintf(NULL, 0, "%c", caractere);
    if (length < 0) {
        printf("Erro ao calcular o tamanho da string.\n");
        exit(1);
    }
    str.string = malloc(length + 1); // aloca memória baseado no tamanho da string
    if (str.string != NULL) {
        sprintf(str.string, "%c", caractere);  
    } else {
        printf("Falha na alocação de memória.\n");
        exit(1);  
    }
    return str;
}

// Concatena duas ou mais Dstring
Dstring concat(Dstring str1, ...){
    va_list args;
    va_start(args, str1);
    Dstring str;
    str.string = malloc(strlen(str1.string) + 1);
    if (str.string != NULL) {
        strcpy(str.string, str1.string);
        Dstring str2;
        while((str2 = va_arg(args, Dstring)).string != NULL){
            str.string = realloc(str.string, strlen(str.string) + strlen(str2.string) + 1);
            if (str.string != NULL) {
                strcat(str.string, str2.string);
            } else {
                printf("Falha na reolocação de memória.\n");
                exit(1);  
            }
        }
    } else {
        printf("Falha na alocação de memória.\n");
        exit(1);  
    }
    va_end(args);
    return str;
}

// Retorna o tamanho de uma Dstring
int tamanho(Dstring str){
    return strlen(str.string);
}

// Converte uma Dstring para um vertor char
char *dstringToChar(Dstring str){
    return DSTRING_TO_CHAR(str);
}

// Libera a memória alocada para uma ou mais Dstring
void freeDstring(Dstring str, ...){
    va_list args;
    va_start(args, str);
    Dstring str2;
    while((str2 = va_arg(args, Dstring)).string != NULL){
        free(str2.string);
        str2.string = NULL;
    }
    va_end(args);
    printf("- Dstring Liberada\n");
}




