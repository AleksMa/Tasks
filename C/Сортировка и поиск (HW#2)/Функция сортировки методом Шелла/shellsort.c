void shellsort(unsigned long nel,
    int (*compare)(unsigned long i, unsigned long j),
    void (*swap)(unsigned long i, unsigned long j))
{

    unsigned long FibB = 1, FibS = 1;
    while (FibB < nel) {
        unsigned long c = FibB;
        FibB += FibS;
        FibS = c;
    }
    unsigned long d = FibS;
    //printf("%d\n", d);
    while (d > 0) {
        unsigned long i = d;
        while (i < nel) {
            long loc = i - d;
            while ((loc >= 0) && (compare(loc, loc + d) == 1)) {
                swap(loc, loc + d);
                loc -= d;
            }
            i += 1;
        }
        if (d == 1)
            break;
        FibS = FibB - FibS;
        FibB = d;
        d = FibS;
    }
}
