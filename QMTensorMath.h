
void QMTensor_(add)(QMTensor *r, QMTensor *t, real value);
void QMTensor_(sub)(QMTensor *r, QMTensor *t, real value);
void QMTensor_(mul)(QMTensor *r, QMTensor *t, real value);
void QMTensor_(div)(QMTensor *r, QMTensor *t, real value);
void QMTensor_(pow)(QMTensor *r, QMTensor *t, real value);

void QMTensor_(cadd)(QMTensor *r, QMTensor *t, real value, QMTensor *src);
void QMTensor_(csub)(QMTensor *r, QMTensor *t, real value, QMTensor *src);
void QMTensor_(cmul)(QMTensor *r, QMTensor *t, QMTensor *src);
void QMTensor_(cdiv)(QMTensor *r, QMTensor *t, QMTensor *src);
void QMTensor_(cpow)(QMTensor *r, QMTensor *t, QMTensor *src);

void QMTensor_(clip)(QMTensor *r, QMTensor *t, real min, real max);