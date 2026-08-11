#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>

#include "qtscript_svg_shared.h"

void qtscript_initialize_com_trolltech_qt_svg_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    qtscript_initialize_QtSvg_namespace(extensionObject);

    extensionObject.setProperty(QStringLiteral("QSvgRenderer"),
                                qtscript_create_QSvgRenderer_class(engine),
                                QScriptValue::SkipInEnumeration);
    extensionObject.setProperty(QStringLiteral("QSvgGenerator"),
                                qtscript_create_QSvgGenerator_class(engine),
                                QScriptValue::SkipInEnumeration);
    extensionObject.setProperty(QStringLiteral("QSvgWidget"),
                                qtscript_create_QSvgWidget_class(engine),
                                QScriptValue::SkipInEnumeration);
    extensionObject.setProperty(QStringLiteral("QGraphicsSvgItem"),
                                qtscript_create_QGraphicsSvgItem_class(engine),
                                QScriptValue::SkipInEnumeration);
}
