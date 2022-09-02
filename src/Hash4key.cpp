#include "Hash4key.hpp"

void InitializeFechada(HashTableFechada *h, int M){
	vector<Lista> Aux;
	for(int i=0; i<M; i++){
		Lista AuxLista;
		AuxLista.first = (Block*) new Block;
		AuxLista.last  = AuxLista.first;
		AuxLista.first->prox = nullptr;

		Aux.push_back(AuxLista);
	}

	h->table = Aux;	
	h->M = M;
	h->col = 0;
}

void InsertFechada(HashTableFechada *h, vector<int> key, vector<vector<int>> matriz){
	int idx = hash(key, h->M);
	
	if(	h->table[idx].first != h->table[idx].last){
		h->col += 1;
	}

	h->table[idx].last->prox = (Block*) new Block;
	h->table[idx].last = h->table[idx].last->prox;
	h->table[idx].last->valores.key = key;
	h->table[idx].last->valores.matriz = matriz;
	h->table[idx].last->prox = nullptr;
}

int getValueFechada(HashTableFechada *h, vector<int> key, vector<vector<int>>* matriz){
	int idx = hash(key, h->M);
	Block *Aux;

	if(h->table[idx].first == h->table[idx].last)
		return -1;

	Aux = h->table[idx].first->prox;

	do{
		if(Aux->valores.key == key){
			(*matriz) = Aux->valores.matriz;
			return 1;
		}
		Aux = Aux->prox;
	}while (Aux != nullptr);

	return -1;
}

void ImprimeFechada(HashTableFechada *h){
	Block *Aux;
	cout << "A Key aqui aparece em ordem Linha Inicial, Linha Final, Coluna Inicial, Coluna Final\n";
	for(int i=0; i<h->M; i++){
		cout << "Indice: " << i <<  " - Lista: ";
		Aux = h->table[i].first;
		if (Aux->prox == nullptr){
			cout << "Vazia\n";
		}
		else{
			Aux = Aux->prox;
			do{
				cout << "KEY: [" << Aux->valores.key[0] << "," << Aux->valores.key[1]  << "," << Aux->valores.key[2]  << "," << Aux->valores.key[3]  << "] - ";
				Aux = Aux->prox;
			}while(Aux != nullptr);
			cout << "\n";
		}
	}
}