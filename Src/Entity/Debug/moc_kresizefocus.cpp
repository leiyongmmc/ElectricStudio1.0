/****************************************************************************
** Meta object code from reading C++ file 'kresizefocus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kresizefocus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kresizefocus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KResizeFocus_t {
    QByteArrayData data[9];
    char stringdata[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KResizeFocus_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KResizeFocus_t qt_meta_stringdata_KResizeFocus = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 18),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 25),
QT_MOC_LITERAL(4, 59, 5),
QT_MOC_LITERAL(5, 65, 13),
QT_MOC_LITERAL(6, 79, 8),
QT_MOC_LITERAL(7, 88, 17),
QT_MOC_LITERAL(8, 106, 20)
    },
    "KResizeFocus\0sigMousePressEvent\0\0"
    "QGraphicsSceneMouseEvent*\0event\0"
    "KResizeFocus*\0curFocus\0sigMouseMoveEvent\0"
    "sigMouseReleaseEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KResizeFocus[] = {

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
       1,    2,   29,    2, 0x06 /* Public */,
       7,    1,   34,    2, 0x06 /* Public */,
       8,    1,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void KResizeFocus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KResizeFocus *_t = static_cast<KResizeFocus *>(_o);
        switch (_id) {
        case 0: _t->sigMousePressEvent((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1])),(*reinterpret_cast< KResizeFocus*(*)>(_a[2]))); break;
        case 1: _t->sigMouseMoveEvent((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->sigMouseReleaseEvent((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< KResizeFocus* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KResizeFocus::*_t)(QGraphicsSceneMouseEvent * , KResizeFocus * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KResizeFocus::sigMousePressEvent)) {
                *result = 0;
            }
        }
        {
            typedef void (KResizeFocus::*_t)(QGraphicsSceneMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KResizeFocus::sigMouseMoveEvent)) {
                *result = 1;
            }
        }
        {
            typedef void (KResizeFocus::*_t)(QGraphicsSceneMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KResizeFocus::sigMouseReleaseEvent)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject KResizeFocus::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KResizeFocus.data,
      qt_meta_data_KResizeFocus,  qt_static_metacall, 0, 0}
};


const QMetaObject *KResizeFocus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KResizeFocus::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KResizeFocus.stringdata))
        return static_cast<void*>(const_cast< KResizeFocus*>(this));
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(const_cast< KResizeFocus*>(this));
    return QObject::qt_metacast(_clname);
}

int KResizeFocus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void KResizeFocus::sigMousePressEvent(QGraphicsSceneMouseEvent * _t1, KResizeFocus * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KResizeFocus::sigMouseMoveEvent(QGraphicsSceneMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KResizeFocus::sigMouseReleaseEvent(QGraphicsSceneMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
