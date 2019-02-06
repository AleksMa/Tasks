int maxarray(void* base, unsigned long nel, unsigned long width,
    int (*compare)(void* a, void* b))
{
    void* p = base;
    void* max = base;
    unsigned long index = 0;

    for (int i = 0; i < nel; i++) {
        if (compare(p + i * width, max) > 0) {
            index = i;
            max = p + width * i;
        }
    }

    return index;
}
