
// Jackson Matheus
//	Lino Mota
//	Rodrigo Taveira


struct Bloco{
	unsigned short int base;
	unsigned short int tamanho; // bound
	Bloco * prox;
};

class Lista{
private:
	Bloco * inicio;
public:
	Lista(unsigned short int tamanho, unsigned short int base){
		this->inicio = new Bloco;
		Bloco * novo = new Bloco;
		novo->base = base;
		novo->tamanho = tamanho;
		this->inicio = novo;

	}
	void inserir_inicio(Bloco * bloco){
		//Bloco * aux = inicio;
		if(this->inicio == NULL){
			inicio = bloco;
		}else{
			bloco->prox = this->inicio;
			inicio = bloco;			
			//while(aux->prox != NULL)aux = aux->prox;
			//aux->prox = bloco;
		}	

	}
	Bloco * inserir_first_fit(unsigned short int tam){
		Bloco * novo = inicio;
		Bloco * candidato = new Bloco;
	
		if(novo == NULL){
			return NULL;
		}else{
			while(novo != NULL){
				if(novo->tamanho >= tam){
					candidato = novo;
					break;
				}
				novo = novo->prox;
			}			
		}
		return candidato;
	}

	Bloco * inserir_best_fit(unsigned short int tam){
		Bloco * candidato = new Bloco;
		Bloco * novo = new Bloco;
		

		candidato = this->inicio;
		novo = candidato->prox;
		
		while(novo != NULL ){
			if(novo->tamanho >= tam &&  novo->tamanho < candidato->tamanho) candidato = novo;
			
			novo = novo->prox;		
		}

		return candidato;
	}

	void altera_bloco(Bloco * novo, unsigned short int tamanho){
		
		Bloco * aux = new Bloco;
		aux =  inicio;
		bool achou = false;
		for(;aux != NULL; aux = aux->prox){
			if(aux->base == novo->base && aux->tamanho == novo->tamanho && aux->prox == novo->prox)
				achou = true;

				break;
			    
		}

		aux->tamanho = aux->tamanho - tamanho;
		aux->base +=tamanho;
	}




	void imprime(){
		Bloco * novo = inicio;
		if(novo != NULL){
			while(novo != NULL ){
				std::cout << "base "    << novo->base    << "\n";
				std::cout << "tamanho " << novo->tamanho << "\n";				
				novo = novo->prox;
			}
		}
		delete novo;

	}

	void coalesce(){
		Bloco * novo;
		Bloco * aux = new Bloco;
		for(; novo != NULL; novo =  novo->prox){
			aux = novo->prox;
			if(novo->base + novo->tamanho == aux->base){
				novo->prox = aux->prox;
				novo->tamanho = novo->tamanho + novo->prox->tamanho;
				inserir_inicio(novo);
				delete aux;
			}

		}
		delete aux;

	}





	~Lista(){
		delete inicio;

	}
	
};
