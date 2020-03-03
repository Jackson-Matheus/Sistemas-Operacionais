#include <iostream>
#include <stdlib.h>
#include "aloca.h"

// Jackson Matheus
//	Lino Mota
//	Rodrigo Taveira


int main(int argc, char const *argv[]){
	std::cout << "TAMANHO DA MEMORA: ";
	int tamanho_memoria;
	std::cin >> tamanho_memoria;

	int politica;
	std::cout << "BEST FIT - 0 ";
	std::cout << "FIRST FIT - 1 ";
	std::cout << "NEXT FIT - 2 ";
	std::cout << "SAIR - 3 \n";

	std::cout << "ESCOLHA A POLITICA DE ALOCAÇÃO ";
	std::cin >> politica;
	if(politica == 3)exit(0);



	while (politica != 0 && politica != 1 && politica != 2){
		std::cout << "NUMERO INVALIDO DIGITE OUTRO ";

		std::cin >> politica;

	}

	


	meualoc gerenciador(tamanho_memoria, politica);
	



	unsigned short int tam_aloca;
	std::cout << "ESCOLHA O TAMANHO PARA SER ALOCADO ";
	std::cin >> tam_aloca;
	
	char * ptr_regiao_alocada = gerenciador.aloca(tam_aloca);
	std::cout << "ALOCADO !!!" <<"\n";
	std::cout << "REGIAO LIVRE" <<"\n";
	gerenciador.imprimeDados();	
	//gerenciador.imprime_bit();

	


	//para desalocar a regiao, basta passr ptr_regiao_alocada em gerendiador.libera()


	gerenciador.libera(ptr_regiao_alocada);
	std::cout << "REGIAO LIVRE" <<"\n";
	std::cout << "\nDESALOCADO" <<"\n";
	


	

	gerenciador.imprimeDados();	

	//gerenciador.imprime_bit();

	std::cout << "\n";
	
	

	return 0;
}
