#include <stdio.h>
#include "database.h"

int main(){

	int opcao;
	
	do{
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
				criarTabela();
				break;

			case 2:
				listarTabelas();
				break;

			case 3:
				criarLinha();
				break;

			case 4:
				listarTodosDados();
				break;

			case 5:
				pesquisarValor();
				break;

			case 6:
				apagarValor();
				break;

			case 7:
				apagarTabela();
				break;

			default:
				printf("Valor Invalido\n");
		}	
	}while(opcao != 0);
	return 0;
}