/****************************************************************************
** Meta object code from reading C++ file 'GWindow.h'
**
** Created: Sat Dec 4 21:55:26 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      21,    9,    8,    8, 0x05,
      55,    8,    8,    8, 0x05,
      82,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     106,    8,    8,    8, 0x08,
     134,  129,    8,    8, 0x08,
     157,  155,    8,    8, 0x08,
     182,  178,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GWindow[] = {
    "GWindow\0\0port,server\0"
    "sendConnectionData(string,string)\0"
    "addtoCommandsText(QString)\0"
    "addtoStateText(QString)\0returnConnectionData()\0"
    "type\0connectionError(int)\0k\0"
    "displayOutcome(bool)\0s,c\0"
    "updateGuiState(string,string)\0"
};

const QMetaObject GWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GWindow,
      qt_meta_data_GWindow, 0 }
};

const QMetaObject *GWindow::metaObject() const
{
    return &staticMetaObject;
}

void *GWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GWindow))
        return static_cast<void*>(const_cast< GWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int GWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendConnectionData((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        case 1: addtoCommandsText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: addtoStateText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: returnConnectionData(); break;
        case 4: connectionError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: displayOutcome((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: updateGuiState((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void GWindow::sendConnectionData(string _t1, string _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GWindow::addtoCommandsText(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GWindow::addtoStateText(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
