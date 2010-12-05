/****************************************************************************
** Meta object code from reading C++ file 'GPA4Client.h'
**
** Created: Sat Dec 4 21:55:24 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GPA4Client.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GPA4Client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GPA4Client[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      26,   12,   11,   11, 0x05,
      55,   53,   11,   11, 0x05,
      67,   11,   11,   11, 0x05,
      92,   87,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     113,   11,   11,   11, 0x08,
     129,   11,   11,   11, 0x08,
     154,  142,   11,   11, 0x08,
     209,  197,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GPA4Client[] = {
    "GPA4Client\0\0state,command\0"
    "setGUIState(string,string)\0t\0weWon(bool)\0"
    "getConnectionData()\0type\0errorConnecting(int)\0"
    "connectToHost()\0getCommand()\0socketError\0"
    "displayError(QAbstractSocket::SocketError)\0"
    "port,server\0updateConnectionData(string,string)\0"
};

const QMetaObject GPA4Client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GPA4Client,
      qt_meta_data_GPA4Client, 0 }
};

const QMetaObject *GPA4Client::metaObject() const
{
    return &staticMetaObject;
}

void *GPA4Client::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GPA4Client))
        return static_cast<void*>(const_cast< GPA4Client*>(this));
    return QObject::qt_metacast(_clname);
}

int GPA4Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setGUIState((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        case 1: weWon((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: getConnectionData(); break;
        case 3: errorConnecting((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: connectToHost(); break;
        case 5: getCommand(); break;
        case 6: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 7: updateConnectionData((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GPA4Client::setGUIState(string _t1, string _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GPA4Client::weWon(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GPA4Client::getConnectionData()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GPA4Client::errorConnecting(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
