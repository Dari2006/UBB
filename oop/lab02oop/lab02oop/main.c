#include <stdio.h>

int prim(x);

int main()
{
	int comanda, nr_prime, k=0, ok;
	while (1)
	{
		printf("MENIU\n0: exit\n1: afiseaza toate numerele mai mici decat un numar\nIntroduceti comanda: ");
		scanf_s("%d", &comanda);
		if (comanda == 0)
		{
			break;
		}
		else if (comanda == 1)
		{
			ok = 0;
			int n=0;
			printf("Introduceti un numar: ");
			scanf_s("%d", &n);
			printf("\nNumerele prime mai mici decat %d sunt:\n", n);
			k=2;
			while (k < n)
			{
				if(prim(k))
				{
					printf("%d", k);
					printf(" ");
					ok = 1;
				}
				if(k==2)
					k=3;
				else
					k+=2;
			}
			if(ok==0)
				printf("Ups! Nu exista numere prime mai mici decat %d", n);
			printf("\n");
		}
		else
			printf("comanda invalida");
		printf("\n");
	}
	return 0;
}


/*
* Functia testeaza daca un numar este prim.
* pre: x numar intreg
* post: functia returneaza 1 daca numarul x este prim, 0 altfel
*/
int prim(int x)
{
	if(x<1 || (x%2==0 && x!=2))
		return 0;
	int d;
	for(d = 3; d*d<=x; d+=2)  //parcurgem numerele pana la radicalul lui x
		if(x%d==0)
			return 0;
	return 1;


}