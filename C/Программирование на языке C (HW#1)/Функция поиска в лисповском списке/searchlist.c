#include "elem.h"

struct Elem* searchlist(struct Elem* list, int a)
{

    int _NULL = 0;
    int fl = 0;
    int k = 0;
    struct Elem* A = list;
    while (A != _NULL) {
        if ((*A).tag == INTEGER && (*A).value.i == a) {
            fl = 1;
            break;
        }
        else if ((*A).tag == LIST) {
            struct Elem* B = searchlist((*A).value.list, a);
            if (B != _NULL) {
                return B;
            }
        }
        A = (*A).tail;
    }
    if (fl)
        return A;
    return _NULL;
}

