#include <stdio.h>
#include "QM.h"

void QMTensor_(print1d)(QMTensor *src)
{
    printf("\n");
    printf("[ ");
    for (int i = 0; i < src->shape[0]; i++)
    {
        printf("%.2"DATA_FORMAT", ", QMTensor_(get1d)(src, i));
    }
    printf("\b\b ]\n");
}

void QMTensor_(print2d)(QMTensor *src)
{
    printf("\n");
    printf("dim %ldx%ld \n", src->shape[0], src->shape[1]);
    for (int i = 0; i < src->shape[0]; i++) {
        printf("[ ");
        for (int j = 0; j < src->shape[1]; j++) {
            printf("%.2"DATA_FORMAT" ", QMTensor_(get2d)(src, i, j));
        }
        printf("]\n");
    }
    printf("\n");
}

void QMTensor_(print3d)(QMTensor *src)
{
    printf("\n");
    for (int k = 0; k < src->shape[0]; k++) {
        printf("dim %dx%ldx%ld \n", k, src->shape[1], src->shape[2]);
        for (int i = 0; i < src->shape[1]; i++) {
            printf("[ ");
            for (int j = 0; j < src->shape[2]; j++) {
                printf("%.2"DATA_FORMAT" ", QMTensor_(get3d)(src, k, i, j));
            }
            printf("]\n");
        }
        printf("\n");
    }
}

void QMTensor_(print)(QMTensor *src)
{
    if (src->ndim == 1) {
        QMTensor_(print1d)(src);
    }
    else if (src->ndim == 2) {
        QMTensor_(print2d)(src);
    }
    else if (src->ndim == 3) {
        QMTensor_(print3d)(src);
    }
    else {
        printf("Not implemented");
    }
}

void QMTensor_(copy)(QMTensor *tensor, QMTensor *src)
{
    if (tensor == src)
        return;

    if (QMTensor_(isContiguous)(tensor) && QMTensor_(isContiguous)(src) && QMTensor_(nElement)(tensor) == QMTensor_(nElement)(src))
    {
        real *selfData = QMTensor_(data)(tensor);
        real *srcData = QMTensor_(data)(src);

        memcpy(selfData, srcData, sizeof(real) * QMTensor_(nElement)(tensor));
    }
    else {
        QM_TENSOR_APPLY2(real, tensor, real, src, *tensor_data = *src_data;);
    }
}