// Proiect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
_CRT_SECURE_NO_WARNINGS;
FILE *f;
typedef struct 
{
	int extr1, extr2;
}muchie;

typedef struct
{
	int nod, vecini[10],numar;
}lista;

void citire(int* m, muchie v[10])
{
	while (!feof(f))
	{
		fscanf_s(f, "%d", &v[*m].extr1);
		fscanf_s(f, "%d", &v[*m].extr2);
		//printf("(%d,%d)\n", v[k].extr1, v[k].extr2);
		*m=*m+1;
	}
}

void matriceAdiacenta(int n, muchie v[10],int a[10][10])
{
	int i = 0;
	for (i = 0; i < n; i++)
		a[v[i].extr1-1][v[i].extr2-1] = a[v[i].extr2 - 1][v[i].extr1 - 1]=1;
}

void matriceIncidenta(int n,int m, int a[10][10], int i[10][20])
{
	int j, k,col=0;
	for (j = 0; j < n; j++)
		for (k = j + 1; k < m; k++)
			if (a[j][k] == 1)
			{
				i[j][col] = i[k][col] = 1;
				col++;
			}
}

void matriceAdiacenta2(int n, int m, int ap[10][10], int i[10][20])
{
	int j, k,extrem1,extrem2;
	for (k = 0; k < m; k++)
	{
		extrem1 = -1, extrem2 = -1;
		for (j = 0; j < n; j++)
		{
			if ((i[j][k] == 1) && (extrem1 == -1)&&(extrem2==-1))
			{
				extrem1 = j;
			}
			else if ((i[j][k] == 1) && (extrem1 != -1))
			{
				extrem2 = j;
				ap[extrem1][extrem2]=ap[extrem2][extrem1] = 1;
			}
		}
			
	}
}

void listaVecini(int n, int ap[10][10], lista l[10])
{
	int j, k;
	for (k = 0; k < n; k++)
	{
		l[k].nod = k + 1;
		l[k].numar = 0;
		for (j = 0; j < n; j++)
		{
			if (ap[j][k] == 1)
			{
				l[k].vecini[l[k].numar] = j + 1;
				l[k].numar = l[k].numar + 1;
			}
		}
		if (l[k].numar == 0)
			l[k].vecini[l[k].numar] = -1;
	}
}

void afisare(int m, muchie v[10])
{
	int i;
	for (i = 0; i < m; i++)
		printf("(%d,%d)\n", v[i].extr1, v[i].extr2);
}

void afisareMatriceAdiacenta(int n, int a[10][10])
{
	int i = 0, j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}	

void afisareMatriceIncidenta(int n, int m, int i[10][20])
{
	int j, k;
	for (j = 0; j < n; j++)
	{
		for (k = 0; k < m; k++)
		{
			printf("%d ", i[j][k]);
		}
		printf("\n");
	}
}

void afisareListaVecini(int n, lista l[10])
{
	int j, k;
	for (j = 0; j < n; j++)
	{
		printf("Nodul %d: ", l[j].nod);
		for (k = 0; k < l[j].numar; k++)
			printf("%d ", l[j].vecini[k]);
		printf("\n");
	}
}
int main()
{
	int n = -1, m = 0, a[10][10] = { 0 }, i[10][20] = { 0 }, ap[10][10] = { 0 };
	muchie v[10];
	lista l[10];


	fopen_s(&f,"input.in","r");
	fscanf_s(f, "%d", &n);
	citire(&m,v);
	printf("Elementele fisierului:\n");
	afisare(m, v);
	printf("\n");
	printf("Matricea de adiacenta:\n");
	matriceAdiacenta(n, v, a);
	afisareMatriceAdiacenta(n, a);
	printf("\n");
	printf("Matricea de incidenta:\n");
	matriceIncidenta(n, m, a, i);
	afisareMatriceIncidenta(n,m,i);
	printf("\n");
	printf("Matricea de adiacenta pornind de la matricea de incidenta:\n");
	matriceAdiacenta2(n, m, ap, i);
	afisareMatriceAdiacenta(n, ap);
	printf("\n");
	printf("Lista de vecini:\n");
	listaVecini(n, ap, l);
	afisareListaVecini(n, l);
	fclose(f);
    return 0;
}

