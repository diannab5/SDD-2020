#include<stdio.h>
#include<malloc.h>
#include<string.h>


//Stive & Cozi
// Stiva LIFO - pe lista simplu inlantuita, dubla si pe vector
//Cozi FIFO -coada la fel 

struct Oras {
	char* denumire;
	int nrLocuitori;
	float suprafata;
};

Oras initializareOras(const char* denumire, int nrLocuitori, float suprafata) {
	Oras o;
	o.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(o.denumire, denumire);
	o.nrLocuitori = nrLocuitori;
	o.suprafata = suprafata;
	return o;
}

void afisareOras(Oras o) {
	printf("Orasul %s are %d locuitori si o suprafa de %5.2f \n", o.denumire, o.nrLocuitori, o.suprafata);
}

struct nod {
	Oras info;
	nod* next;
};

//LIFO - ca toate operatiile (extragere si inserare) se vor face la acelasi capat
//putem face inserarea si la inceput si la sfarsit
void push(nod* &stiva, Oras o) {
	//declaram un nou nod, in care inseram info primita
	//ca sa facem la sfarsit ne deplasam la ultimul nod
	//verificam mai intai daca avem ce parcurge
	//transmitem prin referinta, fiindca modificam
	nod* p = (nod*)malloc(sizeof(nod));
	p->info = o; //shallow copy
	p->next = NULL; //findca inseram la sfarsit
	if (stiva) {// daca exista stiva
		//ne deplasam catre ultimul nod, luam inca un nod fiindca la sfarsit pointerul va avea valoarea de la final
		nod* nou = stiva;
		while (nou->next) //ne oprim pe ultimul nod
		{
			nou = nou->next; 
		}
		nou->next = p; //primeste adresa noului nod creat

}
	else {
		//daca nu avem nimic
		stiva = p; //stiva goala primeste adresa noului nod creat
	}
}

//extragere - pop returneaza un oras fiindca extrage un oras 
//exista posibilitaea sa il modificam de aceea tansmitem prin referinta
Oras pop(nod* &stiva) {
	//ne pozitionam pe penultimul nod;
	if (stiva) {
		nod* copie = stiva;
		while (copie->next && copie->next->next) {
			//ma asigur ca pot sa zic copie->next->next cand verificam copie->next; cat timp avem nodul urmator si inca un noud in fata
		  //ne deplasam
			copie = copie->next;
		}
		//verificam pe care din situatii am iesit
		if (copie->next) {
			Oras o = copie->next->info; //am luat orasul din nodul urmator, shallow copy, dupa care stergem nodul din lista noastra
		    //daca am facut shallow copy nu mai stergem denumirea
			//daca facem deepcopy dam free
			//trebuie sa stergem nodul efectiv
			free(copie->next);
			//setam cu null copie->next ca nu mai are niciun nod in fata
			copie->next = NULL;
			return o;
		}
		else {
			//suntem pe ultimul si unicul nod, extragem ultimul nod din lista
			Oras o = copie->info;
			free(copie);
			stiva = NULL; //nu mai avem noduri, deci stiva e goala
			return o;
		}
	}
	else {
		throw "Nu avem stiva!";
	}
}

//daca avem coada, si nu stiva ; inserarea se face la un capat, extragerea la celalat capat; operatiile se fac la capete diferite
//functie care returneaza nr total de locuitori a tuturor oraselor din stiva mea; vreau sa lucreze cu stiva si la sfarsit stiva sa ramana intacta;
//transmitem prin valoare, dar trebuie sa ne gandim ca avem stergerea aia
//cand lucram cu o stiva ne folosim de cele 2 metode ( push si pop) eunu am voie sa parcurg lista normal, trebuie sa ma folosesc de functia pop obligatoriu, chiar daca dau prin valoare eu sterg nodul
//facem o copie a intregii stive 
//cand avem stiva, avem acces doar la elementul din varful stivei, l-am extras la ala, avem acces la urmatorul; nu o putem parcurge ; trebuie extrase toate elementele pt a o parcurge
//extragem tote elementele si dupa le reinseram, prin extragere le stergem de la adresele alea, prin reinserare realocam spatiul pt ele, spatiul respectiv nu va fi exact in acelasi loc, 
int nrTotalLocuitori(nod* &stiva) {
	nod* copie = NULL;
	int nrTotalLocuitori = 0;
	//isEmpty verifica daca e goala stiva
	while(stiva) {
		//avem ce sa extragem daca avem stiva
		//extragem ultimul oras
		Oras o = pop(stiva); 
		nrTotalLocuitori += o.nrLocuitori;
		//si inseram in copie
		push(copie, o);
		//am luat orasul din varful stivei, am luat nrLoc, si am pus intro stiva auxiliara, dupa ce am terminat stiva trebuie sa le punem inapoi
		//copia e cu susul in jos si cand punem inapoi in stiva, vor fi ca la inceput
		//la push aloc spatiu pt nod, de aia am nevoie de referinta, fiindca modific primul nod, denumirile raman mereu aceleasi
	}
	while (copie) {
		//am pus toate orasele la loc in stiva mea
		push(stiva, pop(copie));
	}
	return nrTotalLocuitori;
}

//facem o functie prin care stergem un oras din stiva noastra
//facem la fel, punem in copie, stergem orasul si punem inapoi
//vreau sa obtin orasul bucuresti chiar daca nu e in varful stivei - returnare
//daca cautam bucuresti ne trebuie & ca modificam primul nod al listei
void stergereOrasDupaNume(nod* &stiva, const char* nume) {
	nod* copie = NULL;
	int ok = 1; //variabila de control
	while (stiva && ok) {
		//nu putem si sa extragem si sa verificam in while
		Oras o = pop(stiva);
		if (strcmp(o.denumire, nume) == 0) {
			free(o.denumire);
			ok = 0; //daca am sters ok devine 0
		}
		else { //daca nu avem else, extragem orasul, comparam numele si vedem ca e ala cautat, daca e ala cautat stergem, si avem ok=0 si ne iese din if executa instructiunea si dupa intra in while; cu brreak intrerupeam executia da nu avem break
			push(copie, o);
		}

	}
	while (copie) {
		Oras o = pop(copie);
		push(stiva, o);
	}
}

//prin referinta fiindca la sfarsit e null
void afisareStiva(nod* &stiva) {
	while (stiva) {
		afisareOras(pop(stiva));
	}

}
void main() {
	nod* stiva = NULL;
	push(stiva, initializareOras("Bucuresti", 2000, 45));
	push(stiva, initializareOras("Craiova", 1000, 50));
	push(stiva, initializareOras("Cluj", 1500, 37.5));
	//ca sa extrag pe bucuresti, mai intai extrag cluj, dupa craviova
	//clujul va fi extras, raman in stiva dupa afisare doar 2 orase
	//afisareOras(pop(stiva));
	//da 3000 ca ne-au ramas 2 orase; daca comentam afisare, ne da 4500
	printf("\nNr total locuitori %d\n", nrTotalLocuitori(stiva));
	stergereOrasDupaNume(stiva, "Craiova");
	afisareStiva(stiva);
}


//daca facem insert pt stiva la inceput (pe primul nod) avem acces de consultare;
