#include <stdio.h>
#include <stdlib.h>
#include "elem.h"

struct Elem *searchlist(struct Elem*, int);

int main()
{
	struct Elem e1;
	e1.tag = FLOAT;
	e1.value.f = 3e8;
	e1.tail = NULL;

	struct Elem e3;
	e3.tag = FLOAT;
	e3.value.f = 2.5;
	e3.tail = NULL;

	struct Elem e2;
	e2.tag = FLOAT;
	e2.value.f = 10.5e-5;
	e2.tail = &e3;

	struct Elem e0;
	e0.tag = LIST;
	e0.value.list = &e1;
	e0.tail = &e2;

	struct Elem *x = searchlist(&e0, 20);
	if (x == NULL) {
		printf("CORRECT\n");
	} else {
		/* Если функция searchlist работает правильно,
		сюда никогда не будет передано управление! */
		printf("WRONG\n");
	}

	return 0;
}
