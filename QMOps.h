void QMTensor_(adds)(real *r, real *t, real value, int n);
void QMTensor_(muls)(real *r, real *t, real value, int n);
void QMTensor_(divs)(real *r, real *t, real value, int n);

void QMTensor_(_cmul)(real *r, real *t, real value, const real *src, int n);