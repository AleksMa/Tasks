#include <stdio.h>

int array[] = {
	404,
	453,
	652,
	657,
	807,
	930
};

const int k = 795;

int compare(unsigned long i)
{
	if (array[i] == k) return 0;
	if (array[i] < k) return -1;
	return 1;
}

unsigned long binsearch(unsigned long, int (*)(unsigned long));

int main(int argc, char **argv)
{
	printf("%lu\n", binsearch(6, compare));
	return 0;
}
