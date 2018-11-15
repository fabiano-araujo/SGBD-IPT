#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileManeger.h"
#include <ctype.h>


int criarTabela(char* tabela)
{
	char nomeTabela[42] = "@";
	char quantidadeColunas[10];
	char nomeDaColuna[40];
	char tipoDaColuna[10];
	char* nomeDoTipo[10];
	int contador=0;
	int resposta;
	int numeroDeColunas;
	int tipo;
	char tipoStr[20];
	char valor[200];
	int i, j;

	FILE* arquivo = fopen("Tabela/Tabelas.txt", "a+");
	fseek(arquivo, 0, SEEK_END);

	if(arquivo == NULL)printf("Erro ao Abrir Arquivo\n");
	else printf("Tudo OK ao abrir arquivo\n");

	//Nome databela
	strcat(nomeTabela, tabela);
	strcat(nomeTabela, ":");

	fprintf(arquivo, "%s", nomeTabela);

	//quantidade de Colunas
	printf("Quantas Colunas deseja? ");
	scanf("%s", &quantidadeColunas);

	numeroDeColunas = atoi(quantidadeColunas);//Função nova

	strcat(quantidadeColunas, ":");

	fprintf(arquivo, "%s", quantidadeColunas);
	colunaNomeTipo* colunas = (colunaNomeTipo*) malloc(numeroDeColunas*sizeof(colunaNomeTipo));

	//Decidindo se tera chave primaria automatica o de preferencia do usuario;
	printf("Deseja escolher a chave primaria?(1 = yes, 0 = no) ");
	scanf("%d", &resposta);
	if (resposta == 0)
	{	
		//Chave primaria automatica
		//Obtendo nome e tipo da coluna
		fprintf(arquivo, "PrimaryKey!2-");
		while(contador<numeroDeColunas){
			char formatando[45] = "";
			tipo = 6;

			printf("Nome da coluna %d: ", contador+1);
			scanf("%s", &nomeDaColuna);
			strcpy(colunas[contador].nome, nomeDaColuna);

			//printf("Passou em\n");
			strcat(formatando, nomeDaColuna);

			strcat(formatando, "!");
			
			//printf("%s\n", colunas[contador].nome);

			//printf("passou tbm\n");
			while(tipo < 1 || tipo > 5){
				printf("Tipo da coluna(Digitar 1 - char, 2 - int, 3 - float, 4 - double, 5 - string):");
				scanf("%d", &tipo);
				if (tipo == 1 || tipo == 2 || tipo == 3 || tipo == 4 || tipo == 5)
				{
					printf("pronto\n");
				}
				else{
					printf("Valor invalido\n");
				}
			}
			colunas[contador].tipo = tipo;
			itoa(tipo, tipoStr, 10);//funcao nova

			strcat(formatando, tipoStr);
			strcat(formatando, "-");

			fprintf(arquivo, "%s", formatando);
			printf("Armazenado %d\n", contador);
			//fflush(stdout);
			//fflush(stdin);
			contador++;
		}
	fprintf(arquivo, "(");

	printf("Quantidade de Linhas: ");
	scanf("%d", &resposta);

	for (i = 0; i < resposta; i++)
	{
		char chavePrimaria[10] = "";
		itoa(i, chavePrimaria, 10);
		strcat(chavePrimaria, ",");
		fprintf(arquivo, "%s", chavePrimaria);
		printf("Linha %d\n", i+1);

		for (j = 0; j < numeroDeColunas; j++)
		{

			printf("%d = %s: ", j, colunas[j].nome);
			scanf("%s", &valor);
			if (j == numeroDeColunas-1)
			{
				if (i == resposta-1)
				{
					strcat(valor, ")");
				}else{
					strcat(valor, ".");
				}
			}
			else{
				strcat(valor, ",");
			}
			fprintf(arquivo, "%s", valor);
			setbuf(stdin, NULL);
		}
	}


	}



	else{
		char formatandoPK[] = "";
		printf("ATENCAO: a chave primaria precisa ser a primeira coluna!\nsendo Obrigatoriamente do tipo INT\n");
		printf("nome da Coluna que sera a chave primaria: ");
		scanf("%s", &nomeDaColuna);
		strcpy(colunas[contador].nome, nomeDaColuna);
		colunas[contador].tipo = 2;
		strcpy(formatandoPK, nomeDaColuna);
		strcat(formatandoPK, "!2-");

		fprintf(arquivo, "%s", formatandoPK);


		//repetido
		contador++;
		while(contador<numeroDeColunas){
			char formatando[45] = "";
			tipo = 6;

			printf("Nome da coluna %d: ", contador+1);
			scanf("%s", &nomeDaColuna);
			strcpy(colunas[contador].nome, nomeDaColuna);

			//printf("Passou em\n");
			strcat(formatando, nomeDaColuna);

			strcat(formatando, "!");
			
			//printf("%s\n", colunas[contador].nome);

			//printf("passou tbm\n");
			while(tipo < 1 || tipo > 5){
				printf("Tipo da coluna(Digitar 1 - char, 2 - int, 3 - float, 4 - double, 5 - string):");
				scanf("%d", &tipo);
				if (tipo == 1 || tipo == 2 || tipo == 3 || tipo == 4 || tipo == 5)
				{
					printf("pronto\n");
				}
				else{
					printf("Valor invalido\n");
				}
			}
			colunas[contador].tipo = tipo;
			itoa(tipo, tipoStr, 10);//funcao nova

			strcat(formatando, tipoStr);
			strcat(formatando, "-");

			fprintf(arquivo, "%s", formatando);
			printf("Armazenado %d\n", contador);
			//fflush(stdout);
			//fflush(stdin);
			contador++;		
		}
	fprintf(arquivo, "(");

	printf("Quantidade de Linhas: ");
	scanf("%d", &resposta);

	for (i = 0; i < resposta; i++)
	{
		printf("Linha %d\n", i+1);

		for (j = 0; j < numeroDeColunas; j++)
		{

			printf("%d = %s: ", j, colunas[j].nome);
			scanf("%s", &valor);
			if (j == numeroDeColunas-1)
			{
				if (i == resposta-1)
				{
					strcat(valor, ")");
				}else{
					strcat(valor, ".");
				}
			}
			else{
				strcat(valor, ",");
			}
			fprintf(arquivo, "%s", valor);
			setbuf(stdin, NULL);
		}
	}

	}









	//Receber os dados quando a chave primaria é automatica
	
	printf("%s\n", nomeTabela);
	printf("%d\n", numeroDeColunas);

	fflush(stdout);
	fprintf(arquivo, ";");
	fprintf(arquivo, "\n");
	fclose(arquivo);
}


