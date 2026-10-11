#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtCore/QStringConverter>
#include <QtCore/QVariant>

// Native Qt 6 encoding enum only. This is not a replacement QTextCodec API;
// QStringEncoder/QStringDecoder and converter instances are not bound here.
Q_DECLARE_METATYPE(QStringConverter::Encoding)

static const char * const encodingNames[] = {
    "Utf8", "Utf16", "Utf16LE", "Utf16BE", "Utf32", "Utf32LE",
    "Utf32BE", "Latin1", "System"
};
static_assert(sizeof(encodingNames) / sizeof(*encodingNames)
    == QStringConverter::LastEncoding + 1, "Update the encoding binding for new Qt encodings");

static QScriptValue encodingToScript(QScriptEngine *engine, const QStringConverter::Encoding &value)
{
    return engine->newVariant(QVariant::fromValue(value));
}

static void encodingFromScript(const QScriptValue &value, QStringConverter::Encoding &out)
{
    if (value.isNumber())
        out = static_cast<QStringConverter::Encoding>(value.toInt32());
    else
        out = value.toVariant().value<QStringConverter::Encoding>();
}

static QScriptValue encodingValueOf(QScriptContext *context, QScriptEngine *engine)
{
    const QVariant value = context->thisObject().toVariant();
    if (value.userType() != qMetaTypeId<QStringConverter::Encoding>())
        return context->throwError(QScriptContext::TypeError, "Not a QStringConverter.Encoding");
    return QScriptValue(engine, static_cast<int>(value.value<QStringConverter::Encoding>()));
}

static QScriptValue encodingToString(QScriptContext *context, QScriptEngine *engine)
{
    const QVariant value = context->thisObject().toVariant();
    if (value.userType() != qMetaTypeId<QStringConverter::Encoding>())
        return context->throwError(QScriptContext::TypeError, "Not a QStringConverter.Encoding");
    const int index = static_cast<int>(value.value<QStringConverter::Encoding>());
    if (index < QStringConverter::Utf8 || index > QStringConverter::LastEncoding)
        return context->throwError(QScriptContext::RangeError, "Invalid QStringConverter.Encoding");
    return QScriptValue(engine, QString::fromLatin1(encodingNames[index]));
}

static QScriptValue constructEncoding(QScriptContext *context, QScriptEngine *engine)
{
    if (context->argumentCount() != 1 || !context->argument(0).isNumber())
        return context->throwError(QScriptContext::TypeError, "QStringConverter.Encoding(): expected one number");
    const double value = context->argument(0).toNumber();
    if (!(value >= QStringConverter::Utf8 && value <= QStringConverter::LastEncoding)
        || value != static_cast<int>(value))
        return context->throwError(QScriptContext::RangeError, "QStringConverter.Encoding(): invalid encoding");
    return encodingToScript(engine, static_cast<QStringConverter::Encoding>(static_cast<int>(value)));
}

QScriptValue qtscript_create_QStringConverter_class(QScriptEngine *engine)
{
    QScriptValue namespaceObject = engine->newObject();
    QScriptValue prototype = engine->newObject();
    prototype.setProperty("valueOf", engine->newFunction(encodingValueOf), QScriptValue::SkipInEnumeration);
    prototype.setProperty("toString", engine->newFunction(encodingToString), QScriptValue::SkipInEnumeration);
    qScriptRegisterMetaType<QStringConverter::Encoding>(engine, encodingToScript, encodingFromScript, prototype);
    const auto constantFlags = QScriptValue::ReadOnly | QScriptValue::Undeletable;
    namespaceObject.setProperty("Encoding", engine->newFunction(constructEncoding, prototype, 1), constantFlags);
    for (int index = QStringConverter::Utf8; index <= QStringConverter::LastEncoding; ++index) {
        namespaceObject.setProperty(QString::fromLatin1(encodingNames[index]),
            encodingToScript(engine, static_cast<QStringConverter::Encoding>(index)), constantFlags);
    }
    namespaceObject.setProperty("LastEncoding", namespaceObject.property("System"), constantFlags);
    return namespaceObject;
}
