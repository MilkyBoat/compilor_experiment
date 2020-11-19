#include <stdio.h>

int main()
{
	int a, b, i, t, n;

	a = 0;
	b = 1;
	i = 1;
	scanf("%d", &n);
	printf("%d ", b);
	while (i < n)
	{
		t = b;
		b = a + b;
		printf("%d ", b);
		a = t;
		i = i + 1;
	}
	printf("\n");
}
