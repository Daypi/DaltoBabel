/****************************************************************************
** Meta object code from reading C++ file 'contactWindow.h'
**
** Created: Fri Dec 20 23:41:09 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Include/Window/contactWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contactWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ContactWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      33,   14,   14,   14, 0x08,
      51,   14,   14,   14, 0x08,
      69,   14,   14,   14, 0x08,
      86,   14,   14,   14, 0x08,
     106,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ContactWindow[] = {
    "ContactWindow\0\0on_call_clicked()\0"
    "on_chat_clicked()\0on_wizz_clicked()\0"
    "on_add_clicked()\0on_remove_clicked()\0"
    "on_block_clicked()\0"
};

void ContactWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ContactWindow *_t = static_cast<ContactWindow *>(_o);
        switch (_id) {
        case 0: _t->on_call_clicked(); break;
        case 1: _t->on_chat_clicked(); break;
        case 2: _t->on_wizz_clicked(); break;
        case 3: _t->on_add_clicked(); break;
        case 4: _t->on_remove_clicked(); break;
        case 5: _t->on_block_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ContactWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ContactWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ContactWindow,
      qt_meta_data_ContactWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ContactWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ContactWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ContactWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ContactWindow))
        return static_cast<void*>(const_cast< ContactWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int ContactWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
