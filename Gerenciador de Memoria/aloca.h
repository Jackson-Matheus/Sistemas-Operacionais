#include "memoria.h"
#include <stdio.h>
#define BESTFIT 0
#define FIRSTFIT 1
#define WORSTFIT 2
//#DEFINE numero_magico 255

class meualoc
{
	char *memoria;
	Bloco *novo;
	Bloco *ultimo;
	Memoria *lista;
	int politica, tamanho;
	char magico;

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

	void atualiza();

	~meualoc();
};

meualoc::meualoc(int tamanhoMemoria, int politica)
{
	this->lista = new Memoria(tamanhoMemoria, 0);
	this->memoria = new char[tamanhoMemoria];
	this->novo = new Bloco;

	this->politica = politica;
	this->tamanho = tamanhoMemoria;
	this->magico = 33;
}

char *meualoc::aloca(unsigned short int tamanho)
{
	int politica = this->politica;

	if (politica == 1)
	{
		Bloco *novo = lista->inserir_first_fit(tamanho);
		this->ultimo = novo;

		if (novo != NULL)
		{

			int i = novo->base;
			this->memoria[i] = this->magico & 255;
			this->memoria[i + 1] = tamanho & 255;
			this->memoria[i + 2] = (tamanho >> 8) & 65535;
			this->lista->altera_bloco(novo, tamanho);
			return this->memoria + i + 3;
		}
	}
	else if (politica == 0)
	{
		Bloco *novo = lista->inserir_best_fit(tamanho);
		this->ultimo = novo;

		if (novo != NULL)
		{
			int i = novo->base;
			this->memoria[i] = this->magico & 255;
			this->memoria[i + 1] = tamanho & 255;
			this->memoria[i + 2] = (tamanho >> 8) & 65535;
			this->lista->altera_bloco(novo, tamanho);
			return this->memoria + i + 3;
		}
	}
	else if (politica == 2)
	{
		Bloco *nov = lista->inserir_worst_fit(tamanho);

		this->ultimo = novo;

		if (novo != NULL)
		{
			int i = novo->base;
			this->memoria[i] = this->magico & 255;
			this->memoria[i + 1] = tamanho & 255;
			this->memoria[i + 2] = (tamanho >> 8) & 65535;
			this->lista->altera_bloco(novo, tamanho);
			return this->memoria + i + 3;
		}

		return NULL;
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
	return *valido == this->magico ? valido : NULL;
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
	for (; aux != ponteiro; i++, aux++)
		;

	i = -3;

	Bloco *nov = new Bloco;
	nov->tamanho = b2;
	nov->base = i;
	nov->prox = NULL;

	this->lista->inserir_inicio(nov);

	return 1;
}

meualoc::~meualoc()
{
	delete memoria;
	delete lista;
	delete novo;
}
