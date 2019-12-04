#include "QM.h"

QMTensor *QMTensor_(new)(void)
{
    QMTensor *self = malloc(sizeof(QMTensor));
    self->ndim = 0;
    self->shape = NULL;
    self->strides = NULL;
    self->data = NULL;
    return self;
}

long QMTensor_(stride)(QMTensor *src, int dim)
{
    return src->strides[dim];
}

long QMTensor_(nElement)(QMTensor *src)
{
    int n = 1;

    for (int i = 0; i < src->ndim; i++) {
        n *= src->shape[i];
    }

    return n;
}

QMTensor *QMTensor_(newFromArray)(double *data, long *shape, int ndim)
{
    QMTensor *self = QMTensor_(new)();

    self->ndim = ndim;
    self->shape = malloc(sizeof(long)*ndim);
    self->strides = malloc(sizeof(long)*ndim);

    for (int i = 0; i < ndim; i++) {
        self->shape[i] = shape[i];
    }

    int s = 1;
    for (int i = ndim-1; i >= 0; i--) {
        self->strides[i] = s;
        s *= self->shape[i];
    }

    long nElement = QMTensor_(nElement)(self);
    self->data = malloc(sizeof(double) * nElement);

    for (int i = 0; i < nElement; i++) {
        self->data[i] = data[i];
    }

    return self;
}

void QMTensor_(free)(QMTensor *src)
{
    free(src->shape);
    free(src->strides);
    free(src->data);
    free(src);
}

double QMTensor_(get2d)(QMTensor *src, int i, int j)
{
    return src->data[i*src->strides[0] + j*src->strides[1]];
}

double QMTensor_(get3d)(QMTensor *src, int i, int j, int k)
{
    return src->data[i*src->strides[0] + j*src->strides[1] + k*src->strides[2]];
}
