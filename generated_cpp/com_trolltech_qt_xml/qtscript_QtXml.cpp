#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QVariant>
#include <__package_shared.h>
#include <qdom.h>

Q_DECLARE_METATYPE(QDomDocument::ParseOption)
Q_DECLARE_METATYPE(QDomDocument::ParseOptions)

namespace {

static const QDomDocument::ParseOption optionValues[] = {
    QDomDocument::ParseOption::Default,
    QDomDocument::ParseOption::UseNamespaceProcessing,
    QDomDocument::ParseOption::PreserveSpacingOnlyNodes
};

static const char * const optionNames[] = {
    "Default",
    "UseNamespaceProcessing",
    "PreserveSpacingOnlyNodes"
};

static QString optionName(QDomDocument::ParseOption value)
{
    for (int i = 0; i < int(sizeof(optionValues) / sizeof(optionValues[0])); ++i) {
        if (optionValues[i] == value)
            return QString::fromLatin1(optionNames[i]);
    }
    return QString();
}

static QDomDocument::ParseOption optionFromScript(const QScriptValue &value)
{
    const QVariant variant = value.toVariant();
    if (variant.userType() == qMetaTypeId<QDomDocument::ParseOption>())
        return qvariant_cast<QDomDocument::ParseOption>(variant);
    if (variant.userType() == qMetaTypeId<QDomDocument::ParseOptions>())
        return static_cast<QDomDocument::ParseOption>(qvariant_cast<QDomDocument::ParseOptions>(variant).toInt());
    return static_cast<QDomDocument::ParseOption>(value.toInt32());
}

static QDomDocument::ParseOptions optionsFromScript(const QScriptValue &value)
{
    const QVariant variant = value.toVariant();
    if (variant.userType() == qMetaTypeId<QDomDocument::ParseOptions>())
        return qvariant_cast<QDomDocument::ParseOptions>(variant);
    if (variant.userType() == qMetaTypeId<QDomDocument::ParseOption>())
        return qvariant_cast<QDomDocument::ParseOption>(variant);
    return QDomDocument::ParseOptions::fromInt(value.toInt32());
}

static QScriptValue enumValue(QScriptEngine *engine, QDomDocument::ParseOption value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static QScriptValue constructOption(QScriptContext *context, QScriptEngine *engine)
{
    if (context->argumentCount() != 1)
        return context->throwError(QScriptContext::TypeError,
                                   QStringLiteral("QtXml.ParseOption(value) expects one argument"));
    const QDomDocument::ParseOption value = optionFromScript(context->argument(0));
    for (const QDomDocument::ParseOption known : optionValues) {
        if (known == value)
            return enumValue(engine, value);
    }
    return context->throwError(QStringLiteral("QtXml.ParseOption(): invalid enum value"));
}

static QScriptValue optionValueOf(QScriptContext *context, QScriptEngine *)
{
    return QScriptValue(context->engine(), static_cast<int>(optionFromScript(context->thisObject())));
}

static QScriptValue optionToString(QScriptContext *context, QScriptEngine *engine)
{
    return QScriptValue(engine, optionName(optionFromScript(context->thisObject())));
}

static QScriptValue constructOptions(QScriptContext *context, QScriptEngine *engine)
{
    QDomDocument::ParseOptions result;
    for (int i = 0; i < context->argumentCount(); ++i) {
        const QVariant variant = context->argument(i).toVariant();
        if (variant.userType() != qMetaTypeId<QDomDocument::ParseOption>()
            && variant.userType() != qMetaTypeId<QDomDocument::ParseOptions>()
            && !context->argument(i).isNumber()) {
            return context->throwError(QScriptContext::TypeError,
                                       QStringLiteral("QtXml.ParseOptions() expects ParseOption values"));
        }
        result |= optionsFromScript(context->argument(i));
    }
    return engine->newVariant(qVariantFromValue(result));
}

static QScriptValue optionsValueOf(QScriptContext *context, QScriptEngine *)
{
    return QScriptValue(context->engine(), optionsFromScript(context->thisObject()).toInt());
}

static QScriptValue optionsToString(QScriptContext *context, QScriptEngine *engine)
{
    const QDomDocument::ParseOptions value = optionsFromScript(context->thisObject());
    QStringList names;
    if (value == QDomDocument::ParseOptions()) {
        names.append(QStringLiteral("Default"));
    } else {
        for (int i = 1; i < int(sizeof(optionValues) / sizeof(optionValues[0])); ++i) {
            if (value.testFlag(optionValues[i]))
                names.append(QString::fromLatin1(optionNames[i]));
        }
    }
    return QScriptValue(engine, names.join(QLatin1Char('|')));
}

static QScriptValue optionsEquals(QScriptContext *context, QScriptEngine *)
{
    return QScriptValue(context->engine(),
                        optionsFromScript(context->thisObject())
                            == optionsFromScript(context->argument(0)));
}

static QScriptValue createEnumClass(QScriptEngine *engine)
{
    QScriptValue prototype = engine->newObject();
    prototype.setProperty(QStringLiteral("valueOf"), engine->newFunction(optionValueOf),
                          QScriptValue::SkipInEnumeration);
    prototype.setProperty(QStringLiteral("toString"), engine->newFunction(optionToString),
                          QScriptValue::SkipInEnumeration);
    return engine->newFunction(constructOption, prototype, 1);
}

static QScriptValue createFlagsClass(QScriptEngine *engine)
{
    QScriptValue prototype = engine->newObject();
    prototype.setProperty(QStringLiteral("valueOf"), engine->newFunction(optionsValueOf),
                          QScriptValue::SkipInEnumeration);
    prototype.setProperty(QStringLiteral("toString"), engine->newFunction(optionsToString),
                          QScriptValue::SkipInEnumeration);
    prototype.setProperty(QStringLiteral("equals"), engine->newFunction(optionsEquals),
                          QScriptValue::SkipInEnumeration);
    return engine->newFunction(constructOptions, prototype);
}

static QScriptValue optionToScriptValue(QScriptEngine *engine,
                                        const QDomDocument::ParseOption &value)
{
    const QScriptValue namespaceObject = engine->globalObject().property(QStringLiteral("QtXml"));
    return namespaceObject.property(optionName(value));
}

static void optionFromScriptValue(const QScriptValue &value,
                                  QDomDocument::ParseOption &out)
{
    out = optionFromScript(value);
}

static QScriptValue optionsToScriptValue(QScriptEngine *engine,
                                         const QDomDocument::ParseOptions &value)
{
    QScriptValue result = engine->newVariant(qVariantFromValue(value));
    result.setPrototype(engine->globalObject().property(QStringLiteral("QtXml"))
                            .property(QStringLiteral("ParseOptions"))
                            .property(QStringLiteral("prototype")));
    return result;
}

static void optionsFromScriptValue(const QScriptValue &value,
                                   QDomDocument::ParseOptions &out)
{
    out = optionsFromScript(value);
}

} // namespace

void qtscript_initialize_QtXml_namespace(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    QScriptValue namespaceObject = engine->newObject();

    QScriptValue optionClass = createEnumClass(engine);
    qScriptRegisterMetaType<QDomDocument::ParseOption>(engine, optionToScriptValue,
                                                        optionFromScriptValue,
                                                        optionClass.property(QStringLiteral("prototype")));
    for (int i = 0; i < int(sizeof(optionValues) / sizeof(optionValues[0])); ++i) {
        namespaceObject.setProperty(QString::fromLatin1(optionNames[i]), enumValue(engine, optionValues[i]),
                                     QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    namespaceObject.setProperty(QStringLiteral("ParseOption"), optionClass,
                                QScriptValue::ReadOnly | QScriptValue::Undeletable);

    const QScriptValue optionsClass = createFlagsClass(engine);
    qScriptRegisterMetaType<QDomDocument::ParseOptions>(engine, optionsToScriptValue,
                                                         optionsFromScriptValue,
                                                         optionsClass.property(QStringLiteral("prototype")));
    namespaceObject.setProperty(QStringLiteral("ParseOptions"), optionsClass,
                                QScriptValue::ReadOnly | QScriptValue::Undeletable);

    extensionObject.setProperty(QStringLiteral("QtXml"), namespaceObject,
                                QScriptValue::SkipInEnumeration);
    QScriptValue documentClass = extensionObject.property(QStringLiteral("QDomDocument"));
    for (int i = 0; i < int(sizeof(optionValues) / sizeof(optionValues[0])); ++i) {
        optionClass.setProperty(QString::fromLatin1(optionNames[i]), enumValue(engine, optionValues[i]),
                                QScriptValue::ReadOnly | QScriptValue::Undeletable);
        documentClass.setProperty(QString::fromLatin1(optionNames[i]), enumValue(engine, optionValues[i]),
                                   QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    documentClass.setProperty(QStringLiteral("ParseOption"), optionClass,
                              QScriptValue::ReadOnly | QScriptValue::Undeletable);
    documentClass.setProperty(QStringLiteral("ParseOptions"), optionsClass,
                              QScriptValue::ReadOnly | QScriptValue::Undeletable);
}
