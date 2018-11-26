#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileManeger.h"
#include <ctype.h>
#include "database.h"


int criarTabela(char* tabela)
{


	char pasta[30] = "Tabelas/";
	strcat(pasta, tabela);
	strcat(pasta, ".txt");

	FILE* arq = fopen(pasta, "r");
	if (!arq)
	{
		fclose(arq);
	}
	else
	{
		printf("Tabela existente\n");
		fclose(arq);
		return 1;
	}

	FILE* arquivo = fopen(pasta, "a+");

	if(arquivo == NULL)printf("Erro ao Abrir Arquivo\n");
	else printf("Tudo OK ao abrir arquivo\n");


	FILE* tabelas = fopen("Tabelas/tabs.txt", "a+");

	if(arquivo == NULL)printf("Erro ao Abrir Arquivo\n");
	else printf("Tudo OK ao abrir arquivo\n");

	fseek(tabelas, 0, SEEK_END);
	fprintf(tabelas, "%s\n", tabela);

	fclose(tabelas);

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
	/*
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
						printf("Digite um novo nome para a tabela: ");
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
	*/
	
	//fseek(arquivo, 0, SEEK_END);

	

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

	//Escolha de opcao para chave primaria automatica
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
	else
	{
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
    
	while((c = fgetc(arquivo)) != EOF){
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
				strcpy(valor[posicaoC][posicaoL].valor, dado);
				contador = 0;
				printf("-%s\n", valor[posicaoC][posicaoL].valor);
				posicaoL++;
			}
			else if(c == '#')
			{
				contador = 0;
				pch = strtok(dado, "#");
				strcpy(valor[posicaoC][posicaoL].valor, dado);
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

	contador = 0;
	pch = strtok(dado, "i");
	strcpy(valor[posicaoC][posicaoL].valor, dado);
	contador = 0;
	printf("-%s\n", valor[posicaoC][posicaoL].valor);

	
	int j;
	printf("-> L: %d. C: %d\n", quantidadeLinhas, numeroDeColunas-48);
	for (i = 0; i < quantidadeLinhas; i++)
	{
		for (j = 0; j < numeroDeColunas-48; j++)
		{
			//printf("%12d %d", i, j);
			printf("%12s", valor[i][j].valor);
			setbuf(stdin, NULL);
		}
		printf("\n");
	}

	// printf("%s\n", valor[0][0].valor);
	// printf("%s\n", valor[0][1].valor);
	// printf("%s\n", valor[0][2].valor);

	// printf("%s\n", valor[1][0].valor);

	// printf("%s\n", valor[1][1].valor);

	// printf("%s\n", valor[1][2].valor);

	//printf("%s\n", colunas[0].nome);
	//printf("%d\n", colunas[0].tipo-48);
	//printf("%s\n", colunas[1].nome);
	//printf("%d\n", colunas[1].tipo-48);
	//printf("%s\n", colunas[2].nome);
	//printf("%d\n", colunas[2].tipo-48);
	//printf("%s\n", colunas[3].nome);
	//printf("%d\n", colunas[3].tipo-48);

	fseek(arquivo, 0, SEEK_END);
	int nPK;
	int bloquear = 0;
	char valorP[10];
	fprintf(arquivo, "#");
	if(strcmp(colunas[0].nome, "PrimaryKey") == 0)
	{
		printf("PrimaryKey automatica\n");

		for (i = 0; i < quantidadeLinhas; i++)
		{
			for (j = 0; j < quantidadeLinhas; j++)
			{
				nPK = atoi(valor[j][0].valor);
				printf("%4s      nPK: %4d.      i: %4d.      j:%4d\n", valor[j][0].valor, nPK, i, j);
				if (i == nPK)
				{
					printf("é igual\n");
					break;
				}
				else if(j+1 == quantidadeLinhas)
				{
					printf("%d\n", i);
					itoa(i, valorP, 10);
					strcat(valorP, ",");
					fprintf(arquivo, "%s", valorP);
					printf("%s\n", valorP);
					bloquear = 1;
					break;
				}
			}
			if(bloquear == 1)
			{
				printf("break!!!\n");
				break;
			}
			if (i+1 == quantidadeLinhas && bloquear == 0)
			{
				itoa(i+1, valorP, 10);
				strcat(valorP, ",");
				fprintf(arquivo, "%s", valorP);
				printf("%s\n", valorP);
			}
		}

		for (j = 1; j < numeroDeColunas-48; j++)
			{

				//Verificar se o valor Digitado é do valor escolhido para a coluna
				printf("%d = %s: ", j, colunas[j].nome);
				scanf("%s", &colunas[j].valor);
				


				if (j == numeroDeColunas-49)
				{
					// if (i == resposta-1)
					// {
						
					// }else{
					// 	strcat(colunas[j].valor, "#");
					// }
				}
				else
				{
					strcat(colunas[j].valor, ",");
				}
				fprintf(arquivo, "%s", colunas[j].valor);
				printf("%s\n", colunas[j].valor);
				setbuf(stdin, NULL);
		}
	}
	else{
		bloquear = 0;
		printf("PrimaryKey manual\n");
		for (j = 0; j < numeroDeColunas-48; j++)
			{
				printf("%d = %s: ", j, colunas[j].nome);
				scanf("%s", &colunas[j].valor);
				while(bloquear == 0)
				{
					for (i = 0; i < quantidadeLinhas; i++)
					{
						if (strcmp(valor[i][0].valor, &colunas[j].valor) == 0)
						{
							printf("Ja existe!\n");
							printf("Digitar outro valor: \n");
							printf("%d = %s: ", j, colunas[j].nome);
							scanf("%s", &colunas[j].valor);
							bloquear = 0;
							break;
						}
						else
						{
							bloquear = 1;
						}
					}
				}
				//Verificar se o valor Digitado é do valor escolhido para a coluna
				// printf("%d = %s: ", j, colunas[j].nome);
				// scanf("%s", &colunas[j].valor);
				


				if (j == numeroDeColunas-49)
				{
					// if (i == resposta-1)
					// {
						
					// }else{
					// 	strcat(colunas[j].valor, "#");
					// }
				}
				else{
					strcat(colunas[j].valor, ",");
				}
				fprintf(arquivo, "%s", colunas[j].valor);
				printf("%s\n", colunas[j].valor);
				setbuf(stdin, NULL);
		}
	}
	fclose(arquivo);
	
	
}
int apagarValor(char* tabela)
{

}
int apagarTabela(char* tabela)
{
	char pasta[30] = "Tabelas/";
	strcat(pasta, tabela);
	strcat(pasta, ".txt");
	int resultado;
	char *pch;

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
		resultado = remove(pasta);
		if (resultado == 0)
		{
			printf("Deletado com sucesso\n");
		}
		else
		{
			printf("Erro ao deletar\n");
		}
	}

	// FILE* arquivo = fopen(pasta, "a+");

	// if(arquivo == NULL)printf("Erro ao Abrir Arquivo\n");
	// else printf("Tudo OK ao abrir arquivo\n");



	FILE* tabelas = fopen("Tabelas/tabs.txt", "a+");
	if (tabelas == NULL)printf("Erro ao abrir arquivo\n");
	else printf("Tudo OK\n");
	

	int contador = 1;
	Valores* nomesDasTabelas = (Valores*) malloc(contador*sizeof(Valores));

	char nomeTabela[30];
	
	while(fgets(nomeTabela, sizeof(nomeTabela), tabelas) != NULL)
	{
		
		strcpy(nomesDasTabelas[contador-1].valor, nomeTabela);
		printf("%s", nomesDasTabelas[contador-1].valor);
		contador++;
		nomesDasTabelas = (Valores*) realloc(nomesDasTabelas, (contador+1)*sizeof(Valores));
	}

	fclose(tabelas);

	FILE* tabelasP = fopen("provisorio.txt", "a+");
	for (int i = 0; i < contador-1; i++)
	{
		pch = strtok(nomesDasTabelas[i].valor, "\n");
		if (strcmp(pch, tabela)==0)
		{
			printf("%s == %s\n", nomesDasTabelas[i].valor, tabela);
		}
		else
		{
			fprintf(tabelasP, "%s\n", pch);
		}
	}
	resultado = remove("Tabelas/tabs.txt");
	if (resultado == 0)
	{
		printf("Deletado com sucesso\n");
	}
	else
	{
		printf("Erro ao deletar\n");
	}

	free(nomesDasTabelas);
	fclose(tabelasP);
	system("ren provisorio.txt tabs.txt");
	system("move /Y tabs.txt Tabelas/");







	
	
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

/*================= O if bugado =====================*/
// if (c == '(' && vaiProsDados == 1);
// 		{
// 			mallocColunasDados = 1;
// 			printf("c: %c. ola %d\n", c, vaiProsDados);
// 			//nomeColunas =0;
// 		}




