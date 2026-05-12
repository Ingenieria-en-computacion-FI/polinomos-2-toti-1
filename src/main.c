#include <stdio.h>
#include <stdlib.h>

#include "polinomio.h"

int main(){

    Polinomio* p1 = crearPolinomio();
    Polinomio* p2 = crearPolinomio();

    insertarTermino(p1, 3, 2);
    insertarTermino(p1, 2, 1);
    insertarTermino(p1, 1, 0);

    insertarTermino(p2, 1, 2);
    insertarTermino(p2, 4, 0);

    char* str1 = polinomioToString(p1);
    char* str2 = polinomioToString(p2);

    printf("P1 = %s\n", str1);
    printf("P2 = %s\n", str2);

    Polinomio* suma =
        sumarPolinomios(p1, p2);

    char* strSuma =
        polinomioToString(suma);

    printf("Suma = %s\n", strSuma);

    Polinomio* mult =
        multiplicarPolinomios(p1, p2);

    char* strMult =
        polinomioToString(mult);

    printf("Multiplicacion = %s\n", strMult);

    float valor =
        evaluarPolinomio(p1, 2);

    printf("Evaluacion P1 en x=2: %.2f\n", valor);

    free(str1);
    free(str2);
    free(strSuma);
    free(strMult);

    destruirPolinomio(p1);
    destruirPolinomio(p2);
    destruirPolinomio(suma);
    destruirPolinomio(mult);

    return 0;
}


