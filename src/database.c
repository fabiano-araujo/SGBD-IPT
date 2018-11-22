#include <stdio.h>
#include <dirent.h>
#include "database.h"

int listarTabelas()
{

	FILE* tabelas = fopen("Tabelas/tabs.txt", "a+");
	if (tabelas == NULL)printf("Erro ao abrir arquivo\n");
	else printf("Tudo OK\n");
	//fseek(tabelas, 0, SEEK_END);

	int contador = 1;
	Valores* nomesDasTabelas = (Valores*) malloc(contador*sizeof(Valores));

	char nomeTabela[30];
	
	while(fgets(nomeTabela, sizeof(nomeTabela), tabelas) != NULL)
	{
		
		strcpy(nomesDasTabelas[contador].valor, nomeTabela);
		printf("%s", nomesDasTabelas[contador].valor);
		contador++;
		nomesDasTabelas = (Valores*) realloc(nomesDasTabelas, (contador+1)*sizeof(Valores));
	}
	free(nomesDasTabelas);




	// FILE* arquivo = fopen("Tabela/Tabelas.txt", "a+");
	// int contador = 0;
	// int comecar = 0;
	// int i;
	// char nomeTabela[42];
	// char *pch;
	// char c;
	// struct dirent **namelist;
	// int n;
	// FILE* arquivo = fopen("Tabela/Tabelas.txt", "a+");
	// int contador = 0;
	// int comecar = 0;
	// int i;
	// char nomeTabela[42];
	// char *pch;
	// char c;
	// struct dirent **namelist;
	// int n;


	//if(arquivo == NULL)printf("Erro ao Abrir Arquivo\n");
	//else printf("Tudo OK ao abrir arquivo\n");
    
// 	while((c = fgetc(arquivo)) != EOF){
// 		if (comecar == 1)
// 		{
// 		nomeTabela[contador] = c;
// 		contador++;
// 			if (c == ':')
// 		{
// 				comecar = 0;
// 				contador = 0;
// 				pch = strtok(nomeTabela, ":");
// 				printf(" %s\n", pch);
// 			}
// 		}
// 		if (c == '@')
// 		{
// 			comecar = 1;	
// 		}
// 	}
}

int listarTodosDados()
{

}
int pesquisarValor()
{
	int tipo;
	printf("Tipo do tipo a ser procurado: ");
	printf("1 - INT\n2 - DOUBLE\n3 - FLOAT\n4 - STRING\n5 - CHAR\n");
	scanf("%d", &tipo);
	switch(tipo)
	{
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		default:
			printf("Fora dos limites\n");
	}
}