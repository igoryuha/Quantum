void QMTensor_(adds)(real *r, real *t, real value, int n);
void QMTensor_(muls)(real *r, real *t, real value, int n);
void QMTensor_(divs)(real *r, real *t, real value, int n);
void QMTensor_(pows)(real *r, real *t, real value, int n);

void QMTensor_(cadds)(real *r, real *t, real value, const real *src, int n);
void QMTensor_(cmuls)(real *r, real *t, const real *src, int n);
void QMTensor_(cdivs)(real *r, real *t, const real *src, int n);
void QMTensor_(cpows)(real *r, real *t, const real *src, int n);

void QMTensor_(clips)(real *r, real *t, real min, real max, int n);