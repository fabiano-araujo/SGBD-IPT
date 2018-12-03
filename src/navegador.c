#include <stdio.h>
#include "database.h"
#include "FileManeger.h"

int main(){

	int opcao;
	char nome[40];	
	
	do{
		printf("%s\n","Digite 0 para sair:");	
		printf("%s\n","Digite 1 para criar uma tabela:");
		printf("%s\n","Digite 2 para listar todas as tabelas:");
		printf("%s\n","Digite 3 para criar uma nova linha na tabela:");	
		printf("%s\n","Digite 4 para listar todos os dados de uma tabela:");
		printf("%s\n","Digite 5 Pesquisar valor em uma tabela:");
		printf("%s\n","Digite 6 para apagar valor de uma tabela:");
		printf("%s\n","Digite 7 para apagar uma tabela:");
		
		scanf("%d",&opcao);

		switch(opcao)
		{
			case 0:
				break;
			case 1:
				nome[40];

				printf("Nome da tabela: ");
				scanf("%s", &nome);

				criarTabela(nome);
				break;

			case 2:
				listarTabelas();
				break;

			case 3:
				nome[40];

				printf("Nome da tabela: ");
				scanf("%s", &nome);

				criarLinha(nome);
				break;

			case 4:
				nome[40];

				printf("Nome da tabela: ");
				scanf("%s", &nome);

				listarTodosDados(nome);
				break;

			case 5:
				pesquisarValor();				
				break;

			case 6:
				nome[40];

				printf("Nome da tabela: ");
				scanf("%s", &nome);

				apagarValor(nome);
				break;

			case 7:
				nome[40];

				printf("Nome da tabela: ");
				scanf("%s", &nome);

				apagarTabela(nome);
				break;

			default:				
				printf("Valor Invalido\n");
		}	
		setbuf(stdin, NULL);
	}while(opcao != 0);
	return 0;
}