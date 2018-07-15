// Proiect2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
FILE *f;
#define inf 1<<20

typedef struct
{
	int nodI, nodF, val;
}legatura;

void citire2(int p, legatura v[20],int* m)
{
	while(!feof(f))
	{
		fscanf_s(f, "%d", &v[*m].nodI);
		fscanf_s(f, "%d", &v[*m].nodF);
		fscanf_s(f, "%d", &v[*m].val);
		*m = *m + 1;
	}
	*m = *m -1;
}

void afisareInput(int p, legatura v[20])
{
	int i;
	for (i = 0; i < p; i++)
		printf("(%d,%d) - %d\n", v[i].nodI, v[i].nodF, v[i].val);
	printf("\n");
}

void zerorizare(int p, int aux[20][20])
{
	int i, j;
	for (i = 0; i < p; i++)
		for (j = 0; j < p; j++)
			aux[i][j] = 0;
}

void creareMatrice(int p, int adiac[20][20], legatura v[20])
{
	int i;
	
	for (i = 0; i < p; i++)
		adiac[v[i].nodF-1][v[i].nodI-1] = adiac[v[i].nodI-1][v[i].nodF-1] = 1;
}

void infinitizare(int p, int aux[20][20])
{
	int i, j;
	for (i = 0; i < p; i++)
		for (j = 0; j < p; j++)
			aux[i][j] = inf;
}

void creareMatricePonderi(int p, int pond[20][20], legatura v[20])
{
	int i;
	for (i = 0; i < p; i++)
	{	
		pond[i][i] = 0;
		pond[v[i].nodF - 1][v[i].nodI - 1] = pond[v[i].nodI - 1][v[i].nodF - 1] = v[i].val;
	}
}

void afisareMartice(int n, int aux[20][20])
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			if (aux[i][j] == inf)
				printf("%c ", '*');
			else printf("%d ", aux[i][j]);
		printf("\n");
	}
	printf("\n");
}

void grad(int n, int a[20][20], int d[20])
{
	int i, j,nr;
	for (i = 0; i < n; i++)
	{
		nr = 0;
		for (j = 0; j < n; j++)
			if (a[i][j] == 1)
				nr++;
		d[i] = nr;
	}
}

void nodIzolat(int n, int a[20][20],int d[20])
{
	int i, nrNoduri=0;
	grad(n, a, d);
	for (i = 0; i < n; i++)
	{
		if (d[i] == 0)
		{
			printf("%d ", i+1);
			nrNoduri++;
		}
	}
	if (nrNoduri == 0)
		printf("(nu exista)\n");
	else printf("\n");
	printf("\n");
}

int grafRegulat(int n, int a[20][20], int d[20])
{
	int i, ok = 1;
	for (i = 0; i < n - 1; i++)
		if (d[i] != d[i + 1])
			ok = 0;
	return ok;
}

void detGrafRegulat(int n, int a[20][20], int d[20])
{
	if (grafRegulat(n, a, d))
		printf("Graful este regulat.\n");
	else printf("Graful nu este regulat.\n");
	printf("\n");
}

int min(int a, int b)
{
	if (a < b)
		return a;
	else return b;
}

void warshall(int n, int aux[20][20])
{
	int i,j,k;
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				aux[i][j] = min(aux[i][j], aux[i][k] + aux[k][j]);
					
}

void copiere(int n, int w[20][20], int a[20][20])
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if ((a[i][j] == 0) &&(i!=j))
				w[i][j] = inf;
			else w[i][j] = a[i][j];
}

int eConex(int n, int aux[20][20])
{
	int i,j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (aux[i][j] ==inf)
				return 0;
	return 1;
}

void conex(int n, int a[20][20])
{
	if (eConex(n,a)==1)
		printf("Graful e conex.\n");
	else printf("Graful nu e conex.\n");
	printf("\n");
}

int main()
{
	legatura v[20];
	int n, m=0, adiac[20][20], pond[20][20], warsh[20][20], grad[20];

	fopen_s(&f, "input.in", "r");

	//citire date de intrare
	fscanf_s(f, "%d", &n);

	printf("Date de intrare:\n");
	citire2(n, v,&m);
	afisareInput(m, v);

	//creare matrice adiacenta
	printf("Matricea de adiacenta: \n");
	zerorizare(n, adiac);
	creareMatrice(m, adiac, v);
	afisareMartice(n, adiac);

	//determinarea nodurilor izolate
	printf("Nodurile izolate: ");
	nodIzolat(n, adiac, grad);

	//determinare graf regulat
	detGrafRegulat(n, adiac, grad);

	//creare matrice ponderi
	printf("Matricea ponderilor: \n");
	infinitizare(n, pond);
	creareMatricePonderi(m, pond, v);
	afisareMartice(n, pond);

	//creare matrice distante
	printf("Matricea distantelor: \n");
	copiere(n, warsh, pond);
	warshall(n, warsh);
	afisareMartice(n, warsh);

	//determinare graf conex
	conex(n, warsh);

	fclose(f);
    return 0;
}