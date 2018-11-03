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
	if (s[i] == '\0')						// se a string estiver vazia
		return (-1);
	while (s[i] != '\0') {					// enquanto nao chegar ao final da string
		if (s[i] == ' ')					// se encontrar um espaco - que separa os termos do polinomio
			g++;	
		i++;	
	}		
	return g;
}
/*----------------------------------------------------------------------------*/
polinomio constroi_polinomio(char *s) {

	int i = 0;								// declara indice auxiliar comecando em 0 para caminhar na string
	int expoente;							// declara variavel para o expoente do termo

	polinomio p = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(p);								// cria lista apenas com a cabeca
	p->grau = grau_polinomio(s);			// variavel grau recebe o resultado da funcao que calcula o grau do polinomio

	if (p->grau == -1) {					// se a string estiver vazia
		printf("Erro! A string com o polinômio está vazia.\n");
		exit;
	}
	for (expoente = p->grau; expoente >= 0; expoente --) {			// ate que o expoente seja 0
		char *coeficiente = (char *) malloc(sizeof(char));			// aloca dinamicamente um ponteiro para char
		int j = 0;													// declara indice j para caminhar na string auxiliar coeficiente
		do {														// usa o do para que execute ao menos uma vez
			coeficiente[j] = s[i];									// posicao j da string coeficiente recebe conteudo da posicao i da string s
			j++; i++;
			coeficiente = (char *) realloc(coeficiente, 1 + j * sizeof(char));		// aloca dinamicamente mais espaco para a string coeficiente
		} while ((s[i] != ' '));			// ate encontrar um espaco vazio na string s
		coeficiente[j] = '\0';				// fecha a string coeficiente com '\0'
		double c = atof(coeficiente);		// faz casting da string coeficiente para um double float
		Insere(c, expoente, p);				// insere novo termo no polinomio
		free (coeficiente);					// libera o espaco alocado dinamicamente para a string coeficiente
	}
	return p;
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
			case 0:														// se o coeficiente for 0
				break;													// nada e impresso
			case -1: {													// se o coeficiente for -1
				if (aux->expoente == 0)	printf("- %g ", aux->coeficiente*(-1));	// e o expoente for 0, imprime apenas o coeficiente -1
				else {
					if (aux->expoente == 1) printf("- x ");				// se o expoente for 1, imprime apenas -x
					else printf("- x^%d ", aux->expoente);				// imprime o x^expoente
				}
				break;
			}
			case 1: {													// se o coeficiente for 1
				if (cont > 1) printf("+");								// e se nao for o primeiro termo
				if (aux->expoente == 0)	printf(" %g ", aux->coeficiente);	// e o expoente for 0, imprime apenas o coeficiente 1
				else {
					if (aux->expoente == 1)	printf(" x ");				// se o expoente for 1, imprime apenas x
					else printf(" x^%d ", aux->expoente);				// imprime o x^expoente
				}
				break;
			}
			default: {
				if (aux->coeficiente < 0) {								// se o coeficiente for negativo e != -1 
					if (aux->expoente != 0) {							// e o expoente for != 0
						if (aux->expoente == 1) printf("- %gx ", aux->coeficiente*(-1));	// e for igual a 1, imprime apenas o coeficiente
						else printf("- %gx^%d ", aux->coeficiente*(-1), aux->expoente);	// imprime o coeficiente x^expoente
					}
					else printf("- %g ", aux->coeficiente*(-1));		// imprime apenas o coeficiente 
				}
				else {													// se o coeficiente for positivo e != 1 
					if (cont > 1) printf("+");							// e se nao for o primeiro termo
					if (aux->expoente != 0) {							// e o expoente for != 0
						if (aux->expoente == 1)	printf(" %gx ", aux->coeficiente);	// e for igual a 1, imprime coeficiente x
						else printf(" %gx^%d ", aux->coeficiente, aux->expoente);	// imprime coeficiente x^expoente
					}
					else printf(" %g ", aux->coeficiente);				// imprime apenas o coeficiente
				}
				break;
			}
		}
		aux = aux->prox;												// aponta para o proximo
		cont++;	
	}
	return p;
}

