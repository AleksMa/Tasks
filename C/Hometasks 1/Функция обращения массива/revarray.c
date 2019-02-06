void revarray(void* base, unsigned long nel, unsigned long width)
{

    char* p = base;
    int k = 0;
    if (nel % 2 != 0)
        k = 1;
    int N = width * (nel / 2);
    for (int i = 0; i < N; i += width) {
        for (int j = 0; j < width; j++) {
            char t = p[i + j];
            p[i + j] = p[width * nel - i - width + j];
            p[width * nel - i - width + j] = t;
        }
    }
}
