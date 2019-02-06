#include <stdio.h>

int array[] = {
	181,
	238,
	999,
	483,
	610,
	284,
	727,
	228
};

int less(unsigned long i, unsigned long j)
{
	return array[i] < array[j];
}

unsigned long peak(unsigned long, int (*)(unsigned long, unsigned long));

int main(int argc, char **argv)
{
	int i = peak(8, less);
	if ((i == 0 || array[i] >= array[i-1]) &&
		(i == 7 || array[i] >= array[i+1])) {
		printf("CORRECT\n");
	} else {
		/* Если функция peak работает правильно,
		сюда никогда не будет передано
		управление! */
		printf("WRONG\n");
	}
	return 0;
}
