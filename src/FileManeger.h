#include <stdio.h>

typedef struct{
	char nome[40];
	int tipo;
}colunaNomeTipo;

int criarTabela(char* tabela);

int criarLinha(char* tabela);

int apagarValor(char* tabela);

int apagarTabela(char* tabela);
