
/* metadata */
typedef struct QMTensor {
    int refCount;
    int ndim;
    long *shape;
    long *strides;
    QMStorage *storage;
    long storageOffset;
} QMTensor;

QMTensor *QMTensor_(new)(void);
QMTensor *QMTensor_(newFromArray)(const real *data, const long *shape, int ndim);

void QMTensor_(transpose)(QMTensor *self, QMTensor *src, int dim1, int dim2);
void QMTensor_(set)(QMTensor *self, QMTensor *src);
void QMTensor_(reshape2d)(QMTensor *self,long dim1, long dim2);
void QMTensor_(reshape3d)(QMTensor *self,long dim1, long dim2, long dim3);
void QMTensor_(reshape)(QMTensor *self, int ndim, const long *shape, const long *strides);

long QMTensor_(stride)(QMTensor *src, int dim);
long QMTensor_(shape)(QMTensor *src, int dim);
long QMTensor_(nElement)(QMTensor *src);

void QMTensor_(free)(QMTensor *src);

real QMTensor_(get2d)(QMTensor *src,  int i, int j);
real QMTensor_(get3d)(QMTensor *src,  int i, int j, int k);
