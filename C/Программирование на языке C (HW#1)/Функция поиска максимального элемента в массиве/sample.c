#include <stdio.h>

unsigned char array[] = {
	153,
	1,
	15,
	191,
	232,
	251,
	27,
	174,
	26,
	3,
	68,
	48
};

int compare(void *a, void *b)
{
	return (int)(*(unsigned char*)a) - (int)(*(unsigned char*)b);
}

int maxarray(void*, unsigned long, unsigned long,
	int (*)(void *a, void *b));

int main(int argc, char **argv)
{
	printf("%d\n", maxarray(array, 12, sizeof(unsigned char), compare));
	return 0;
}
