# tadNetMap/*Trabalho 1 - Estrutura de Dados 1
 *Dupla: Dener Silva Guimaraes e Tassio Santuchi
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tadroteador.h"
#include "tadterminal.h"
#include "tadconexao.h"
#define TAM 41

int main(){
	FILE* arq;//Declaracao da variavel do tipo FILE* para o arquivo de entrada.

	char comando[TAM];
	char roteador[TAM];
	char roteador2[TAM];
	char nome_operadora[TAM];
	char terminal[TAM];
	char nome_localidade[TAM];

	ListRot* lst = inicializaListaRot();//Inicializa a lista de roteadores vazia.
	ListTerminais* lstTerminais = inicializaListaTerminais();//Inicializa a lista de terminais vazia.

	arq = fopen("entradaNetMap.txt", "r");
	if(arq == NULL){
		printf("ERRO: arquivo inexistente ou nao encontrado!\n");
		exit(1);
	}
	do{
		fscanf(arq, "%s", comando);//Efetua a leitura do comando dado no arquivo de entrada.
		//printf("%s", comando);
		if( strcmp(comando, "CADASTRAROTEADOR") == 0){
			fscanf(arq, "%s %s", roteador, nome_operadora);
			//printf("ROTEADOR: %s; OPERADORA: %s\n", roteador, nome_operadora);
			lst = cadastraRoteador(lst, roteador, nome_operadora);
		}
		else if( strcmp(comando, "CADASTRATERMINAL") == 0){
			fscanf(arq, "%s %s", terminal, nome_localidade);
			//printf("TERMINAL: %s; CIDADE: %s\n", terminal, nome_localidade);
			lstTerminais = cadastraTerminal(lstTerminais, terminal, nome_localidade);
		}
		else if( strcmp(comando, "REMOVEROTEADOR") == 0){
			fscanf(arq, "%s", roteador);
			//removeRoteador(lst, roteador);
			//printf("Entrou na REMOVEROTEADOR: %s\n", roteador);
		}
		else if( strcmp(comando, "REMOVETERMINAL") == 0){
			fscanf(arq, "%s", terminal);
			//printf("TERMINAL: %s\n", terminal);
			//removeTerminal(lstTerminais, terminal);
		}
		else if( strcmp(comando, "CONECTAROTEADORES") == 0){
			fscanf(arq, "%s %s", roteador, roteador2);
			//printf("ROTEADOR1: %s ROTEADOR2: %s\n", roteador, roteador2);
			conectaRoteador(lst, roteador, roteador2);
		}
		else if( strcmp(comando, "CONECTATERMINAL") == 0){
			//printf("Entrou na CONECTATERMINAL\n");
		}
		else if( strcmp(comando, "IMPRIMENETMAP") == 0){
			//printf("Entrou na IMPRIMENETMAP\n");
		}
		else if( strcmp(comando, "DESCONECTAROTEADORES") == 0){
			//printf("Entrou na DESCONECTAROTEADORES\n");
		}
		else if( strcmp(comando, "DESCONECTATERMINAL") == 0){
			//printf("Entrou na DESCONECTATERMINAL\n");
		}
		else if( strcmp(comando, "FREQUENCIAOPERADORA") == 0){
			//printf("Entrou na FREQUENCIAOPERADORA\n");
		}
		else if( strcmp(comando, "FREQUENCIATERMINAL") == 0){
			//printf("Entrou na FREQUENCIATERMINAL\n");
		}
		else if( strcmp(comando, "ENVIARPACOTESDADOS") == 0){
			//printf("Entrou na ENVIARPACOTESDADOS\n");
		}
	}while( strcmp(comando, "FIM") != 0 );

	//imprimeRoteadores(lst);
	//imprimeTerminais(lstTerminais);

	fclose(arq);

	return 0;
}

