#include <stdio.h>

int main() {
	int sum = 0, n, i, x;
	printf("introdu numarul de numere: ");
	scanf_s("%d", &n);

	printf("introdu numerele: ");
	for (i = 1; i <= n; i++)
	{
		scanf_s("%d", &x);
		sum+=x;
	}

	printf("Suma este: %d", sum);


	return 0;
}