/****************************************************************************
** Meta object code from reading C++ file 'first_game.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../first_game.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'first_game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
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
struct qt_meta_tag_ZN10first_gameE_t {};
} // unnamed namespace

template <> constexpr inline auto first_game::qt_create_metaobjectdata<qt_meta_tag_ZN10first_gameE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "first_game",
        "backToMain",
        "",
        "on_pushButton_8_clicked",
        "loadQuestionsFromJson",
        "loadQuestion",
        "checkanswer",
        "QPushButton*",
        "button",
        "on_pushButton_option1_clicked",
        "on_pushButton_option2_clicked",
        "on_pushButton_option3_clicked",
        "on_pushButton_option4_clicked",
        "on_pushButton_next_clicked",
        "scoring_result",
        "score",
        "on_pushButton_play_again_clicked",
        "timefonction",
        "on_pushButton_suppr_clicked",
        "on_pushButton_reveal_clicked",
        "on_pushButton_time_clicked",
        "on_pushButton_AI_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'backToMain'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'on_pushButton_8_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'loadQuestionsFromJson'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'loadQuestion'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'checkanswer'
        QtMocHelpers::SlotData<void(QPushButton *)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Slot 'on_pushButton_option1_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_option2_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_option3_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_option4_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_next_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'scoring_result'
        QtMocHelpers::SlotData<void(int)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'on_pushButton_play_again_clicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'timefonction'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_suppr_clicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_reveal_clicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_time_clicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_AI_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<first_game, qt_meta_tag_ZN10first_gameE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject first_game::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10first_gameE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10first_gameE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10first_gameE_t>.metaTypes,
    nullptr
} };

void first_game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<first_game *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->backToMain(); break;
        case 1: _t->on_pushButton_8_clicked(); break;
        case 2: _t->loadQuestionsFromJson(); break;
        case 3: _t->loadQuestion(); break;
        case 4: _t->checkanswer((*reinterpret_cast<std::add_pointer_t<QPushButton*>>(_a[1]))); break;
        case 5: _t->on_pushButton_option1_clicked(); break;
        case 6: _t->on_pushButton_option2_clicked(); break;
        case 7: _t->on_pushButton_option3_clicked(); break;
        case 8: _t->on_pushButton_option4_clicked(); break;
        case 9: _t->on_pushButton_next_clicked(); break;
        case 10: _t->scoring_result((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_pushButton_play_again_clicked(); break;
        case 12: _t->timefonction(); break;
        case 13: _t->on_pushButton_suppr_clicked(); break;
        case 14: _t->on_pushButton_reveal_clicked(); break;
        case 15: _t->on_pushButton_time_clicked(); break;
        case 16: _t->on_pushButton_AI_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPushButton* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (first_game::*)()>(_a, &first_game::backToMain, 0))
            return;
    }
}

const QMetaObject *first_game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *first_game::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10first_gameE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int first_game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void first_game::backToMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
