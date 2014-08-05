#ifndef ENTITY_GLOBAL_H
#define ENTITY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ENTITY_LIBRARY)
#  define ENTITYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ENTITYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ENTITY_GLOBAL_H
