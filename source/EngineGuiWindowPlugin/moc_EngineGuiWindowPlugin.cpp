/****************************************************************************
** Meta object code from reading C++ file 'EngineGuiWindowPlugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "EngineGuiWindowPlugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EngineGuiWindowPlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EngineGuiWindowPlugin_t {
    QByteArrayData data[1];
    char stringdata0[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EngineGuiWindowPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EngineGuiWindowPlugin_t qt_meta_stringdata_EngineGuiWindowPlugin = {
    {
QT_MOC_LITERAL(0, 0, 21) // "EngineGuiWindowPlugin"

    },
    "EngineGuiWindowPlugin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EngineGuiWindowPlugin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void EngineGuiWindowPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject EngineGuiWindowPlugin::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_EngineGuiWindowPlugin.data,
    qt_meta_data_EngineGuiWindowPlugin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EngineGuiWindowPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EngineGuiWindowPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EngineGuiWindowPlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "::Editor::Plugin"))
        return static_cast< ::Editor::Plugin*>(this);
    if (!strcmp(_clname, "com.unigine.EditorPlugin"))
        return static_cast< Editor::Plugin*>(this);
    return QObject::qt_metacast(_clname);
}

int EngineGuiWindowPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x18,  'c',  'o',  'm',  '.',  'u', 
    'n',  'i',  'g',  'i',  'n',  'e',  '.',  'E', 
    'd',  'i',  't',  'o',  'r',  'P',  'l',  'u', 
    'g',  'i',  'n', 
    // "className"
    0x03,  0x75,  'E',  'n',  'g',  'i',  'n',  'e', 
    'G',  'u',  'i',  'W',  'i',  'n',  'd',  'o', 
    'w',  'P',  'l',  'u',  'g',  'i',  'n', 
    // "MetaData"
    0x04,  0xa6,  0x6d,  'C',  'o',  'm',  'p',  'a', 
    't',  'V',  'e',  'r',  's',  'i',  'o',  'n', 
    0x67,  '1',  '.',  '0',  '.',  '0',  '.',  '0', 
    0x6c,  'D',  'e',  'p',  'e',  'n',  'd',  'e', 
    'n',  'c',  'i',  'e',  's',  0x80,  0x6b,  'D', 
    'e',  's',  'c',  'r',  'i',  'p',  't',  'i', 
    'o',  'n',  0x78,  0x6a,  '<',  'p',  '>',  'T', 
    'h',  'e',  ' ',  'p',  'l',  'u',  'g',  'i', 
    'n',  ' ',  'i',  's',  ' ',  'u',  's',  'e', 
    'd',  ' ',  't',  'o',  ' ',  'd',  'e',  'm', 
    'o',  'n',  's',  't',  'r',  'a',  't',  'e', 
    ' ',  't',  'h',  'e',  ' ',  'u',  's',  'a', 
    'g',  'e',  ' ',  'o',  'f',  ' ',  't',  'h', 
    'e',  ' ',  'E',  'n',  'g',  'i',  'n',  'e', 
    'G',  'u',  'i',  'W',  'i',  'n',  'd',  'o', 
    'w',  ' ',  'w',  'd',  'i',  'g',  'e',  't', 
    ' ',  'f',  'o',  'r',  ' ',  'r',  'e',  'n', 
    'd',  'e',  'r',  ' ',  'G',  'U',  'I',  ' ', 
    'o',  'f',  ' ',  'e',  'n',  'g',  'i',  'n', 
    'e',  '.',  '<',  '/',  'p',  '>',  0x64,  'N', 
    'a',  'm',  'e',  0x75,  'E',  'n',  'g',  'i', 
    'n',  'e',  'G',  'u',  'i',  'W',  'i',  'n', 
    'd',  'o',  'w',  'P',  'l',  'u',  'g',  'i', 
    'n',  0x66,  'V',  'e',  'n',  'd',  'o',  'r', 
    0x60,  0x67,  'V',  'e',  'r',  's',  'i',  'o', 
    'n',  0x67,  '1',  '.',  '0',  '.',  '0',  '.', 
    '0', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(EngineGuiWindowPlugin, EngineGuiWindowPlugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
