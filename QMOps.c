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

void QMTensor_(_cadd)(real *r, real *t, real value, const real *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = t[i] + value * src[i];
    }
}

void QMTensor_(_cmul)(real *r, real *t, const real *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = t[i] * src[i];
    }
}

void QMTensor_(_cdiv)(real *r, real *t, const real *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = t[i] / src[i];
    }
}

void QMTensor_(_cpow)(real *r, real *t, const real *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = pow(t[i], src[i]);
    }
}