#include <iostream>
#include <stdlib.h>
#include "aloca.h"

int main(int argc, char const *argv[])
{
	std::cout << "TAMANHO DA MEMORA: ";
	int tamanho_memoria;
	int politica;

	std::cin >> tamanho_memoria;
	std::cout << "ESCOLHA A POLITICA DE ALOCAÇÃO ";
	std::cout << "BEST FIT - 0  \n";
	std::cout << "FIRST FIT - 1 \n";
	std::cout << "NEXT FIT - 2  \n";
	std::cout << "SAIR - 3      \n";
	std::cin >> politica;

	while (politica != 0 && politica != 1 && politica != 2)
	{
		std::cout << "NUMERO INVALIDO DIGITE OUTRO ";
		std::cin >> politica;
	}

	meualoc gerenciador(tamanho_memoria, politica);

	unsigned short int tam_aloca;
	std::cout << "ESCOLHA O TAMANHO PARA SER ALOCADO ";
	std::cin >> tam_aloca;
	char *ptr_ = gerenciador.aloca(tam_aloca);
	int i = 0;
	while (i < 10)
	{
		char *ptr_ = gerenciador.aloca(tam_aloca);
		gerenciador.imprimeDados();
		gerenciador.libera(ptr_);

		i++;
	}

	std::cout << "\n";

	return 0;
}
