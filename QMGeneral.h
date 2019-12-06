#define QMTensor_(NAME) QMTensor_ ## NAME
#define QMStorage_(NAME) QMStorage_ ## NAME

#define QMArgCheck(condition, msg) _QMArgCheck(__FILE__, __LINE__, condition, msg);

void _QMArgCheck(const char *file, int line, int condition, char *msg);
