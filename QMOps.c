#include "QM.h"

void QMTensor_(adds)(real *r, real *t, real value, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = t[i] + value;
    }
}

void QMTensor_(muls)(real *r, real *t, real value, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = t[i] * value;
    }
}

void QMTensor_(divs)(real *r, real *t, real value, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = t[i] / value;
    }
}