int criarLinha(char* tabela)
{

}
int apagarValor(char* tabela)
{

}
int apagarTabela(char* tabela)
{

}



















char* verificarTipo(int Tipo)
{
	//if (Tipo == 1)
	//{
		char* nomeDoTipo = "CHAR";
		return nomeDoTipo;
	//}


	//----------------------Talvez vá pro lixo------------------------\\
	//int tamanho;
	//tamanho = strlen(*nomeDoTipo);
	/*
	char t_char[4] = "CHAR";
	char t_int[3] = "INT";
	char t_float[5] = "FLOAT";
	char t_double[6] = "DOUBLE";
	char t_string[6] = "STRING";
	for (int i = 0; i < 6; i++)
	{
		//printf("1\n");
		if(!(isupper(*(nomeDoTipo+i))))
       {
       		//printf("2\n");
           *(nomeDoTipo+i)=toupper(*(nomeDoTipo+i));
       }
	}
	printf("%s\n", nomeDoTipo);
	if(strcmp(nomeDoTipo,t_char) == 0){
		return 0;
	}
	else if(strcmp(nomeDoTipo,t_int) == 0){
		return 1;
	}
	else if(strcmp(nomeDoTipo,t_float) == 0){
		return 2;
	}
	else if(strcmp(nomeDoTipo,t_double) == 0){
		return 3;
	}
	else if(strcmp(nomeDoTipo, t_string) == 0){
		return 4;
	}
	else{
		printf("Tipo invalido\n");
		return 5;
	}
	*/
}