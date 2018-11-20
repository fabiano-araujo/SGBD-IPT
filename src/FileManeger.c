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
	//char tipoDaColuna[10];
	//char* nomeDoTipo[10];
	int contador=0;
	int resposta;
	int numeroDeColunas;
	int tipo;
	char tipoStr[20];
	char valor[200];
	int i, j, k;

	//Verificar se a tabela ja existe
	int contador2 = 0;
	int comecar = 0;
	char nomeDaTabela[42];
	char *pch;
	char c;
	int saida = 0;
	FILE* arquivo = fopen("Tabela/Tabelas.txt", "a+");
	while(saida != 1){
		fseek(arquivo, 0, SEEK_SET);
		while((c = fgetc(arquivo)) != EOF){
			if (comecar == 1)
			{
				nomeDaTabela[contador2] = c;
				contador2++;
				if (c == ':')
				{
					comecar = 0;
					contador2 = 0;
					pch = strtok(nomeDaTabela, ":");
					//printf("%s == %s, %s\n", tabela, pch, nomeDaTabela);

					if(strcmp(tabela, nomeDaTabela)==0){
						printf("Tabela ja existe\n");
						printf("Digite um novo nome para a tabela:\n");
						scanf("%s", tabela);
						//printf("%s\n", tabela);
						saida = 0;
						break;
						//setbuf(stdout, NULL);
						//fflush(stdout);
					}else{
						saida = 1;
					}
				}
			}
			if (c == '@')
			{
				comecar = 1;	
			}
		}
	}
	
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


	colunaNomeTipo* colunas = (colunaNomeTipo*) malloc(numeroDeColunas*sizeof(colunaNomeTipo));

	//Decidindo se tera chave primaria automatica ou de preferencia do usuario;
	printf("Deseja escolher a chave primaria?(1 = yes, 0 = no) ");
	scanf("%d", &resposta);
	if (resposta == 0)
	{	
		itoa(numeroDeColunas+1, quantidadeColunas, 10);
		strcat(quantidadeColunas, ":");

		fprintf(arquivo, "%s", quantidadeColunas);
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
					//printf("pronto\n");
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
			//printf("Armazenado %d\n", contador);
			//fflush(stdout);
			//fflush(stdin);
			contador++;
		}
		fprintf(arquivo, "(");

		printf("Quantidade de Linhas inicialmente: ");
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

				//Verificar se o valor Digitado é do valor escolhido para a coluna
				printf("%d = %s: ", j, colunas[j].nome);
				scanf("%s", &colunas[j].valor);
				


				if (j == numeroDeColunas-1)
				{
					if (i == resposta-1)
					{
						
					}else{
						strcat(colunas[j].valor, "#");
					}
				}
				else{
					strcat(colunas[j].valor, ",");
				}
				fprintf(arquivo, "%s", colunas[j].valor);
				setbuf(stdin, NULL);
			}
		}


	}


	//Escolha de opcao para chave primaria manual
	else{
		strcat(quantidadeColunas, ":");

		fprintf(arquivo, "%s", quantidadeColunas);
		char formatandoPK[] = "";
		printf("\nATENCAO: a chave primaria precisa ser a primeira coluna!\nsendo Obrigatoriamente do tipo INT\n");
		printf("Nome da Coluna que sera a chave primaria: ");
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

			printf("\nNome da coluna %d: ", contador+1);
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
					//printf("pronto\n");
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
			//printf("Armazenado %d\n", contador);
			//fflush(stdout);
			//fflush(stdin);
			contador++;		
		}
		fprintf(arquivo, "(");

		printf("Quantidade de Linhas inicialmente: ");
		scanf("%d", &resposta);

		//Pegando os dados

		valoresPrimarios* valorPrimario = (valoresPrimarios*) malloc(resposta*sizeof(valoresPrimarios));
		for (i = 0; i < resposta; i++)
		{
			printf("Linha %d\n", i+1);

			for (j = 0; j < numeroDeColunas; j++)
			{
				printf("%d = %s: ", j, colunas[j].nome);
				scanf("%s", &colunas[j].valor);
				if (j == 0)
				{
					saida = 0;
					while(saida != 1){
						strcpy(valorPrimario[i].valor, colunas[j].valor);
						for (k = 0; k < resposta; k++)
						{
							if (k != i)
							{
								if (strcmp(valorPrimario[k].valor, valorPrimario[i].valor)==0)
								{
									printf("Ja existe!\n");
									printf("Digitar outro valor: \n");
									printf("%d = %s: ", j, colunas[j].nome);
									scanf("%s", &colunas[j].valor);
									saida = 0;
									break;
								}
								else{
									saida = 1;
								}
							}
						}
					}
				}

				if (j == numeroDeColunas-1)
				{
					if (i == resposta-1)
					{
						
					}else{
						strcat(colunas[j].valor, "#");
					}
				}
				else{
					strcat(colunas[j].valor, ",");
				}
				fprintf(arquivo, "%s", colunas[j].valor);
				setbuf(stdin, NULL);
			}
		}

	}
	
	
	printf("%s\n", nomeTabela);
	printf("%d\n", numeroDeColunas);

	fflush(stdout);
	fprintf(arquivo, ");");
	fprintf(arquivo, "\n");
	fclose(arquivo);
}



