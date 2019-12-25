/****************************************************************************
** Meta object code from reading C++ file 'PipeToolWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/PipeToolWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PipeToolWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PipeToolWindow_t {
    QByteArrayData data[21];
    char stringdata0[282];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PipeToolWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PipeToolWindow_t qt_meta_stringdata_PipeToolWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PipeToolWindow"
QT_MOC_LITERAL(1, 15, 8), // "nextStep"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "preStep"
QT_MOC_LITERAL(4, 33, 6), // "finish"
QT_MOC_LITERAL(5, 40, 14), // "choosePipeData"
QT_MOC_LITERAL(6, 55, 17), // "traverseAllVector"
QT_MOC_LITERAL(7, 73, 12), // "qstrFileName"
QT_MOC_LITERAL(8, 86, 14), // "chooseSavePath"
QT_MOC_LITERAL(9, 101, 15), // "chooseModelPath"
QT_MOC_LITERAL(10, 117, 14), // "colorCellClick"
QT_MOC_LITERAL(11, 132, 3), // "row"
QT_MOC_LITERAL(12, 136, 6), // "column"
QT_MOC_LITERAL(13, 143, 13), // "addColorClick"
QT_MOC_LITERAL(14, 157, 16), // "deleteColorClick"
QT_MOC_LITERAL(15, 174, 19), // "selectAllColorClick"
QT_MOC_LITERAL(16, 194, 17), // "defaultColorClick"
QT_MOC_LITERAL(17, 212, 17), // "chooseSingleModel"
QT_MOC_LITERAL(18, 230, 14), // "selectAllModel"
QT_MOC_LITERAL(19, 245, 16), // "checkHasSelected"
QT_MOC_LITERAL(20, 262, 19) // "deleteSelectedModel"

    },
    "PipeToolWindow\0nextStep\0\0preStep\0"
    "finish\0choosePipeData\0traverseAllVector\0"
    "qstrFileName\0chooseSavePath\0chooseModelPath\0"
    "colorCellClick\0row\0column\0addColorClick\0"
    "deleteColorClick\0selectAllColorClick\0"
    "defaultColorClick\0chooseSingleModel\0"
    "selectAllModel\0checkHasSelected\0"
    "deleteSelectedModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PipeToolWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    0,   97,    2, 0x0a /* Public */,
       6,    1,   98,    2, 0x0a /* Public */,
       8,    0,  101,    2, 0x0a /* Public */,
       9,    0,  102,    2, 0x0a /* Public */,
      10,    2,  103,    2, 0x0a /* Public */,
      13,    0,  108,    2, 0x0a /* Public */,
      14,    0,  109,    2, 0x0a /* Public */,
      15,    0,  110,    2, 0x0a /* Public */,
      16,    0,  111,    2, 0x0a /* Public */,
      17,    0,  112,    2, 0x0a /* Public */,
      18,    0,  113,    2, 0x0a /* Public */,
      19,    0,  114,    2, 0x0a /* Public */,
      20,    0,  115,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,

       0        // eod
};

void PipeToolWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PipeToolWindow *_t = static_cast<PipeToolWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextStep(); break;
        case 1: _t->preStep(); break;
        case 2: _t->finish(); break;
        case 3: _t->choosePipeData(); break;
        case 4: _t->traverseAllVector((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->chooseSavePath(); break;
        case 6: _t->chooseModelPath(); break;
        case 7: _t->colorCellClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->addColorClick(); break;
        case 9: _t->deleteColorClick(); break;
        case 10: _t->selectAllColorClick(); break;
        case 11: _t->defaultColorClick(); break;
        case 12: _t->chooseSingleModel(); break;
        case 13: _t->selectAllModel(); break;
        case 14: { bool _r = _t->checkHasSelected();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->deleteSelectedModel(); break;
        default: ;
        }
    }
}

const QMetaObject PipeToolWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PipeToolWindow.data,
      qt_meta_data_PipeToolWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PipeToolWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PipeToolWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PipeToolWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PipeToolWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
