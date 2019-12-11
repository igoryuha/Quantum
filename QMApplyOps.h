
#define __QM_TENSOR_APPLYX_PREAMBLE(TYPE, TENSOR, DIM, ALLOW_CONTIGUOUS) \
    TYPE *TENSOR##_data = NULL; \
    long *TENSOR##_counter = NULL, *TENSOR##_shape = NULL, *TENSOR##_strides = NULL, *TENSOR##_dimOffset = NULL; \
    long TENSOR##_len = 0, TENSOR##_stride = 0, TENSOR##_dim = 0, TENSOR##_i, TENSOR##_n; \
    int TENSOR##_contiguous = ALLOW_CONTIGUOUS && DIM < 0; \
    TENSOR##_n = (TENSOR->ndim ? 1 : 0); \
    for (TENSOR##_i = 0; TENSOR##_i < TENSOR->ndim; TENSOR##_i++) \
        TENSOR##_n *= TENSOR->shape[TENSOR##_i];\
    \
    if (TENSOR->ndim == 0) \
        QM_TENSOR_APPLY_hasFinished = 1; \
    else \
    { \
       TENSOR##_data = TENSOR->storage->data+TENSOR->storageOffset; \
       TENSOR##_len = 1; \
       TENSOR##_stride = 1; \
       for (TENSOR##_i = TENSOR->ndim-1; TENSOR##_i >= 0; TENSOR##_i--) \
       { \
          if (TENSOR->shape[TENSOR##_i] != 1) \
          { \
            if (TENSOR->strides[TENSOR##_i] == TENSOR##_len && TENSOR##_i != DIM) \
                TENSOR##_len *= TENSOR->shape[TENSOR##_i]; \
            else { \
                TENSOR##_contiguous = 0; \
                break; \
            } \
          } \
       } \
       if (!TENSOR##_contiguous) { \
          TENSOR##_dim = 1;  \
          for (TENSOR##_i = TENSOR->ndim-2; TENSOR##_i >= 0; TENSOR##_i--) \
          { \
            if (TENSOR->strides[TENSOR##_i] != TENSOR->strides[TENSOR##_i+1] * TENSOR->shape[TENSOR##_i+1] || TENSOR##_i == DIM || TENSOR##_i+1 == DIM) \
                TENSOR##_dim++; \
          } \
          TENSOR##_counter = (long*)malloc(sizeof(long)*(3*TENSOR##_dim)); \
          TENSOR##_shape = TENSOR##_counter + TENSOR##_dim; \
          TENSOR##_strides = TENSOR##_counter + 2*TENSOR##_dim; \
          QM_TENSOR_dim_index = TENSOR##_dim-1; \
          TENSOR##_dimOffset = (DIM == TENSOR->ndim-1) ? &TENSOR##_i : &TENSOR##_counter[DIM];  \
          TENSOR##_shape[QM_TENSOR_dim_index] = TENSOR->shape[TENSOR->ndim-1]; \
          TENSOR##_strides[QM_TENSOR_dim_index] = TENSOR->strides[TENSOR->ndim-1]; \
          \
          for (TENSOR##_i = TENSOR##_dim-1; TENSOR##_i >= 0; --TENSOR##_i) { \
             TENSOR##_counter[TENSOR##_i] = 0; \
          } \
          for (TENSOR##_i = TENSOR->ndim-2; TENSOR##_i >=0; --TENSOR##_i) { \
             if (TENSOR->strides[TENSOR##_i] == TENSOR->strides[TENSOR##_i+1] * TENSOR->shape[TENSOR##_i+1] && TENSOR##_i != DIM && TENSOR##_i+1 != DIM) { \
                TENSOR##_shape[QM_TENSOR_dim_index] = TENSOR->shape[TENSOR##_i] * TENSOR##_shape[QM_TENSOR_dim_index]; \
                if (DIM != TENSOR->ndim-1 && TENSOR##_i < DIM)  \
                   TENSOR##_dimOffset--; \
             } else { \
                --QM_TENSOR_dim_index;  \
                TENSOR##_shape[QM_TENSOR_dim_index] = TENSOR->shape[TENSOR##_i]; \
                TENSOR##_strides[QM_TENSOR_dim_index] = TENSOR->strides[TENSOR##_i]; \
             } \
          } \
          TENSOR##_len = TENSOR##_shape[TENSOR##_dim-1]; \
          TENSOR##_stride = TENSOR##_strides[TENSOR##_dim-1]; \
       } \
    } \
    TENSOR##_i = 0;

#define  __QM_TENSOR_APPLYX_UPDATE_COUNTERS(TENSOR, ALWAYS_UPDATE) \
  if(TENSOR##_i == TENSOR##_len || ALWAYS_UPDATE) \
  { \
    if(TENSOR##_contiguous) \
      break; \
\
    if(TENSOR##_dim == 1) \
       break; \
\
    TENSOR##_data -= TENSOR##_len*TENSOR##_stride; \
    for(TENSOR##_i = TENSOR##_dim-2; TENSOR##_i >= 0; TENSOR##_i--) \
    { \
      TENSOR##_counter[TENSOR##_i]++; \
      TENSOR##_data += TENSOR##_strides[TENSOR##_i]; \
\
      if(TENSOR##_counter[TENSOR##_i]  == TENSOR##_shape[TENSOR##_i]) \
      { \
        if(TENSOR##_i == 0) \
        { \
          QM_TENSOR_APPLY_hasFinished = 1; \
          break; \
        } \
          else \
        { \
          TENSOR##_data -= TENSOR##_counter[TENSOR##_i]*TENSOR##_strides[TENSOR##_i]; \
          TENSOR##_counter[TENSOR##_i] = 0; \
        } \
      } \
      else \
        break; \
    } \
    TENSOR##_i = 0; \
  } \

#define QM_TENSOR_APPLY3_D(TYPE1, TENSOR1, TYPE2, TENSOR2, TYPE3, TENSOR3, DIM, CODE) \
{ \
   int QM_TENSOR_APPLY_hasFinished = 0; \
  long QM_TENSOR_dim_index = 0; \
  __QM_TENSOR_APPLYX_PREAMBLE(TYPE1, TENSOR1, DIM, 1) \
  __QM_TENSOR_APPLYX_PREAMBLE(TYPE2, TENSOR2, DIM, 1) \
  __QM_TENSOR_APPLYX_PREAMBLE(TYPE3, TENSOR3, DIM, 1) \
   \
    while(!QM_TENSOR_APPLY_hasFinished) \
  { \
    for(; TENSOR1##_i < TENSOR1##_len && TENSOR2##_i < TENSOR2##_len && TENSOR3##_i < TENSOR3##_len; TENSOR1##_i++, TENSOR2##_i++, TENSOR3##_i++, TENSOR1##_data += TENSOR1##_stride, TENSOR2##_data += TENSOR2##_stride, TENSOR3##_data += TENSOR3##_stride) \
    { \
      CODE \
    } \
    __QM_TENSOR_APPLYX_UPDATE_COUNTERS(TENSOR1, 0) \
    __QM_TENSOR_APPLYX_UPDATE_COUNTERS(TENSOR2, 0) \
    __QM_TENSOR_APPLYX_UPDATE_COUNTERS(TENSOR3, 0) \
  } \
}

#define QM_TENSOR_APPLY2_D(TYPE1, TENSOR1, TYPE2, TENSOR2, DIM, CODE) \
{ \
   int QM_TENSOR_APPLY_hasFinished = 0; \
   long QM_TENSOR_dim_index = 0; \
   __QM_TENSOR_APPLYX_PREAMBLE(TYPE1, TENSOR1, DIM, 1) \
   __QM_TENSOR_APPLYX_PREAMBLE(TYPE2, TENSOR2, DIM, 1) \
   \
    while(!QM_TENSOR_APPLY_hasFinished) \
      { \
        for(; TENSOR1##_i < TENSOR1##_len && TENSOR2##_i < TENSOR2##_len; TENSOR1##_i++, TENSOR2##_i++, TENSOR1##_data += TENSOR1##_stride, TENSOR2##_data += TENSOR2##_stride) \
        { \
          CODE \
        } \
        __QM_TENSOR_APPLYX_UPDATE_COUNTERS(TENSOR1, 0) \
        __QM_TENSOR_APPLYX_UPDATE_COUNTERS(TENSOR2, 0) \
      } \
}

#define QM_TENSOR_APPLY3(TYPE1, TENSOR1, TYPE2, TENSOR2, TYPE3, TENSOR3, CODE) \
  QM_TENSOR_APPLY3_D(TYPE1, TENSOR1, TYPE2, TENSOR2, TYPE3, TENSOR3, -1, CODE)

#define QM_TENSOR_APPLY2(TYPE1, TENSOR1, TYPE2, TENSOR2, CODE) \
    QM_TENSOR_APPLY2_D(TYPE1, TENSOR1, TYPE2, TENSOR2, -1, CODE)