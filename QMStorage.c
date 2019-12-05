#include "QM.h"

QMStorage *QMStorage_(new)(void)
{
    QMStorage *src = malloc(sizeof(QMStorage));
    src->refCount = 1;
    src->data = NULL;

    return src;
}

void QMStorage_(link)(QMStorage *src)
{
    QMIncRef(&src->refCount);
}

void QMStorage_(free)(QMStorage *src)
{
    if (QMDecRef(&src->refCount))
    {
        free(src->data);
        free(src);
    }
}