//======================================CRIAR LINHA=====================================//


int criarLinha(char* tabela)
{
	FILE* arquivo = fopen("Tabela/Tabelas.txt", "a+");
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
	char nomeTabela[42];
	char nomesColunas[40];
	char *pch;
	char c;
	int coluna = 0;
	colunaNomeTipo* colunas;


	if(arquivo == NULL)printf("Erro ao Abrir Arquivo\n");
	else printf("Tudo OK ao abrir arquivo\n");

	//          COM FSCANF
	//fscanf(arquivo, "@%s:", &nomeTabela);
	//printf("%s\n", nomeTabela);

    //          COM FGETC
    
	while((c = fgetc(arquivo)) != EOF){
		//printf("%c", c);
		if (valores == 1)
		{
			
		}
		if (tipoDaColuna == 1)
		{
			colunas[coluna].tipo = (int)c;
			printf("%c, coluna = %d\n", colunas[coluna].tipo, coluna);
			coluna++;
			tipoDaColuna = 0;
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
			if(c == '!')
			{
				contador = 0;
				pch = strtok(nomesColunas, "!");
				strcpy(colunas[coluna].nome,pch);
				printf("%s\n", colunas[coluna].nome);
				nomeColunas = 0;
				tipoDaColuna = 1;
			}
		}

		if (inicionomeColunas == 1 && c == ':' && encontrada == 1)
		{
			nomeColunas = 1;
			inicionomeColunas = 0;
		}
		if (c == '(' && encontrada == 1);
		{
			valores = 1;
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
		}
		if (criarMalloc == 1)
		{
			colunas = (colunaNomeTipo*) malloc(numeroDeColunas*sizeof(colunaNomeTipo));
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
				printf("%s == %s, %s\n", tabela, pch, nomeTabela);

				if(strcmp(tabela, nomeTabela)==0){
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
	fclose(arquivo);
	//printf("%s\n", colunas[0].nome);
	//printf("%d\n", colunas[0].tipo-48);
	//printf("%s\n", colunas[1].nome);
	//printf("%d\n", colunas[1].tipo-48);
	//printf("%s\n", colunas[2].nome);
	//printf("%d\n", colunas[2].tipo-48);
	//printf("%s\n", colunas[3].nome);
	//printf("%d\n", colunas[3].tipo-48);
	
	
	
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




//=============================Procura tabela===========================//

/*
FILE* arquivo = fopen("Tabela/Tabelas.txt", "a+");
	int contador = 0;
	int comecar = 0;
	int i;
	char nomeTabela[42];
	char *pch;

	if(arquivo == NULL)printf("Erro ao Abrir Arquivo\n");
	else printf("Tudo OK ao abrir arquivo\n");
    
	while((c = fgetc(arquivo)) != EOF){

		if (comecar == 1)
		{
			nomeTabela[contador] = c;
			contador++;
			if (c == ':')
			{
				comecar = 0;
				contador = 0;
				pch = strtok(nomeTabela, ":");
				printf("%s == %s, %s\n", tabela, pch, nomeTabela);

				if(strcmp(tabela, nomeTabela)==0){
					printf("Pronto\n");

					setbuf(stdout, NULL);
					fflush(stdout);
				}
			}
		}
		if (c == '@')
		{
			comecar = 1;	
		}
	}
*/