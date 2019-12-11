#include "QM.h"

#ifdef _OPENMP
#include <omp.h>
#endif

#ifdef _OPENMP

#ifndef _WIN32
#define PRAGMA(P) _Pragma(#P)
#else
#define PRAGMA(P) __pragma(P)
#endif

#define QM_TENSOR_APPLY_CONTIG(TYPE, TENSOR, CODE)                                          \
{                                                                                           \
    long TENSOR1_size = QMTensor_(nElement)(TENSOR);                                        \
    PRAGMA(omp parallel)                                                                    \
    {                                                                                       \
        size_t num_threads = omp_get_num_threads();                                         \
        size_t tid = omp_get_thread_num();                                                  \
        int data_offset = (TENSOR_size / num_threads) * tid;                                \
        int TENSOR##_len = (num_threads - tid) == 1                                         \
                ? (TENSOR1_size / num_threads) + (TENSOR1_size % num_threads)               \
                : (TENSOR1_size / num_threads);                                             \
        TYPE1 *TENSOR##_data = QMTensor_(data)(TENSOR1) + data_offset;                      \
        CODE                                                                                \
    }                                                                                       \
}
#else
#define QM_TENSOR_APPLY_CONTIG(TYPE, TENSOR, CODE) \
{ \
   \
}
#endif

#ifdef _OPENMP
#define QM_TENSOR_APPLY2_CONTIG(TYPE1, TENSOR1, TYPE2, TENSOR2, CODE)                       \
{                                                                                           \
    long TENSOR1_size = QMTensor_(nElement)(TENSOR1);                                       \
    PRAGMA(omp parallel)                                                                    \
    {                                                                                       \
        size_t num_threads = omp_get_num_threads();                                         \
        size_t tid = omp_get_thread_num();                                                  \
        int data_offset = (TENSOR1_size / num_threads) * tid;                               \
        int TENSOR1##_len = (num_threads - tid) == 1                                        \
                ? (TENSOR1_size / num_threads) + (TENSOR1_size % num_threads)               \
                : (TENSOR1_size / num_threads);                                             \
        TYPE1 *TENSOR1##_data = QMTensor_(data)(TENSOR1) + data_offset;                     \
        TYPE2 *TENSOR2##_data = QMTensor_(data)(TENSOR2) + data_offset;                     \
        CODE                                                                                \
    }                                                                                       \
}

#else
#define QM_TENSOR_APPLY2_CONTIG(TYPE, TENSOR, CODE) \
{\
    \
}
#endif

#ifdef _OPENMP
#define QM_TENSOR_APPLY3_CONTIG(TYPE1, TENSOR1, TYPE2, TENSOR2, TYPE3, TENSOR3, CODE)       \
{                                                                                           \
    long TENSOR1_size = QMTensor_(nElement)(TENSOR1);                                       \
    PRAGMA(omp parallel)                                                                    \
    {                                                                                       \
        size_t num_threads = omp_get_num_threads();                                         \
        size_t tid = omp_get_thread_num();                                                  \
        int data_offset = (TENSOR1_size / num_threads) * tid;                               \
        int TENSOR1##_len = (num_threads - tid) == 1                                        \
                ? (TENSOR1_size / num_threads) + (TENSOR1_size % num_threads)               \
                : (TENSOR1_size / num_threads);                                             \
        TYPE1 *TENSOR1##_data = QMTensor_(data)(TENSOR1) + data_offset;                     \
        TYPE2 *TENSOR2##_data = QMTensor_(data)(TENSOR2) + data_offset;                     \
        TYPE2 *TENSOR3##_data = QMTensor_(data)(TENSOR3) + data_offset;                     \
        CODE                                                                                \
    }                                                                                       \
}

#else
#define QM_TENSOR_APPLY3_CONTIG(TYPE, TENSOR, CODE) \
{\
    \
}
#endif


void QMTensor_(add)(QMTensor *r, QMTensor *t, real value)
{
    if (QMTensor_(isContiguous)(r) && QMTensor_(isContiguous)(t) && QMTensor_(nElement)(r) == QMTensor_(nElement)(t))
    {
        QM_TENSOR_APPLY2_CONTIG(real, r, real, t,
                QMTensor_(adds)(r_data, t_data, value, r_len);
        )
    }
    else {
        QM_TENSOR_APPLY2(real, r, real, t, *r_data = *t_data + value;);
    }
}

