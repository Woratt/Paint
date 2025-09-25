/****************************************************************************
** Meta object code from reading C++ file 'menubar.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../menubar.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>

#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menubar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace
{
struct qt_meta_tag_ZN7MenuBarE_t
{
};
} // unnamed namespace

template <> constexpr inline auto MenuBar::qt_create_metaobjectdata<qt_meta_tag_ZN7MenuBarE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData{"MenuBar", "save", "", "close", "newFile", "open"};

    QtMocHelpers::UintData qt_methods{
        // Slot 'save'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'close'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'newFile'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'open'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties{};
    QtMocHelpers::UintData qt_enums{};
    return QtMocHelpers::metaObjectData<MenuBar, qt_meta_tag_ZN7MenuBarE_t>(QMC::MetaObjectFlag{}, qt_stringData,
                                                                            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MenuBar::staticMetaObject = {
    {QMetaObject::SuperData::link<QMenuBar::staticMetaObject>(),
     qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7MenuBarE_t>.stringdata,
     qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7MenuBarE_t>.data, qt_static_metacall, nullptr,
     qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7MenuBarE_t>.metaTypes, nullptr}};

void MenuBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MenuBar *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        switch (_id)
        {
            case 0:
                _t->save();
                break;
            case 1:
                _t->close();
                break;
            case 2:
                _t->newFile();
                break;
            case 3:
                _t->open();
                break;
            default:;
        }
    }
    (void)_a;
}

const QMetaObject *MenuBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuBar::qt_metacast(const char *_clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7MenuBarE_t>.strings))
        return static_cast<void *>(this);
    return QMenuBar::qt_metacast(_clname);
}

int MenuBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenuBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
