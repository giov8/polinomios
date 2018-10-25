#include <stdio.h>
#include <stdlib>
#include "lista.h"

/*Preencher com o código fonte */

//----------------------------------
// 1. Funcao que inicializa a lista 
//----------------------------------

lista * NovaLista () {

        lista *l = malloc(sizeof(lista));                               // faz alocacao dinamica de espaco para a lista
        l->prim = l->ult = NULL;                                        // aponta ponteiro de primeiro e de ultimo para NULL
        l->tam = 0;                                             	// inicializa o tamanho da lista em 0
        return l;                                                       // retorna a lista
}

//---------------------------------------------
// 2. Funcao que cria a lista vazia com cabeca
//---------------------------------------------

void FLvazia (lista *l) {

        l->prim = (TipoPonteiro) malloc (sizeof(termo));                // primeira posicao da lista aponta para o endereco no qual termo foi alocado
        if (l->prim == NULL) {						// se o malloc retornar NULL, nao ha espaco de memoria
                printf ("Erro. Espaço de memória insuficiente.\n");     // imprime mensagem de erro
                exit;	                                                // sai do programa
        }
        l->ult = l->prim;                                        	// primeira e ultima posicao da lista coincidem
        l->prim->prox = NULL;                                           // campo prox da primeira posicao aponta para NULL
	l->prim->termo = ' ';						// inicializa o campo termo com ' ', pois a lista tera cabeca
        return;
}

//-------------------------------------------
// 3. Funcao que checa se a lista esta vazia
//-------------------------------------------

int VaziaLista (lista *l) {

        return (l->prim == l->ult);					// testa se os ponteiros para primeiro e ultimo apontam o mesmo node
}

//----------------------------------------------------
// 4. Funcao que insere novo termo no inicio da lista 
//----------------------------------------------------

void InsereTermo (int x, lista *l) {

	l->ult->prox = (TipoPonteiro) malloc (sizeof(termo));           // insere um node na lista
	if (l->ult->prox == NULL) {					// se o malloc retornar NULL, nao ha espaco de memoria
        	printf ("Erro. Espaço de memória insuficiente.\n");     // imprime mensagem de erro
                exit;							// sai do programa
        }
	l->ult = l->ult->prox;            				// atualiza o ponteiro que indica o ultimo elemento
        l->ult->coeficiente = x;                                        // coeficiente do novo termo inserido recebe inteiro lido do polinomio e armazenado em x
	l->ult->prox = NULL;                     			// campo prox da ultima posicao aponta para NULL
        l->tam = l->tam + 1;						// atualiza o tamanho da lista		
        return;
}

//----------------------------------------------------------
// 5. Funcao que limpa a lista - do primeiro ao ultimo node
//----------------------------------------------------------

void LimpaLista (lista *l) {

	TipoPonteiro aux1, aux2;					// declara ponteiros auxiliares

	if (VaziaLista(l)) {                                            // se a lista estiver vazia
		printf ("Erro. A lista está vazia\n");                  // imprime mensagem de erro
                exit;	                                                // sai do programa
        }
        else {
	        while (l->prim->prox != NULL) {				// enquanto nao chegar ao ultimo node
                        aux1 = l->prim->prox;                           // ponteiro aux1 aponta para primeiro node ocupado
                        aux2 = aux1->prox;                              // ponteiro aux2 aponta para o segundo node ocupado 
                        free (aux1);                                    // libera o conteudo do local para onde aponta o ponteiro aux1
                        l->prim->prox = aux2;                           // a cabeca da lista aponta para o proximo node
	        }
		aux2 = NULL;    					// ponteiro auxiliar aponta para NULL
                free (aux2);                                            // libera o ponteiro auxiliar
                l->ult = l->prim;                                       // ajusta o ponteiro de ultimo para a cabeca da lista
	        return;
        }	
}
