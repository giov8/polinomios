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

	LimpaLista(p);							// limpa os termos ocupados da lista
	free(p);								// libera o ponteiro do polinomio e a cabeca da lista

 }
/*----------------------------------------------------------------------------*/
polinomio escreve_polinomio(polinomio p) {

	TipoPonteiro aux = p->prim->prox;	// cria um ponteiro auxiliar apontando para o primeiro termo da lista
	int cont = 1;						// inicializa o contador que serve apenas para evitar que seja impresso o sinal + antes do primeiro termo

	while (aux != NULL) {												// vai ate o final da lista 
		switch ((int)aux->coeficiente) {
			case 0:														// se o coeficiente for 0:
				break;													// sai do switch
			case -1: {													// se o coeficiente for -1
				if (aux->expoente == 0)									// e o expoente for 0:
					printf("- %g ", aux->coeficiente*(-1));				// imprime apenas o coeficiente -1
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
					printf(" %g ", aux->coeficiente);					// imprime apenas o coeficiente 1
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
							printf("- %gx ", aux->coeficiente*(-1));	// imprime apenas o coeficiente
						else											// se for != 1
							printf("- %gx^%d ", aux->coeficiente*(-1), aux->expoente);	// imprime o coeficiente x^expoente
					}
					else												// se o expoente for 0
						printf("- %g ", aux->coeficiente*(-1));			// imprime apenas o coeficiente 
				}
				else {													// se o coeficiente for positivo e != 1 
					if (cont > 1) printf("+");							// e se nao for o primeiro termo

					if (aux->expoente != 0) {							// e o expoente for != 0
						if (aux->expoente == 1)							// e for igual a 1:
							printf(" %gx ", aux->coeficiente);			// imprime coeficiente x
						else											// se for diferente de != 1:
							printf(" %gx^%d ", aux->coeficiente, aux->expoente);	// imprime coeficiente x^expoente
					}
					else												// se o expoente for 0:
						printf(" %g ", aux->coeficiente);				// imprime apenas o coeficiente
				}
				break;
			}
		}
		aux = aux->prox;												// aponta para o proximo
		cont++;															// incrementa o contador
	}
    return p;															// devolve o polinomio p
}

