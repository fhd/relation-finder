/****************************************************************************
** Meta object code from reading C++ file 'fetcher.h'
**
** Created: Wed Sep 26 22:39:51 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fetcher.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fetcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_Fetcher[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_Fetcher[] = {
    "Fetcher\0"
};

const QMetaObject Fetcher::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Fetcher,
      qt_meta_data_Fetcher, 0 }
};

const QMetaObject *Fetcher::metaObject() const
{
    return &staticMetaObject;
}

void *Fetcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Fetcher))
	return static_cast<void*>(const_cast< Fetcher*>(this));
    return QThread::qt_metacast(_clname);
}

int Fetcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
