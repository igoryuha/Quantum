
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

QMTensor *QMTensor_(newClone)(QMTensor *self);
QMTensor *QMTensor_(newContiguous)(QMTensor *self);

void QMTensor_(transpose)(QMTensor *self, QMTensor *src, int dim1, int dim2);
void QMTensor_(set)(QMTensor *self, QMTensor *src);
void QMTensor_(reshape2d)(QMTensor *self,long dim1, long dim2);
void QMTensor_(reshape3d)(QMTensor *self,long dim1, long dim2, long dim3);
void QMTensor_(reshape)(QMTensor *self, int ndim, const long *shape, const long *strides);

void QMTensor_(narrow)(QMTensor *self, QMTensor *src, int dim, int start, int length);
void QMTensor_(select)(QMTensor *self, QMTensor *src, int dim, int index);

long QMTensor_(stride)(QMTensor *src, int dim);
long QMTensor_(shape)(QMTensor *src, int dim);
long QMTensor_(nElement)(QMTensor *src);
int QMTensor_(nDimension)(QMTensor *src);

void QMTensor_(free)(QMTensor *src);

void QMTensor_(link)(QMTensor *src);

int QMTensor_(isContiguous)(QMTensor *src);

void QMTensor_(slice2d)(QMTensor *self, QMTensor *src, int iStart, int iStop, int jStart, int jStop);

real *QMTensor_(data)(QMTensor *src);

real QMTensor_(get1d)(QMTensor *src, int i);
real QMTensor_(get2d)(QMTensor *src,  int i, int j);
real QMTensor_(get3d)(QMTensor *src,  int i, int j, int k);
