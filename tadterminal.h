/*Trabalho 1 - Estrutura de Dados 1
 *Dupla: Dener Silva Guimaraes e Tassio Santuchi
 	**************************************
 	***** IMPLEMENTACAO TAD TERMINAL *****
 	**************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*----- Estrutura dos Terminais -----*/

typedef struct tipoterminal TipoTerminal;

struct tipoterminal{
	char* nomeTer;
	char* localidade;
};

typedef struct celterminal CelTerminal;

struct celterminal{
	TipoTerminal* info;
	struct celterminal* prox;
};

typedef struct listterminais ListTerminais;

struct listterminais{
	CelTerminal* prim;
	CelTerminal* ult;
};

/*--------- Inicializacao da lista de terminais ---------*/

ListTerminais* inicializaListaTerminais(){
	ListTerminais* l = (ListTerminais*)malloc(sizeof(ListTerminais));
	l->prim = NULL;
	l->ult = NULL;
	return(l);
}

/*----- Insere novo terminal na lista -----*/

TipoTerminal* inicializaTipoTerminal(char* nome, char* localidade){
	TipoTerminal* novoter = (TipoTerminal*)malloc(sizeof(TipoTerminal));
	novoter->nomeTer = malloc( (strlen(nome)+1)*sizeof(char) );
	strcpy(novoter->nomeTer, nome);
	novoter->localidade = malloc( (strlen(localidade)+1)*sizeof(char) );
	strcpy(novoter->localidade, localidade);
	return(novoter);
}

ListTerminais* cadastraTerminal(ListTerminais* lstTer, char* terminal, char* localidade){
	TipoTerminal* tipoTer = inicializaTipoTerminal(terminal, localidade);
	//Aloca espaco para uma nova celula
	CelTerminal* nova_celterminal = (CelTerminal*)malloc(sizeof(CelTerminal));
	nova_celterminal->info = tipoTer;
	nova_celterminal->prox = NULL;
	//Se a lista estiver vazia:
	if(lstTer->prim == NULL){
		lstTer->prim = nova_celterminal;
		lstTer->ult = nova_celterminal;
	}
	else{//Insere no final da lista:
		lstTer->ult->prox = nova_celterminal;
		lstTer->ult = nova_celterminal;
	}
	return(lstTer);
}

/*----- Imprime a lista de terminais -----*/

void imprimeTerminais(ListTerminais* l){
	CelTerminal* p = l->prim;
	while(p != NULL){
		printf("TERMINAL: %s, CIDADE: %s\n", p->info->nomeTer, p->info->localidade);
		p = p->prox;
	}
}

/*----- Remove terminal do NetMap -----*/

void removeTerminal(ListTerminais* lstTer, char* terminal){
	CelTerminal* p = lstTer->prim;
	CelTerminal* ant = NULL;
	while(p != NULL && (strcmp(p->info->nomeTer, terminal) != 0	) ){//Percorre a lista ate achar o elemento ou ate ela ser NULL.
		ant = p;
		p = p->prox;
	}
	if(p == NULL){//Se o elemento nao estiver na lista.
		printf("Erro: %s inexistente no NetMap\n", terminal);
		return;
	}
	if(p == lstTer->prim && p == lstTer->ult){
		lstTer->prim = NULL;
		lstTer->ult = NULL;
		free(p);
		return;
	}
	if(p == lstTer->prim){//Se elemento a ser retirado estiver no inicio.
		lstTer->prim = p->prox;
		free(p);
		return;
	}
	if(p == lstTer->ult){//Se elemento a ser retirado estiver no final.
		lstTer->ult = ant;
		ant->prox = NULL;
		free(p);
		return;
	}
	else{//Se elemento a ser retirado estiver no meio.
		ant->prox = p->prox;
		p = ant->prox;
		free(p);
		return;
	}
}
