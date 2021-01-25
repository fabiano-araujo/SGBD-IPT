#include <stdio.h>

typedef struct{
	char nome[40];
	int tipo;
	char valor[200];
}colunaNomeTipo;

typedef struct{
	char valor[200];
}valoresPrimarios;

typedef struct{
	char valor[40];
}valores;

valores **valor;

int criarTabela(char* tabela);

int criarLinha(char* tabela);

int apagarValor(char* tabela);

int apagarTabela(char* tabela);
