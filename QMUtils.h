#include "QMGeneral.h"

void QMTensor_(print1d)(QMTensor *src);
void QMTensor_(print2d)(QMTensor *src);
void QMTensor_(print3d)(QMTensor *src);
void QMTensor_(print)(QMTensor *src);

int QMTensor_(copyTransposeValid)(QMTensor *tensor, QMTensor *src);

void QMTensor_(copy)(QMTensor *tensor, QMTensor *src);
void QMTensor_(copyTranspose)(QMTensor *tensor, QMTensor *src);