#include "polinomio.h"

Nodo* crearNodo(float coef, int exp){
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));

    if(nodo == NULL){
        return NULL;
    }

    nodo->termino.coeficiente = coef;
    nodo->termino.exponente = exp;
    nodo->siguiente = NULL;
    nodo->anterior = NULL;

    return nodo;
}

Polinomio* crearPolinomio(){
    Polinomio* p = (Polinomio*)malloc(sizeof(Polinomio));

    if(p == NULL){
        return NULL;
    }

    p->cabeza = NULL;
    p->cola = NULL;

    return p;
}

void insertarNodoOrdenado(Polinomio* p, Nodo* nuevo){

    if(p->cabeza == NULL){
        p->cabeza = nuevo;
        p->cola = nuevo;
        return;
    }

    Nodo* temp = p->cabeza;

    while(temp != NULL && temp->termino.exponente > nuevo->termino.exponente){
        temp = temp->siguiente;
    }

    if(temp == NULL){
        nuevo->anterior = p->cola;
        p->cola->siguiente = nuevo;
        p->cola = nuevo;
        return;
    }

    if(temp == p->cabeza){
        nuevo->siguiente = p->cabeza;
        p->cabeza->anterior = nuevo;
        p->cabeza = nuevo;
        return;
    }

    nuevo->siguiente = temp;
    nuevo->anterior = temp->anterior;

    temp->anterior->siguiente = nuevo;
    temp->anterior = nuevo;
}

void eliminarNodo(Polinomio* p, int exp){

    Nodo* temp = p->cabeza;

    while(temp != NULL){

        if(temp->termino.exponente == exp){

            if(temp == p->cabeza && temp == p->cola){
                p->cabeza = NULL;
                p->cola = NULL;
            }

            else if(temp == p->cabeza){
                p->cabeza = temp->siguiente;
                p->cabeza->anterior = NULL;
            }

            else if(temp == p->cola){
                p->cola = temp->anterior;
                p->cola->siguiente = NULL;
            }

            else{
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;
            }

            free(temp);
            return;
        }

        temp = temp->siguiente;
    }
}

void insertarTermino(Polinomio* p, float coef, int exp){

    if(coef == 0){
        return;
    }

    Nodo* temp = p->cabeza;

    while(temp != NULL){

        if(temp->termino.exponente == exp){

            temp->termino.coeficiente += coef;

            if(temp->termino.coeficiente == 0){
                eliminarNodo(p, exp);
            }

            return;
        }

        temp = temp->siguiente;
    }

    Nodo* nuevo = crearNodo(coef, exp);
    insertarNodoOrdenado(p, nuevo);
}

float evaluarPolinomio(Polinomio* p, float x){

    float res = 0;
    Nodo* temp = p->cabeza;

    while(temp != NULL){
        res += temp->termino.coeficiente * pow(x, temp->termino.exponente);
        temp = temp->siguiente;
    }

    return res;
}

Polinomio* sumarPolinomios(Polinomio* p1, Polinomio* p2){

    Polinomio* res = crearPolinomio();

    Nodo* temp = p1->cabeza;

    while(temp != NULL){
        insertarTermino(res, temp->termino.coeficiente, temp->termino.exponente);
        temp = temp->siguiente;
    }

    temp = p2->cabeza;

    while(temp != NULL){
        insertarTermino(res, temp->termino.coeficiente, temp->termino.exponente);
        temp = temp->siguiente;
    }

    return res;
}

Polinomio* multiplicarPolinomios(Polinomio* p1, Polinomio* p2){

    Polinomio* res = crearPolinomio();

    Nodo* a = p1->cabeza;

    while(a != NULL){

        Nodo* b = p2->cabeza;

        while(b != NULL){

            float coef = a->termino.coeficiente * b->termino.coeficiente;
            int exp = a->termino.exponente + b->termino.exponente;

            insertarTermino(res, coef, exp);

            b = b->siguiente;
        }

        a = a->siguiente;
    }

    return res;
}

char* polinomioToString(Polinomio* p){

    char* texto = (char*)malloc(1024);
    texto[0] = '\0';

    if(p->cabeza == NULL){
        strcpy(texto, "0");
        return texto;
    }

    Nodo* temp = p->cabeza;

    while(temp != NULL){

        char parte[100];
        float coef = temp->termino.coeficiente;
        int exp = temp->termino.exponente;

        if(strlen(texto) > 0 && coef > 0){
            strcat(texto, "+");
        }

        if(exp == 0){
            sprintf(parte, "%g", coef);
        }

        else if(exp == 1){

            if(coef == 1){
                sprintf(parte, "x");
            }

            else if(coef == -1){
                sprintf(parte, "-x");
            }

            else{
                sprintf(parte, "%gx", coef);
            }
        }

        else{

            if(coef == 1){
                sprintf(parte, "x^%d", exp);
            }

            else if(coef == -1){
                sprintf(parte, "-x^%d", exp);
            }

            else{
                sprintf(parte, "%gx^%d", coef, exp);
            }
        }

        strcat(texto, parte);
        temp = temp->siguiente;
    }

    return texto;
}

void destruirPolinomio(Polinomio* p){

    Nodo* temp = p->cabeza;

    while(temp != NULL){
        Nodo* aux = temp;
        temp = temp->siguiente;
        free(aux);
    }

    free(p);
}