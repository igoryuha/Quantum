#include "QMGeneral.h"

/* metadata */
typedef struct QMTensor {
    int ndim;
    long *shape;
    long *strides;
    double *data;
} QMTensor;

QMTensor *QMTensor_(new)(void);
QMTensor *QMTensor_(newFromArray)(double *data, long *shape, int ndim);

void QMTensor_(transpose)(QMTensor *self, QMTensor *src, int dim1, int dim2);
void QMTensor_(set)(QMTensor *self, QMTensor *src);
void QMTensor_(resize)(QMTensor *self, int ndim, long *shape, long *strides);

long QMTensor_(stride)(QMTensor *src, int dim);
long QMTensor_(nElement)(QMTensor *src);

void QMTensor_(free)(QMTensor *src);

double QMTensor_(get2d)(QMTensor *src,  int i, int j);
double QMTensor_(get3d)(QMTensor *src,  int i, int j, int k);
