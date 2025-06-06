/****************************************************************************
** Meta object code from reading C++ file 'novacontrollerworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../novacontrollerworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'novacontrollerworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NovaControllerWorker_t {
    QByteArrayData data[20];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NovaControllerWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NovaControllerWorker_t qt_meta_stringdata_NovaControllerWorker = {
    {
QT_MOC_LITERAL(0, 0, 20), // "NovaControllerWorker"
QT_MOC_LITERAL(1, 21, 8), // "slotInit"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 16), // "slotPlayProgram1"
QT_MOC_LITERAL(4, 48, 8), // "fontSize"
QT_MOC_LITERAL(5, 57, 7), // "content"
QT_MOC_LITERAL(6, 65, 10), // "audioTimes"
QT_MOC_LITERAL(7, 76, 12), // "voiceContent"
QT_MOC_LITERAL(8, 89, 11), // "audioSwitch"
QT_MOC_LITERAL(9, 101, 11), // "audiovolume"
QT_MOC_LITERAL(10, 113, 16), // "slotPlayProgram2"
QT_MOC_LITERAL(11, 130, 6), // "base64"
QT_MOC_LITERAL(12, 137, 16), // "slotPlayProgram3"
QT_MOC_LITERAL(13, 154, 17), // "slotSetDefaultTxt"
QT_MOC_LITERAL(14, 172, 4), // "size"
QT_MOC_LITERAL(15, 177, 17), // "slotSetDefaultPic"
QT_MOC_LITERAL(16, 195, 28), // "slotSetCurrentDefaultProgram"
QT_MOC_LITERAL(17, 224, 14), // "currentProgram"
QT_MOC_LITERAL(18, 239, 27), // "slotPlayPicProgramByPicName"
QT_MOC_LITERAL(19, 267, 7) // "picName"

    },
    "NovaControllerWorker\0slotInit\0\0"
    "slotPlayProgram1\0fontSize\0content\0"
    "audioTimes\0voiceContent\0audioSwitch\0"
    "audiovolume\0slotPlayProgram2\0base64\0"
    "slotPlayProgram3\0slotSetDefaultTxt\0"
    "size\0slotSetDefaultPic\0"
    "slotSetCurrentDefaultProgram\0"
    "currentProgram\0slotPlayPicProgramByPicName\0"
    "picName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NovaControllerWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    6,   55,    2, 0x0a /* Public */,
      10,    1,   68,    2, 0x0a /* Public */,
      12,    7,   71,    2, 0x0a /* Public */,
      13,    2,   86,    2, 0x0a /* Public */,
      15,    1,   91,    2, 0x0a /* Public */,
      16,    1,   94,    2, 0x0a /* Public */,
      18,    1,   97,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,    4,    5,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::QString,    4,    5,    6,    7,    8,    9,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,   14,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::QString,   19,

       0        // eod
};

void NovaControllerWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NovaControllerWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotInit(); break;
        case 1: _t->slotPlayProgram1((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 2: _t->slotPlayProgram2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->slotPlayProgram3((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        case 4: _t->slotSetDefaultTxt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->slotSetDefaultPic((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->slotSetCurrentDefaultProgram((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slotPlayPicProgramByPicName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NovaControllerWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NovaControllerWorker.data,
    qt_meta_data_NovaControllerWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NovaControllerWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NovaControllerWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NovaControllerWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NovaControllerWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
