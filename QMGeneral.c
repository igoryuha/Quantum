#include "QM.h"

void _QMArgCheck(const char *file, int line, int condition, char *msg)
{
    if (!condition)
    {
        printf("Error: %s, at %s:%d\n", msg, file, line);
        exit(-1);
    }
}