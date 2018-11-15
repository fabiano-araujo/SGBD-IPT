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
	int contador=0;
	int resposta;
	int numeroDeColunas;
	int tipo;
	char tipoStr[20];

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
		fprintf(arquivo, "KeyPrimary!1-");
		while(contador<numeroDeColunas){
			char formatando[45] = "";
			tipo = 6;
			printf("Nome da coluna %d: ", contador+1);
			scanf("%s", &nomeDaColuna);
			*(colunas+contador)->nome = nomeDaColuna;
			printf("Passou em\n");
			strcat(formatando, nomeDaColuna);
			strcat(formatando, "!");
			
			printf("%s\n", (colunas+contador)->nome);
			printf("passou tbm\n");
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
			itoa(tipo, tipoStr, 10);//funcao nova

			strcat(formatando, tipoStr);
			strcat(formatando, "-");

			fprintf(arquivo, "%s", formatando);
			printf("Armazenado %d\n", contador);
			fflush(stdout);
			fflush(stdin);
			contador++;
		}

	}
	else{

	}


	printf("%s\n", nomeTabela);
	printf("%d\n", numeroDeColunas);

	fflush(stdout);
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







int verificarTipo(int Tipo)
{
	































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