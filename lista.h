#ifndef _lista_
#define _lista_

	typedef struct termo *TipoPonteiro;		// define um TipoPonteiro para nodes de termos do polinomio

	typedef struct termo {					// define o tipo termo
		double coeficiente;					// esse campo vai indicar o coeficiente
		int expoente;						// esse campo vai indicar o expoente
		TipoPonteiro prox;					// esse campo vai apontar para o proximo node
	} termo;

	typedef struct lista {
		int grau;							// esse campo vai indicar o numero de nos (graus) da lista (polinomio)
		TipoPonteiro prim;					// esse campo vai apontar para o primeiro node
		TipoPonteiro ult;					// esse campo vai apontar para o ultimo node
	} lista;
#endif

lista * NovaLista ();
void FLVazia (lista *l);
int Vazia (lista *l);
void Insere (double c, int e, lista *l);
void LimpaLista (lista *l);