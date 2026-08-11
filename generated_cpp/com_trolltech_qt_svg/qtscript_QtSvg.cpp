#include "qtscript_svg_shared.h"

namespace {

static QScriptValue createEnumClass(QScriptEngine *engine,
                                    QScriptEngine::FunctionSignature construct,
                                    QScriptEngine::FunctionSignature valueOf,
                                    QScriptEngine::FunctionSignature toString)
{
    QScriptValue prototype = engine->newObject();
    prototype.setProperty(QStringLiteral("valueOf"), engine->newFunction(valueOf),
                          QScriptValue::SkipInEnumeration);
    prototype.setProperty(QStringLiteral("toString"), engine->newFunction(toString),
                          QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, prototype, 1);
}

static QScriptValue createFlagsClass(QScriptEngine *engine,
                                     QScriptEngine::FunctionSignature construct,
                                     QScriptEngine::FunctionSignature valueOf,
                                     QScriptEngine::FunctionSignature toString,
                                     QScriptEngine::FunctionSignature equals)
{
    QScriptValue prototype = engine->newObject();
    prototype.setProperty(QStringLiteral("valueOf"), engine->newFunction(valueOf),
                          QScriptValue::SkipInEnumeration);
    prototype.setProperty(QStringLiteral("toString"), engine->newFunction(toString),
                          QScriptValue::SkipInEnumeration);
    prototype.setProperty(QStringLiteral("equals"), engine->newFunction(equals),
                          QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, prototype);
}

static const QtSvg::Option optionValues[] = {
    QtSvg::NoOption,
    QtSvg::Tiny12FeaturesOnly,
    QtSvg::AssumeTrustedSource,
    QtSvg::DisableSMILAnimations,
    QtSvg::DisableCSSAnimations,
    QtSvg::DisableAnimations
};

static const char * const optionNames[] = {
    "NoOption",
    "Tiny12FeaturesOnly",
    "AssumeTrustedSource",
    "DisableSMILAnimations",
    "DisableCSSAnimations",
    "DisableAnimations"
};

static QString optionName(QtSvg::Option value)
{
    for (int i = 0; i < static_cast<int>(sizeof(optionValues) / sizeof(optionValues[0])); ++i) {
        if (optionValues[i] == value)
            return QString::fromLatin1(optionNames[i]);
    }
    return QString();
}

static QScriptValue optionToScriptValue(QScriptEngine *engine, const QtSvg::Option &value)
{
    return qtscript_svg::optionValue(engine, value);
}

static void optionFromScriptValue(const QScriptValue &value, QtSvg::Option &out)
{
    out = qtscript_svg::option(value);
}

static QScriptValue constructOption(QScriptContext *context, QScriptEngine *engine)
{
    if (context->argumentCount() != 1)
        return context->throwError(QScriptContext::TypeError,
                                   QStringLiteral("QtSvg.Option(value) expects one argument"));
    const QtSvg::Option value = qtscript_svg::option(context->argument(0));
    for (const QtSvg::Option known : optionValues) {
        if (known == value)
            return qScriptValueFromValue(engine, value);
    }
    return context->throwError(QStringLiteral("QtSvg.Option(): invalid enum value"));
}

static QScriptValue optionValueOf(QScriptContext *context, QScriptEngine *engine)
{
    return QScriptValue(engine, static_cast<int>(qtscript_svg::option(context->thisObject())));
}

static QScriptValue optionToString(QScriptContext *context, QScriptEngine *engine)
{
    return QScriptValue(engine, optionName(qtscript_svg::option(context->thisObject())));
}

static QScriptValue optionsToScriptValue(QScriptEngine *engine, const QtSvg::Options &value)
{
    return qtscript_svg::optionsValue(engine, value);
}

static void optionsFromScriptValue(const QScriptValue &value, QtSvg::Options &out)
{
    out = qtscript_svg::options(value);
}

static QScriptValue constructOptions(QScriptContext *context, QScriptEngine *engine)
{
    QtSvg::Options result;
    if (context->argumentCount() == 1 && context->argument(0).isNumber()) {
        result = QtSvg::Options::fromInt(context->argument(0).toInt32());
    } else {
        for (int i = 0; i < context->argumentCount(); ++i) {
            const QVariant value = context->argument(i).toVariant();
            if (value.userType() == qMetaTypeId<QtSvg::Options>())
                result |= qvariant_cast<QtSvg::Options>(value);
            else if (value.userType() == qMetaTypeId<QtSvg::Option>())
                result |= qvariant_cast<QtSvg::Option>(value);
            else
                return context->throwError(QScriptContext::TypeError,
                                           QStringLiteral("QtSvg.Options() expects Option values"));
        }
    }
    return qtscript_svg::optionsValue(engine, result);
}

static QScriptValue optionsValueOf(QScriptContext *context, QScriptEngine *engine)
{
    return QScriptValue(engine, static_cast<int>(qtscript_svg::options(context->thisObject())));
}

static QScriptValue optionsToString(QScriptContext *context, QScriptEngine *engine)
{
    const QtSvg::Options value = qtscript_svg::options(context->thisObject());
    QStringList names;
    for (int i = 0; i < static_cast<int>(sizeof(optionValues) / sizeof(optionValues[0])); ++i) {
        if (optionValues[i] != QtSvg::NoOption
            && (value & optionValues[i]) == optionValues[i]) {
            names.append(QString::fromLatin1(optionNames[i]));
        }
    }
    if (names.isEmpty())
        names.append(QStringLiteral("NoOption"));
    return QScriptValue(engine, names.join(QLatin1Char('|')));
}

static QScriptValue optionsEquals(QScriptContext *context, QScriptEngine *engine)
{
    return QScriptValue(engine, qtscript_svg::options(context->thisObject())
                        == qtscript_svg::options(context->argument(0)));
}

} // namespace

void qtscript_initialize_QtSvg_namespace(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    QScriptValue namespaceObject = engine->newObject();

    const QScriptValue optionClass = createEnumClass(engine, constructOption,
                                                      optionValueOf, optionToString);
    qScriptRegisterMetaType<QtSvg::Option>(engine, optionToScriptValue,
                                           optionFromScriptValue,
                                           optionClass.property(QStringLiteral("prototype")));
    for (int i = 0; i < static_cast<int>(sizeof(optionValues) / sizeof(optionValues[0])); ++i) {
        namespaceObject.setProperty(QString::fromLatin1(optionNames[i]),
                                     qtscript_svg::optionValue(engine, optionValues[i]),
                                     QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    namespaceObject.setProperty(QStringLiteral("Option"), optionClass,
                                QScriptValue::ReadOnly | QScriptValue::Undeletable);

    const QScriptValue optionsClass = createFlagsClass(engine, constructOptions,
                                                        optionsValueOf, optionsToString,
                                                        optionsEquals);
    qScriptRegisterMetaType<QtSvg::Options>(engine, optionsToScriptValue,
                                             optionsFromScriptValue,
                                             optionsClass.property(QStringLiteral("prototype")));
    namespaceObject.setProperty(QStringLiteral("Options"), optionsClass,
                                QScriptValue::ReadOnly | QScriptValue::Undeletable);

    extensionObject.setProperty(QStringLiteral("QtSvg"), namespaceObject,
                                QScriptValue::SkipInEnumeration);
    // Qt 5's type system called this namespace QSvg. Keep the alias while
    // making the Qt 6 spelling available as the canonical one.
    extensionObject.setProperty(QStringLiteral("QSvg"), namespaceObject,
                                QScriptValue::SkipInEnumeration);
}
