
typedef struct QMStorage {
    int refCount;
    real *data;
} QMStorage;

QMStorage *QMStorage_(new)(void);

void QMStorage_(free)(QMStorage *src);

void QMStorage_(link)(QMStorage *src);
