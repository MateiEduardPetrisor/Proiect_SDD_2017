#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void newLine()
{
	printf("\n");
}

enum FormatDocument
{
	pdf = 1,
	docx = 2,
	rtf = 3,
	doc = 4,
	cpp = 5,
	card = 6,
};

struct Document
{
	int idDocument;
	char* continutDocument;
	double dimensiuneDocument;
	char* autorDocument;
	FormatDocument formatDocument;
};

struct Cerere
{
	char* tipCerere;
	int prioritate;
	Document document;
};

struct Setari
{
	int printezaPortret;
	int numarCopii;
	int fataVerso;
	char* delimitator;
};

struct Vector
{
	int indexCurent;
	int dimensiuneVector;
	Setari* vectorSetari;
};

struct NodArbore
{
	Document info;
	NodArbore* stanga;
	NodArbore* dreapta;
};

struct NodStiva
{
	Document info;
	NodStiva* next;
};

struct NodLista
{
	Document info;
	NodLista* next;
};

struct NodCoada
{
	Document info;
	NodCoada* next;
};

struct HashTable
{
	int size;
	NodLista** liste;
};

struct Heap
{
	int indexCurent;
	int dimensiuneHeap;
	Cerere* vectorCereri;
};

struct Imprimanta
{
	int idImprimanta;
	int numarVecini;
	Cerere cerere;
	Setari setari;
};

struct NodVecin
{
	int idImprimanta;
	NodVecin* next;
};

struct NodGraf
{
	Imprimanta info;
	NodVecin* next;
};

struct Graf
{
	int indexCurent;
	int dimensiuneGraf;
	NodGraf** vector;
};

void afisareFormatDocument(FormatDocument format)
{
	switch (format)
	{
	case(1):
		printf("pdf ");
		break;
	case(2):
		printf("docx ");
		break;
	case(3):
		printf("rtf ");
		break;
	case(4):
		printf("doc ");
		break;
	case(5):
		printf("cpp ");
		break;
	case(6):
		printf("card ");
		break;
	default:
		printf("document invalid ");
		break;
	}
}
//////////////////////////////// Structura Lista Simpla Circulara /////////////////////////////////////////
NodLista* creareNodLista(Document document)
{
	NodLista* nod = (NodLista*)malloc(sizeof(NodLista));
	nod->info = document;
	nod->next = NULL;
	return nod;
}

void afisareNodLista(NodLista* nod)
{
	if (nod != NULL)
	{
		printf("%d ", nod->info.idDocument);
		printf("%s ", nod->info.continutDocument);
		printf("%4.1lf ", nod->info.dimensiuneDocument);
		printf("%s ", nod->info.autorDocument);
		afisareFormatDocument(nod->info.formatDocument);
		newLine();
	}
}

void afisareListaCirculara(NodLista* lista)
{
	if (lista)
	{
		NodLista* temp = lista;
		while (temp->next != lista)
		{
			afisareNodLista(temp);
			temp = temp->next;
		}
		afisareNodLista(temp);
	}
}

NodLista* inserareInceputListaCirculara(NodLista* lista, NodLista* nod)
{
	if (lista == NULL)
	{
		lista = nod;
		nod->next = lista;
	}
	else
	{
		NodLista* temp = lista;
		while (temp->next != lista)
			temp = temp->next;
		temp->next = nod;

		nod->next = lista;
		lista = nod;
	}
	return lista;
}

void deazalocaListaCirculara(NodLista* &lista)
{
	if (lista != NULL)
	{
		NodLista* temp = lista;
		while (temp->next != lista)
		{
			NodLista* sterge = temp;
			temp = temp->next;
			sterge->next = NULL;
			free(sterge->info.continutDocument);
			free(sterge->info.autorDocument);
			free(sterge);
			sterge = NULL;
		}
		free(temp->info.continutDocument);
		free(temp->info.autorDocument);
		free(temp);
		temp->next = NULL;
		lista = NULL;
	}
}

//////////////////////////////// Structura Hash Table Mecanismul Chaining & Linear Probing ////////////////////////////////
HashTable* creareHashTable(int dimensiuneHashTable)
{
	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
	hashTable->size = dimensiuneHashTable;
	hashTable->liste = (NodLista**)malloc(sizeof(NodLista*)*hashTable->size);
	for (int i = 0; i < hashTable->size; i++)
	{
		hashTable->liste[i] = NULL;
	}
	return hashTable;
}

void afisareHashTable(HashTable* hashTable)
{
	printf("%s", "Documente Aflate In Hash Table \n");
	if (hashTable != NULL)
	{
		if (hashTable->liste != NULL)
		{
			for (int i = 0; i < hashTable->size; i++)
			{
				NodLista* tmp = hashTable->liste[i];
				afisareListaCirculara(tmp);
			}
		}
	}
	else
	{
		printf("Tabela Hash Goala\n");
	}
}

int functiaHash(HashTable* hashTable, double dimensiuneDocument)
{
	printf("index %d \n", (int)dimensiuneDocument%hashTable->size);
	return (int)dimensiuneDocument%hashTable->size;
}

float calculeazaGradulDeIncarcare(HashTable* hashTable)
{
	int pozitiiOcupate = 0;
	if (hashTable != NULL)
	{
		if (hashTable->liste != NULL)
		{
			for (int indexHashTable = 0; indexHashTable < hashTable->size; indexHashTable++)
			{
				NodLista* tmp = hashTable->liste[indexHashTable];
				if (tmp != NULL)
				{
					pozitiiOcupate++;
				}
			}
			return (float)pozitiiOcupate / (float)hashTable->size;
		}
	}
}

HashTable* inserareHashTableChaining(HashTable* &hashTable, NodLista* nod);

HashTable* inserareHashTableLinearProbing(HashTable* &hashTable, NodLista* nod);

void dezalocaHashTable(HashTable* &hashTable);

void copiereHashTableInHashTableLinearProbing(HashTable* &rezultat, HashTable* sursa)
{
	if (sursa != NULL)
	{
		if (sursa->liste != NULL)
		{
			for (int indexHashTable = 0; indexHashTable < sursa->size; indexHashTable++)
			{
				if (sursa->liste[indexHashTable] != NULL)
				{
					NodLista* temp = sursa->liste[indexHashTable];
					while (temp->next != sursa->liste[indexHashTable])
					{
						Document document;
						document.idDocument = temp->info.idDocument;
						document.continutDocument = (char*)malloc(sizeof(char)*strlen(temp->info.continutDocument) + 1);
						strcpy(document.continutDocument, temp->info.continutDocument);
						document.dimensiuneDocument = temp->info.dimensiuneDocument;
						document.autorDocument = (char*)malloc(sizeof(char)*strlen(temp->info.autorDocument) + 1);
						strcpy(document.autorDocument, temp->info.autorDocument);
						document.formatDocument = (FormatDocument)temp->info.formatDocument;
						inserareHashTableLinearProbing(rezultat, creareNodLista(document));
						temp = temp->next;
					}
					Document document;
					document.idDocument = temp->info.idDocument;
					document.continutDocument = (char*)malloc(sizeof(char)*strlen(temp->info.continutDocument) + 1);
					strcpy(document.continutDocument, temp->info.continutDocument);
					document.dimensiuneDocument = temp->info.dimensiuneDocument;
					document.autorDocument = (char*)malloc(sizeof(char)*strlen(temp->info.autorDocument) + 1);
					strcpy(document.autorDocument, temp->info.autorDocument);
					document.formatDocument = (FormatDocument)temp->info.formatDocument;
					inserareHashTableLinearProbing(rezultat, creareNodLista(document));
				}
			}
		}
	}
}

void copiereHashTableInHashTableChaining(HashTable* &rezultat, HashTable* sursa)
{
	if (sursa != NULL)
	{
		if (sursa->liste != NULL)
		{
			for (int indexHashTable = 0; indexHashTable < sursa->size; indexHashTable++)
			{
				if (sursa->liste[indexHashTable] != NULL)
				{
					NodLista* temp = sursa->liste[indexHashTable];
					while (temp->next != sursa->liste[indexHashTable])
					{
						Document document;
						document.idDocument = temp->info.idDocument;
						document.continutDocument = (char*)malloc(sizeof(char)*strlen(temp->info.continutDocument) + 1);
						strcpy(document.continutDocument, temp->info.continutDocument);
						document.dimensiuneDocument = temp->info.dimensiuneDocument;
						document.autorDocument = (char*)malloc(sizeof(char)*strlen(temp->info.autorDocument) + 1);
						strcpy(document.autorDocument, temp->info.autorDocument);
						document.formatDocument = (FormatDocument)temp->info.formatDocument;
						inserareHashTableChaining(rezultat, creareNodLista(document));
						temp = temp->next;
					}
					Document document;
					document.idDocument = temp->info.idDocument;
					document.continutDocument = (char*)malloc(sizeof(char)*strlen(temp->info.continutDocument) + 1);
					strcpy(document.continutDocument, temp->info.continutDocument);
					document.dimensiuneDocument = temp->info.dimensiuneDocument;
					document.autorDocument = (char*)malloc(sizeof(char)*strlen(temp->info.autorDocument) + 1);
					strcpy(document.autorDocument, temp->info.autorDocument);
					document.formatDocument = (FormatDocument)temp->info.formatDocument;
					inserareHashTableChaining(rezultat, creareNodLista(document));
				}
			}
		}
	}
}

HashTable* inserareHashTableChaining(HashTable* &hashTable, NodLista* nod)
{
	if (calculeazaGradulDeIncarcare(hashTable) >= 0.75)
	{
		printf("Realocare Hash Table\n");
		printf("Gradul De Ocupare %4.2f \n", calculeazaGradulDeIncarcare(hashTable));
		HashTable* rezultat = creareHashTable(hashTable->size * 2);
		copiereHashTableInHashTableChaining(rezultat, hashTable);
		dezalocaHashTable(hashTable);
		hashTable = rezultat;
	}
	int index = functiaHash(hashTable, nod->info.idDocument);
	hashTable->liste[index] = inserareInceputListaCirculara(hashTable->liste[index], nod);
	//hashTable->vectorListe[index] = inserareSfarsit(hashTable->vectorListe[index], nod);
	return hashTable;
}

