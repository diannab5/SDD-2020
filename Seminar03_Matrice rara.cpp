#include<stdio.h>
#include<malloc.h>
#include<string.h>

//Matrice rara = sa nu aiba toate elementele ( sa nu am peste tot valori)
//vector de pointeri cu m m elemente
//un vector care sa contina cate elemente avem pe fiecare linie


struct Casa {
	char* strada;
	int nrEtaje;
	float suprafataUtila;

};

Casa citesteCasa() {
	Casa c;
	//varabila auxiliara pe care o alocam static
	char aux[30];
	printf("Numele strazii:");
	scanf("%s", aux);
	c.strada = (char*)malloc(sizeof(char)*(strlen(aux) + 1));
	strcpy(c.strada, aux);
	printf("Numar etaje:");
	scanf("%d", &c.nrEtaje);
	printf("Suprafata utila:");
	scanf("%f", &c.suprafataUtila);
	return c;


}

//ne trebuie adresa, o retinem intr-un pointer, de aceea avem ***
//matrice transmisa prin pointer

//pointer la un vector **coloane , mai intai deferentiem pt a-l accesa
void citesteCartierDeCase(int *nrLinii, int* *nrColoane, Casa** *cartier) {
	printf("Cate randuri de case are cartierul: ");
	//diferentiez, imediat obtin adresa
	scanf("%d", nrLinii);
	(*nrColoane) = (int*)malloc(sizeof(int)*(*nrLinii)); //alocare nr coloane
	(*cartier) = (Casa**)malloc(sizeof(Casa*)*(*nrLinii));
	for (int i = 0; i < *nrLinii; i++) {
		printf("Cate case avem pe linia %d ", i);
		//deferentiere (*nrColoane)[i]) ,indexez,  ii dau adresa , fiindca nu poate sa citeasca valoarea 
		scanf("%d", &(*nrColoane)[i]);
		//alocare spatiu pentru cartier[i]
		(*cartier)[i] = (Casa*)malloc(sizeof(Casa)*(*nrColoane)[i]);
		for (int j = 0; j < (*nrColoane)[i]; j++) {
			(*cartier)[i][j] = citesteCasa();
			//*((*((*cartier) + i)) + j) = citesteCasa();
		}
	}



}

void afisareCasa(Casa c)
{
	printf(" Strada:%s ", c.strada);
	printf("Nr etaje:%d ", c.nrEtaje);
	printf("Suprafata utila: %5.2f  ", c.suprafataUtila);

}
void afisareMatrice(Casa** c, int nrLinii, int *nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		printf("\nCasele de pe linia %d", i);
		for (int j = 0; j < nrColoane[i]; j++) {
			afisareCasa(c[i][j]);
		}
	}
}


//adaugare o noua casa pe o linie
void adaugaCasaInMatrice(Casa** cartier, int nrLinii, int *nrColoane) {
	printf("Pe ce linie adaugam: ");
	int linie = 0;
	scanf("%d", &linie);
	Casa* copie = (Casa*)malloc(sizeof(Casa)*(nrColoane[linie] + 1));
	for (int i = 0; i < nrColoane[linie]; i++) {
		copie[i] = cartier[linie][i];
	}
	printf("Introduceti noua casa:");
	copie[nrColoane[linie]] = citesteCasa();
	free(cartier[linie]); // e un pointer, care contine o adresa; eliberam memoria
	cartier[linie] = copie;
	nrColoane[linie]++;

}

void main() {

	Casa** cartier;
	int nrLinii;
	int* nrColoane;
	citesteCartierDeCase(&nrLinii, &nrColoane, &cartier);

	//afisareMatrice(cartier, nrLinii, nrColoane);
	printf("\n");
	adaugaCasaInMatrice(cartier, nrLinii, nrColoane);
	afisareMatrice(cartier, nrLinii, nrColoane);


}