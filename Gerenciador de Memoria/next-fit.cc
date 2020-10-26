No * meualoc::NextFit(tipo tamanho,bool aglutinada = false){
	//verifica se tem espaco disponivel na livres
	if(livres->disp_memoria < tamanho)
		return NULL;

	if(livres->last == NULL)
		livres->last = livres->head;


	//procura o primeiro no que tenha o tamanho desejado
	while(livres->last != NULL && livres->last->block.bound < tamanho){
		livres->last = livres->last->prox;
	}

	//caso nao tenha um no que contém a quantidade 
	//de memoria e a livres  ainda nao foi agloutinada
	if(livres->last == NULL && !aglutinada){
		livres->aglutina();
		return NextFit(tamanho,true);
	}
	
	No *retorno = livres->last;
	if(retorno != NULL)
		livres->last = livres->last->prox;
	return retorno;
}
