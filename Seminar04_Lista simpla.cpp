
#include<stdio.h>
#include<string.h>
#include<malloc.h>


struct Ferma {
	char* nume;
	int nrAnimale;
	float suprafataTeren;

};

Ferma initializareFerma(const char* nume, int nrAnimale, float suprafataTeren) {
	Ferma f;
	f.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.nrAnimale = nrAnimale;
	f.suprafataTeren = suprafataTeren;
	return f;
}


struct nod {
	Ferma info;
	nod* next;
};

nod* inserareInceput(nod* cap, Ferma f) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = f; //shallow copy
	nou->next = cap;
	return nou;
}

//functie care sa afiseze o ferma
void afisareFerma(Ferma f) {
	printf("Ferma %s are %d animale si o suprafata de %5.2f. \n", f.nume, f.nrAnimale, f.suprafataTeren);
}

void afisareListaFerme(nod* cap) {
	while (cap) {
		afisareFerma(cap->info);
		cap = cap->next;
	}
}

void stergereListaFerme(nod* &cap) {
	while (cap) {
		free(cap->info.nume);
		nod* temp = cap;
		cap = cap->next;
		free(temp);
	}
}

void inserareDupaOFerma(nod* &cap, Ferma f, const char* numeFermaCautata) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = f; //shallow copy util
	if (cap) {
		nod* p = cap;
		while (strcmp(numeFermaCautata,p->info.nume)!=0 && p->next) {
			p = p->next;

		}
		nou->next = p->next;
		p->next = nou;
	}
	else {
		nou->next;
		cap = nou;
	}
}

void main() {
	nod* lista = NULL;
	lista = inserareInceput(lista, initializareFerma("Ferma mea", 20, 20));
	lista = inserareInceput(lista, initializareFerma("Ferma vedetelor", 5, 7));
	lista = inserareInceput(lista, initializareFerma("Avicola", 2000, 200));
	afisareListaFerme(lista);
	printf("\n");
	inserareDupaOFerma(lista, initializareFerma("FermaNoua", 200, 40),"Avicola");

	afisareListaFerme(lista);

	stergereListaFerme(lista);
	afisareListaFerme(lista);
	


}