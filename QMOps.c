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

void QMTensor_(pows)(real *r, real *t, real value, int n){
    for (int i = 0; i < n; i++)
    {
        r[i] = pow(t[i], value);
    }
}

void QMTensor_(cadds)(real *r, real *t, real value, const real *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = t[i] + value * src[i];
    }
}

void QMTensor_(cmuls)(real *r, real *t, const real *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = t[i] * src[i];
    }
}

void QMTensor_(cdivs)(real *r, real *t, const real *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = t[i] / src[i];
    }
}

void QMTensor_(cpows)(real *r, real *t, const real *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = pow(t[i], src[i]);
    }
}

void QMTensor_(clips)(real *r, real *t, real min, real max, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = t[i] < min ? min : (t[i] > max ? max : t[i]);
    }
}