/*----------------------------------------------------------------------------*/
polinomio soma(polinomio p, polinomio q) {
  
	polinomio r = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(r);								// cria lista apenas com a cabeca
	if (p->grau > q->grau)					// se o grau do polinomio p for maior do que o grau do polinomio q
		r->grau = p->grau;					// o polinomio r recebe o grau de p
	else
		r->grau = q->grau; 					// o polinomio r recebe o grau de q
	TipoPonteiro auxP = p->prim->prox;		// cria um ponteiro auxiliar apontando para o primeiro termo da lista p
	TipoPonteiro auxQ = q->prim->prox;		// cria um ponteiro auxiliar apontando para o primeiro termo da lista q
	while ((auxP != NULL) && (auxQ != NULL)) {		// enquanto nao chega ate o final dos polinomios p e q
		if (auxP->expoente == auxQ->expoente) {		// se os expoentes dos termos de p e q forem iguais
			Insere(auxP->coeficiente + auxQ->coeficiente, auxP->expoente, r);		// insere no polinomio r o a soma dos coeficientes dos termos de p e q, e o expoente de p
			auxP = auxP->prox;				// aponta ponteiro auxiliar de p para o proximo termo do polinomio p
			auxQ = auxQ->prox;				// aponta ponteiro auxiliar de q para o proximo termo do polinomio q
		}
		else {
			if (auxP->expoente > auxQ->expoente){	// se o expoente de p for maior do que o de q
				Insere(auxP->coeficiente, auxP->expoente, r); 		// insere no polinomio r o coeficiente do termo de p e seu expoente
				auxP = auxP->prox;			// aponta ponteiro auxiliar de p para o proximo termo do polinomio p
			}
			else {
				Insere(auxQ->coeficiente, auxQ->expoente, r); 		// insere no polinomio r o coeficiente do termo de q e seu expoente
				auxQ = auxQ->prox;			// aponta ponteiro auxiliar de q para o proximo termo do polinomio q
			}
		}
	}
	return r;
}
/*----------------------------------------------------------------------------*/
polinomio multiplica(polinomio p, polinomio q) {
	
	/*
	EXPLICACAO: Considerando que os primeiros elementos das listas
	de polinomio(lp) sao sempre os com maiores expoentes, sera 
	criada uma lp com o tamanho maximo, com todos os coeficientes 
	iguais a zero. Depois, sera feita a distributiva: a primeira 
	lp tera todos os seus elementos multiplicados pela segunda e 
	guardados na lp resultante (r), que devera andar de uma em uma 
	posicao (por isso sera guardada em outro ponteiro a proxima 
	posicao dela) - pensando que todas as lps sao completas e, 
	entao, o expoente diminuira em um a cada multiplicao (pois
	sao somados).
	*/

	polinomio r = NovaLista();				// cria um ~novo~ polinomio vazio do tamanho maximo 			
	FLVazia(r);								
	for (int i = p->prim->prox->expoente + q->prim->prox->expoente; i >= 0; i--)
		Insere(0, i, r); 					// adiciona coeficiente 0 em todos 
	TipoPonteiro auxP = p->prim->prox;		// cria ponteiros auxiliares para percorrer os polinomios 
	TipoPonteiro auxQ = q->prim->prox;
	TipoPonteiro auxR = r->prim->prox;
	TipoPonteiro guardaR = NULL;
	while (auxP != NULL) {
		guardaR = auxR->prox;				// guarda o prox R, pois é onde a lista vai começar no prox loop 
		while (auxQ != NULL) {
			auxR->coeficiente += auxP->coeficiente * auxQ->coeficiente;
			auxQ = auxQ->prox;
			auxR = auxR->prox;
		}	
		auxP = auxP->prox;					
		auxQ = q->prim->prox;	
		auxR = guardaR;
	}
	r->grau = r->prim->prox->expoente;
	return r;   
}
/*----------------------------------------------------------------------------*/
polinomio subtrai(polinomio p, polinomio q) {
  
	polinomio r = NovaLista();				// inicializa/ aloca a lista vazia
	FLVazia(r);								// cria lista apenas com a cabeca
	if (p->grau > q->grau)					// se o grau do polinomio p for maior do que o grau do polinomio q
		r->grau = p->grau;					// o polinomio r recebe o grau de p
	else 
		r->grau = q->grau;					// o polinomio r recebe o grau de q
	TipoPonteiro auxP = p->prim->prox;		// cria um ponteiro auxiliar apontando para o primeiro termo da lista p
	TipoPonteiro auxQ = q->prim->prox;		// cria um ponteiro auxiliar apontando para o primeiro termo da lista q
	while ((auxP != NULL) && (auxQ != NULL)) {		// enquanto nao chega ate o final dos polinomios p e q
		if (auxP->expoente == auxQ->expoente) {		// se os expoentes dos termos de p e q forem iguais
			Insere(auxP->coeficiente - auxQ->coeficiente, auxP->expoente, r); 		// insere no polinomio r o a subtracao dos coeficientes dos termos de p e q (p -q), e o expoente de p
			auxP = auxP->prox;				// aponta ponteiro auxiliar de p para o proximo termo do polinomio p
			auxQ = auxQ->prox;				// aponta ponteiro auxiliar de q para o proximo termo do polinomio q
		}
		else {
			if (auxP->expoente > auxQ->expoente) {	// se o expoente de p for maior do que o de q
				Insere(auxP->coeficiente, auxP->expoente, r); 		// insere no polinomio r o coeficiente do termo de p e seu expoente
				auxP = auxP->prox;			// aponta ponteiro auxiliar de p para o proximo termo do polinomio p
			}
			else {
				Insere(auxQ->coeficiente, auxQ->expoente, r); 		// insere no polinomio r o coeficiente do termo de q e seu expoente
				auxQ = auxQ->prox;			// aponta ponteiro auxiliar de q para o proximo termo do polinomio q
			}
		}
	}
	return r;
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
	return r;
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
	aux = NULL;
	r->grau = r->prim->prox->expoente;		// atualiza o grau do polinomio r
	return r;
}
/*----------------------------------------------------------------------------*/
float avalia(polinomio p, float x) {

	float resultado = 0;					// declara variavel resultado iniciando em 0
	TipoPonteiro aux = p->prim->prox;		// declara ponteiro auxiliar apontando para primeiro termo ocupado do polinomio p
	while (aux != NULL) {					// enquanto nao chega ao final da lista
		resultado += pow(x,aux->expoente) * aux->coeficiente;		// resultado recebe resultado mais o produto do x dado elevado ao expoente pelo coeficiente
		aux = aux->prox;					// ponteiro auxiliar aponta para o proximo termo
	}
	return resultado;
}