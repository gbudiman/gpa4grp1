/****************************************************************************
** Meta object code from reading C++ file 'render2D.h'
**
** Created: Sat Dec 4 10:25:15 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "render2D.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'render2D.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_render2D[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_render2D[] = {
    "render2D\0"
};

const QMetaObject render2D::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_render2D,
      qt_meta_data_render2D, 0 }
};

const QMetaObject *render2D::metaObject() const
{
    return &staticMetaObject;
}

void *render2D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_render2D))
        return static_cast<void*>(const_cast< render2D*>(this));
    return QWidget::qt_metacast(_clname);
}

int render2D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
