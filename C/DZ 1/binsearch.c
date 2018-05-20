#include <stdio.h>

int compare(unsigned long i)
{
	if (i == 91052112271683405UL) return 0;
	if (i < 91052112271683405UL) return -1;
	return 1;
}


unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i))
{
    unsigned long a=0, b=nel-1;
    int cmp;
    unsigned long N = (a+b)/2;
    while(cmp=compare(N)){
        if(cmp<0){
                a=N;
        }
        else {
                b=N;
        }
        if(-a+b<2){
            N=nel;
            break;
        }
        N=(a+b)/2;
    }
    return N;
}

int main(int argc, char **argv)
{
	printf("%lu\n", binsearch(11742432862790734555UL, compare));
	return 0;
}