/*----------------------------------------------------------------------------*/
polinomio soma(polinomio p, polinomio q) {
  
	polinomio r = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(r);								// cria lista apenas com a cabeca
	if (p->grau > q->grau)					// se o grau do polinomio p for maior do que o grau do polinomio q
		r->grau = p->grau;					// o polinomio r recebe o grau de p
	else  									// caso contrario
		r->grau = q->grau; 					// o polinomio r recebe o grau de q

	TipoPonteiro auxP = p->prim->prox;		// cria um ponteiro auxiliar apontando para o primeiro termo da lista p
	TipoPonteiro auxQ = q->prim->prox;		// cria um ponteiro auxiliar apontando para o primeiro termo da lista q

	while ((auxP != NULL) && (auxQ != NULL)) {		// enquanto nao chega ate o final dos polinomios p e q
		if (auxP->expoente == auxQ->expoente) {		// se os expoentes dos termos de p e q forem iguais
			Insere(auxP->coeficiente + auxQ->coeficiente, auxP->expoente, r);		// insere no polinomio r o a soma dos coeficientes dos termos de p e q, e o expoente de p
			auxP = auxP->prox;				// aponta ponteiro auxiliar de p para o proximo termo do polinomio p
			auxQ = auxQ->prox;				// aponta ponteiro auxiliar de q para o proximo termo do polinomio q
		}
		else {								// se os expoentes dos termos de p e q forem diferentes
			if (auxP->expoente > auxQ->expoente){	// se o expoente de p for maior do que o de q
				Insere(auxP->coeficiente, auxP->expoente, r); 		// insere no polinomio r o coeficiente do termo de p e seu expoente
				auxP = auxP->prox;			// aponta ponteiro auxiliar de p para o proximo termo do polinomio p
			}
			else {							// se o expoente de q for maior do que o de p
				Insere(auxQ->coeficiente, auxQ->expoente, r); 		// insere no polinomio r o coeficiente do termo de q e seu expoente
				auxQ = auxQ->prox;			// aponta ponteiro auxiliar de q para o proximo termo do polinomio q
			}
		}
	}
	return r;								// devolve o polinomio r
}
/*----------------------------------------------------------------------------*/
polinomio organiza(polinomio p) {

	polinomio r = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(r);								// cria lista apenas com a cabeca

	TipoPonteiro aux = p->prim->prox;		// cria um ponteiro auxiliar apontando para o primeiro termo da lista p
	int expoente = 0;						// declara variavel expoente, iniciando em 0, para receber o expoente do termo que sera organizado
	double coeficiente = 0;					// declara variavel coeficiente, iniciando em 0, para receber o coeficiente do termo que sera organizado

	while (aux != NULL) {					// varre a lista ate o final em busca do primeiro termo com o maior expoente
		if (aux->expoente > expoente) {		// se o expoente do termo apontado pelo auxiliar for maior do que o expoente
			expoente = aux->expoente;		// expoente recebe o expoente do termo apontado
		}
		aux = aux->prox;					// aponta ponteiro auxiliar para o proximo termo
	}
	for (expoente; expoente >= 0; expoente--) {		// enquanto o expoente for maior ou igual a zero, fica neste laco que decrementa o expoente
		aux = p->prim->prox;				// ponteiro auxiliar aponta para o primeiro termo da lista p
		coeficiente = 0;					// zera o coeficiente
		while (aux != NULL) {				// enquanto nao chega ao final da lista
			if (expoente == aux->expoente)			// se o expoente do termo apontado pelo auxiliar for igual ao expoente
				coeficiente += aux->coeficiente;	// coeficiente recebe soma do coeficiente com o coeficiente do termo apontado
			aux = aux->prox;				// aponta ponteiro auxiliar para o proximo termo
		}
		Insere(coeficiente, expoente, r);	// insere no polinomio r termo com o coeficiente acumulado e o expoente em curso
	}
	r->grau = r->prim->prox->expoente;		// atualiza o grau do polinomio r
	return r;								// devolve o polinomio r 
}
/*----------------------------------------------------------------------------*/
polinomio multiplica(polinomio p, polinomio q) {
  
	polinomio r = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(r);								// cria lista apenas com a cabeca
	TipoPonteiro auxP = p->prim->prox;		// cria um ponteiro auxiliar apontando para o primeiro termo da lista p
	TipoPonteiro auxQ = q->prim->prox;		// cria um ponteiro auxiliar apontando para o primeiro termo da lista q

	while (auxP != NULL) {					// enquanto nao chega ao final do polinomio p, faz a distribuitiva
		while (auxQ != NULL) {				// enquanto nao chega ao final do polinomio q, faz a distribuitiva
				Insere (auxP->coeficiente * auxQ->coeficiente, auxP->expoente + auxQ->expoente, r);		// multiplica um termo de p por um termo de q
				auxQ = auxQ->prox;			// aponta ponteiro auxiliar de q para o proximo termo do polinomio q
		}
	auxP = auxP->prox;						// aponta ponteiro auxiliar de p para o proximo termo do polinomio p
	auxQ = q->prim->prox;					// volta o ponteiro auxiliar de q para o primeiro termo da lista q
	}
	r = organiza(r);						// polinomio r recebe o polinomio r com graus organizados e termos de mesmo grau somados
	return r; 								// devolve o polinomio r
}
/*----------------------------------------------------------------------------*/
polinomio subtrai(polinomio p, polinomio q) {
  
	polinomio r = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(r);								// cria lista apenas com a cabeca
	if (p->grau > q->grau)					// se o grau do polinomio p for maior do que o grau do polinomio q
		r->grau = p->grau;					// o polinomio r recebe o grau de p
	else 									// caso contrario
		r->grau = q->grau;					// o polinomio r recebe o grau de q

	TipoPonteiro auxP = p->prim->prox;	// cria um ponteiro auxiliar apontando para o primeiro termo da lista p
	TipoPonteiro auxQ = q->prim->prox;	// cria um ponteiro auxiliar apontando para o primeiro termo da lista q

	while ((auxP != NULL) && (auxQ != NULL)) {		// enquanto nao chega ate o final dos polinomios p e q
		if (auxP->expoente == auxQ->expoente) {		// se os expoentes dos termos de p e q forem iguais
			Insere(auxP->coeficiente - auxQ->coeficiente, auxP->expoente, r); 		// insere no polinomio r o a subtracao dos coeficientes dos termos de p e q (p -q), e o expoente de p
			auxP = auxP->prox;				// aponta ponteiro auxiliar de p para o proximo termo do polinomio p
			auxQ = auxQ->prox;				// aponta ponteiro auxiliar de q para o proximo termo do polinomio q
		}
			else {								// se os expoentes dos termos de p e q forem diferentes
			if (auxP->expoente > auxQ->expoente){	// se o expoente de p for maior do que o de q
				Insere(auxP->coeficiente, auxP->expoente, r); 		// insere no polinomio r o coeficiente do termo de p e seu expoente
				auxP = auxP->prox;			// aponta ponteiro auxiliar de p para o proximo termo do polinomio p
			}
			else {							// se o expoente de q for maior do que o de p
				Insere(auxQ->coeficiente, auxQ->expoente, r); 		// insere no polinomio r o coeficiente do termo de q e seu expoente
				auxQ = auxQ->prox;			// aponta ponteiro auxiliar de q para o proximo termo do polinomio q
			}
		}
	}
	return r;								// devolve o polinomio r
}

