/****************************************************************************
** Meta object code from reading C++ file 'admin_form.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../admin_form.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'admin_form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN12SerialWorkerE_t {};
} // unnamed namespace

template <> constexpr inline auto SerialWorker::qt_create_metaobjectdata<qt_meta_tag_ZN12SerialWorkerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SerialWorker",
        "portOpened",
        "",
        "ok",
        "err",
        "portClosed",
        "cardRead",
        "cardNo",
        "openPort",
        "portName",
        "closePort",
        "readSerialData"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'portOpened'
        QtMocHelpers::SignalData<void(bool, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'portClosed'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cardRead'
        QtMocHelpers::SignalData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Slot 'openPort'
        QtMocHelpers::SlotData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'closePort'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'readSerialData'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SerialWorker, qt_meta_tag_ZN12SerialWorkerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SerialWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SerialWorkerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SerialWorkerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12SerialWorkerE_t>.metaTypes,
    nullptr
} };

void SerialWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SerialWorker *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->portOpened((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->portClosed(); break;
        case 2: _t->cardRead((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->openPort((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->closePort(); break;
        case 5: _t->readSerialData(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SerialWorker::*)(bool , const QString & )>(_a, &SerialWorker::portOpened, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SerialWorker::*)()>(_a, &SerialWorker::portClosed, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SerialWorker::*)(const QString & )>(_a, &SerialWorker::cardRead, 2))
            return;
    }
}

const QMetaObject *SerialWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12SerialWorkerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SerialWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SerialWorker::portOpened(bool _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void SerialWorker::portClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SerialWorker::cardRead(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
namespace {
struct qt_meta_tag_ZN10Admin_FormE_t {};
} // unnamed namespace

template <> constexpr inline auto Admin_Form::qt_create_metaobjectdata<qt_meta_tag_ZN10Admin_FormE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Admin_Form",
        "on_Btn_Scan_clicked",
        "",
        "on_Btn_Open_card_clicked",
        "onPortOpened",
        "success",
        "error",
        "onPortClosed",
        "onCardRead",
        "cardNo",
        "on_pushButton_register_clicked",
        "on_Btn_find_clicked",
        "on_pushButton_recharge_clicked",
        "initDatabase",
        "registerMember",
        "name",
        "phone",
        "initialBalance",
        "queryMember",
        "QMap<QString,QVariant>",
        "rechargeMember",
        "amount"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_Btn_Scan_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Btn_Open_card_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPortOpened'
        QtMocHelpers::SlotData<void(bool, const QString &)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 5 }, { QMetaType::QString, 6 },
        }}),
        // Slot 'onPortClosed'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCardRead'
        QtMocHelpers::SlotData<void(const QString &)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'on_pushButton_register_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Btn_find_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_recharge_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'initDatabase'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'registerMember'
        QtMocHelpers::SlotData<bool(const QString &, const QString &, const QString &, double)>(14, 2, QMC::AccessPrivate, QMetaType::Bool, {{
            { QMetaType::QString, 9 }, { QMetaType::QString, 15 }, { QMetaType::QString, 16 }, { QMetaType::Double, 17 },
        }}),
        // Slot 'registerMember'
        QtMocHelpers::SlotData<bool(const QString &, const QString &, const QString &)>(14, 2, QMC::AccessPrivate | QMC::MethodCloned, QMetaType::Bool, {{
            { QMetaType::QString, 9 }, { QMetaType::QString, 15 }, { QMetaType::QString, 16 },
        }}),
        // Slot 'queryMember'
        QtMocHelpers::SlotData<QMap<QString,QVariant>(const QString &)>(18, 2, QMC::AccessPrivate, 0x80000000 | 19, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'rechargeMember'
        QtMocHelpers::SlotData<bool(const QString &, double)>(20, 2, QMC::AccessPrivate, QMetaType::Bool, {{
            { QMetaType::QString, 9 }, { QMetaType::Double, 21 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Admin_Form, qt_meta_tag_ZN10Admin_FormE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Admin_Form::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10Admin_FormE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10Admin_FormE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10Admin_FormE_t>.metaTypes,
    nullptr
} };

void Admin_Form::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Admin_Form *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_Btn_Scan_clicked(); break;
        case 1: _t->on_Btn_Open_card_clicked(); break;
        case 2: _t->onPortOpened((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->onPortClosed(); break;
        case 4: _t->onCardRead((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_pushButton_register_clicked(); break;
        case 6: _t->on_Btn_find_clicked(); break;
        case 7: _t->on_pushButton_recharge_clicked(); break;
        case 8: _t->initDatabase(); break;
        case 9: { bool _r = _t->registerMember((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[4])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->registerMember((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { QMap<QString,QVariant> _r = _t->queryMember((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QMap<QString,QVariant>*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->rechargeMember((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *Admin_Form::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Admin_Form::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10Admin_FormE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Admin_Form::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
