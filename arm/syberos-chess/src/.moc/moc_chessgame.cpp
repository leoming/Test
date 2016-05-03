/****************************************************************************
** Meta object code from reading C++ file 'chessgame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../chessgame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chessgame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CChessGame_t {
    QByteArrayData data[20];
    char stringdata[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CChessGame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CChessGame_t qt_meta_stringdata_CChessGame = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 11),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 9),
QT_MOC_LITERAL(4, 34, 5),
QT_MOC_LITERAL(5, 40, 5),
QT_MOC_LITERAL(6, 46, 3),
QT_MOC_LITERAL(7, 50, 3),
QT_MOC_LITERAL(8, 54, 10),
QT_MOC_LITERAL(9, 65, 10),
QT_MOC_LITERAL(10, 76, 1),
QT_MOC_LITERAL(11, 78, 1),
QT_MOC_LITERAL(12, 80, 20),
QT_MOC_LITERAL(13, 101, 20),
QT_MOC_LITERAL(14, 122, 18),
QT_MOC_LITERAL(15, 141, 18),
QT_MOC_LITERAL(16, 160, 7),
QT_MOC_LITERAL(17, 168, 12),
QT_MOC_LITERAL(18, 181, 4),
QT_MOC_LITERAL(19, 186, 5)
    },
    "CChessGame\0computerRun\0\0moveChess\0"
    "fromX\0fromY\0toX\0toY\0isGameOver\0"
    "getChessAt\0x\0y\0getComputerMoveFromX\0"
    "getComputerMoveFromY\0getComputerMoveToX\0"
    "getComputerMoveToY\0reStart\0setMoveChess\0"
    "BYTE\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CChessGame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    4,   65,    2, 0x0a /* Public */,
       8,    0,   74,    2, 0x0a /* Public */,
       9,    2,   75,    2, 0x0a /* Public */,
      12,    0,   80,    2, 0x0a /* Public */,
      13,    0,   81,    2, 0x0a /* Public */,
      14,    0,   82,    2, 0x0a /* Public */,
      15,    0,   83,    2, 0x0a /* Public */,
      16,    0,   84,    2, 0x0a /* Public */,
      17,    3,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    4,    5,    6,    7,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 18, 0x80000000 | 18,   10,   11,   19,

       0        // eod
};

void CChessGame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CChessGame *_t = static_cast<CChessGame *>(_o);
        switch (_id) {
        case 0: _t->computerRun(); break;
        case 1: { bool _r = _t->moveChess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->isGameOver();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->getChessAt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { int _r = _t->getComputerMoveFromX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { int _r = _t->getComputerMoveFromY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: { int _r = _t->getComputerMoveToX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: { int _r = _t->getComputerMoveToY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: _t->reStart(); break;
        case 9: _t->setMoveChess((*reinterpret_cast< BYTE(*)>(_a[1])),(*reinterpret_cast< BYTE(*)>(_a[2])),(*reinterpret_cast< BYTE(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject CChessGame::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CChessGame.data,
      qt_meta_data_CChessGame,  qt_static_metacall, 0, 0}
};


const QMetaObject *CChessGame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CChessGame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CChessGame.stringdata))
        return static_cast<void*>(const_cast< CChessGame*>(this));
    return QObject::qt_metacast(_clname);
}

int CChessGame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