void QMTensor_(sub)(QMTensor *r, QMTensor *t, real value)
{
    QMTensor_(add)(r, t, -value);
}

void QMTensor_(mul)(QMTensor *r, QMTensor *t, real value)
{
    if (QMTensor_(isContiguous)(r) && QMTensor_(isContiguous)(t) && QMTensor_(nElement)(r) == QMTensor_(nElement)(t))
    {
        QM_TENSOR_APPLY2_CONTIG(real, r, real, t,
                QMTensor_(muls)(r_data, t_data, value, r_len);
        )
    }
}

void QMTensor_(div)(QMTensor *r, QMTensor *t, real value)
{
    if (QMTensor_(isContiguous)(r) && QMTensor_(isContiguous)(t) && QMTensor_(nElement)(r) == QMTensor_(nElement)(t))
    {
        QM_TENSOR_APPLY2_CONTIG(real, r, real, t,
                QMTensor_(divs)(r_data, t_data, value, r_len);
        )
    }
}

void QMTensor_(pow)(QMTensor *r, QMTensor *t, real value)
{
    if (QMTensor_(isContiguous)(r) && QMTensor_(isContiguous)(t) && QMTensor_(nElement)(r) == QMTensor_(nElement)(t))
    {
        QM_TENSOR_APPLY2_CONTIG(real, r, real, t,
                QMTensor_(pows)(r_data, t_data, value, r_len);
        )
    }
}

void QMTensor_(cadd)(QMTensor *r, QMTensor *t, real value, QMTensor *src)
{
    if (QMTensor_(isContiguous)(r) && QMTensor_(isContiguous)(t) && QMTensor_(nElement)(r) == QMTensor_(nElement)(t))
    {
        QM_TENSOR_APPLY3_CONTIG(real, r, real, t, real, src,
                QMTensor_(cadds)(r_data, t_data, value, src_data, r_len);
        )
    }
    else {
        QM_TENSOR_APPLY3(real, r, real, t, real, src, *r_data = *t_data + value * *src_data;);
    }
}

void QMTensor_(csub)(QMTensor *r, QMTensor *t, real value, QMTensor *src)
{
    QMTensor_(cadd)(r, t, -value, src);
}

void QMTensor_(cmul)(QMTensor *r, QMTensor *t, QMTensor *src)
{
    if (QMTensor_(isContiguous)(r) && QMTensor_(isContiguous)(t) && QMTensor_(nElement)(r) == QMTensor_(nElement)(t))
    {
        QM_TENSOR_APPLY3_CONTIG(real, r, real, t, real, src,
                QMTensor_(cmuls)(r_data, t_data, src_data, r_len);
        )
    }
}

void QMTensor_(cdiv)(QMTensor *r, QMTensor *t, QMTensor *src)
{
    if (QMTensor_(isContiguous)(r) && QMTensor_(isContiguous)(t) && QMTensor_(nElement)(r) == QMTensor_(nElement)(t))
    {
        QM_TENSOR_APPLY3_CONTIG(real, r, real, t, real, src,
                QMTensor_(cdivs)(r_data, t_data, src_data, r_len);
        )
    }
}

void QMTensor_(cpow)(QMTensor *r, QMTensor *t, QMTensor *src)
{
    if (QMTensor_(isContiguous)(r) && QMTensor_(isContiguous)(t) && QMTensor_(nElement)(r) == QMTensor_(nElement)(t))
    {
        QM_TENSOR_APPLY3_CONTIG(real, r, real, t, real, src,
                QMTensor_(cpows)(r_data, t_data, src_data, r_len);
        )
    }
}

void QMTensor_(clip)(QMTensor *r, QMTensor *t, real min, real max)
{
    if (QMTensor_(isContiguous)(r) && QMTensor_(isContiguous)(t) && QMTensor_(nElement)(r) == QMTensor_(nElement)(t))
    {
        QM_TENSOR_APPLY2_CONTIG(real, r, real, t,
                QMTensor_(clips)(r_data, t_data, min, max, r_len);
        )
    }
}