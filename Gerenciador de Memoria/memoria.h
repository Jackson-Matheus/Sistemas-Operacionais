#include <iostream>
#include <stdlib.h>
struct Bloco
{
	unsigned short int base;
	unsigned short int tamanho;
	Bloco *prox;
};

class Memoria
{
private:
	Bloco *inicio;

public:
	Memoria(unsigned short int tamanho, unsigned short int base)
	{
		Bloco *novo = new Bloco;
		novo->base = base;
		novo->tamanho = tamanho;
		this->inicio = novo;
	}
	void inserir_inicio(Bloco *bloco)
	{

		if (this->inicio == NULL)
		{
			inicio = bloco;
			return;
		}
		bloco->prox = this->inicio;
		inicio = bloco;
	}
	Bloco *inserir_first_fit(unsigned short int tam)
	{
		Bloco *novo = inicio;

		if (novo == NULL)
			return NULL;

		for (; novo != NULL && novo->tamanho < tam; novo = novo->prox)
			;

		return novo;
	}

	Bloco *inserir_best_fit(unsigned short int tam)
	{
		Bloco *candidato = new Bloco;
		Bloco *novo = new Bloco;

		candidato = this->inicio;
		novo = candidato->prox;
		while (novo != NULL)
		{
			if (novo->tamanho >= tam && novo->tamanho < candidato->tamanho)
				candidato = novo;
			novo = novo->prox;
		}

		return candidato;
	}
	Bloco *inserir_worst_fit(unsigned short int tam)
	{
		Bloco *candidato = new Bloco;
		Bloco *novo = new Bloco;

		candidato = this->inicio;
		novo = candidato->prox;

		while (novo != NULL)
		{
			if (novo->tamanho >= tam && novo->tamanho > candidato->tamanho)
				candidato = novo;
			novo = novo->prox;
		}

		return candidato;
	}

	void altera_bloco(Bloco *novo, unsigned short int tamanho)
	{

		Bloco *aux = new Bloco;
		aux = inicio;
		bool achou = false;
		for (; aux != NULL && aux->base != novo->base && aux->tamanho != novo->tamanho && aux->prox != novo->prox; aux = aux->prox)
			;

		aux->tamanho = aux->tamanho - tamanho;
		aux->base += tamanho;
	}

	void imprime()
	{
		Bloco *novo = inicio;
		if (novo != NULL)
		{
			while (novo != NULL)
			{
				std::cout << "base " << novo->base << "\n";
				std::cout << "tamanho " << novo->tamanho << "\n";
				novo = novo->prox;
			}
		}
		delete novo;
	}

	void coalesce()
	{
		Bloco *novo;
		Bloco *aux = new Bloco;
		for (; novo != NULL; novo = novo->prox)
		{
			aux = novo->prox;
			if (novo->base + novo->tamanho == aux->base)
			{
				novo->prox = aux->prox;
				novo->tamanho = novo->tamanho + novo->prox->tamanho;
				inserir_inicio(novo);
				delete aux;
			}
		}
		delete aux;
	}

	~Memoria()
	{
		delete inicio;
	}
};
