#include "QM.h"

QMTensor *QMTensor_(new)(void)
{
    QMTensor *self = malloc(sizeof(QMTensor));
    self->refCount = 1;
    self->ndim = 0;
    self->shape = NULL;
    self->strides = NULL;
    self->storage = NULL;
    self->storageOffset = 0;

    return self;
}

long QMTensor_(stride)(QMTensor *src, int dim)
{
    return src->strides[dim];
}

long QMTensor_(shape)(QMTensor *src, int dim)
{
    return src->shape[dim];
}

long QMTensor_(nElement)(QMTensor *src)
{
    long n = 1;

    for (int i = 0; i < src->ndim; i++) {
        n *= src->shape[i];
    }

    return n;
}

QMTensor *QMTensor_(newFromArray)(const real *data, const long *shape, int ndim)
{
    QMTensor *self = QMTensor_(new)();
    self->storage = QMStorage_(new)();

    self->ndim = ndim;
    self->shape = malloc(sizeof(long)*ndim);
    self->strides = malloc(sizeof(long)*ndim);

    for (int i = 0; i < ndim; i++) {
        self->shape[i] = shape[i];
    }

    long s = 1;
    for (int i = ndim-1; i >= 0; i--) {
        self->strides[i] = s;
        s *= self->shape[i];
    }

    long nElement = QMTensor_(nElement)(self);
    self->storage->data = malloc(sizeof(real) * nElement);

    for (int i = 0; i < nElement; i++) {
        self->storage->data[i] = data[i];
    }

    return self;
}

void QMTensor_(transpose)(QMTensor *self, QMTensor *src, int dim1, int dim2)
{
    long tmp;

    if (!src) {
        src = self;
    }

    if (self != src) {
        QMTensor_(set)(self, src);
    }

    tmp = self->strides[dim1];
    self->strides[dim1] = self->strides[dim2];
    self->strides[dim2] = tmp;
    tmp = self->shape[dim1];
    self->shape[dim1] = self->shape[dim2];
    self->shape[dim2] = tmp;
}

void QMTensor_(set)(QMTensor *self, QMTensor *src)
{
    if (self == src)
        return;

    if (self->storage)
        QMStorage_(free)(self->storage);

    self->storage = src->storage;
    QMStorage_(link)(self->storage);

    self->storageOffset = src->storageOffset;

    QMTensor_(reshape)(self, src->ndim, src->shape, NULL);
}

void QMTensor_(reshape2d)(QMTensor *self,long dim1, long dim2)
{
    long shape[2] = {dim1, dim2};
    QMTensor_(reshape)(self, 2, shape, NULL);
}

void QMTensor_(reshape3d)(QMTensor *self,long dim1, long dim2, long dim3)
{
    long shape[3] = {dim1, dim2, dim3};
    QMTensor_(reshape)(self, 3, shape, NULL);
}

void QMTensor_(reshape)(QMTensor *self, int ndim, const long *shape, const long *strides)
{
    int isSameSize = 1;

    if (strides)
    {
        for (int i = 0; i < ndim; i++)
        {
            if (self->shape[i] != shape[i])
                isSameSize = 0;

            if (self->strides[i] != strides[i])
                isSameSize = 0;
        }

        if (self->ndim != ndim)
            isSameSize = 0;

        if (isSameSize)
            return;
    }
    
    if (self->ndim != ndim)
    {
        self->shape = realloc(self->shape, sizeof(long)*ndim);
        self->strides = realloc(self->strides, sizeof(long)*ndim);
    }

    long s = 1;
    for (int i = ndim-1; i >= 0; i--)
    {
        self->shape[i] = shape[i];

        self->strides[i] = s;
        s *= shape[i];
    }

    self->ndim = ndim;

    if (!self->storage) {
        self->storage = QMStorage_(new)();
        self->storage->data = malloc(sizeof(real)*QMTensor_(nElement)(self));
    }
}

void QMTensor_(free)(QMTensor *src)
{
    if (QMDecRef(&src->refCount))
    {
        free(src->shape);
        free(src->strides);
        if (src->storage)
        {
            QMStorage_(free)(src->storage);
        }
        free(src);
    }
}

int QMTensor_(isContiguous)(QMTensor *src)
{
    long s = 1;

    for (int i = src->ndim-1; i >= 0; i--)
    {
        if (src->strides[i] != s)
            return 0;

        s *= src->shape[i];
    }

    return 1;
}

real QMTensor_(get2d)(QMTensor *src, int i, int j)
{
    return src->storage->data[i*src->strides[0] + j*src->strides[1]];
}

real QMTensor_(get3d)(QMTensor *src, int i, int j, int k)
{
    return src->storage->data[i*src->strides[0] + j*src->strides[1] + k*src->strides[2]];
}
