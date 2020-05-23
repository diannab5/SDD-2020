#include<stdio.h>
#include<malloc.h>
#include<string.h>


struct Carte {
	char* titlu;
	int nrPagini;
	float pret;
};

Carte initCarte(const char* titlu, int nrPagini, float pret) {
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	//este pointer, deci trebuie alocata memorie
	c.titlu = (char*)malloc(sizeof(char)*(strlen(titlu) + 1));
	//sursa e parametrul primit, destinatia e c.titlu
	strcpy(c.titlu, titlu);
	return c;
}

void afisareCarte(Carte c) {
	printf(" Cartea %s are %d pagini si pretul de %5.2f\n", c.titlu, c.nrPagini, c.pret);
}

struct nod {
	Carte info; //informatia utila e de tip carte
	nod* next; //adresa urmatorului nod; retin adresa intr-o variabila pointer la nod

};

//Inserarea in lista se poate face la inceput, sfarsit, undeva in lista
//Inserare la inceput
//parametrii cartea pe care vrem sa o inseram si lista
nod* inserareLaInceput(Carte c, nod* cap) {
	nod* nou = (nod*)malloc(sizeof(nod));//alocam spatiu pentru noul nod pe care vrem sa il inseram
	//punem informatie in el dupa ce l-am creat
	nou->info = c; //c-ul primit ca parametru; shallow copy util
	nou->next = cap; //facem legatura cu fostul prim nod
	return nou;
}

void afisareListaCarti(nod* cap) {
	while (cap) {
		afisareCarte(cap->info);
		cap = cap->next; //ne mutam pe nodul urmator
	}
}

//Transmitem prin referinta, fol c++, deoarece daca lasam simplu,pointeaza catre o zona goala de memorie si crapa
//la transmiterea prin valoare, am facut o copie si s-a modificat doar copia
void stergereLista(nod*& cap) {
	while (cap) {
		free(cap->info.titlu);
		//daca cap=cap->next nu am sters nodul, doar info utila
		//retinem adresa nodului curent in alt pointer
		nod* temp = cap;
		cap = cap->next;
		free(temp);
	}
}


void inserareSortataDupaNrPagini(nod*& cap, Carte c) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = c; //punem informatia utila in nodul nostru
	if (cap) { //daca avem lista
		if (cap->info.nrPagini > c.nrPagini) {//primul caz, verificam daca trebuie inserat la inceput 
			//daca info din nodul existent e mai mare decat info din noul nod
			nou->next = cap;
			cap = nou;
		}
		else {//undeva in interior
			nod* temp = cap;//pierd nodurile din spate daca nu iau un temp
			while (temp->next && temp->next->info.nrPagini < c.nrPagini) {
				temp = temp->next; //ne deplasam
			}
			//leg se fac de la nod la lista si dupa de la lista la nod
			//niciodata de la lista catre nod
			nou->next = temp->next;
			temp->next = nou;
		}
	}
	else {
		nou->next = NULL; //nu exista nod in lista, cream noi
		cap = nou;
	}
}

void main() {
	//daca am adresa primul nod, pot ajunge la toate celelalte
	//o pot retine intr-un pointer adresa
	nod* lista = NULL; //adresa primului nod, deci lista, am initializat-o cu null findca e goala

	//lista = inserareLaInceput(initCarte("Marea", 45, 67.7), lista);
	
	//in cadrul functiei de initializare am alocat spatiu pentru sirul de caractere
	//daca la inserare inceput faceam deep copy, mai alocam inca o data spatiu pt sirul de caractere 
	//si l-am fi avut in lista, dar si in initializare carte , nu am acces sa sterg de la initCarte
	//daca declaram carte c = init, aveam acces la zona de mem initCarte
	//daca apelez direct din line nu mai am posibilitate sa sterg, de aceea e util shallow copy

	//lista = inserareLaInceput(initCarte("Morometii", 90, 200), lista);
	//lista = inserareLaInceput(initCarte("Enigma otiliei", 245, 40), lista);
	
	inserareSortataDupaNrPagini(lista, initCarte("Morometii", 90, 200));
	inserareSortataDupaNrPagini(lista, initCarte("Loca", 10, 200));
	inserareSortataDupaNrPagini(lista, initCarte("Vida", 45, 200));

	afisareListaCarti(lista);
	stergereLista(lista);
	afisareListaCarti(lista);

	

	
}