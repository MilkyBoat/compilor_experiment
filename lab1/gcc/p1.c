#include <stdio.h>

int main()
{
	int i, n, f;

	scanf("%d", &n);
	i = 2;
	f = 1;
	while (i <= n)
	{
		f = f * i;
		i = i + 1;
	}
	printf("%d\n", f);
}
