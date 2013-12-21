/****************************************************************************
** Meta object code from reading C++ file 'chatWindow.h'
**
** Created: Fri Dec 20 21:56:52 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Include/Window/chatWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChatWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      31,   11,   11,   11, 0x08,
      49,   11,   11,   11, 0x08,
      67,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ChatWindow[] = {
    "ChatWindow\0\0on_close_clicked()\0"
    "on_send_clicked()\0on_wizz_clicked()\0"
    "on_call_clicked()\0"
};

void ChatWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ChatWindow *_t = static_cast<ChatWindow *>(_o);
        switch (_id) {
        case 0: _t->on_close_clicked(); break;
        case 1: _t->on_send_clicked(); break;
        case 2: _t->on_wizz_clicked(); break;
        case 3: _t->on_call_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ChatWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ChatWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ChatWindow,
      qt_meta_data_ChatWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChatWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChatWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChatWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChatWindow))
        return static_cast<void*>(const_cast< ChatWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int ChatWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
