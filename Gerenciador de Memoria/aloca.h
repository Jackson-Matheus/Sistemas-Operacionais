#include "memoria.h"
#include <stdio.h>
#define BESTFIT 0
#define FIRSTFIT 1
#define NEXTFIT 2
//#DEFINE numero_magico 255

class meualoc
{
	char *memoria; //char* pois eh byte a byte
	Bloco *novo;
	Bloco *ultimo_cara;
	int politica, tamanho;
	char magico;
	Memoria *lista;
	int total;

public:
	//tamanhoMemoria vai definir o tamanho da memória que o alocador vai utilizar
	//politicaMem define como escolher o bloco de onde saira a memória
	meualoc(int tamanhoMemoria, int politicaMem);

	//Pega um pedaco da variavel memoria e aloca, retornando o ponteiro para o comeco dessa regiao e atualizando a lista de livres.
	char *aloca(unsigned short int tamanho);

	//Verifica se a posicao dada pelo ponteiro esta alocada
	char *verifica(char *ponteiro, int posicao = 0);

	//Libera o espaco ocupado na posicao, de forma analoga ao free. Ou seja, liberar toda a memoria alocada para este ponteiro na funcao aloca.
	int libera(char *ponteiro);

	//Imprime o numero de elementos na lista de vazios, o maior e a media de tamanhos dos blocos vazios
	void imprimeDados();

	void imprime_bit();

	void atualiza();

	~meualoc();
};

meualoc::meualoc(int tamanhoMemoria, int politicaMem)
{
	this->lista = new Memoria(tamanhoMemoria, 0);
	this->memoria = new char[tamanhoMemoria];
	this->novo = new Bloco;

	this->politica = politicaMem;
	this->tamanho = tamanhoMemoria;
	this->magico = 33;
	total = 0;
}

char *meualoc::aloca(unsigned short int tamanho)
{
	if (this->politica == 1)
	{
		Bloco *nov = lista->inserir_first_fit(tamanho);
		this->ultimo_cara = nov;

		if (nov != NULL)
		{
			int i = nov->base;
			this->memoria[i] = this->magico & 255;
			this->memoria[i + 1] = tamanho & 255;
			this->memoria[i + 2] = (tamanho >> 8) & 65535;
			this->lista->altera_bloco(nov, tamanho);
			return this->memoria + i + 3;
		}
	}
	else if (this->politica == 0)
	{
		Bloco *nov = lista->inserir_best_fit(tamanho);
		this->ultimo_cara = nov;

		if (nov != NULL)
		{
			int i = nov->base;
			this->memoria[i] = this->magico & 255;
			this->memoria[i + 1] = tamanho & 255;
			this->memoria[i + 2] = (tamanho >> 8) & 65535;
			this->lista->altera_bloco(nov, tamanho);
			return this->memoria + i + 3;
		}
	}

	return NULL;
}

void meualoc::imprimeDados()
{
	this->lista->imprime();
}

char *meualoc::verifica(char *ponteiro, int posicao)
{
	char *valido;
	valido = this->memoria - *ponteiro - 3;
	if (*valido == this->magico)
		return valido;
	return NULL;
}

void meualoc::imprime_bit()
{
	for (int i = 0; i < this->tamanho; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << ((memoria[i] >> j) & 1);
		}
		std::cout << " ";
	}
}
int meualoc::libera(char *ponteiro)
{
	if ((char)*(ponteiro - 3) != this->magico || ponteiro == NULL)
	{
		return -1;
	}
	ponteiro[-3] = 0;

	unsigned short int b1 = (*(ponteiro - 1) & 255) << 8;
	unsigned short int b2 = *(ponteiro - 2) & 255;
	b2 += b1;

	char *aux = this->memoria;
	int i = 0;
	for (;; i++, aux++)
	{
		if (aux == ponteiro)
			break;
	}
	i = i - 3;

	Bloco *nov = new Bloco;
	nov->tamanho = b2;
	nov->base = i;
	nov->prox = NULL;

	this->lista->inserir_inicio(nov);
	this->total++;

	return 1;
}

void meualoc::atualiza()
{
	if (this->total == 5)
	{
		lista->coalesce();
		this->total = 0;
	}
}

meualoc::~meualoc()
{
	delete memoria;
	delete lista;
	delete novo;
}
