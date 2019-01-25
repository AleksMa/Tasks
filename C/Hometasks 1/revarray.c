#include <stdio.h>



unsigned long array[] = {
	17052000999081062155UL,
	7844146236621954665UL,
	102281693791187972UL,
	3712932412348307157UL,
	15171118595533986912UL,
	2395282194588458195UL,
	12097832858704557214UL
};

void revarray(void *base, unsigned long nel, unsigned long width)
{

    char *p = base;
    int k = 0;
    if(nel%2!=0)k=1;
    int N = width*(nel/2);
    for(int i = 0; i < N; i+=width){
        for(int j = 0; j < width; j++)
        {
            char t = p[i+j];
            p[i+j] = p[width*nel-i-width+j];
            p[width*nel-i-width+j] = t;
        }
    }

}





int main(int argc, char **argv)
{
	revarray(array, 7, sizeof(unsigned long));

	int i;
	for (i = 0; i < 7; i++) {
		printf("%lu\n", array[i]);
	}

	return 0;
}

