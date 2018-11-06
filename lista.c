#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

//----------------------------------
// 1. Funcao que inicializa a lista 
//----------------------------------
lista * NovaLista () {

	lista *l = malloc(sizeof(lista));							// faz alocacao dinamica de espaco para a lista
	l->prim = l->ult = NULL;									// aponta ponteiro de primeiro e de ultimo para NULL
	l->grau = -1;												// inicializa o grau da lista em -1
	return l;
}
//---------------------------------------------
// 2. Funcao que cria a lista vazia com cabeca
//---------------------------------------------
void FLVazia (lista *l) {

	l->prim = (TipoPonteiro) malloc (sizeof(termo));			// primeira posicao da lista aponta para o endereco no qual termo foi alocado
	if (l->prim == NULL) {										// se o malloc retornar NULL, nao ha espaco de memoria
		printf ("Erro. Espaço de memória insuficiente.\n");	
		exit;
	}
	l->ult = l->prim;											// primeira e ultima posicao da lista coincidem
	l->prim->prox = NULL;										// campo prox da primeira posicao aponta para NULL
	l->prim->coeficiente = ' ';									// inicializa o campo coeficiente com ' ', pois a lista tera cabeca
	l->prim->expoente = ' ';									// inicializa o campo expoente com ' ', pois a lista tera cabeca
	return;
}
//-------------------------------------------
// 3. Funcao que checa se a lista esta vazia
//-------------------------------------------
int Vazia (lista *l) {

	return (l->prim == l->ult);									// testa se os ponteiros para primeiro e ultimo apontam o mesmo node
}
//----------------------------------------------------
// 4. Funcao que insere novo termo no inicio da lista 
//----------------------------------------------------
void Insere (double c, int e, lista *l) {

	l->ult->prox = (TipoPonteiro) malloc (sizeof(termo));		// insere um node na lista
	if (l->ult->prox == NULL) {									// se o malloc retornar NULL, nao ha espaco de memoria
		printf ("Erro. Espaço de memória insuficiente.\n");
		exit;
	}
	l->ult = l->ult->prox;										// atualiza o ponteiro que indica o ultimo elemento
	l->ult->coeficiente = c;									// coeficiente do novo termo inserido recebe float lido do polinomio e armazenado em c
	l->ult->expoente = e;										// expoente do novo termo inserido recebe int lido do polinomio e armazenado em e
	l->ult->prox = NULL;										// campo prox da ultima posicao aponta para NULL
	return;
}
//-------------------------------------------------------------------
// 5. Funcao que limpa a lista - do primeiro ao ultimo node ocupados
//-------------------------------------------------------------------
void LimpaLista (lista *l) {

	TipoPonteiro aux;											
	if (Vazia(l)) {												
		printf ("Erro. A lista está vazia\n");
		exit;
	}
	
	while (l->prim->prox != NULL) {								// enquanto nao chegar ao ultimo node
		aux = l->prim->prox;									// ponteiro aux aponta para primeiro node ocupado
		l->prim->prox = aux->prox;								// ajusta ponteiro de proximo da cabeca para o proximo node ocupado 
		free (aux);												// libera o conteudo do local para onde aponta o ponteiro aux
	}
	l->ult = l->prim;											// ajusta o ponteiro de ultimo para a cabeca da lista
	return;	
}