#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileManeger.h"
#include <ctype.h>
#include "database.h"

/*
	cria a tabela com suas colunas e os dados se for de sua escolha
	os nomes das tabelas são armazenados em um arquivo separado para leitura da função listarTabelas
*/
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

	FILE* tabelas = fopen("Tabelas/tabs.txt", "a+");
	if(arquivo == NULL)printf("Erro ao Abrir Arquivo\n");

	fseek(tabelas, 0, SEEK_END);
	fprintf(tabelas, "%s\n", tabela);

	fclose(tabelas);

	char nomeTabela[42] = "@";
	char quantidadeColunas[10];
	char nomeDaColuna[40];
	int contador=0;
	int resposta;
	int numeroDeColunas;
	int tipo;
	char tipoStr[20];
	char valor[200];
	int i, j, k;
	int contador2 = 0;
	int comecar = 0;
	char nomeDaTabela[42];
	char *pch;
	char c;
	int saida = 0;
	strcat(nomeTabela, tabela);
	strcat(nomeTabela, ":");

	fprintf(arquivo, "%s", nomeTabela);

	//quantidade de Colunas

	printf("Quantas Colunas deseja? ");
	scanf("%s", &quantidadeColunas);

	numeroDeColunas = atoi(quantidadeColunas);


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

		//Obtendo nome e tipo da coluna
		fprintf(arquivo, "PrimaryKey!2-");
		while(contador<numeroDeColunas)
		{
			char formatando[45] = "";
			tipo = 6;

			printf("Nome da coluna %d: ", contador+1);
			scanf("%s", &nomeDaColuna);
			strcpy(colunas[contador].nome, nomeDaColuna);

			strcat(formatando, nomeDaColuna);

			strcat(formatando, "!");

			while(tipo < 1 || tipo > 5)
			{
				printf("Tipo da coluna(Digitar 1 - char, 2 - int, 3 - float, 4 - double, 5 - string):");
				scanf("%d", &tipo);
				if (tipo == 1 || tipo == 2 || tipo == 3 || tipo == 4 || tipo == 5)
				{

				}
				else
				{
					printf("Valor invalido\n");
				}
			}
			colunas[contador].tipo = tipo;
			itoa(tipo, tipoStr, 10);

			strcat(formatando, tipoStr);
			strcat(formatando, "-");
			fprintf(arquivo, "%s", formatando);

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
				printf("%d = %s: ", j, colunas[j].nome);
				scanf("%s", &colunas[j].valor);
				if (j == numeroDeColunas-1)
				{
					if (i == resposta-1)
					{
						
					}else
					{
						strcat(colunas[j].valor, "#");
					}
				}
				else
				{
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

		contador++;
		while(contador<numeroDeColunas)
		{
			char formatando[45] = "";
			tipo = 6;

			printf("\nNome da coluna %d: ", contador+1);
			scanf("%s", &nomeDaColuna);
			strcpy(colunas[contador].nome, nomeDaColuna);

			strcat(formatando, nomeDaColuna);

			strcat(formatando, "!");
			
			while(tipo < 1 || tipo > 5)
			{
				printf("Tipo da coluna(Digitar 1 - char, 2 - int, 3 - float, 4 - double, 5 - string):");
				scanf("%d", &tipo);

				if (tipo == 1 || tipo == 2 || tipo == 3 || tipo == 4 || tipo == 5)
				{

				}
				else
				{
					printf("Valor invalido\n");
				}
			}
			colunas[contador].tipo = tipo;
			itoa(tipo, tipoStr, 10);

			strcat(formatando, tipoStr);
			strcat(formatando, "-");
			fprintf(arquivo, "%s", formatando);

			contador++;		
		}

		fprintf(arquivo, "(");

		printf("Quantidade de Linhas inicialmente: ");
		scanf("%d", &resposta);

		//Solicitar e armazenar os dados

		valoresPrimarios* valorPrimario = (valoresPrimarios*) malloc(resposta*sizeof(valoresPrimarios));
		for (i = 0; i < resposta; i++)
		{
			printf("Linha %d\n", i+1);

			for (j = 0; j < numeroDeColunas; j++)
			{
				printf("%s: ", j, colunas[j].nome);
				scanf("%s", &colunas[j].valor);
				if (j == 0)
				{
					saida = 0;
					while(saida != 1)
					{
						strcpy(valorPrimario[i].valor, colunas[j].valor);
						for (k = 0; k < resposta; k++)
						{
							if (k != i)
							{
								if (strcmp(valorPrimario[k].valor, valorPrimario[i].valor)==0)
								{
									printf("Ja existe!\n");
									printf("Digitar outro valor: \n");
									printf("%s: ", colunas[j].nome);
									scanf("%s", &colunas[j].valor);
									saida = 0;
									break;
								}
								else
								{
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
						
					}else
					{
						strcat(colunas[j].valor, "#");
					}
				}
				else
				{
					strcat(colunas[j].valor, ",");
				}
				fprintf(arquivo, "%s", colunas[j].valor);
				setbuf(stdin, NULL);
			}
		}
	}
	
	fflush(stdout);
	fclose(arquivo);
}
/* 
		ler cada valor da tabela escolhida e armazena em uma matriz de struct, 
		a matriz sofre realloc a cada linha lida no arquivo almentando seu tamanho sem valor pre-definido.
		Como a função trabalha passando de caracter em caracter foi-se necessario a uma enorme quanridade de if's e variaveis
		que controlam o armazenamento dos dados e os nomes das colunas
		como os dados são salvos em apenas um linha do arquivo.txt,
		 os novos dados são armazenado no mesmo arquivo logo apos os existentes
*/



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

	while((c = fgetc(arquivo)) != EOF)
	{
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
				posicaoL++;
			}
			else if(c == '#')
			{
				contador = 0;
				pch = strtok(dado, "#");
				strcpy(valor[posicaoC][posicaoL].valor, dado);
				contador = 0;
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
			coluna++;
			tipoDaColuna = 0;
			if (coluna == numeroDeColunas-48)
			{
				encontrada = 0;
				vaiProsDados = 1;
			}
		}

		if (nomeColunas == 1 && encontrada == 1)
		{
			nomesColunas[contador] = c;
			contador++;
			if(c == '!')
			{
				contador = 0;
				pch = strtok(nomesColunas, "!");
				strcpy(colunas[coluna].nome,pch);
				nomeColunas = 0;
				tipoDaColuna = 1;
			}
		}

		if (inicionomeColunas == 1 && c == ':' && encontrada == 1)
		{
			nomeColunas = 1;
			inicionomeColunas = 0;		
		}
		if (c == '-' && encontrada == 1)
		{
			nomeColunas = 1;
		}
		
		if (quantidadeColunas == 1)
		{
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
			if (colunas == NULL)
			{

			}
			else
			{

			}
			criarMalloc = 2;
		}
		if (comecar == 1)
		{
			nomeTabela[contador] = c;
			contador++;
			if (c == ':')
			{
				comecar = 0;
				contador = 0;
				pch = strtok(nomeTabela, ":");

				quantidadeColunas = 1;
				encontrada = 1;
			}
		}
		if (c == '@')
		{
			comecar = 1;
		}
		if (c == ';' && encontrada == 1)
		{
			break;
		}
	}

	contador = 0;
	pch = strtok(dado, ";");
	strcpy(valor[posicaoC][posicaoL].valor, dado);
	contador = 0;

	int j;
	printf("\n");

	fseek(arquivo, 0, SEEK_END);
	int nPK;
	int bloquear = 0;
	char valorP[10];
	fprintf(arquivo, "#");
	if(strcmp(colunas[0].nome, "PrimaryKey") == 0)
	{
		for (i = 0; i < quantidadeLinhas; i++)
		{
			for (j = 0; j < quantidadeLinhas; j++)
			{
				nPK = atoi(valor[j][0].valor);
				if (i == nPK)
				{
					break;
				}
				else if(j+1 == quantidadeLinhas)
				{
					itoa(i, valorP, 10);
					strcat(valorP, ",");
					fprintf(arquivo, "%s", valorP);
					bloquear = 1;
					break;
				}
			}
			if(bloquear == 1)
			{
				break;
			}
			if (i+1 == quantidadeLinhas && bloquear == 0)
			{
				itoa(i+1, valorP, 10);
				strcat(valorP, ",");
				fprintf(arquivo, "%s", valorP);
			}
		}

		for (j = 1; j < numeroDeColunas-48; j++)
			{
				printf("%s: ",colunas[j].nome);
				scanf("%s", &colunas[j].valor);

				if (j == numeroDeColunas-49)
				{

				}
				else
				{
					strcat(colunas[j].valor, ",");
				}
				fprintf(arquivo, "%s", colunas[j].valor);
				setbuf(stdin, NULL);
		}
	}
	else
	{
		bloquear = 0;
		for (j = 0; j < numeroDeColunas-48; j++)
			{
				printf("%s: ", colunas[j].nome);
				scanf("%s", &colunas[j].valor);
				while(bloquear == 0)
				{
					for (i = 0; i < quantidadeLinhas; i++)
					{
						if (strcmp(valor[i][0].valor, &colunas[j].valor) == 0)
						{
							printf("Ja existe!\n");
							printf("Digitar outro valor: \n");
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

				if (j == numeroDeColunas-49)
				{

				}
				else
				{
					strcat(colunas[j].valor, ",");
				}

				fprintf(arquivo, "%s", colunas[j].valor);
				setbuf(stdin, NULL);
		}
	}
	fclose(arquivo);
}
/* 
		primeiramente ler cada valor da tabela escolhida e armazena em uma matriz de struct, 
		a matriz sofre realloc a cada linha lida no arquivo almentando seu tamanho sem valor pre-definido.
		Como a função trabalha passando de caracter em caracter foi-se necessario a uma enorme quanridade de if's e variaveis
		que controlam o armazenamento dos dados e os nomes das colunas
		em seguida, cria um novo arquivo e armazena todos os dados nesse novo arquivo
		só que sem a linha escolhida para ser apagada, depois exclui o arquivo antigo
*/
int apagarValor(char* tabela)
{
	char pasta[30] = "Tabelas/";
	char tabelaPro[20];
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

	int contador = 0;
	int comecar = 0;
	int i, j;
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
	int saida;
	char dado[20];
	char nomeTabela[42];
	char nomesColunas[40];
	char *pch;
	char c;
	int coluna = 0;
	colunaNomeTipo* colunas;

	while((c = fgetc(arquivo)) != EOF){
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
				posicaoL++;
			}
			else if(c == '#')
			{
				contador = 0;
				pch = strtok(dado, "#");
				strcpy(valor[posicaoC][posicaoL].valor, pch);
				contador = 0;
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
			coluna++;
			tipoDaColuna = 0;

			if (coluna == numeroDeColunas-48)
			{
				encontrada = 0;
				vaiProsDados = 1;
			}
		}
		if (nomeColunas == 1 && encontrada == 1)
		{
			nomesColunas[contador] = c;
			contador++;
			if(c == '!')
			{
				contador = 0;
				pch = strtok(nomesColunas, "!");
				strcpy(colunas[coluna].nome,pch);
				nomeColunas = 0;
				tipoDaColuna = 1;
			}
		}

		if (inicionomeColunas == 1 && c == ':' && encontrada == 1)
		{
			nomeColunas = 1;
			inicionomeColunas = 0;
		}
		if (c == '-' && encontrada == 1)
		{
			nomeColunas = 1;
		}
		
		if (quantidadeColunas == 1)
		{
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
			if (colunas == NULL)
			{
				printf("Erro no malloc colunas\n");
			}
			else{
			}
			criarMalloc = 2;
		}
		if (comecar == 1)
		{
			nomeTabela[contador] = c;
			contador++;
			if (c == ':')
			{
				comecar = 0;
				contador = 0;
				pch = strtok(nomeTabela, ":");
				quantidadeColunas = 1;
				encontrada = 1;
			}
		}
		if (c == '@')
		{
			comecar = 1;
		}
		if (c == ';' && encontrada == 1)
		{
			break;
		}
	}

	int len;
	char str[15];
	strcpy(str, dado);
	len = strxfrm(pch, str, contador);
	strcpy(valor[posicaoC][posicaoL].valor, pch);

	char pk[10];
	int ignorar;
	
	fclose(arquivo);
	saida = 0;
	while(saida != 1){
		printf("Numero da chave primaria que deseja excluir: ");
		scanf("%s", &pk);
		for (i = 0; i < quantidadeLinhas; i++)
		{
			if (strcmp(valor[i][0].valor, pk)==0)
			{
				ignorar = i;
				saida = 1;
				break;
			}
		}
		if (saida != 1)
		{
			printf("Chave primaria não encontrada\n");
		}
	}

	strcpy(tabelaPro, tabela);
	strcat(tabelaPro, ".txt");
	FILE* arquivoPro = fopen(tabelaPro, "a+");

	if(arquivoPro == NULL)printf("Erro ao Abrir Arquivo\n");

	fprintf(arquivoPro, "@%s:%d:", tabela, numeroDeColunas-48);
	
	for (i = 0; i < numeroDeColunas-48; i++)
	{
		fprintf(arquivoPro, "%s!%d-", colunas[i].nome, colunas[i].tipo-48);
	}

	fprintf(arquivoPro, "(");
	for (i = 0; i < quantidadeLinhas; i++)
	{
		for (j = 0; j < numeroDeColunas-48; j++)
		{
			if (strcmp(valor[i][0].valor, pk)==0)
			{
				break;
			}
			fprintf(arquivoPro, "%s", valor[i][j].valor);
			if (j == numeroDeColunas-49)
			{
				if (i == quantidadeLinhas-1)
				{
						
				}
				else
				{
					fprintf(arquivoPro, "#");
				}
			}
			else
			{
				fprintf(arquivoPro, ",");
			}
			setbuf(stdin, NULL);
		}
	}
	int resultado;
	resultado = remove(pasta);
	if (resultado == 0)
	{

	}
	else
	{
		printf("Erro ao deletar\n");
	}

	fclose(arquivoPro);
	char comando[50] = "move /Y ";
	strcat(comando, tabelaPro);
	strcat(comando, " Tabelas/");
	system(comando);
}

/*

*/

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

	FILE* tabelas = fopen("Tabelas/tabs.txt", "a+");
	if (tabelas == NULL)printf("Erro ao abrir arquivo\n");
	

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
