#include <stdio.h>

int prim(int x);
int prime_intre_ele(int x, int y);
int cmmdc(x, y);

int main() {
	int k=0, nr = 3, ok, comanda=0;
	printf("Programul afiseaza toate numerele naturale mai mari decat 2\ncu proprietatea ca toate numerele mai mici care sunt prime cu el\nsunt prime\n");
	while (1) {
		printf("1:executa\n2:exit\n");
		scanf_s("%d", &comanda);
		if(comanda!=1 && comanda!=2)
			printf("Comanda invalida");
		else if(comanda == 2)
			break;
		else if (comanda == 1)
		{
			k=0;
			nr = 3;
			while(k<8){
				ok=1;
				for (int i = 2; i < nr; i++) {
					if(prime_intre_ele(i, nr) && prim(i)==0)
						ok=0;
				}
				if (ok)
				{
					printf("%d ",nr);
					k++;
				}
				nr++;
			}
		}
		printf("\n");
	}
	
}

int prim(int x)
{
/*
test if a number is prime
x: int, the num to be tested
preconditions: x is an int
postconditions:return 1 if x is prime, 0 otherwise
*/
	if(x<2 || (x>2 && x%2==0))
		return 0;
	else {
		for(int d=3; d*d<=x; d+=2)
			if(x%d==0)
				return 0;
	}
	return 1;
}

static int cmmdc(int a, int b)
{
	int rest;
	while (b != 0) {
		rest = a%b;
		a=b;
		b=rest;
	}
	return a;
}

int prime_intre_ele(int x, int y)
{
/*
functie care testeaza daca 2 numere sunt prime intre ele
folosind cmmdc
preconditii: x,y numere naturale
postconditii: 1 daca x si y sunt prime intre ele, 0 altfel
*/
	if(x==0 || y==0)
		return 0;
	if(cmmdc(x,y)==1)
		return 1;
	return 0;
}