unsigned long peak(unsigned long nel,
    int (*less)(unsigned long i, unsigned long j))
{
    unsigned long P = 0;
    if (!less(0, 1))
        return 0;
    else if (!less(nel - 1, nel - 2))
        return nel - 1;
    else {
        unsigned long a = 0, b = nel - 1, N = a / 2 + b / 2;
        while (!P) {
            if (less(N, N - 1)) {
                b = N;
            }
            else if (less(N, N + 1))
                a = N;
            else {
                P = N;
                break;
            }
            N = a / 2 + b / 2;
            if (a % 2 == 1 && b % 2 == 1)
                N++;
        }
    }
    return P;
}
