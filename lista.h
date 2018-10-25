#ifndef _lista_
#define _lista_

/* PREENCHER COM SUAS DEFINIÇÕES DE TIPOS E FUNÇÕES */

	typedef struct termo *TipoPonteiro;     // define um TipoPonteiro para nodes de termos do polinomio

	typedef struct termo {                  // define o tipo termo
		int coeficiente;                // esse campo vai indicar o coeficiente
		TipoPonteiro prox;              // esse campo vai apontar para o proximo node
	} termo;

        typedef struct lista {
                int tam;                        // esse campo vai indicar o numero de nos (graus) da lista (polinomio)
		TipoPonteiro prim;              // esse campo vai apontar para o primeiro node
		TipoPonteiro ult;               // esse campo vai apontar para o ultimo node
        } lista;
#endif