/*----------------------------------------------------------------------------*/
polinomio derivada(polinomio p) {
	polinomio r = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(r);								// cria lista apenas com a cabeca

	TipoPonteiro aux = p->prim->prox;		// declara ponteiro auxiliar apontando para primeiro termo ocupado do polinomio p
	while (aux != NULL) {					// enquanto nao chega ao final da lista
		Insere(aux->coeficiente * aux->expoente, aux->expoente - 1, r); 	// deriva o termo do polinomio p e insere no polinomio r
		aux = aux->prox;					// ponteiro auxiliar aponta para o proximo termo
	}
	r->grau = r->prim->prox->expoente;		// atualiza o grau do polinomio r
	return r;								// devolve o polinomio r
}
/*----------------------------------------------------------------------------*/
polinomio primitiva(polinomio p) {
	polinomio r = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(r);								// cria lista apenas com a cabeca

	TipoPonteiro aux = p->prim->prox;		// declara ponteiro auxiliar apontando para primeiro termo ocupado do polinomio p
	while (aux->prox != NULL) {				// ate o ultimo termo ocupado do polinomio p
		Insere(aux->coeficiente / (aux->expoente + 1), aux->expoente + 1, r);	// integra o termo do polinomio p e insere no polinomio r
		aux = aux->prox; 					// ponteiro auxiliar aponta para o proximo termo
	}
	Insere(0, 0, r);						// insere a constante (grau 0 do polinomio) como 0, conforme descritivo do trabalho
	aux = NULL;								// aponta o ponteiro auxiliar para NULL
	r->grau = r->prim->prox->expoente;		// atualiza o grau do polinomio r
	return r;								// devolve o polinomio r
}
/*----------------------------------------------------------------------------*/
float avalia(polinomio p, float x) {

	float resultado = 0;					// declara variavel resultado iniciando em 0
	TipoPonteiro aux = p->prim->prox;		// declara ponteiro auxiliar apontando para primeiro termo ocupado do polinomio p

	while (aux != NULL) {					// enquanto nao chega ao final da lista
		resultado += pow(x,aux->expoente)*aux->coeficiente;		// resultado recebe resultado mais o produto do x dado elevado ao expoente pelo coeficiente
		aux = aux->prox;					// ponteiro auxiliar aponta para o proximo termo
	}
	return resultado;						// devolve o resultado
}