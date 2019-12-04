#include "QMGeneral.h"

/* metadata */
typedef struct QMTensor {
    int ndim;
    long *shape;
    long *strides;
    double *data;
} QMTensor;

QMTensor *QMTensor_(new)(void);
QMTensor *QMTensor_(newFromArray)(const double *data, const long *shape, int ndim);

void QMTensor_(transpose)(QMTensor *self, QMTensor *src, int dim1, int dim2);
void QMTensor_(set)(QMTensor *self, QMTensor *src);
void QMTensor_(reshape2d)(QMTensor *self,long dim1, long dim2);
void QMTensor_(reshape3d)(QMTensor *self,long dim1, long dim2, long dim3);
void QMTensor_(reshape)(QMTensor *self, int ndim, const long *shape, const long *strides);

long QMTensor_(stride)(QMTensor *src, int dim);
long QMTensor_(nElement)(QMTensor *src);

void QMTensor_(free)(QMTensor *src);

double QMTensor_(get2d)(QMTensor *src,  int i, int j);
double QMTensor_(get3d)(QMTensor *src,  int i, int j, int k);
