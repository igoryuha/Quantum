
int QMIncRef(int *refCount)
{
    return ++(*refCount) ? 0 : 1;
}

int QMDecRef(int *refCount)
{
    return --(*refCount) ? 0 : 1;
}
