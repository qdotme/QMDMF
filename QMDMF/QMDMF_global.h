#ifndef QMDMF_GLOBAL_H
#define QMDMF_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QMDMF_LIBRARY)
#  define QMDMFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMDMFSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMDMF_GLOBAL_H
