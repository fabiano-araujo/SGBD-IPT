#include <stdio.h>
#include <dirent.h>
#include "database.h"
#include "FileManeger.h"

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

int listarTodosDados(char* tabela)
{
	char pasta[30] = "Tabelas/";
	strcat(pasta, tabela);
	strcat(pasta, ".txt");

	FILE* arq = fopen(pasta, "r");
	if (!arq)
	{
		printf("Tabela inexistente\n");
		fclose(arq);
		return 1;
	}
	else
	{
		fclose(arq);
	}

	FILE* arquivo = fopen(pasta, "a+");

	if(arquivo == NULL)printf("Erro ao Abrir Arquivo\n");
	else printf("Tudo OK ao abrir arquivo\n");

	int contador = 0;
	int comecar = 0;
	int i;
	int encontrada = 0;
	int criarMalloc = 0;
	int numeroDeColunas = 0;
	int inicionomeColunas = 0;
	int nomeColunas = 0;
	int quantidadeColunas = 0;
	int tipoColuna = 0;
	int tipoDaColuna = 0;
	int valores = 0;
	int mallocColunasDados = 0;
	int mallocDados = 0;
	int dados = 0;
	int posicaoL = 0;
	int posicaoC = 0;
	int vaiProsDados = 0;
	int contMatriz = 1;
	int quantidadeLinhas = 1;
	char dado[20];
	char nomeTabela[42];
	char nomesColunas[40];
	char *pch;
	char c;
	int coluna = 0;
	colunaNomeTipo* colunas;


	//          COM FSCANF
	//fscanf(arquivo, "@%s:", &nomeTabela);
	//printf("%s\n", nomeTabela);

    //          COM FGETC
    
	while((c = fgetc(arquivo)) != EOF)
	{

		//printf("%c", c);
		// if(c == "\0")
		// {
		// 	contador = 0;
		// 	pch = strtok(dado, "i");
		// 	strcpy(valor[posicaoC][posicaoL].valor, dado);
		// 	contador = 0;
		// 	dados = 0;
		// 	printf("-%s\n", valor[posicaoC][posicaoL].valor);
		// }
		if (dados == 1)
		{
			dado[contador]=c;
			contador++;
			if(c == ',')
			{
				contador = 0;
				pch = strtok(dado, ",");
				strcpy(valor[posicaoC][posicaoL].valor, pch);
				contador = 0;
				printf("-%s\n", valor[posicaoC][posicaoL].valor);
				posicaoL++;
			}
			else if(c == '#')
			{
				contador = 0;
				pch = strtok(dado, "#");
				strcpy(valor[posicaoC][posicaoL].valor, pch);
				contador = 0;
				printf("-%s\n", valor[posicaoC][posicaoL].valor);
				posicaoL=0;
				quantidadeLinhas++;

				contMatriz++;
				valor = (variaveis**) realloc(valor,contMatriz*sizeof(variaveis*));
				valor[contMatriz-1] = (variaveis*)malloc(numeroDeColunas*sizeof(variaveis));
				posicaoC++;

			}
			
		}
		if (vaiProsDados == 1 && c == '(')
		{
			//printf("%d %c\n", vaiProsDados, c);
			mallocColunasDados = 1;
		}
		if (mallocColunasDados == 1)
		{
			valor = (variaveis**) malloc(contMatriz*sizeof(variaveis*));
			mallocDados = 1;
			mallocColunasDados = 0;
		}
		if (mallocDados == 1)
		{
			valor[0] = (variaveis*)malloc(numeroDeColunas*sizeof(variaveis));
			mallocDados = 0;
			dados = 1;
		}


		if (tipoDaColuna == 1)
		{
			colunas[coluna].tipo = (int)c;
			printf("%c, coluna = %d\n", colunas[coluna].tipo, coluna);
			coluna++;
			tipoDaColuna = 0;
			//printf("coluna = %d, numeroDeColunas == %d\n", coluna+1, numeroDeColunas-48);
			if (coluna == numeroDeColunas-48)
			{
				encontrada = 0;
				vaiProsDados = 1;
				//printf("encontrada = %d\n", encontrada);
			}
			//printf("%d, numeroDeColunas: %d\n", nomeColunas, numeroDeColunas-48);
		}
		//if(tipoColuna == 1 && encontrada == 1)
		//{
		//	tipoDaColuna = 1;
		//	tipoColuna = 0;
		//}
		

		if (nomeColunas == 1 && encontrada == 1)
		{
			nomesColunas[contador] = c;
			contador++;
			//printf("c: %c. nomesColunas: %s. contador: %d ", c, nomesColunas, contador);
			//printf("passou3\n");
			if(c == '!')
			{
				contador = 0;
				//printf("Passou4\n");
				pch = strtok(nomesColunas, "!");
				//printf("pch %s nomesColunas %s\n", pch, nomesColunas);
				strcpy(colunas[coluna].nome,pch);
				printf("%s\n", colunas[coluna].nome);
				nomeColunas = 0;
				tipoDaColuna = 1;
				//printf("Passou5\n");
			}
		}

		if (inicionomeColunas == 1 && c == ':' && encontrada == 1)
		{
			nomeColunas = 1;
			inicionomeColunas = 0;
			//printf("passou2\n");
		}
		if (c == '-' && encontrada == 1)
		{
			nomeColunas = 1;
		}
		
		if (quantidadeColunas == 1)
		{
			printf("%c\n", c);
			numeroDeColunas = (int)c;
			quantidadeColunas = 0;
			if (criarMalloc != 2)
			{
				criarMalloc = 1;
			}
			inicionomeColunas = 1;
			//printf("Passou1\n");
		}
		if (criarMalloc == 1)
		{
			colunas = (colunaNomeTipo*) malloc(numeroDeColunas*sizeof(colunaNomeTipo));
			if (colunas == NULL)
			{
				printf("malloc colunas BAD\n");
			}
			else{
				printf("malloc colunas ok\n");
			}
			criarMalloc = 2;
		}
		//if (nomeColunas == 1)
		//{
		//	
		//}
		if (comecar == 1)
		{
			//printf("%c", c);
			//printf("Passou no while\n");
			nomeTabela[contador] = c;
			contador++;
			if (c == ':')
			{
				comecar = 0;
				contador = 0;
				pch = strtok(nomeTabela, ":");
				//printf("%s == %s, %s\n", tabela, pch, nomeTabela);

				printf("Pronto\n");
				quantidadeColunas = 1;
				encontrada = 1;
					//printf("%s\n", nomeTabela);
					//strcpy(nomeTabela, vetorVazio);
					//memset(nomeTabela,'', 42);
					//printf("%s\n", nomeTabela);

					//setbuf(stdout, NULL);
					//fflush(stdout);
			}
		}
		if (c == '@')
		{
			comecar = 1;
			printf("1\n");
		}
		if (c == ';' && encontrada == 1)
		{
			//printf("2\n");
			break;
		}
	}

	//setbuf(stdin, NULL);

	int len;
	int tamanho;
	char str[15];
	strcpy(str, dado);
	//contador = 0;
	printf("dado: %s\n", dado);
	printf("%d\n", contador);
	//pch = strtok(str, "p");
	len = strxfrm(pch, str, contador);
	//strcpy(valor[posicaoC][posicaoL].valor, ptr);
	//printf("%s\n", ptr);
		//contador = 0;
	strcpy(valor[posicaoC][posicaoL].valor, pch);
	
	printf("Tamanho: %d. len: %d\n", tamanho, len);
	printf("-%s\n", valor[posicaoC][posicaoL].valor);

	
	int j;
	printf("-> L: %d. C: %d\n", quantidadeLinhas, numeroDeColunas-48);
	for (i = 0; i < quantidadeLinhas; i++)
	{
		for (j = 0; j < numeroDeColunas-48; j++)
		{
			//printf("%12d %d", i, j);
			printf("%12s", valor[i][j].valor);
		}
		printf("\n");
	}
	printf("%s\n", valor[3][2].valor);
	setbuf(stdin, NULL);
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