/****************************************************************************
** Meta object code from reading C++ file 'krotateitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../krotateitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'krotateitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KRotateItem_t {
    QByteArrayData data[7];
    char stringdata[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KRotateItem_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KRotateItem_t qt_meta_stringdata_KRotateItem = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 18),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 25),
QT_MOC_LITERAL(4, 58, 5),
QT_MOC_LITERAL(5, 64, 17),
QT_MOC_LITERAL(6, 82, 20)
    },
    "KRotateItem\0sigMousePressEvent\0\0"
    "QGraphicsSceneMouseEvent*\0event\0"
    "sigMouseMoveEvent\0sigMouseReleaseEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KRotateItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    1,   32,    2, 0x06 /* Public */,
       6,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void KRotateItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KRotateItem *_t = static_cast<KRotateItem *>(_o);
        switch (_id) {
        case 0: _t->sigMousePressEvent((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->sigMouseMoveEvent((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->sigMouseReleaseEvent((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KRotateItem::*_t)(QGraphicsSceneMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KRotateItem::sigMousePressEvent)) {
                *result = 0;
            }
        }
        {
            typedef void (KRotateItem::*_t)(QGraphicsSceneMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KRotateItem::sigMouseMoveEvent)) {
                *result = 1;
            }
        }
        {
            typedef void (KRotateItem::*_t)(QGraphicsSceneMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KRotateItem::sigMouseReleaseEvent)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject KRotateItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KRotateItem.data,
      qt_meta_data_KRotateItem,  qt_static_metacall, 0, 0}
};


const QMetaObject *KRotateItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KRotateItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KRotateItem.stringdata))
        return static_cast<void*>(const_cast< KRotateItem*>(this));
    if (!strcmp(_clname, "QGraphicsEllipseItem"))
        return static_cast< QGraphicsEllipseItem*>(const_cast< KRotateItem*>(this));
    return QObject::qt_metacast(_clname);
}

int KRotateItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void KRotateItem::sigMousePressEvent(QGraphicsSceneMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KRotateItem::sigMouseMoveEvent(QGraphicsSceneMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KRotateItem::sigMouseReleaseEvent(QGraphicsSceneMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
