
void QMTensor_(add)(QMTensor *r, QMTensor *t, real value);
void QMTensor_(sub)(QMTensor *r, QMTensor *t, real value);
void QMTensor_(mul)(QMTensor *r, QMTensor *t, real value);
void QMTensor_(div)(QMTensor *r, QMTensor *t, real value);

void QMTensor_(cadd)(QMTensor *r, QMTensor *t, real value, QMTensor *src);