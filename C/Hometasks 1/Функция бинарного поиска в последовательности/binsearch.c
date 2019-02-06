
unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i))
{
    unsigned long a = 0, b = nel - 1;
    int cmp;
    unsigned long N = (a + b) / 2;
    while (cmp = compare(N)) {
        if (cmp < 0) {
            a = N;
        }
        else {
            b = N;
        }
        if (-a + b < 2) {
            N = nel;
            break;
        }
        N = (a + b) / 2;
    }
    return N;
}
