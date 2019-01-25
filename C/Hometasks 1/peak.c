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

unsigned long peak(unsigned long nel,
        int (*less)(unsigned long i, unsigned long j))
{
    unsigned long P=0;
    if(!less(0, 1))return 0;
    else if(!less(nel-1, nel-2)) return nel-1;
    else{
        unsigned long a=0, b=nel-1, N=a/2+b/2;
        //printf("%lu\n", N);
        while(!P){
            if(less(N, N-1)){
                    b=N;
            }
            else if (less(N, N+1)) a=N;
            else {
                P=N;
                break;
            }
            N=a/2 + b/2;
            if(a%2==1 && b%2==1)N++;
        }
    }
    return P;
}

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



/*
else{
        unsigned long a = 1, b = nel-2;
        unsigned long N = (a+b)/2;
        while(-a+b>1){
            N = (a+b)/2;
            if(!less(N, N-1)&& !less(N, N+1)){
                P=N;
                break;
            }
            a=N;
        }
        if(P!=0)return P;
        while(-a+b>1){
            N = (a+b)/2;
            if(!less(N, N-1)&& !less(N, N+1)){
                P=N;
                break;
            }
            b=N;
        }
        return P;
    }
    */
