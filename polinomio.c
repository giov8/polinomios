#include "polinomio.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*----------------------------------------------------------------------------*/
int grau_polinomio(char *s) {

	int g = 0;								// declara inteiro para representar o grau do polinomio iniciando em 0
	int i = 0;								// declara indice auxiliar comecando em 0 para caminhar na string

	if (s[i] == '\0') {						// se a string estiver vazia
		return (-1);						// a funcao retorna -1
	}
	while (s[i] != '\0') {					// enquanto nao chegar ao final da string
		if (s[i] == ' ') {					// se encontrar um espaco - que separa os termos do polinomio
			g++;							// aumenta o grau do polinomio
		}
		i++;								// incrementa o indice que caminha no vetor
	}		
	return g;								// retorna g
}
/*----------------------------------------------------------------------------*/
polinomio constroi_polinomio(char *s) {

	int i = 0;								// declara indice auxiliar comecando em 0 para caminhar na string
	int expoente;							// declara variavel para o expoente do termo

	polinomio p = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(p);								// cria lista apenas com a cabeca
	p->grau = grau_polinomio(s);			// variavel grau recebe o resultado da funcao que calcula o grau do polinomio

	if (p->grau == -1) {					// se a string estiver vazia
		printf("Erro! A string com o polinômio está vazia.\n");		// retorna mensagem de erro
		exit;								// e sai do programa
	}
	for (expoente = p->grau; expoente >= 0; expoente --) {			// ate que o expoente seja 0
		char *coeficiente = (char *) malloc(sizeof(char));			// aloca dinamicamente um ponteiro para char
		int j = 0;													// declara indice j para caminhar na string auxiliar coeficiente
		do {														// usa o do para que execute ao menos uma vez
			coeficiente[j] = s[i];									// posicao j da string coeficiente recebe conteudo da posicao i da string s
			j++; i++;												// incremente os indices
			coeficiente = (char *) realloc(coeficiente, 1 + j * sizeof(char));		// aloca dinamicamente mais espaco para a string coeficiente
		} while ((s[i] != ' '));			// ate encontrar um espaco vazio na string s
		coeficiente[j] = '\0';				// fecha a string coeficiente com '\0'
		double c = atof(coeficiente);		// faz casting da string coeficiente para um double float
		Insere(c, expoente, p);				// insere novo termo no polinomio
		free (coeficiente);					// libera o espaco alocado dinamicamente para a string coeficiente
	}
	return p;								// retorna p
}
/*----------------------------------------------------------------------------*/
void destroi_polinomio(polinomio p) { 

	LimpaLista(p);
	free(p);

 }
/*----------------------------------------------------------------------------*/
polinomio escreve_polinomio(polinomio p) {

	TipoPonteiro aux = p->prim->prox;	// cria um ponteiro auxiliar apontando para o primeiro termo da lista
	int cont = 1;						// inicializa o contador que serve apenas para evitar que seja impresso o sinal + antes do primeiro termo

	while (aux != NULL) {												// vai até o final da lista 
		switch ((int)aux->coeficiente) {
			case 0:														// se o coeficiente for 0:
				break;													// sai do switch
			case -1: {													// se o coeficiente for -1
				if (aux->expoente == 0)									// e o expoente for 0:
					printf("-%2.lf ", aux->coeficiente*(-1));			// imprime apenas o coeficiente -1
				else {													// e o expoente for != 0:
					if (aux->expoente == 1)								// se o expoente for 1
						printf("- x ");									// imprime apenas -x
					else												// se o expoente for != 1
						printf("- x^%d ", aux->expoente);				// imprime o x^expoente
				}
				break;
			}
			case 1: {													// se o coeficiente for 1
				if (cont > 1) printf("+");								// e se nao for o primeiro termo

				if (aux->expoente == 0)									// e o expoente for 0:
					printf("%2.lf ", aux->coeficiente);					// imprime apenas o coeficiente 1
				else {													// e o expoente for != 0:
					if (aux->expoente == 1)								// se o expoente for 1
						printf(" x ");									// imprime apenas x
					else												// se o expoente for != 1
						printf(" x^%d ", aux->expoente);				// imprime o x^expoente
				}
				break;
			}
			default: {
				if (aux->coeficiente < 0) {								// se o coeficiente for negativo e != -1 
					if (aux->expoente != 0) {							// e o expoente for != 0
						if (aux->expoente == 1)							// e for igual a 1:
							printf("-%2.lfx ", aux->coeficiente*(-1));	// imprime apenas o coeficiente
						else											// se for != 1
							printf("-%2.lfx^%d ", aux->coeficiente*(-1), aux->expoente);	// imprime o coeficiente x^expoente
					}
					else												// se o expoente for 0
						printf("-%2.lf ", aux->coeficiente*(-1));		// imprime apenas o coeficiente 
				}
				else {													// se o coeficiente for positivo e != 1 
					if (cont > 1) printf("+");							// e se nao for o primeiro termo

					if (aux->expoente != 0) {							// e o expoente for != 0
						if (aux->expoente == 1)							// e for igual a 1:
							printf("%2.lfx ", aux->coeficiente);		// imprime coeficiente x
						else											// se for diferente de != 1:
							printf("%2.lfx^%d ", aux->coeficiente, aux->expoente);		// imprime coeficiente x^expoente
					}
					else												// se o expoente for 0:
						printf("%2.lf ", aux->coeficiente);				// imprime apenas o coeficiente
				}
				break;
			}
		}
		aux = aux->prox;												// aponta para o proximo
		cont++;															// incrementa o contador
	}

    aux = NULL;															// aponta para NULL		
    free (aux);															// libera o ponteiro auxiliar
    return p;															// devolve o polinomio p
}


