/****************************************************************************
** Meta object code from reading C++ file 'PlaybackController.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/PlaybackController.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlaybackController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
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
struct qt_meta_tag_ZN18PlaybackControllerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN18PlaybackControllerE = QtMocHelpers::stringData(
    "PlaybackController",
    "playingChanged",
    "",
    "pausedChanged",
    "currentIndexChanged",
    "totalReadingsChanged",
    "playbackSpeedChanged",
    "loopEnabledChanged",
    "currentTimestampChanged",
    "dataPoint",
    "temperature",
    "pressure",
    "timestamp",
    "frameFilename",
    "playbackFinished",
    "statisticsChanged",
    "nextDataPoint",
    "loadData",
    "QList<SensorReading>",
    "readings",
    "play",
    "pause",
    "stop",
    "forward",
    "rewind",
    "seekToIndex",
    "index",
    "seekToTimestamp",
    "getReadingsInRange",
    "start",
    "end",
    "getStatistics",
    "QVariantMap",
    "isPlaying",
    "isPaused",
    "currentIndex",
    "totalReadings",
    "playbackSpeed",
    "loopEnabled",
    "currentTimestamp"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN18PlaybackControllerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       7,  179, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  140,    2, 0x06,    8 /* Public */,
       3,    0,  141,    2, 0x06,    9 /* Public */,
       4,    0,  142,    2, 0x06,   10 /* Public */,
       5,    0,  143,    2, 0x06,   11 /* Public */,
       6,    0,  144,    2, 0x06,   12 /* Public */,
       7,    0,  145,    2, 0x06,   13 /* Public */,
       8,    0,  146,    2, 0x06,   14 /* Public */,
       9,    4,  147,    2, 0x06,   15 /* Public */,
      14,    0,  156,    2, 0x06,   20 /* Public */,
      15,    0,  157,    2, 0x06,   21 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      16,    0,  158,    2, 0x08,   22 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      17,    1,  159,    2, 0x02,   23 /* Public */,
      20,    0,  162,    2, 0x02,   25 /* Public */,
      21,    0,  163,    2, 0x02,   26 /* Public */,
      22,    0,  164,    2, 0x02,   27 /* Public */,
      23,    0,  165,    2, 0x02,   28 /* Public */,
      24,    0,  166,    2, 0x02,   29 /* Public */,
      25,    1,  167,    2, 0x02,   30 /* Public */,
      27,    1,  170,    2, 0x02,   32 /* Public */,
      28,    2,  173,    2, 0x02,   34 /* Public */,
      31,    0,  178,    2, 0x102,   37 /* Public | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::QString, QMetaType::QString,   10,   11,   12,   13,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::QDateTime,   12,
    0x80000000 | 18, QMetaType::QDateTime, QMetaType::QDateTime,   29,   30,
    0x80000000 | 32,

 // properties: name, type, flags, notifyId, revision
      33, QMetaType::Bool, 0x00015001, uint(0), 0,
      34, QMetaType::Bool, 0x00015001, uint(1), 0,
      35, QMetaType::Int, 0x00015001, uint(2), 0,
      36, QMetaType::Int, 0x00015001, uint(3), 0,
      37, QMetaType::Double, 0x00015103, uint(4), 0,
      38, QMetaType::Bool, 0x00015103, uint(5), 0,
      39, QMetaType::QDateTime, 0x00015001, uint(6), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject PlaybackController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN18PlaybackControllerE.offsetsAndSizes,
    qt_meta_data_ZN18PlaybackControllerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN18PlaybackControllerE_t,
        // property 'isPlaying'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'isPaused'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'currentIndex'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'totalReadings'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'playbackSpeed'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'loopEnabled'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'currentTimestamp'
        QtPrivate::TypeAndForceComplete<QDateTime, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PlaybackController, std::true_type>,
        // method 'playingChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pausedChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'totalReadingsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playbackSpeedChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loopEnabledChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'currentTimestampChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'dataPoint'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'playbackFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'statisticsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nextDataPoint'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<SensorReading> &, std::false_type>,
        // method 'play'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pause'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'forward'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rewind'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'seekToIndex'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'seekToTimestamp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>,
        // method 'getReadingsInRange'
        QtPrivate::TypeAndForceComplete<QList<SensorReading>, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>,
        // method 'getStatistics'
        QtPrivate::TypeAndForceComplete<QVariantMap, std::false_type>
    >,
    nullptr
} };

void PlaybackController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlaybackController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->playingChanged(); break;
        case 1: _t->pausedChanged(); break;
        case 2: _t->currentIndexChanged(); break;
        case 3: _t->totalReadingsChanged(); break;
        case 4: _t->playbackSpeedChanged(); break;
        case 5: _t->loopEnabledChanged(); break;
        case 6: _t->currentTimestampChanged(); break;
        case 7: _t->dataPoint((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 8: _t->playbackFinished(); break;
        case 9: _t->statisticsChanged(); break;
        case 10: _t->nextDataPoint(); break;
        case 11: _t->loadData((*reinterpret_cast< std::add_pointer_t<QList<SensorReading>>>(_a[1]))); break;
        case 12: _t->play(); break;
        case 13: _t->pause(); break;
        case 14: _t->stop(); break;
        case 15: _t->forward(); break;
        case 16: _t->rewind(); break;
        case 17: _t->seekToIndex((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 18: _t->seekToTimestamp((*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[1]))); break;
        case 19: { QList<SensorReading> _r = _t->getReadingsInRange((*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QList<SensorReading>*>(_a[0]) = std::move(_r); }  break;
        case 20: { QVariantMap _r = _t->getStatistics();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<SensorReading> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (PlaybackController::*)();
            if (_q_method_type _q_method = &PlaybackController::playingChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (PlaybackController::*)();
            if (_q_method_type _q_method = &PlaybackController::pausedChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (PlaybackController::*)();
            if (_q_method_type _q_method = &PlaybackController::currentIndexChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (PlaybackController::*)();
            if (_q_method_type _q_method = &PlaybackController::totalReadingsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (PlaybackController::*)();
            if (_q_method_type _q_method = &PlaybackController::playbackSpeedChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (PlaybackController::*)();
            if (_q_method_type _q_method = &PlaybackController::loopEnabledChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (PlaybackController::*)();
            if (_q_method_type _q_method = &PlaybackController::currentTimestampChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (PlaybackController::*)(double , double , const QString & , const QString & );
            if (_q_method_type _q_method = &PlaybackController::dataPoint; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (PlaybackController::*)();
            if (_q_method_type _q_method = &PlaybackController::playbackFinished; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (PlaybackController::*)();
            if (_q_method_type _q_method = &PlaybackController::statisticsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isPlaying(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isPaused(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->currentIndex(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->totalReadings(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->playbackSpeed(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->loopEnabled(); break;
        case 6: *reinterpret_cast< QDateTime*>(_v) = _t->currentTimestamp(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 4: _t->setPlaybackSpeed(*reinterpret_cast< double*>(_v)); break;
        case 5: _t->setLoopEnabled(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *PlaybackController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlaybackController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN18PlaybackControllerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PlaybackController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void PlaybackController::playingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PlaybackController::pausedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PlaybackController::currentIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PlaybackController::totalReadingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PlaybackController::playbackSpeedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PlaybackController::loopEnabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void PlaybackController::currentTimestampChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void PlaybackController::dataPoint(double _t1, double _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PlaybackController::playbackFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void PlaybackController::statisticsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
