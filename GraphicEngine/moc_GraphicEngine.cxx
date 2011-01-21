/****************************************************************************
** Meta object code from reading C++ file 'GraphicEngine.hpp'
**
** Created: Fri Jan 21 12:42:01 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GraphicEngine.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphicEngine.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FreePhyloTree__GraphicEngine[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FreePhyloTree__GraphicEngine[] = {
    "FreePhyloTree::GraphicEngine\0\0animate()\0"
};

const QMetaObject FreePhyloTree::GraphicEngine::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_FreePhyloTree__GraphicEngine,
      qt_meta_data_FreePhyloTree__GraphicEngine, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FreePhyloTree::GraphicEngine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FreePhyloTree::GraphicEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FreePhyloTree::GraphicEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FreePhyloTree__GraphicEngine))
        return static_cast<void*>(const_cast< GraphicEngine*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int FreePhyloTree::GraphicEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: animate(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