HashTable* inserareHashTableLinearProbing(HashTable* &hashTable, NodLista* nod)
{
	if (calculeazaGradulDeIncarcare(hashTable) >= 0.75)
	{
		printf("Realocare Realocare Hash Table\n");
		printf("Gradul De Ocupare %4.2f \n", calculeazaGradulDeIncarcare(hashTable));
		HashTable* rezultat = creareHashTable(hashTable->size * 2);
		copiereHashTableInHashTableLinearProbing(rezultat, hashTable);
		dezalocaHashTable(hashTable);
		hashTable = rezultat;
	}
	int index = functiaHash(hashTable, nod->info.dimensiuneDocument);
	if (hashTable->liste[index] == NULL)
		hashTable->liste[index] = inserareInceputListaCirculara(hashTable->liste[index], nod);
	else
	{
		while (index < hashTable->size && hashTable->liste[index] != NULL)
			index++;

		if (index == hashTable->size)
		{
			index = functiaHash(hashTable, nod->info.dimensiuneDocument);

			while (index > 0 && hashTable->liste[index] != NULL)
				index--;

			if (index == 0)
				printf("\n Coliziune \n");
			else
				hashTable->liste[index] = inserareInceputListaCirculara(hashTable->liste[index], nod);
		}
		else
			hashTable->liste[index] = inserareInceputListaCirculara(hashTable->liste[index], nod);
	}
	return hashTable;
}

void dezalocaHashTable(HashTable* &hashTable)
{
	if (hashTable != NULL)
	{
		if (hashTable->liste != NULL)
		{
			for (int i = 0; i < hashTable->size; i++)
			{
				NodLista* tmp = hashTable->liste[i];
				while (tmp != NULL)
				{
					deazalocaListaCirculara(tmp);
				}
			}
			free(hashTable->liste);
			hashTable->liste = NULL;
		}
		free(hashTable);
		hashTable = NULL;
	}
	else
	{
		printf("Tabela Dispersie Goala\n");
	}
}

////////////////////////////// Structura Coada (LIFO) ///////////////////////////////////////////////////
void afisareNodCoada(NodCoada* nod)
{
	if (nod != NULL)
	{
		printf("%d ", nod->info.idDocument);
		printf("%s ", nod->info.continutDocument);
		printf("%4.1lf ", nod->info.dimensiuneDocument);
		printf("%s ", nod->info.autorDocument);
		afisareFormatDocument(nod->info.formatDocument);
		newLine();
	}
}

NodCoada* creareNodCoada(Document document)
{
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->info = document;
	nod->next = NULL;
	return nod;
}

NodCoada* inserareSfarsit(NodCoada* coada, NodCoada* nod)
{
	if (coada == NULL)
		return nod;
	else
	{
		NodCoada* tmp = coada;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = nod;
	}
	return coada;
}

Document extrageInceput(NodCoada* &coada)
{
	Document d;
	if (coada)
	{
		NodCoada* nodExtras = coada;
		coada = coada->next;
		d.idDocument = nodExtras->info.idDocument;
		d.formatDocument = (FormatDocument)nodExtras->info.idDocument;
		d.dimensiuneDocument = nodExtras->info.dimensiuneDocument;
		d.autorDocument = (char*)malloc(sizeof(char)*strlen(nodExtras->info.autorDocument) + 1);
		strcpy(d.autorDocument, nodExtras->info.autorDocument);
		d.continutDocument = (char*)malloc(sizeof(char)*strlen(nodExtras->info.continutDocument) + 1);
		strcpy(d.continutDocument, nodExtras->info.continutDocument);

		nodExtras->next = NULL;
		free(nodExtras->info.autorDocument);
		free(nodExtras->info.continutDocument);
		free(nodExtras);
		nodExtras = NULL;
	}
	else
	{
		printf("Coada Goala\n");
	}
	return d;
}

