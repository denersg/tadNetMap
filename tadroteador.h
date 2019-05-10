/*Trabalho 1 - Estrutura de Dados 1
 *Dupla: Dener Silva Guimaraes e Tassio Santuchi
 	**************************************
 	***** IMPLEMENTACAO TAD ROTEADOR *****
 	**************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*----- Estrutura dos Roteadores -----*/

typedef struct tiporoteador TipoRoteador;

struct tiporoteador{
	char* nomeRot;
	char* operadora;
};

typedef struct celrot CelRot;

struct celrot{
	TipoRoteador* item;
	struct celrot* outrosRot;//Faz a conexao com outros roteadores, a partir daquele roteador.
	struct celrot* prox;
	struct celrot* prim;
	struct celrot* ult;
};

typedef struct listrot ListRot;

struct listrot{
	CelRot* prim;
	CelRot* ult;
};

/*--------- Inicializacao das listas ---------*/

ListRot* inicializaListaRot(){
	ListRot* l = (ListRot*)malloc(sizeof(ListRot));
	l->prim = NULL;
	l->ult = NULL;
	return(l);
}

/*----- Insere novo roteador na lista -----*/

TipoRoteador* inicializaTipoRoteador(char* nome, char* op){
	TipoRoteador* novorot = (TipoRoteador*)malloc(sizeof(TipoRoteador));
	novorot->nomeRot = malloc( (strlen(nome)+1)*sizeof(char) );
	strcpy(novorot->nomeRot, nome);
	novorot->operadora = malloc( (strlen(op)+1)*sizeof(char) );
	strcpy(novorot->operadora, op);
	return (novorot);
}

ListRot* cadastraRoteador(ListRot* lstRot, char* roteador, char* operadora){
	TipoRoteador* tipoRot = inicializaTipoRoteador(roteador, operadora);

	CelRot* nova_celroteador = (CelRot*)malloc(sizeof(CelRot));
	nova_celroteador->item = tipoRot;
	nova_celroteador->prox = NULL;
	nova_celroteador->prim = NULL;
	nova_celroteador->ult = NULL;
	//Se lista vazia:
	if(lstRot->prim == NULL){
		lstRot->prim = nova_celroteador;
		lstRot->ult = nova_celroteador;
	}
	//Insere no final da lista:
	lstRot->ult->prox = nova_celroteador;
	lstRot->ult = nova_celroteador;
	return(lstRot);
}

void imprimeRoteadores(ListRot* l){
	CelRot* p = l->prim;
	while(p != NULL){
		printf("ROTEADOR: %s, OPERADORA: %s\n", p->item->nomeRot, p->item->operadora);
		p = p->prox;
	}
}

/*----- Remove roteador do NetMap -----*/

void removeRoteador(ListRot* lstRot, char* roteador){
	CelRot* p = lstRot->prim;
	CelRot* ant = NULL;
	while(p != NULL && (strcmp(p->item->nomeRot, roteador) != 0	) ){
		ant = p;
		p = p->prox;
	}
	if(p == NULL){
		printf("Erro: %s inexistente no NetMap\n", roteador);
		return;
	}
	if(p == lstRot->prim && p == lstRot->ult){//Se o elemento for unico.
		lstRot->prim = NULL;
		lstRot->ult = NULL;
		free(p);
		return;
	}
	if(p == lstRot->prim){//Se o elemento estiver no inicio da lista.
		lstRot->prim = p->prox;
		free(p);
		return;
	}
	if(p == lstRot->ult){//Se o elemento estiver no final da lista.
		lstRot->ult = ant;
		ant->prox = NULL;
		free(p);
		return;
	}
	else{//Se o elemento estiver no meio da lista.
		ant->prox = p->prox;
		p = ant->prox;
		free(p);
		return;
	}
}

CelRot* buscaRot(ListRot* lstRot, char* roteador){
	CelRot* aux = lstRot->prim;
	//printf("Memoria de aux fora do loop: %p\t\t", aux);
	//printf("Roteador a conectar 1: %s\n", roteador);
	while(aux != NULL){
		if( strcmp(aux->item->nomeRot, roteador) == 0 ){
			//printf("Rot na lista: %s Endereco memoria na lista: %p | Rot q foi passado: %s Memoria: %p\t\t", aux->item->nomeRot, aux->item->nomeRot, roteador, roteador);
			//printf("aux dentro do loop: %p\n", aux);
			return(aux);
		}
		aux = aux->prox;
	}
	return(NULL);
}


