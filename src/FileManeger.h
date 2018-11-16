#include <stdio.h>

typedef struct{
	char nome[40];
	int tipo;
	char valor[200];
}colunaNomeTipo;
typedef struct{
	char valor[200];
}valoresPrimarios;

int criarTabela(char* tabela);

int criarLinha(char* tabela);

int apagarValor(char* tabela);

int apagarTabela(char* tabela);
