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
		
		strcpy(nomesDasTabelas[contador-1].valor, nomeTabela);
		printf("%s", nomesDasTabelas[contador-1].valor);
		contador++;
		nomesDasTabelas = (Valores*) realloc(nomesDasTabelas, (contador+1)*sizeof(Valores));
	}
	free(nomesDasTabelas);
	fclose(tabelas);




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
	//else printf("Tudo OK ao abrir arquivo\n");

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
				//printf("-%s\n", valor[posicaoC][posicaoL].valor);
				posicaoL++;
			}
			else if(c == '#')
			{
				contador = 0;
				pch = strtok(dado, "#");
				strcpy(valor[posicaoC][posicaoL].valor, pch);
				contador = 0;
				//printf("-%s\n", valor[posicaoC][posicaoL].valor);
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
			//printf("%c, coluna = %d\n", colunas[coluna].tipo, coluna);
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
				//printf("%s\n", colunas[coluna].nome);
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
			//printf("%c\n", c);
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
				//printf("malloc colunas BAD\n");
			}
			else{
				//printf("malloc colunas ok\n");
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

				//printf("Pronto\n");
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
			//printf("1\n");
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
	fclose(arquivo);
	//contador = 0;
	//printf("dado: %s\n", dado);
	//printf("%d\n", contador);
	//pch = strtok(str, "p");
	len = strxfrm(pch, str, contador);
	//strcpy(valor[posicaoC][posicaoL].valor, ptr);
	//printf("%s\n", ptr);
		//contador = 0;
	strcpy(valor[posicaoC][posicaoL].valor, pch);
	
	//printf("Tamanho: %d. len: %d\n", tamanho, len);
	//printf("-%s\n", valor[posicaoC][posicaoL].valor);

	//printf("-> L: %d. C: %d\n", quantidadeLinhas, numeroDeColunas-48);
	
	int j;
	for (i = 0; i < numeroDeColunas-48; i++)
	{
		printf("%12s", colunas[i].nome);
	}
	printf("\n");
	for (i = 0; i < quantidadeLinhas; i++)
	{
		for (j = 0; j < numeroDeColunas-48; j++)
		{
			//printf("%12d %d", i, j);
			printf("%12s", valor[i][j].valor);
		}
		printf("\n");
	}
	//printf("%s\n", valor[3][2].valor);
	setbuf(stdin, NULL);
}

/*
	Adiciona um caractere a uma string.
	recebe uma string e um caractere a ser adicionado 
	retorna uma nova string com o caractere adicionado
*/
char *addChar(char *str, char c){	   
    size_t len = strlen(str);
    char *str2 = malloc(len + 1 + 1 ); 
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';
    
    return str2;
}


/*
	Quebra uma string pelo caractere passado por parmêtro.
	recebe a string que será quebrada e o caractere a ser procurado
	retorna uma matriz de char (um array de string)
*/
char** split(char *str, char *c){	  
    char* temp = 0;
    char** result = 0;
    unsigned int tamanho = 0;

    temp = strtok(str, c);
    
    if (temp) {
        result = malloc( (tamanho + 1) * sizeof(char**));
        result[tamanho++] = temp;
    }

    while ( (temp = strtok(0, c)) != 0 ) {
        result = realloc(result, (tamanho + 1) * sizeof(char**));
        result[tamanho++] = temp;
    }   
    result = realloc(result, (tamanho + 1) * sizeof(char**));
    result[tamanho++] = "\0";
	return result;
}

/*
	Lê todos os caracteres de um arquivo txt
	retorna a string com todos os caracteres
*/
char *readFileComplete(char* nomeFile){
	FILE *arquivo;	
	char *txt = "";
	arquivo = fopen(nomeFile,"r");
	int count = 0;
	if( arquivo == NULL ) {		
		return NULL;
	}else{	
		while(!feof(arquivo)){			
			char c = fgetc(arquivo);			
			txt = addChar(txt, c);
		}				
		fclose( arquivo );
		return txt;
	}	
}

/*
	Pesquisa por um valor específico no "banco de dados"
	são solicitados o nome da tabela, o nome da coluna e o valor da coluna
	caso ache o valor correspondente ele printa o valor
*/
int pesquisarValor()
{
	char nomeTabela[80];
	char nomeColuna[80];
	char valorDaColuna[90];
	printf("Digite o nome da tabela que voce quer pesquisar: \n");	
	scanf("%s", &nomeTabela);

	char file[80] = "Tabelas/";	 	
	strcat(file, nomeTabela);
	strcat(file, ".txt");

	char *txt = readFileComplete(file);
	if (txt == NULL){		
		printf("%s\n", "Tabela não encontrada!");
	}else{		
		printf("Digite o nome da coluna que voce quer pesquisar: \n");	
		scanf("%s", &nomeColuna);
		printf("Digite o valor da coluna: \n");	
		scanf("%s", &valorDaColuna);

		char *dados = split(txt,":")[2];		
				
		char *colunas = strtok(dados, "(");		
		char *valores = strtok(NULL, "(");				

		int positionInFile = 0;
		char *coluna;
		char **colunasMostrar = split(colunas,"-");							
		int achouColuna = 0;
		int i = 0;
		while(1 == 1){																		
			if (colunasMostrar[i] == "\0"){				
				break;
			}				
			coluna = split(colunasMostrar[i],"!")[0];			
			if (strcmp(coluna,nomeColuna) == 0){								
				achouColuna =1;
				break;
			}
			i++;			
			positionInFile++;			
		}			
		if (achouColuna == 0){					
			printf("A coluna %s nao existe nessa tabela", nomeColuna);
			return -1;
		}				
		valores = strtok(valores, ");");		
		char **itens = split(valores,"#");				
		i = 0;
		int achouAlgumValor = 0;
		while(1 ==1 ){			
			if (itens[i] == "\0"){				
				break;
			}								
			char **item = split(itens[i],",");						
			int equais = strcmp(item[positionInFile],valorDaColuna);								
			if (equais == 0){	
				achouAlgumValor = 1;
				int j = 0;			
				printf("%s\n","------------------------------------------------------------");															
				while(1 ==1 ){						
					if (colunasMostrar[j] == "\0"){				
						break;
					}	
					printf("|  %s = %s ",split(colunasMostrar[j],"!")[0], item[j]);
					j++;
				}
				printf("%s\n", "");
			}
			i++;		
		}			
		if (achouAlgumValor == 0){			
			printf("Não foi achado nenhum valor correspondente");
		}
		printf("%s\n\n\n", "");
	}		
}