//Como eu quero inserir no rot3 
CelRot* insereConexao(CelRot* original, CelRot* anexado){
	CelRot* novo = (CelRot*)malloc(sizeof(CelRot));

	//printf("Anexado: %s\nOriginal: %s\n", anexado->item->nomeRot, original->item->nomeRot);
	//novo->outrosRot = anexado;
	//novo->prox = NULL;
	//novo->prox = original;
	//printf("'prim': %p\n", original->prim);
	if(original->prim == NULL){
		//printf("Lista vazia - insere em 'prim' e 'ult':\n");
		original->prim = anexado;
		original->ult = anexado;
		//original->ult->prox = NULL;
		//printf("prim: %s\n", original->prim->item->nomeRot);
		//printf("ult: %s\n", original->ult->item->nomeRot);
	}
	else{
//		printf("Ha mais de 1 elemento - insere no final:\n");
		original->ult->prox = anexado;
		original->ult = anexado;
//		printf("ult: %s\n", original->ult->item->nomeRot);
	}
	printf("\n***********************************\n");
	return(original);
}

void imprimeSubListaRot(CelRot* aux){//Vai imprimir a lista a partir de uma celula presente na lista principal.
	printf("Memoria tmp2 dentro da imprime: %p\n", aux);
	CelRot* p = aux->prim;
	/*while(p != NULL){
		printf("%s\n", p->item->nomeRot);
		p = p->prim->prox;
	}*/
}

void conectaRoteador(ListRot* lstRot, char* rot1, char* rot2){
	CelRot* tmp1 = NULL;//Variavel que vai receber o ponteiro da celula de rot1, se ele existir na lista.
	CelRot* tmp2 = NULL;//Variavel que vai receber o ponteiro da celula de rot2, se ele existir na lista.
	//printf("Roteador a conectar 1: %s\n", rot1);
	//Efetua a busca na lista
	tmp1 = buscaRot(lstRot, rot1);
	tmp2 = buscaRot(lstRot, rot2);
	//
	//
	//
	//
	//TENHO QUE FAZER 'tmp1' SER SENTINELA DA LISTA Q/ VAI SURGIR DELE.
	//
	//
	//
	//
	if(tmp1 != NULL && tmp2 != NULL){//Para ser feita a conexao, os dois precisam existir na lista.
		CelRot* p = lstRot->prim;
		CelRot* ant;
		while(p != NULL){
			if( strcmp(p->item->nomeRot, rot1) == 0 ){
				//printf("Roteador 1: %s\n", p->item->nomeRot);
				p->outrosRot = tmp2;//Insere em 'outrosRot' o endereco de memoria do segundo roteador
				//printf("Outro roteador dentro do rot: %s\n", p->outrosRot->item->nomeRot);
			}//Agora irei fazer o enlace no caminho contrario
			if( strcmp(p->item->nomeRot, rot2) == 0 ){
				//printf("Roteador 2: %s\n", p->item->nomeRot);
				//p->outrosRot = tmp1;
				//printf("Outro roteador dentro do rot3: %s\n", p->outrosRot->item->nomeRot);

				//'tmp2' neste caso eh 'rot3' (em quem eu quero inserir), e o parametro passado dentro dele vai ser 'rot1' e todos que vierem em seguida.
				//printf("Memoria 'tmp2' antes: %p\n", tmp2);
				//printf("tmp2:\t %s\n", tmp2->item->nomeRot);
				//printf("tmp1:\t %s\n", tmp1->item->nomeRot);
				printf("Memoria tmp2 fora do imprime: %p\n", tmp2);
				tmp2 = insereConexao(tmp2, tmp1);
				imprimeSubListaRot(tmp2);
				//printf("Memoria 'tmp2' depois: %p\n", tmp2);
//				CelRot* j = tmp2;
				/*while(j != NULL){
					printf("Endadeamento das conexoes: %s\n", j->outrosRot->item->nomeRot);
					j = j->prox;
				}*/
			}
			p = p->prox;
		}
		//tmp1->outrosRot = tmp2;
		//printf("Memoria tmp1: %p Dentro outrosrot: %p Outros->prox: %p\tMemoria tmp2: %p\n***********************************\n", tmp1, tmp1->outrosRot, tmp1->outrosRot->prox, tmp2);
	}
	/*while(p != NULL){
		if( strcmp(p->item->nomeRot, rot1) == 0 ){
			printf("Memoria de 'p': %p\n", p);
		}
		p = p->prox;
	}*/
}
