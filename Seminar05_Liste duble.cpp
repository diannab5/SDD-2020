#include<stdio.h>
#include<malloc.h>
#include<string.h>


struct Bloc {
	int nrEtaje;
	int* apartamentePerEtaj;
	float intretinere;

};

struct nod {
	Bloc info;
	nod* next;
	nod* prev;
};

struct ListaDubla {
	nod* first; //adresa primului nod
	nod* last;
};

Bloc initializareBloc(int nrEtaje, int* apartamentePerEtaj, float intretinere) {
	Bloc b;
	b.nrEtaje = nrEtaje;
	b.apartamentePerEtaj = (int*)malloc(sizeof(int)*nrEtaje);
	for (int i = 0; i < nrEtaje; i++) {
		b.apartamentePerEtaj[i] = apartamentePerEtaj[i];
	}
	b.intretinere = intretinere;
	return b;
}

void afisareBloc(Bloc b) {
	printf("Blocul cu %d etaje cu o intretinere de %5.2f ", b.nrEtaje, b.intretinere);
	for (int i = 0; i < b.nrEtaje; i++)
	printf("%d", b.apartamentePerEtaj[i]);
	printf("\n");
}

ListaDubla inserareInceput(ListaDubla lista,Bloc b) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = b; //shallow copy
	nou->next = lista.first;
	nou->prev = NULL;
	if (lista.first) {
		lista.first->prev = nou;
		lista.first = nou;
	}
	else
	{
		lista.first = nou;
		lista.last = nou;
	}
	return lista;

}

void afisareListaInceput(ListaDubla l) {
	nod* p = l.first;
	while (p) {
		afisareBloc(p->info);
		p = p->next;
	}
}

void afisareSfarsitInceput(ListaDubla l) {
	for (nod* p = l.last; p != NULL; p = p->prev) {
		afisareBloc(p->info);
	}
}

void stergereLista(ListaDubla &lista) {
	nod* p = lista.first;
	while (p) {
		free(p->info.apartamentePerEtaj);
		nod* temp = p;
		p = p->next;
		free(temp);
	}
	lista.first = NULL;
	lista.last = NULL;
}
void main() {
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;

	int* v;
	v = (int*)malloc(sizeof(int) * 3);
	v[0] = 2;
	v[1] = 4;
	v[2] = 3;
	lista=inserareInceput(lista, initializareBloc(3, v, 120));
	v[1] = 5;
	lista=inserareInceput(lista, initializareBloc(3, v, 120));
	afisareListaInceput(lista);

	printf("\n");
	afisareSfarsitInceput(lista);
	stergereLista(lista);
	free(v);
	afisareSfarsitInceput(lista);
}