void afisareCoada(NodCoada* coada)
{
	printf("Documente Aflate In Coada \n");
	if (coada != NULL)
	{
		NodCoada* tmp = coada;
		while (tmp)
		{
			afisareNodCoada(tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		printf("Coada Goala\n");
	}
}

void dezalocaCoada(NodCoada* &coada)
{
	if (coada != NULL)
	{
		while (coada != NULL)
		{
			NodCoada* tmp = coada;
			coada = coada->next;
			tmp->next = NULL;
			free(tmp->info.continutDocument);
			free(tmp->info.autorDocument);
			free(tmp);
			tmp = NULL;
		}
	}
	else
	{
		printf("Coada Goala\n");
	}
}

////////////////// Structura Arbore Binar De Cautare (ABC) /////////////////////////////////////////////
NodArbore* creareNodArbore(Document document)
{
	NodArbore* nod = (NodArbore*)malloc(sizeof(NodArbore));
	nod->info = document;
	nod->stanga = NULL;
	nod->dreapta = NULL;
	return nod;
}

void afisareNodArbore(NodArbore* nod)
{
	if (nod != NULL)
	{
		printf("idDocument: %d ", nod->info.idDocument);
		printf("continutDocument: %s ", nod->info.continutDocument);
		printf("dimensiuneDocument: %4.1lf ", nod->info.dimensiuneDocument);
		printf("autorDocument: %s ", nod->info.autorDocument);
		printf("formatDocument: ");
		afisareFormatDocument(nod->info.formatDocument);
		newLine();
	}
}

void adaugaStangaDreapta(NodArbore* &radacina, NodArbore* nod)
{
	if (radacina == NULL)
		radacina = nod;
	else
	{
		if (radacina->info.idDocument < nod->info.idDocument)
		{
			if (radacina->dreapta != NULL)
				adaugaStangaDreapta(radacina->dreapta, nod);
			else
				radacina->dreapta = nod;
		}
		else
		{
			if (radacina->info.idDocument == nod->info.idDocument)
				printf("Exista\n");
			else
			{
				if (radacina->info.idDocument > nod->info.idDocument)
				{
					if (radacina->stanga != NULL)
						adaugaStangaDreapta(radacina->stanga, nod);
					else
						radacina->stanga = nod;
				}
			}
		}
	}
}

void parcurgeInordine(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		parcurgeInordine(radacina->stanga);
		afisareNodArbore(radacina);
		parcurgeInordine(radacina->dreapta);
	}
}

void dezalocaArbore(NodArbore* &radacina)
{
	if (radacina != NULL)
	{
		dezalocaArbore(radacina->stanga);
		dezalocaArbore(radacina->dreapta);
		{
			free(radacina->info.continutDocument);
			free(radacina->info.autorDocument);
			radacina->stanga = NULL;
			radacina->dreapta = NULL;
			free(radacina);
			radacina = NULL;
		}
	}
}

/////////////////////////////////////// Structura De Tip Vector (Masiv Unidimensional) ////////////////
Vector* creareVector(int dimensiuneVector)
{
	Vector* vector = (Vector*)malloc(sizeof(Vector));
	vector->vectorSetari = (Setari*)malloc(sizeof(Setari)*dimensiuneVector);
	vector->dimensiuneVector = dimensiuneVector;
	vector->indexCurent = 0;
	return vector;
}

void afisareSetare(Setari setare)
{
	printf("%s ", setare.delimitator);
	printf("%d ", setare.fataVerso);
	printf("%d ", setare.numarCopii);
	printf("%d", setare.printezaPortret);
	newLine();
}

void afisareVector(Vector* vector)
{
	if (vector != NULL)
	{
		for (int indexVector = 0; indexVector < vector->indexCurent; indexVector++)
		{
			afisareSetare(vector->vectorSetari[indexVector]);
		}
	}
	else
	{
		printf("\nVector Gol\n");
	}
}

void dezalocaVector(Vector* &vector)
{
	if (vector != NULL)
	{
		for (int indexVector = 0; indexVector < vector->indexCurent; indexVector++)
		{
			free(vector->vectorSetari[indexVector].delimitator);
		}
		free(vector->vectorSetari);
		vector->vectorSetari = NULL;
		vector->indexCurent = 0;
		vector->dimensiuneVector = 0;
		free(vector);
		vector = NULL;
	}
}

void copiereVectorInVector(Vector* &rezultat, Vector* sursa)
{
	if (sursa != NULL)
	{
		if (sursa->vectorSetari != NULL)
		{
			for (int indexVector = 0; indexVector < sursa->indexCurent; indexVector++)
			{
				Setari setare;
				setare.fataVerso = sursa->vectorSetari[indexVector].fataVerso;
				setare.printezaPortret = sursa->vectorSetari[indexVector].printezaPortret;
				setare.numarCopii = sursa->vectorSetari[indexVector].numarCopii;
				setare.delimitator = (char*)malloc(sizeof(char)*strlen(sursa->vectorSetari[indexVector].delimitator) + 1);
				strcpy(setare.delimitator, sursa->vectorSetari[indexVector].delimitator);
				rezultat->vectorSetari[indexVector] = setare;
				rezultat->indexCurent = indexVector + 1;
			}
		}
	}
}

void inserareSetari(Vector* &vector, Setari setare)
{
	if (vector->indexCurent == vector->dimensiuneVector)
	{
		printf("Realocare Vector\n");
		Vector* rezultat = creareVector(vector->dimensiuneVector * 2);
		copiereVectorInVector(rezultat, vector);
		dezalocaVector(vector);
		vector = rezultat;
	}
	int index = vector->indexCurent;
	vector->vectorSetari[index] = setare;
	vector->indexCurent = index + 1;
}

void afisareDimensiuneIndex(Vector* vector)
{
	if (vector != NULL)
	{
		if (vector->vectorSetari != NULL)
		{
			printf("Dimensiune Vector: %d\n", vector->dimensiuneVector);
			printf("Index Curent Vector: %d\n", vector->indexCurent);
		}
	}
}

/////////////////////////////////////// Structura De Tip Stiva (FIFO) //////////////////////////////////
void afisareNodStiva(NodStiva* nod)
{
	if (nod != NULL)
	{
		printf("%d ", nod->info.idDocument);
		printf("%s ", nod->info.continutDocument);
		printf("%4.1lf ", nod->info.dimensiuneDocument);
		printf("%s ", nod->info.autorDocument);
		afisareFormatDocument(nod->info.formatDocument);
		newLine();
	}
}

NodStiva* creareNodStiva(Document document)
{
	NodStiva* nod = (NodStiva*)malloc(sizeof(NodStiva));
	nod->info = document;
	nod->next = NULL;
	return nod;
}

NodStiva* inserareInceputStiva(NodStiva* &stiva, NodStiva* &nod)
{
	if (stiva == NULL)
		stiva = nod;
	else
	{
		nod->next = stiva;
		stiva = nod;
	}
	return stiva;
}

void afisareStiva(NodStiva* stiva)
{
	if (stiva != NULL)
	{
		NodStiva* tmp = stiva;
		while (tmp)
		{
			afisareNodStiva(tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		printf("Stiva Goala\n");
	}
}

void dezalocaStiva(NodStiva* &stiva)
{
	if (stiva != NULL)
	{
		while (stiva != NULL)
		{
			NodStiva* tmp = stiva;
			stiva = stiva->next;
			tmp->next = NULL;
			free(tmp->info.autorDocument);
			free(tmp->info.continutDocument);
			free(tmp);
			tmp = NULL;
		}
	}
	else
	{
		printf("Stiva Goala\n");
	}
}

/////////////////////////////////////// Structura Graf ///////////////////////////////////////////////
NodVecin* creareNodVecin(int id)
{
	NodVecin* nod = (NodVecin*)malloc(sizeof(NodVecin));
	nod->idImprimanta = id;
	nod->next = NULL;
	return nod;
}

NodGraf* creareNodGraf(Imprimanta imprimanta)
{
	NodGraf* nod = (NodGraf*)malloc(sizeof(NodGraf));
	nod->info = imprimanta;
	nod->info.numarVecini = 0;
	nod->next = NULL;
	return nod;
}

Graf* creareGraf(int dimensiuneGraf)
{
	Graf* graf = (Graf*)malloc(sizeof(Graf));
	graf->dimensiuneGraf = dimensiuneGraf;
	graf->indexCurent = 0;
	graf->vector = (NodGraf**)malloc(sizeof(NodGraf*)*graf->dimensiuneGraf);
	for (int indexVectorNoduriGraf = 0; indexVectorNoduriGraf < graf->dimensiuneGraf; indexVectorNoduriGraf++)
	{
		graf->vector[indexVectorNoduriGraf] = NULL;
	}
	return graf;
}

NodVecin* inserareVecinSfarsit(NodVecin* listaVecini, NodVecin* nod)
{
	if (listaVecini == NULL)
	{
		listaVecini = nod;
	}
	else
	{
		NodVecin* tmp = listaVecini;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = nod;
		nod = tmp;
	}
	return listaVecini;
}

void afisareNodGraf(NodGraf* nod)
{
	if (nod != NULL)
	{
		printf("Setari: ");
		printf("%d ", nod->info.setari.fataVerso);
		printf("%d ", nod->info.setari.numarCopii);
		printf("%d ", nod->info.setari.printezaPortret);
		printf("%s ", nod->info.setari.delimitator);
		printf(" Cerere: ");
		printf("%s ", nod->info.cerere.tipCerere);
		printf("%d ", nod->info.cerere.prioritate);
		printf(" Document: ");
		printf("%d ", nod->info.cerere.document.idDocument);
		printf("%s ", nod->info.cerere.document.continutDocument);
		printf("%4.1lf ", nod->info.cerere.document.dimensiuneDocument);
		printf("%s ", nod->info.cerere.document.autorDocument);
		afisareFormatDocument(nod->info.cerere.document.formatDocument);
	}
}

void afisareNodVecin(NodVecin* nod)
{
	if (nod != NULL)
	{
		printf(" %d", nod->idImprimanta);
	}
}

void afisareGraf(Graf* graf)
{
	if (graf != NULL)
	{
		if (graf->vector != NULL)
		{
			for (int i = 0; i < graf->dimensiuneGraf; i++)
			{
				if (graf->vector[i] != NULL)
				{
					afisareNodGraf(graf->vector[i]);
					NodVecin* tmp = graf->vector[i]->next;
					printf("vecini:");
					while (tmp)
					{
						afisareNodVecin(tmp);
						tmp = tmp->next;
					}
					newLine();
				}
			}
		}
	}
	else
	{
		printf("Graf Gol\n");
	}
}

void dezalocaListaVecini(NodVecin* &lista)
{
	while (lista != NULL)
	{
		NodVecin* tmp = lista;
		lista = lista->next;
		free(tmp);
		tmp->next = NULL;
		tmp = NULL;
	}
	lista = NULL;
}

void dezalocareGraf(Graf* &graf)
{
	if (graf != NULL)
	{
		if (graf->vector != NULL)
		{
			for (int i = 0; i < graf->indexCurent; i++)
			{
				if (graf->vector[i] != NULL)
				{
					NodVecin* tmp = graf->vector[i]->next;
					dezalocaListaVecini(tmp);
					NodGraf* sterge = graf->vector[i];
					sterge->next = NULL;
					free(sterge->info.cerere.document.autorDocument);
					free(sterge->info.cerere.document.continutDocument);
					free(sterge->info.cerere.tipCerere);
					free(sterge->info.setari.delimitator);
					free(sterge);
					sterge = NULL;
				}
			}
		}
		free(graf->vector);
		graf->vector = NULL;
		free(graf);
		graf = NULL;
	}
	else
	{
		printf("Graf Gol\n");
	}
}

void copiereGrafInGraf(Graf* &rezultat, Graf* sursa)
{
	if (sursa != NULL)
	{
		if (sursa->vector != NULL)
		{
			for (int indexVector = 0; indexVector < sursa->indexCurent; indexVector++)
			{
				Imprimanta imprimanta;
				Document document;
				Cerere cerere;
				Setari setare;
				imprimanta.idImprimanta = sursa->vector[indexVector]->info.idImprimanta;
				document.idDocument = sursa->vector[indexVector]->info.cerere.document.idDocument;
				document.continutDocument = (char*)malloc(sizeof(char) * strlen(sursa->vector[indexVector]->info.cerere.document.continutDocument) + 1);
				strcpy(document.continutDocument, sursa->vector[indexVector]->info.cerere.document.continutDocument);
				document.dimensiuneDocument = sursa->vector[indexVector]->info.cerere.document.dimensiuneDocument;
				document.autorDocument = (char*)malloc(sizeof(char) * strlen(sursa->vector[indexVector]->info.cerere.document.autorDocument) + 1);
				strcpy(document.autorDocument, sursa->vector[indexVector]->info.cerere.document.autorDocument);
				document.formatDocument = (FormatDocument)sursa->vector[indexVector]->info.cerere.document.formatDocument;
				cerere.tipCerere = (char*)malloc(sizeof(char) * strlen(sursa->vector[indexVector]->info.cerere.tipCerere) + 1);
				strcpy(cerere.tipCerere, sursa->vector[indexVector]->info.cerere.tipCerere);
				cerere.prioritate = sursa->vector[indexVector]->info.cerere.prioritate;
				cerere.document = document;
				setare.delimitator = (char*)malloc(sizeof(char)* strlen(sursa->vector[indexVector]->info.setari.delimitator) + 1);
				strcpy(setare.delimitator, sursa->vector[indexVector]->info.setari.delimitator);
				setare.fataVerso = sursa->vector[indexVector]->info.setari.fataVerso;
				setare.numarCopii = sursa->vector[indexVector]->info.setari.numarCopii;
				setare.printezaPortret = sursa->vector[indexVector]->info.setari.printezaPortret;
				imprimanta.cerere = cerere;
				imprimanta.setari = setare;
				imprimanta.numarVecini = sursa->vector[indexVector]->info.numarVecini;
				NodGraf* nodGraf = creareNodGraf(imprimanta);
				while (sursa->vector[indexVector]->next)
				{
					nodGraf->next = inserareVecinSfarsit(nodGraf->next, creareNodVecin(sursa->vector[indexVector]->next->idImprimanta));
					sursa->vector[indexVector]->next = sursa->vector[indexVector]->next->next;
				}
				rezultat->vector[indexVector] = nodGraf;
				rezultat->indexCurent = indexVector + 1;
			}
		}
	}
}

Graf* inserareNodGraf(Graf* &graf, NodGraf* nod)
{
	if (graf->indexCurent == graf->dimensiuneGraf)
	{
		printf("Realocare Graf\n");
		Graf* rezultat = creareGraf(graf->dimensiuneGraf * 2);
		copiereGrafInGraf(rezultat, graf);
		dezalocareGraf(graf);
		graf = rezultat;
	}
	int index = graf->indexCurent;
	graf->vector[index] = nod;
	graf->indexCurent = index + 1;
	return graf;
}

/////////////////////////////////////// Structura Heap (Max) /////////////////////////////////////////
Heap* creareHeap(int dimensiuneHeap)
{
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	heap->dimensiuneHeap = dimensiuneHeap;
	heap->indexCurent = 0;
	heap->vectorCereri = (Cerere*)malloc(sizeof(Cerere)*heap->dimensiuneHeap);
	return heap;
}

void afisareCerere(Cerere cerere)
{
	printf("%d ", cerere.document.idDocument);
	printf("%s ", cerere.document.continutDocument);
	printf("%4.1lf ", cerere.document.dimensiuneDocument);
	printf("%s ", cerere.document.autorDocument);
	afisareFormatDocument(cerere.document.formatDocument);
	newLine();
}

void parcurgerePeNivele(Heap* heap)
{
	if (heap != NULL)
	{
		int NrElemNivel = 1;
		int nr = 0;
		for (int i = 0; i < heap->indexCurent; i++)
		{
			if (nr == NrElemNivel)
			{
				NrElemNivel = NrElemNivel * 2;
				nr = 0;
			}
			nr++;
			afisareCerere(heap->vectorCereri[i]);
		}
	}
}

void inteschimbare(Heap* heap, int index, int indexMax)
{
	Cerere tmp = heap->vectorCereri[index];
	heap->vectorCereri[index] = heap->vectorCereri[indexMax];
	heap->vectorCereri[indexMax] = tmp;
}

void filtrareHeap(Heap* heap, int index)
{
	int indexMax = index;
	int indexStg = 2 * index + 1;
	int indexDr = 2 * index + 2;
	if (indexStg < heap->indexCurent && heap->vectorCereri[indexStg].prioritate >
		heap->vectorCereri[indexMax].prioritate)
	{
		indexMax = indexStg;
	}
	if (indexDr < heap->indexCurent && heap->vectorCereri[indexDr].prioritate >
		heap->vectorCereri[indexMax].prioritate)
	{
		indexMax = indexDr;
	}
	if (index != indexMax)
	{
		inteschimbare(heap, index, indexMax);
	}
}

void dezalocaHeap(Heap* &heap)
{
	if (heap != NULL)
	{
		if (heap->vectorCereri != NULL)
		{
			for (int i = 0; i < heap->indexCurent; i++)
			{
				free(heap->vectorCereri[i].tipCerere);
				free(heap->vectorCereri[i].document.autorDocument);
				free(heap->vectorCereri[i].document.continutDocument);
			}
			free(heap->vectorCereri);
			heap->vectorCereri = NULL;
			heap->dimensiuneHeap = 0;
			heap->indexCurent = 0;
		}
		free(heap);
		heap = NULL;
	}
	else
	{
		printf("Heap Gol\n");
	}
}

void copiereHeapInHeap(Heap* &rezultat, Heap* sursa)
{
	if (sursa != NULL)
	{
		if (sursa->vectorCereri != NULL)
		{
			for (int indexVector = 0; indexVector < sursa->indexCurent; indexVector++)
			{
				Cerere cerere;
				Document document;
				cerere.tipCerere = (char*)malloc(sizeof(char)*strlen(sursa->vectorCereri[indexVector].tipCerere) + 1);
				strcpy(cerere.tipCerere, sursa->vectorCereri[indexVector].tipCerere);
				cerere.prioritate = sursa->vectorCereri[indexVector].prioritate;
				document.idDocument = sursa->vectorCereri[indexVector].document.idDocument;
				document.continutDocument = (char*)malloc(sizeof(char)*strlen(sursa->vectorCereri[indexVector].document.continutDocument) + 1);
				strcpy(document.continutDocument, sursa->vectorCereri[indexVector].document.continutDocument);
				document.dimensiuneDocument = sursa->vectorCereri[indexVector].document.dimensiuneDocument;
				document.autorDocument = (char*)malloc(sizeof(char)*strlen(sursa->vectorCereri[indexVector].document.autorDocument) + 1);
				strcpy(document.autorDocument, sursa->vectorCereri[indexVector].document.autorDocument);
				document.formatDocument = (FormatDocument)sursa->vectorCereri[indexVector].document.formatDocument;
				cerere.document = document;
				rezultat->vectorCereri[indexVector] = cerere;
				rezultat->indexCurent = indexVector + 1;
			}
		}
	}
}

void inserareCerere(Heap* &heap, Cerere cerere)
{
	if (heap->indexCurent == heap->dimensiuneHeap)
	{
		printf("Realocare Heap\n");
		Heap* rezultat = creareHeap(heap->dimensiuneHeap * 2);
		copiereHeapInHeap(rezultat, heap);
		dezalocaHeap(heap);
		heap = rezultat;
	}
	int	index = heap->indexCurent;
	heap->vectorCereri[index] = cerere;
	heap->indexCurent = index + 1;
	for (int i = (heap->indexCurent - 1) / 2; i >= 0; i--)
	{
		filtrareHeap(heap, i);
	}
}

/////////////////////////////////////// Functii suplimentare /////////////////////////////////////////
void fflushstdin()
{
	int c;
	while ((c = fgetc(stdin)) != EOF && c != '\n');
}

NodArbore* citireFisier(char numeFisier[20], int &isDocumente)
{
	NodArbore* radacina = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f)
	{
		char* token;
		char buffer[100000];
		char delimitator[4] = "^^^";
		while (fgets(buffer, sizeof(buffer), f))
		{
			Document document;

			token = strtok(buffer, delimitator);
			int idDocument = atoi(token);
			document.idDocument = idDocument;

			token = strtok(NULL, delimitator);
			document.continutDocument = (char*)malloc((strlen(token) + 1) * sizeof(char));
			strcpy(document.continutDocument, token);

			token = strtok(NULL, delimitator);
			double dimensiuneDocument = atol(token);
			document.dimensiuneDocument = dimensiuneDocument;

			token = strtok(NULL, delimitator);
			document.autorDocument = (char*)malloc(strlen(token) + 1 * sizeof(char));
			strcpy(document.autorDocument, token);

			token = strtok(NULL, delimitator);
			int format = atoi(token);
			document.formatDocument = (FormatDocument)format;

			NodArbore* nod = creareNodArbore(document);
			adaugaStangaDreapta(radacina, nod);
		}
		fclose(f);
		isDocumente = 1;
		return radacina;
	}
	else
	{
		isDocumente = 0;
		printf("Fisiserul Documente.txt Nu Exista\n");
	}
}

NodCoada* cautaArbore(NodArbore* radacina, NodCoada* &coada, int &idDocument)
{
	if (radacina != NULL)
	{
		if (radacina->info.idDocument == idDocument)
		{
			Document document;
			document.idDocument = radacina->info.idDocument;
			document.formatDocument = (FormatDocument)radacina->info.idDocument;
			document.dimensiuneDocument = radacina->info.dimensiuneDocument;
			document.autorDocument = (char*)malloc(sizeof(char)*strlen(radacina->info.autorDocument) + 1);
			strcpy(document.autorDocument, radacina->info.autorDocument);
			document.continutDocument = (char*)malloc(sizeof(char)*strlen(radacina->info.continutDocument) + 1);
			strcpy(document.continutDocument, radacina->info.continutDocument);
			NodCoada* nod = creareNodCoada(document);
			coada = inserareSfarsit(coada, nod);
		}
		cautaArbore(radacina->stanga, coada, idDocument);
		cautaArbore(radacina->dreapta, coada, idDocument);
	}
	return coada;
}

void printeazaDocumente(NodCoada* &coada, char numeFisier[20], Setari setari)
{
	FILE* f = fopen(numeFisier, "a+");
	if (f)
	{
		while (coada != NULL)
		{
			Document docExtras = extrageInceput(coada);
			for (int i = 0; i < setari.numarCopii; i++)
			{
				fprintf(f, "%s \n", docExtras.continutDocument);
			}
			printf("~~~ Se Printeaza Documentul Cu Id-ul %d ~~~\n", docExtras.idDocument);
		}
		coada = NULL;
		fclose(f);
	}
	else
	{
		printf("\n Printare Nereusita \n");
	}
}

void scaneazaDocument(NodLista* &lista, int &numarDocumente)
{
	while (numarDocumente > 0)
	{
		Document document;
		int id;
		printf("idDocument: ");
		scanf("%d", &id);
		document.idDocument = id;
		fflushstdin();

		printf("dimensiuneDocument: ");
		double dimensiuneDocument;
		scanf("%lf", &dimensiuneDocument);
		document.dimensiuneDocument = dimensiuneDocument;
		fflushstdin();

		int format;
		printf("formatDocument: ");
		scanf("%d", &format);
		document.formatDocument = (FormatDocument)format;
		fflushstdin();

		char buffer1[10000];
		printf("continutDocument: ");
		while (fgets(buffer1, sizeof(buffer1), stdin) != NULL)
		{
			buffer1[strcspn(buffer1, "" "\r\n")] = 0;
		}
		document.continutDocument = (char*)malloc(sizeof(char)*(strlen(buffer1) + 1));
		strcpy(document.continutDocument, buffer1);

		char buffer2[10000];
		printf("autorDocument: ");
		while (fgets(buffer2, sizeof(buffer2), stdin) != NULL)
		{
			buffer2[strcspn(buffer2, "" "\r\n")] = 0;
		}
		document.autorDocument = (char*)malloc(sizeof(char)*(strlen(buffer2) + 1));
		strcpy(document.autorDocument, buffer2);

		NodLista* nodLista = creareNodLista(document);
		lista = inserareInceputListaCirculara(lista, nodLista);
		numarDocumente--;
	}
}

void scrieListaInFisierText(NodLista* lista, char numeFisier[20], Setari setari)
{
	FILE* f = fopen(numeFisier, "a+");
	if (f)
	{
		if (lista != NULL)
		{
			NodLista* tmp = lista;
			while (tmp->next != lista)
			{
				for (int i = 0; i < setari.numarCopii; i++)
				{
					fprintf(f, "%d%s", tmp->info.idDocument, setari.delimitator);
					fprintf(f, "%s%s", tmp->info.continutDocument, setari.delimitator);
					fprintf(f, "%4.1lf%s", tmp->info.dimensiuneDocument, setari.delimitator);
					fprintf(f, "%s%s", tmp->info.autorDocument, setari.delimitator);
					fprintf(f, "%d%s\n", tmp->info.formatDocument, setari.delimitator);
				}
				tmp = tmp->next;
			}
			for (int i = 0; i < setari.numarCopii; i++)
			{
				fprintf(f, "%d%s", tmp->info.idDocument, setari.delimitator);
				fprintf(f, "%s%s", tmp->info.continutDocument, setari.delimitator);
				fprintf(f, "%4.1lf%s", tmp->info.dimensiuneDocument, setari.delimitator);
				fprintf(f, "%s%s", tmp->info.autorDocument, setari.delimitator);
				fprintf(f, "%d%s\n", tmp->info.formatDocument, setari.delimitator);
			}
		}
		else
		{
			printf("Lista Goala\n");
		}
		fclose(f);
	}
	else
	{
		printf("Scanare Documente Nereusita \n");
	}
}

void scrieListaInFisierTextCarduri(NodLista* lista, char numeFisier[20], Setari setari)
{
	FILE* f = fopen(numeFisier, "w");
	if (f)
	{
		if (lista != NULL)
		{
			NodLista* tmp = lista;
			while (tmp->next != lista)
			{
				for (int i = 0; i < setari.numarCopii; i++)
				{
					fprintf(f, "%s\n", tmp->info.continutDocument);
					fprintf(f, "\t\t%s\n", tmp->info.autorDocument);
				}
				tmp = tmp->next;
			}
			for (int i = 0; i < setari.numarCopii; i++)
			{
				fprintf(f, "%s\n", tmp->info.continutDocument);
				fprintf(f, "\t\t%s\n", tmp->info.autorDocument);
			}
		}
		else
		{
			printf("Lista Goala\n");
		}
		fclose(f);
	}
	else
	{
		printf("Printare Carduri Nereusita \n");
	}
}

void scrieListaInFisierTextOneTime(NodLista* lista, char numeFisier[20])
{
	FILE* f = fopen(numeFisier, "a+");
	if (f)
	{
		if (lista != NULL)
		{
			NodLista* tmp = lista;
			while (tmp->next != lista)
			{
				fprintf(f, "%d^^^", tmp->info.idDocument);
				fprintf(f, "%s^^^", tmp->info.continutDocument);
				fprintf(f, "%4.1lf^^^", tmp->info.dimensiuneDocument);
				fprintf(f, "%s^^^", tmp->info.autorDocument);
				fprintf(f, "%d^^^\n", tmp->info.formatDocument);
				tmp = tmp->next;
			}
			fprintf(f, "%d^^^", tmp->info.idDocument);
			fprintf(f, "%s^^^", tmp->info.continutDocument);
			fprintf(f, "%4.1lf^^^", tmp->info.dimensiuneDocument);
			fprintf(f, "%s^^^", tmp->info.autorDocument);
			fprintf(f, "%d^^^\n", tmp->info.formatDocument);
		}
		else
		{
			printf("Lista Goala\n");
		}
		fclose(f);
	}
	else
	{
		printf("Scriere DocumenteScanate.txt nereustia \n");
	}
}

void xeroxDocument(HashTable* &hashtable, int &numarDocumente)
{
	while (numarDocumente > 0)
	{
		printf("Intodu Numele Fisierului Care Va Fi Xeroxat: ");
		char tmp[100];
		scanf("%s", &tmp);
		strcat(tmp, ".txt");
		fflushstdin();
		FILE* f = fopen(tmp, "r");
		if (f)
		{
			char* token;
			char buffer[100000];
			char delimitator[4] = "^^^";
			while (fgets(buffer, sizeof(buffer), f))
			{
				Document d;

				token = strtok(buffer, delimitator);
				int idDocument = atoi(token);
				d.idDocument = idDocument;

				token = strtok(NULL, delimitator);
				d.continutDocument = (char*)malloc((strlen(token) + 1) * sizeof(char));
				strcpy(d.continutDocument, token);

				token = strtok(NULL, delimitator);
				double dimensiuneDocument = atol(token);
				d.dimensiuneDocument = dimensiuneDocument;

				token = strtok(NULL, delimitator);
				d.autorDocument = (char*)malloc(strlen(token) + 1 * sizeof(char));
				strcpy(d.autorDocument, token);

				token = strtok(NULL, delimitator);
				int format = atoi(token);
				d.formatDocument = (FormatDocument)format;

				NodLista* nodL = creareNodLista(d);
				hashtable = inserareHashTableChaining(hashtable, nodL);
				printf("Document Adaugat\n");
			}
			fclose(f);
		}
		else
		{
			printf("Xeroxare Nereusita\n");
		}
		numarDocumente--;
	}
}

HashTable* citesteCarduriFisier(char numeFisier[20], HashTable* &hashTable, int &isCarduri)
{
	FILE* f = fopen(numeFisier, "r");
	if (f)
	{
		char* token;
		char buffer[100000];
		char delimitator[4] = "^^^";
		while (fgets(buffer, sizeof(buffer), f))
		{
			Document document;

			token = strtok(buffer, delimitator);
			int idDocument = atoi(token);
			document.idDocument = idDocument;

			token = strtok(NULL, delimitator);
			document.continutDocument = (char*)malloc((strlen(token) + 1) * sizeof(char));
			strcpy(document.continutDocument, token);

			token = strtok(NULL, delimitator);
			double dimensiuneDocument = atol(token);
			document.dimensiuneDocument = dimensiuneDocument;

			token = strtok(NULL, delimitator);
			document.autorDocument = (char*)malloc(strlen(token) + 1 * sizeof(char));
			strcpy(document.autorDocument, token);

			token = strtok(NULL, delimitator);
			int format = atoi(token);
			document.formatDocument = (FormatDocument)format;

			NodLista* nodL = creareNodLista(document);
			hashTable = inserareHashTableChaining(hashTable, nodL);
		}
		isCarduri = 1;
		fclose(f);
	}
	else
	{
		printf("Printare Carduri Nereusita\n");
		isCarduri = 0;
	}
	return hashTable;
}

void scrieHashTableInFisierDocumente(HashTable* hashTable, Setari setari)
{
	int numarDocumente = 0;
	if (hashTable != NULL)
	{
		if (hashTable->liste != NULL)
		{
			for (int i = 0; i < hashTable->size; i++)
			{
				NodLista* tmp = hashTable->liste[i];
				if (tmp != NULL)
				{
					char numeFisiser[100];
					strcpy(numeFisiser, tmp->info.autorDocument);
					strcat(numeFisiser, ".txt");
					scrieListaInFisierText(tmp, numeFisiser, setari);
					tmp = tmp->next;
					numarDocumente++;
				}
			}
			printf("S-au Xeroxat/Printat %d Documente/Carduri\n", numarDocumente);
		}
	}
	else
	{
		printf("Tabela Hash Goala\n");
	}
}

void scrieHashTableInFisierTextCarduri(HashTable* hashTable, Setari setari)
{
	int numarDocumente = 0;
	if (hashTable != NULL)
	{
		if (hashTable->liste != NULL)
		{
			for (int i = 0; i < hashTable->size; i++)
			{
				NodLista* tmp = hashTable->liste[i];
				if (tmp != NULL)
				{
					char numeFisiser[100];
					strcpy(numeFisiser, tmp->info.autorDocument);
					strcat(numeFisiser, ".txt");
					scrieListaInFisierTextCarduri(tmp, numeFisiser, setari);
					tmp = tmp->next;
					numarDocumente++;
				}
			}
			printf("S-au Printat %d Carduri\n", numarDocumente);
		}
	}
	else
	{
		printf("Tabela Hash Goala\n");
	}
}

void citesteSetariFisier(Vector* &vectorSetari, char numeFisier[20], int &numarSetariExistente, int &isSetari)
{
	FILE*f = fopen(numeFisier, "r");
	if (f)
	{
		int indexVectorSetari = 0;
		while (!feof(f) != NULL)
		{
			Setari setare;
			fscanf(f, "%d ", &setare.printezaPortret);
			fscanf(f, "%d ", &setare.numarCopii);
			fscanf(f, "%d ", &setare.fataVerso);
			char buffer[4];
			fscanf(f, "%s ", &buffer);
			setare.delimitator = (char*)malloc(sizeof(char)*strlen(buffer) + 1);
			strcpy(setare.delimitator, buffer);
			inserareSetari(vectorSetari, setare);
		}
		numarSetariExistente = indexVectorSetari;
		fclose(f);
		isSetari = 1;
	}
	else
	{
		isSetari = 0;
		printf("Fisierul Setari.txt Nu Exista\n");
	}
}

void scrieSetariFisier(Vector* setari, char numeFisier[20])
{
	FILE* f = fopen(numeFisier, "w");
	if (f)
	{
		for (int i = 0; i < setari->indexCurent; i++)
		{
			fprintf(f, "%d ", setari->vectorSetari[i].printezaPortret);
			fprintf(f, "%d ", setari->vectorSetari[i].numarCopii);
			fprintf(f, "%d ", setari->vectorSetari[i].fataVerso);
			fprintf(f, "%s", setari->vectorSetari[i].delimitator);
			fprintf(f, "\n");
		}
		fprintf(f, "\n");
		fclose(f);
	}
	else
	{
		printf("\nEroare\n");
	}
}

Graf* grafCitireFisier(Graf* &graf, char numeFisier[20], int &isImprimante)
{
	FILE* f = fopen(numeFisier, "r");
	if (f)
	{
		char* token;
		char buffer[100000];
		char delimitator[4] = "^^^";
		char delimitatorVecini[2] = ",";
		while (fgets(buffer, sizeof(buffer), f))
		{
			Imprimanta imprimanta;
			Document document;
			Cerere cerere;
			Setari setare;
			token = strtok(buffer, delimitator);
			int idI = atoi(token);
			imprimanta.idImprimanta = idI;
			token = strtok(NULL, delimitator);
			int portret = atoi(token);
			setare.printezaPortret = portret;
			token = strtok(NULL, delimitator);
			int nrCopii = atoi(token);
			setare.numarCopii = nrCopii;
			token = strtok(NULL, delimitator);
			int fataV = atoi(token);
			setare.fataVerso = fataV;
			token = strtok(NULL, delimitator);
			setare.delimitator = (char*)malloc(sizeof(char) * sizeof(token) + 1);
			strcpy(setare.delimitator, token);
			token = strtok(NULL, delimitator);
			int idDocument = atoi(token);
			document.idDocument = idDocument;
			token = strtok(NULL, delimitator);
			document.continutDocument = (char*)malloc((strlen(token) + 1) * sizeof(char));
			strcpy(document.continutDocument, token);
			token = strtok(NULL, delimitator);
			double dimensiuneDocument = atol(token);
			document.dimensiuneDocument = dimensiuneDocument;
			token = strtok(NULL, delimitator);
			document.autorDocument = (char*)malloc(strlen(token) + 1 * sizeof(char));
			strcpy(document.autorDocument, token);
			token = strtok(NULL, delimitator);
			int format = atoi(token);
			document.formatDocument = (FormatDocument)format;
			cerere.document = document;
			cerere.prioritate = rand() % 100;
			char tip[20] = "GRAF";
			cerere.tipCerere = (char*)malloc(sizeof(char)*strlen(tip) + 1);
			strcpy(cerere.tipCerere, tip);
			cerere.document = document;
			imprimanta.cerere = cerere;
			imprimanta.setari = setare;
			token = strtok(NULL, delimitator);
			imprimanta.numarVecini = atoi(token);
			NodGraf* nodGraf = creareNodGraf(imprimanta);
			char* token2 = strtok(token, delimitatorVecini);
			for (int i = 0; i < imprimanta.numarVecini; i++)
			{
				token2 = strtok(NULL, delimitatorVecini);
				int vecin = atoi(token2);
				NodVecin* nodVecin = creareNodVecin(vecin);
				nodGraf->next = inserareVecinSfarsit(nodGraf->next, nodVecin);
			}
			graf = inserareNodGraf(graf, nodGraf);
		}
		isImprimante = 1;
		fclose(f);
		return graf;
	}
	else
	{
		printf("\n~~~ Eroare Citire imprimante.txt ~~~\n");
		isImprimante = 0;
	}
}

void scrieNodGrafText(NodGraf* nod, char numeFisiser[20])
{
	FILE* f = fopen(numeFisiser, "a+");
	if (f)
	{
		if (nod != NULL)
		{
			for (int i = 0; i < nod->info.setari.numarCopii; i++)
			{
				fprintf(f, "%s ", nod->info.cerere.tipCerere);
				fprintf(f, "%s ", nod->info.cerere.document.continutDocument);
				fprintf(f, "\n");
			}
		}
		fclose(f);
	}
	else
	{
		printf("\nScriere NodGraf In Fisiser Nereusita\n");
	}
}

void scrieNodVecinText(NodVecin* nod, char numeFisiser[20])
{
	FILE* f = fopen(numeFisiser, "a+");
	if (f)
	{
		if (nod != NULL)
		{
			//fprintf(f, "%d,", nod->idImprimanta);
		}
		fclose(f);
	}
	else
	{
		printf("\nScriere NodVecin In Fisiser Nereusita\n");
	}
}

void scrieGrafInText(Graf* graf)
{
	if (graf != NULL)
	{
		if (graf->vector != NULL)
		{
			for (int i = 0; i < graf->indexCurent; i++)
			{
				if (graf->vector[i] != NULL)
				{
					scrieNodGrafText(graf->vector[i], "NoduriScrise.txt");
					NodVecin* tmp = graf->vector[i]->next;
					while (tmp)
					{
						scrieNodVecinText(tmp, "NoduriScrise.txt");
						tmp = tmp->next;
					}
				}
			}
		}
	}
	else
	{
		printf("Graf Gol\n");
	}
}

void sortareInterschimbare(NodStiva* &stiva)
{
	for (NodStiva *nodCurent = stiva; nodCurent->next != NULL; nodCurent = nodCurent->next)
	{
		for (NodStiva *nodUrmator = nodCurent->next; nodUrmator != NULL; nodUrmator = nodUrmator->next)
		{
			if (nodCurent->info.dimensiuneDocument < nodUrmator->info.dimensiuneDocument)
			{
				Document aux = nodCurent->info;
				nodCurent->info = nodUrmator->info;
				nodUrmator->info = aux;
			}
		}
	}
}

void sortareStiva(NodStiva* &stiva, NodStiva* nodNou)
{
	NodStiva* nodCurent;
	if (stiva == NULL || strlen(stiva->info.continutDocument) < strlen(nodNou->info.continutDocument))
	{
		nodNou->next = stiva;
		stiva = nodNou;
	}
	else
	{
		nodCurent = stiva;
		while (nodCurent->next != NULL && strlen((nodCurent->next->info.continutDocument)) > strlen(nodNou->info.continutDocument))
		{

			nodCurent = nodCurent->next;
		}
		nodNou->next = nodCurent->next;
		nodCurent->next = nodNou;
	}
}

void sortareInsertie(NodStiva* &stiva)
{
	NodStiva* stivaSortata = NULL;
	NodStiva* nodCurent = stiva;
	while (nodCurent != NULL)
	{
		NodStiva *next = nodCurent->next;
		sortareStiva(stivaSortata, nodCurent);
		nodCurent = next;
	}
	stiva = stivaSortata;
}

void sortareBule(NodStiva* &stiva)
{
	bool stare = true;
	NodStiva* auxSort = NULL;
	while (stare == true)
	{
		stare = false;
		auxSort = stiva;
		while (auxSort->next)
		{
			if (auxSort->info.idDocument > auxSort->next->info.idDocument) // "<" for descending ">" for ascending
			{
				Document document = auxSort->info;
				auxSort->info = auxSort->next->info;
				auxSort->next->info = document;
				stare = true;
			}
			auxSort = auxSort->next;
		}
	}
}

void citesteCardTastatura(HashTable* &hashTable, int &numarCarduri)
{
	while (numarCarduri > 0)
	{
		Document document;
		int id;
		printf("idCard: ");
		scanf("%d", &id);
		document.idDocument = id;
		fflushstdin();

		char buffer[100];
		printf("SerieCard: ");
		scanf("%s", &buffer);
		fflushstdin();
		document.continutDocument = (char*)malloc(sizeof(char)*strlen(buffer) + 1);
		strcpy(document.continutDocument, buffer);
		document.dimensiuneDocument = 10;

		char buffer2[100];
		printf("autorDocument: ");
		scanf("%s", &buffer2);
		fflushstdin();
		document.autorDocument = (char*)malloc((strlen(buffer2) + 1) * sizeof(char));
		strcpy(document.autorDocument, buffer2);

		document.formatDocument = (FormatDocument)6;

		NodLista* nodLista = creareNodLista(document);
		hashTable = inserareHashTableLinearProbing(hashTable, nodLista);
		numarCarduri--;
	}
}

NodStiva* abcToStiva(NodStiva* &stiva, NodArbore* radacina)
{
	if (radacina != NULL)
	{
		abcToStiva(stiva, radacina->stanga);
		Document document;
		document.idDocument = radacina->info.idDocument;
		document.formatDocument = (FormatDocument)radacina->info.formatDocument;
		document.dimensiuneDocument = radacina->info.dimensiuneDocument;
		document.autorDocument = (char*)malloc(sizeof(char)*strlen(radacina->info.autorDocument) + 1);
		strcpy(document.autorDocument, radacina->info.autorDocument);
		document.continutDocument = (char*)malloc(sizeof(char)*strlen(radacina->info.continutDocument) + 1);
		strcpy(document.continutDocument, radacina->info.continutDocument);
		NodStiva* nod = creareNodStiva(document);
		stiva = inserareInceputStiva(stiva, nod);
		abcToStiva(stiva, radacina->dreapta);
	}
	return stiva;
}

NodStiva* htToStiva(NodStiva* &stiva, HashTable* hashTable)
{
	printf("%s", "Documente Aflate In Hash Table \n");
	if (hashTable != NULL)
	{
		if (hashTable->liste != NULL)
		{
			for (int i = 0; i < hashTable->size; i++)
			{
				NodLista* tmp = hashTable->liste[i];
				if (tmp)
				{
					NodLista* temp = tmp;
					while (temp->next != tmp)
					{
						Document document;
						document.idDocument = temp->info.idDocument;
						document.formatDocument = (FormatDocument)temp->info.formatDocument;
						document.dimensiuneDocument = temp->info.dimensiuneDocument;
						document.autorDocument = (char*)malloc(sizeof(char)*strlen(temp->info.autorDocument) + 1);
						strcpy(document.autorDocument, temp->info.autorDocument);
						document.continutDocument = (char*)malloc(sizeof(char)*strlen(temp->info.continutDocument) + 1);
						strcpy(document.continutDocument, temp->info.continutDocument);
						NodStiva* nodStiva = creareNodStiva(document);
						stiva = inserareInceputStiva(stiva, nodStiva);
						temp = temp->next;
					}
					Document document;
					document.idDocument = temp->info.idDocument;
					document.formatDocument = (FormatDocument)temp->info.formatDocument;
					document.dimensiuneDocument = temp->info.dimensiuneDocument;
					document.autorDocument = (char*)malloc(sizeof(char)*strlen(temp->info.autorDocument) + 1);
					strcpy(document.autorDocument, temp->info.autorDocument);
					document.continutDocument = (char*)malloc(sizeof(char)*strlen(temp->info.continutDocument) + 1);
					strcpy(document.continutDocument, temp->info.continutDocument);
					NodStiva* nodStiva = creareNodStiva(document);
					stiva = inserareInceputStiva(stiva, nodStiva);
				}
			}
		}
	}
	else
	{
		printf("Tabela Hash Goala\n");
	}
	return stiva;
}

NodStiva* coadaToStiva(NodStiva* & stiva, NodCoada* coadaDocumente)
{
	if (coadaDocumente != NULL)
	{
		NodCoada* tmp = coadaDocumente;
		while (tmp)
		{
			Document document;
			document.idDocument = tmp->info.idDocument;
			document.formatDocument = (FormatDocument)tmp->info.formatDocument;
			document.dimensiuneDocument = tmp->info.dimensiuneDocument;
			document.autorDocument = (char*)malloc(sizeof(char)*strlen(tmp->info.autorDocument) + 1);
			strcpy(document.autorDocument, tmp->info.autorDocument);
			document.continutDocument = (char*)malloc(sizeof(char)*strlen(tmp->info.continutDocument) + 1);
			strcpy(document.continutDocument, tmp->info.continutDocument);
			NodStiva* nodStiva = creareNodStiva(document);
			stiva = inserareInceputStiva(stiva, nodStiva);
			tmp = tmp->next;
		}
	}
	return stiva;
}

NodStiva* listaToStiva(NodStiva *& stiva, NodLista* lista)
{
	if (lista)
	{
		NodLista* tmp = lista;
		while (tmp->next != lista)
		{
			Document document;
			document.idDocument = tmp->info.idDocument;
			document.formatDocument = (FormatDocument)tmp->info.formatDocument;
			document.dimensiuneDocument = tmp->info.dimensiuneDocument;
			document.autorDocument = (char*)malloc(sizeof(char)*strlen(tmp->info.autorDocument) + 1);
			strcpy(document.autorDocument, tmp->info.autorDocument);
			document.continutDocument = (char*)malloc(sizeof(char)*strlen(tmp->info.continutDocument) + 1);
			strcpy(document.continutDocument, tmp->info.continutDocument);
			NodStiva* nodStiva = creareNodStiva(document);
			stiva = inserareInceputStiva(stiva, nodStiva);
			tmp = tmp->next;
		}
		Document document;
		document.idDocument = tmp->info.idDocument;
		document.formatDocument = (FormatDocument)tmp->info.formatDocument;
		document.dimensiuneDocument = tmp->info.dimensiuneDocument;
		document.autorDocument = (char*)malloc(sizeof(char)*strlen(tmp->info.autorDocument) + 1);
		strcpy(document.autorDocument, tmp->info.autorDocument);
		document.continutDocument = (char*)malloc(sizeof(char)*strlen(tmp->info.continutDocument) + 1);
		strcpy(document.continutDocument, tmp->info.continutDocument);
		NodStiva* nodStiva = creareNodStiva(document);
		stiva = inserareInceputStiva(stiva, nodStiva);
	}
	return stiva;
}

Heap* abcToHeap(Heap* &heap, NodArbore* radacina)
{
	if (radacina != NULL)
	{
		abcToHeap(heap, radacina->stanga);
		Document document;
		Cerere cerere;
		document.idDocument = radacina->info.idDocument;
		document.continutDocument = (char*)malloc(sizeof(char)*strlen(radacina->info.continutDocument) + 1);
		strcpy(document.continutDocument, radacina->info.continutDocument);
		document.autorDocument = (char*)malloc(sizeof(char)*strlen(radacina->info.autorDocument) + 1);
		strcpy(document.autorDocument, radacina->info.autorDocument);
		document.dimensiuneDocument = radacina->info.dimensiuneDocument;
		document.formatDocument = (FormatDocument)radacina->info.formatDocument;
		cerere.document = document;
		char tip[20] = "ABC";
		cerere.tipCerere = (char*)malloc(sizeof(char)*strlen(tip) + 1);
		strcpy(cerere.tipCerere, tip);
		int p = rand() % 100;
		cerere.prioritate = p;
		inserareCerere(heap, cerere);
		abcToHeap(heap, radacina->dreapta);
	}
	return heap;
}

Heap* htToHeap(Heap* &heap, HashTable* hashTable)
{
	if (hashTable != NULL)
	{
		if (hashTable->liste != NULL)
		{
			for (int i = 0; i < hashTable->size; i++)
			{
				NodLista* tmp = hashTable->liste[i];
				if (tmp)
				{
					NodLista* temp = tmp;
					while (temp->next != tmp)
					{
						Cerere cerere;
						Document document;
						document.idDocument = temp->info.idDocument;
						document.continutDocument = (char*)malloc(sizeof(char)*strlen(temp->info.continutDocument) + 1);
						strcpy(document.continutDocument, temp->info.continutDocument);
						document.autorDocument = (char*)malloc(sizeof(char)*strlen(temp->info.autorDocument) + 1);
						strcpy(document.autorDocument, temp->info.autorDocument);
						document.dimensiuneDocument = temp->info.dimensiuneDocument;
						document.formatDocument = (FormatDocument)temp->info.formatDocument;
						cerere.document = document;
						char tip[20] = "HT";
						cerere.tipCerere = (char*)malloc(sizeof(char)*strlen(tip) + 1);
						strcpy(cerere.tipCerere, tip);
						int p = rand() % 100;
						cerere.prioritate = p;
						inserareCerere(heap, cerere);
						temp = temp->next;
					}
					Document document;
					Cerere cerere;
					document.idDocument = temp->info.idDocument;
					document.continutDocument = (char*)malloc(sizeof(char)*strlen(temp->info.continutDocument) + 1);
					strcpy(document.continutDocument, temp->info.continutDocument);
					document.autorDocument = (char*)malloc(sizeof(char)*strlen(temp->info.autorDocument) + 1);
					strcpy(document.autorDocument, temp->info.autorDocument);
					document.dimensiuneDocument = temp->info.dimensiuneDocument;
					document.formatDocument = (FormatDocument)temp->info.formatDocument;
					cerere.document = document;
					char tip[20] = "HT";
					cerere.tipCerere = (char*)malloc(sizeof(char)*strlen(tip) + 1);
					strcpy(cerere.tipCerere, tip);
					int p = rand() % 100;
					cerere.prioritate = p;
					inserareCerere(heap, cerere);
				}
			}
		}
	}
	else
	{
		printf("Tabela Hash Goala\n");
	}
	return heap;
}

Heap* coadaToHeap(Heap* &heap, NodCoada* coadaDocumente)
{
	if (coadaDocumente != NULL)
	{
		NodCoada* tmp = coadaDocumente;
		while (tmp)
		{
			Document document;
			Cerere cerere;
			document.idDocument = tmp->info.idDocument;
			document.continutDocument = (char*)malloc(sizeof(char)*strlen(tmp->info.continutDocument) + 1);
			strcpy(document.continutDocument, tmp->info.continutDocument);
			document.autorDocument = (char*)malloc(sizeof(char)*strlen(tmp->info.autorDocument) + 1);
			strcpy(document.autorDocument, tmp->info.autorDocument);
			document.dimensiuneDocument = tmp->info.dimensiuneDocument;
			document.formatDocument = (FormatDocument)tmp->info.formatDocument;
			cerere.document = document;
			char tip[20] = "QUEUE";
			cerere.tipCerere = (char*)malloc(sizeof(char)*strlen(tip) + 1);
			strcpy(cerere.tipCerere, tip);
			int p = rand() % 100;
			cerere.prioritate = p;
			inserareCerere(heap, cerere);
			tmp = tmp->next;
		}
	}
	return heap;
}

Heap* listaToHeap(Heap* &heap, NodLista* lista)
{
	if (lista)
	{
		NodLista* temp = lista;
		while (temp->next != lista)
		{
			Document document;
			Cerere cerere;
			document.idDocument = temp->info.idDocument;
			document.continutDocument = (char*)malloc(sizeof(char)*strlen(temp->info.continutDocument) + 1);
			strcpy(document.continutDocument, temp->info.continutDocument);
			document.autorDocument = (char*)malloc(sizeof(char)*strlen(temp->info.autorDocument) + 1);
			strcpy(document.autorDocument, temp->info.autorDocument);
			document.dimensiuneDocument = temp->info.dimensiuneDocument;
			document.formatDocument = (FormatDocument)temp->info.formatDocument;
			cerere.document = document;
			char tip[20] = "LIST";
			cerere.tipCerere = (char*)malloc(sizeof(char)*strlen(tip) + 1);
			strcpy(cerere.tipCerere, tip);
			int p = rand() % 100;
			cerere.prioritate = p;
			inserareCerere(heap, cerere);
			temp = temp->next;
		}

		Document document;
		Cerere cerere;
		document.idDocument = temp->info.idDocument;
		document.continutDocument = (char*)malloc(sizeof(char)*strlen(temp->info.continutDocument) + 1);
		strcpy(document.continutDocument, temp->info.continutDocument);
		document.autorDocument = (char*)malloc(sizeof(char)*strlen(temp->info.autorDocument) + 1);
		strcpy(document.autorDocument, temp->info.autorDocument);
		document.dimensiuneDocument = temp->info.dimensiuneDocument;
		document.formatDocument = (FormatDocument)temp->info.formatDocument;
		cerere.document = document;
		char tip[20] = "LIST";
		cerere.tipCerere = (char*)malloc(sizeof(char)*strlen(tip) + 1);
		strcpy(cerere.tipCerere, tip);
		int p = rand() % 100;
		cerere.prioritate = p;
		inserareCerere(heap, cerere);
	}
	return heap;
}

void adaugaSetari(Vector* &vector, int &numarSetari, int &setariExistente)
{
	while (numarSetari > 0)
	{
		Setari setare;
		printf("Printeaza Portret: ");
		scanf("%d", &setare.printezaPortret);
		printf("Numar Copii: ");
		scanf("%d", &setare.numarCopii);
		printf("Fata-Verso: ");
		scanf("%d", &setare.fataVerso);
		printf("Delimitator: ");
		char buffer[4];
		scanf("%s", &buffer);
		setare.delimitator = (char*)malloc(sizeof(char)*strlen(buffer) + 1);
		strcpy(setare.delimitator, buffer);
		inserareSetari(vector, setare);
		numarSetari--;
	}
}

void scrieHeapInText(char numeFisier[20], Heap* heap, Setari setareaAleasa)
{
	FILE* f = fopen(numeFisier, "a+");
	if (f)
	{
		if (heap != NULL)
		{
			int NrElemNivel = 1;
			int nr = 0;
			for (int i = 0; i < heap->indexCurent; i++)
			{
				if (nr == NrElemNivel)
				{
					NrElemNivel = NrElemNivel * 2;
					nr = 0;
				}
				nr++;
				for (int contor = 0; contor < setareaAleasa.numarCopii; contor++)
				{
					fprintf(f, "%s ", heap->vectorCereri[i].tipCerere);
					fprintf(f, "%d ", heap->vectorCereri[i].prioritate);
					fprintf(f, "%d ", heap->vectorCereri[i].document.idDocument);
					fprintf(f, "%s ", heap->vectorCereri[i].document.continutDocument);
					fprintf(f, "%4.1lf ", heap->vectorCereri[i].document.dimensiuneDocument);
					fprintf(f, "%s ", heap->vectorCereri[i].document.autorDocument);
					fprintf(f, "%d \n", heap->vectorCereri[i].document.formatDocument);
				}
			}
			fclose(f);
		}
	}
	else
	{
		printf("Eroare\n");
	}
}

void afiseazaMeniuFunctionalitati()
{
	printf("~~~ Alege O Optiune Din Meniul Functionalitati ~~~\n");
	printf("1 Pentru Vizualizare Documente Citite:\n");
	printf("2 Pentru Printare Documente:\n");
	printf("3 Pentru Scanare Document:\n");
	printf("4 Pentru Xerox Document:\n");
	printf("5 Pentru Printare Carduri:\n");
	printf("6 Pentru Sortari:\n");
	printf("7 Pentru Graf:\n");
	printf("8 Pentru Coada De Proritati:\n");
	printf("9 Pentru Setari:\n");
	printf("10 Pentru Exit:\n");
}

void afiseazaMeniuSetari()
{
	printf("~~~ Alege O Optiune Din Meniul Setari ~~~\n");
	printf("1 Pentru Vizualizare Setari Disponibile:\n");
	printf("2 Pentru Adaugarea Unor Noi Setari:\n");
	printf("3 Pentru Selectarea Unei Optiuni:\n");
	printf("4 Pentru Vizualizarea Setarii Curente:\n");
	printf("5 Pentru Trecerea Mai Departe:\n");
}

void dezalocaMemoria(NodArbore* &arboreDocumente, NodCoada* &coadaDocumente, NodLista* &documenteScanate,
	HashTable* &hashTableDocumente, HashTable* &hashTableCarduri, NodStiva* &stivaPentruSortare,
	Graf* &grafImprimante, Heap* &heapDocumente, Vector* &vectorSetari)
{
	dezalocaArbore(arboreDocumente);
	dezalocaCoada(coadaDocumente);
	deazalocaListaCirculara(documenteScanate);
	dezalocaHashTable(hashTableCarduri);
	dezalocaHashTable(hashTableDocumente);
	dezalocaStiva(stivaPentruSortare);
	dezalocareGraf(grafImprimante);
	dezalocaHeap(heapDocumente);
	dezalocaVector(vectorSetari);
}

void afisareToateStructurile(NodArbore* arboreDocumente, NodCoada* coadaDocumente, NodLista* documenteScanate,
	HashTable* hashTableDocumente, HashTable* hashTableCarduri, NodStiva* stivaPentruSortare,
	Graf* grafImprimante, Heap* heapDocumente, Vector* vectorSetari)
{
	printf("~~~ Incercarea De A Afisa Toate Structurile Dupa Dezalocare ~~~\n");
	printf("~~~ Afisare Arbore ~~~\n");
	parcurgeInordine(arboreDocumente);
	printf("~~~ Afisare Coada ~~~\n");
	afisareCoada(coadaDocumente);
	printf("~~~ Afisare Lista Circulara ~~~\n");
	afisareListaCirculara(documenteScanate);
	printf("~~~ Afisare Hash Documente ~~~\n");
	afisareHashTable(hashTableDocumente);
	printf("~~~ Afisare Hash Carduri ~~~\n");
	afisareHashTable(hashTableCarduri);
	printf("~~~ Afisare Stiva ~~~\n");
	afisareStiva(stivaPentruSortare);
	printf("~~~ Afisare Graf ~~~\n");
	afisareGraf(grafImprimante);
	printf("~~~ Afisare Heap ~~~\n");
	parcurgerePeNivele(heapDocumente);
	printf("~~~ Afisare Vector ~~~\n");
	afisareVector(vectorSetari);
}

void main()
{
	int isSetari = 0;
	int isDocumente = 0;
	int isImprimante = 0;
	int isCarduri = 0;
	int indexHeap = 0;
	printf("~~~ In Acest Proiect S-a Incercat Simularea Unei Imprimante ~~~\n");
	NodArbore* arboreDocumente = citireFisier("Documente.txt", isDocumente);
	NodCoada* coadaDocumente = NULL;
	NodLista* documenteScanate = NULL;
	HashTable* hashTableDocumente = creareHashTable(5);
	HashTable* hashTableCarduri = creareHashTable(5);
	hashTableCarduri = citesteCarduriFisier("Carduri.txt", hashTableCarduri, isCarduri);
	NodStiva* stivaPentruSortare = NULL;
	Graf* grafImprimante = creareGraf(5);
	grafImprimante = grafCitireFisier(grafImprimante, "Imprimante.txt", isImprimante);
	Heap* heapDocumente = NULL;
	int numarSetariExistente = 0;
	Vector* vectorSetari = creareVector(5);
	citesteSetariFisier(vectorSetari, "Setari.txt", numarSetariExistente, isSetari);
	if ((isSetari == 1) & (isDocumente == 1) & (isImprimante == 1) & (isCarduri == 1))
	{
		Setari setareaAleasa = vectorSetari->vectorSetari[0];
		printf("~~~ Configuratia Curenta A Imprimantei ~~~\n");
		afisareSetare(setareaAleasa);
		////////////////////////////////////////////////////////// Meniul Functionalitatilor ///////////////////////////////////////////////////
		afiseazaMeniuFunctionalitati();
		int indexFunctionalitati = 0;
		while (indexFunctionalitati != 10)
		{
			printf("Introdu Numarul Optiunii: ");
			scanf("%d", &indexFunctionalitati);
			fflushstdin();

			if (indexFunctionalitati == 0)
			{
				printf("~~~ Ai Introdus O Optiune Invalida ~~~\n");
				afiseazaMeniuFunctionalitati();
				printf("Introdu Numarul Optiunii: ");
				scanf("%d", &indexFunctionalitati);
				fflushstdin();
			}

			while (indexFunctionalitati > 10)
			{
				printf("~~~ Ai Introdus O Optiune Invalida ~~~\n");
				afiseazaMeniuFunctionalitati();
				printf("Introdu Numarul Optiunii: ");
				scanf("%d", &indexFunctionalitati);
				fflushstdin();
			}

			while (indexFunctionalitati < 0)
			{
				printf("~~~ Ai Introdus O Optiune Invalida ~~~\n");
				afiseazaMeniuFunctionalitati();
				printf("Introdu Numarul Optiunii: ");
				scanf("%d", &indexFunctionalitati);
				fflushstdin();
			}

			if (indexFunctionalitati == 1)
			{
				parcurgeInordine(arboreDocumente);
				afiseazaMeniuFunctionalitati();
				indexFunctionalitati = 0;
			}

			if (indexFunctionalitati == 2)
			{
				printf("~~~ Alege Un Document Din Lista: ~~~ \n");
				parcurgeInordine(arboreDocumente);
				int idDoc = -99;
				while (idDoc != -1)
				{
					printf("Id-ul Documentului Care Doriti Sa Il Printati: ");
					scanf_s("%d", &idDoc);
					fflushstdin();
					coadaDocumente = cautaArbore(arboreDocumente, coadaDocumente, idDoc);
				}
				printeazaDocumente(coadaDocumente, "DocumentePrintate.txt", setareaAleasa);
				afiseazaMeniuFunctionalitati();
				indexFunctionalitati = 0;
			}

			if (indexFunctionalitati == 3)
			{
				int numarDocumente = -1;
				printf("Introdu Numarul De Documente Pe Care Vrei Sa Le Scanezi: ");
				scanf("%d", &numarDocumente);
				fflushstdin();
				scaneazaDocument(documenteScanate, numarDocumente);
				afisareListaCirculara(documenteScanate);
				scrieListaInFisierTextOneTime(documenteScanate, "DocumenteScanate.txt");
				afiseazaMeniuFunctionalitati();
				indexFunctionalitati = 0;
			}

			if (indexFunctionalitati == 4)
			{
				printf("~~~ Cate Documente Vei Xeroxa ~~~\n");
				int numarDocumente;
				printf("Introdu Numarul De Documente Pe Care Le Vei Xeroxa: ");
				scanf("%d", &numarDocumente);
				fflushstdin();
				while (numarDocumente > 0)
				{
					xeroxDocument(hashTableDocumente, numarDocumente);
				}
				afisareHashTable(hashTableDocumente);
				scrieHashTableInFisierDocumente(hashTableDocumente, setareaAleasa);
				afiseazaMeniuFunctionalitati();
				indexFunctionalitati = 0;
			}

			if (indexFunctionalitati == 5)
			{
				afisareHashTable(hashTableCarduri);
				int numarCarduri = -1;
				printf("Introdu Numarul De Carduri Pe Care Vrei Sa Le Introduci: ");
				scanf("%d", &numarCarduri);
				fflushstdin();
				while (numarCarduri > 0)
				{
					citesteCardTastatura(hashTableCarduri, numarCarduri);
				}
				afisareHashTable(hashTableCarduri);
				scrieHashTableInFisierTextCarduri(hashTableCarduri, setareaAleasa);
				afiseazaMeniuFunctionalitati();
				indexFunctionalitati = 0;
			}

			if (indexFunctionalitati == 6)
			{
				stivaPentruSortare = abcToStiva(stivaPentruSortare, arboreDocumente);
				stivaPentruSortare = htToStiva(stivaPentruSortare, hashTableCarduri);
				stivaPentruSortare = htToStiva(stivaPentruSortare, hashTableDocumente);
				stivaPentruSortare = coadaToStiva(stivaPentruSortare, coadaDocumente);
				stivaPentruSortare = listaToStiva(stivaPentruSortare, documenteScanate);

				newLine();
				printf("~~~ Stiva Nesortata ~~~\n");
				newLine();
				afisareStiva(stivaPentruSortare);

				newLine();
				printf("~~~ Sortare Prin Metoda Bulelor Crescator Dupa ID ~~~\n");
				newLine();
				sortareBule(stivaPentruSortare);
				afisareStiva(stivaPentruSortare);

				newLine();
				printf("~~~ Sortare Prin Interschimbare Descrescator Dupa Dimensiune ~~~\n");
				newLine();
				sortareInterschimbare(stivaPentruSortare);
				afisareStiva(stivaPentruSortare);

				newLine();
				printf("~~~ Sortare Prin Insertie Dupa Dimensiune Document (strlen) Crescator ~~~\n");
				newLine();
				sortareInsertie(stivaPentruSortare);
				afisareStiva(stivaPentruSortare);
				newLine();

				afiseazaMeniuFunctionalitati();
				dezalocaStiva(stivaPentruSortare);
				indexFunctionalitati = 0;
			}

			if (indexFunctionalitati == 7)
			{
				afisareGraf(grafImprimante);
				scrieGrafInText(grafImprimante);
				afiseazaMeniuFunctionalitati();
				indexFunctionalitati = 0;
			}

			if (indexFunctionalitati == 8)
			{
				heapDocumente = creareHeap(1);
				heapDocumente = abcToHeap(heapDocumente, arboreDocumente);
				heapDocumente = htToHeap(heapDocumente, hashTableCarduri);
				heapDocumente = htToHeap(heapDocumente, hashTableDocumente);
				heapDocumente = coadaToHeap(heapDocumente, coadaDocumente);
				heapDocumente = listaToHeap(heapDocumente, documenteScanate);
				parcurgerePeNivele(heapDocumente);
				scrieHeapInText("Prioritate.txt", heapDocumente, setareaAleasa);
				afiseazaMeniuFunctionalitati();
				dezalocaHeap(heapDocumente);
				indexFunctionalitati = 0;
			}

			if (indexFunctionalitati == 9)
			{
				///////////////////////////////////////////////////////// Meniul Setarilor ////////////////////////////////////////////////////////////////
				int indexSetari = 0;
				char password[20] = "admin";
				char buffer[20];
				printf("Introdu Parola Administratorului Imprimantei: ");
				scanf("%s", &buffer);
				fflushstdin();
				if (strcmp(password, buffer) == 0)
				{
					while (indexSetari != 5)
					{
						afiseazaMeniuSetari();
						printf("~~~ Alege O Optiune Din Lista ~~~\n");
						printf("Introdu Numarul Optiunii: ");
						scanf("%d", &indexSetari);
						fflushstdin();

						if (indexSetari == 0)
						{
							printf("~~~ Ai Introdus O Optiune Invalida ~~~\n");
							afiseazaMeniuSetari();
							printf("Introdu Numarul Optiunii: ");
							scanf("%d", &indexSetari);
							fflushstdin();
						}

						while (indexSetari > 5)
						{
							printf("~~~ Ai Introdus O Optiune Invalida ~~~\n");
							afiseazaMeniuSetari();
							printf("Introdu Numarul Optiunii: ");
							scanf("%d", &indexSetari);
							fflushstdin();
						}

						if (indexSetari == 1)
						{
							printf("~~~ Setarile Disponinile ~~~\n");
							afisareVector(vectorSetari);
							indexSetari = 0;
						}

						if (indexSetari == 2)
						{
							int numarSetariNoi;
							printf("Introdu Numarul De Setari Pe Care Vrei Sa Le Definesti: ");
							scanf("%d", &numarSetariNoi);
							fflushstdin();
							adaugaSetari(vectorSetari, numarSetariNoi, numarSetariExistente);
							scrieSetariFisier(vectorSetari, "Setari.txt");
							indexSetari = 0;
						}

						if (indexSetari == 3)
						{
							afisareVector(vectorSetari);
							printf("Intodu Numarul Configuratiei Dorite: ");
							int config;
							scanf("%d", &config);
							fflushstdin();
							if ((config >= 0) & (config < vectorSetari->indexCurent))
							{
								setareaAleasa = vectorSetari->vectorSetari[config];
								printf("~~~ Setarile Imprimantei Au Fost Modificate ~~~\n");
								afisareSetare(setareaAleasa);
								indexSetari = 0;
							}
						}

						if (indexSetari == 4)
						{
							printf("~~~ Setarea Curenta A Imprimantei ~~~\n");
							afisareSetare(setareaAleasa);
							indexSetari = 0;
						}

						if (indexSetari == 5)
						{
							indexFunctionalitati = 0;
							printf("~~~ Vei Ajunge In Meniul De Functionalitati ~~~\n");
							afiseazaMeniuFunctionalitati();
						}
					}
				}
				else
				{
					printf("~~~ Parola Incorecta!!! ~~~\n");
					afiseazaMeniuFunctionalitati();
					indexFunctionalitati = 0;
				}
			}

			if (indexFunctionalitati == 10)
			{
				newLine();
				dezalocaMemoria(arboreDocumente, coadaDocumente, documenteScanate, hashTableCarduri, hashTableDocumente, stivaPentruSortare, grafImprimante, heapDocumente, vectorSetari);
				afisareToateStructurile(arboreDocumente, coadaDocumente, documenteScanate, hashTableCarduri, hashTableDocumente, stivaPentruSortare, grafImprimante, heapDocumente, vectorSetari);
				newLine();
				printf("~~~ Program Terminat Apasa O Tasta Pentru A Inchide ~~~\n");
				_getch();
			}
		}
	}
	else
	{
		printf("\nUnul Dintre Fisiserele De Date Nu Exista\n");
		_getch();
	}
}