/*----------------------------------------------------------------------------*/
polinomio soma(polinomio p, polinomio q) {
  
	polinomio r = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(r);								// cria lista apenas com a cabeca
	if (p->grau > q->grau) {
		r->grau = p->grau;
	}
	else{ 
		r->grau = q->grau;
	}
	TipoPonteiro auxP = p->prim->prox;	// cria um ponteiro auxiliar apontando para o primeiro termo da lista p
	TipoPonteiro auxQ = q->prim->prox;	// cria um ponteiro auxiliar apontando para o primeiro termo da lista q
	while ((auxP != NULL) && (auxQ != NULL)) {				// vai até o final da lista
		if (auxP->expoente == auxQ->expoente) {
			Insere(auxP->coeficiente + auxQ->coeficiente, auxP->expoente, r);
			auxP = auxP->prox;
			auxQ = auxQ->prox;
		}
		else {
			if (auxP->expoente > auxQ->expoente){
				Insere(auxP->coeficiente, auxP->expoente, r);
				auxP = auxP->prox;
			}
			else{
				Insere(auxQ->coeficiente, auxQ->expoente, r);
				auxQ = auxQ->prox;
			}
		}
	}
	return r;
}
/*----------------------------------------------------------------------------*/
polinomio multiplica(polinomio p, polinomio q) {
  
  /* Preencher com seu código aqui */
}
/*----------------------------------------------------------------------------*/
polinomio subtrai(polinomio p, polinomio q) {
  
	polinomio r = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(r);								// cria lista apenas com a cabeca
	if (p->grau > q->grau) {
		r->grau = p->grau;
	}
	else{ 
		r->grau = q->grau;
	}
	TipoPonteiro auxP = p->prim->prox;	// cria um ponteiro auxiliar apontando para o primeiro termo da lista p
	TipoPonteiro auxQ = q->prim->prox;	// cria um ponteiro auxiliar apontando para o primeiro termo da lista q
	while ((auxP != NULL) && (auxQ != NULL)) {				// vai até o final da lista
		if (auxP->expoente == auxQ->expoente) {
			Insere(auxP->coeficiente - auxQ->coeficiente, auxP->expoente, r);
			auxP = auxP->prox;
			auxQ = auxQ->prox;
		}
		else {
			if (auxP->expoente > auxQ->expoente){
				Insere(auxP->coeficiente, auxP->expoente, r);
				auxP = auxP->prox;
			}
			else{
				Insere(auxQ->coeficiente, auxQ->expoente, r);
				auxQ = auxQ->prox;
			}
		}
	}
	return r;
}

/*----------------------------------------------------------------------------*/
polinomio derivada(polinomio p) {
  
  /* Preencher com seu código aqui */
}
/*----------------------------------------------------------------------------*/
polinomio primitiva(polinomio p) {
  
  /* Preencher com seu código aqui */
}
/*----------------------------------------------------------------------------*/
float avalia(polinomio p, float x) {

	float resultado = 0;
	TipoPonteiro aux = p->prim->prox;

	while (aux != NULL) {
		resultado += pow(x,aux->expoente)*aux->coeficiente;
		aux = aux->prox;
	}

	return resultado;
}
