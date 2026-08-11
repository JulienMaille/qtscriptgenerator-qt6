#include <QtScript/QScriptExtensionPlugin>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QtPlugin>
#include "plugin.h"


QStringList com_trolltech_qt_svg_ScriptPlugin::keys() const
{
    QStringList list;
    list << QLatin1String("qt");
    list << QLatin1String("qt.svg");
    list << QLatin1String("qt.svgwidgets");
    return list;
}

void com_trolltech_qt_svg_ScriptPlugin::initialize(const QString &key, QScriptEngine *engine)
{
    if (key == QLatin1String("qt")) {
    } else if (key == QLatin1String("qt.svg")
               || key == QLatin1String("qt.svgwidgets")) {
        QScriptValue extensionObject = engine->globalObject();
        const QString marker = QStringLiteral("__qtscript_svg_initialized");
        if (extensionObject.property(marker).toBool())
            return;
        extensionObject.setProperty(marker, QScriptValue(engine, true),
                                    QScriptValue::ReadOnly | QScriptValue::Undeletable
                                    | QScriptValue::SkipInEnumeration);
        qtscript_initialize_com_trolltech_qt_svg_bindings(extensionObject);
    } else {
        Q_ASSERT_X(false, "com_trolltech_qt_svg::initialize", qPrintable(key));
    }
}

