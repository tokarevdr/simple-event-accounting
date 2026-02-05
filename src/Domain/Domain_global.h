#ifndef DOMAIN_GLOBAL_H
#define DOMAIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DOMAIN_LIBRARY)
#define DOMAIN_EXPORT Q_DECL_EXPORT
#else
#define DOMAIN_EXPORT Q_DECL_IMPORT
#endif

#endif // DOMAIN_GLOBAL_H
