/*Trabalho 1 - Estrutura de Dados 1
 *Dupla: Dener Silva Guimaraes e Tassio Santuchi
 	**************************************
 	***** IMPLEMENTACAO TAD CONEXAO ******
 	**************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*----- Estrutura das Conexoes -----*/

typedef struct tipoconexao TipoConexao;

struct tipoconexao{
    int num;
    int numramos;
};

typedef struct celconexao CelConexao;

struct celconexao{
    void* dispositivo;
    struct celconexao* prox;
};

