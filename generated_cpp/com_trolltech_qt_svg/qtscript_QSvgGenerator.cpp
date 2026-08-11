#include "qtscript_svg_shared.h"

#include <QtCore/QDebug>
#include <QtCore/QRect>
#include <QtCore/QSize>

namespace {

static constexpr uint kGeneratorTag = 0x53570000u;

static const char * const generatorMethodNames[] = {
    "title",
    "setTitle",
    "description",
    "setDescription",
    "size",
    "setSize",
    "viewBox",
    "viewBoxF",
    "setViewBox",
    "fileName",
    "setFileName",
    "outputDevice",
    "setOutputDevice",
    "setResolution",
    "resolution",
    "svgVersion",
    "toString"
};

static const int generatorMethodLengths[] = {
    0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0
};

static const QSvgGenerator::SvgVersion versionValues[] = {
    QSvgGenerator::SvgVersion::SvgTiny12,
    QSvgGenerator::SvgVersion::Svg11
};

static const char * const versionNames[] = {
    "SvgTiny12",
    "Svg11"
};

static QString versionName(QSvgGenerator::SvgVersion value)
{
    for (int i = 0; i < 2; ++i) {
        if (versionValues[i] == value)
            return QString::fromLatin1(versionNames[i]);
    }
    return QString();
}

static QScriptValue versionToScriptValue(QScriptEngine *engine,
                                         const QSvgGenerator::SvgVersion &value)
{
    return engine->newVariant(QVariant::fromValue(value));
}

static void versionFromScriptValue(const QScriptValue &value,
                                   QSvgGenerator::SvgVersion &out)
{
    const QVariant variantValue = value.toVariant();
    if (variantValue.userType() == qMetaTypeId<QSvgGenerator::SvgVersion>())
        out = qvariant_cast<QSvgGenerator::SvgVersion>(variantValue);
    else
        out = static_cast<QSvgGenerator::SvgVersion>(value.toInt32());
}

static QScriptValue constructVersion(QScriptContext *context, QScriptEngine *engine)
{
    if (context->argumentCount() != 1)
        return context->throwError(QScriptContext::TypeError,
                                   QStringLiteral("QSvgGenerator.SvgVersion(value) expects one argument"));
    const int value = context->argument(0).toInt32();
    if (value < 0 || value > 1)
        return context->throwError(QStringLiteral("QSvgGenerator.SvgVersion(): invalid enum value"));
    return qScriptValueFromValue(engine, versionValues[value]);
}

static QScriptValue versionValueOf(QScriptContext *context, QScriptEngine *engine)
{
    return QScriptValue(engine, static_cast<int>(qvariant_cast<QSvgGenerator::SvgVersion>(
        context->thisObject().toVariant())));
}

static QScriptValue versionToString(QScriptContext *context, QScriptEngine *engine)
{
    return QScriptValue(engine, versionName(qvariant_cast<QSvgGenerator::SvgVersion>(
        context->thisObject().toVariant())));
}

static QSvgGenerator *generatorFromThis(QScriptContext *context)
{
    return qtscript_svg::generator(context->thisObject());
}

static QScriptValue generatorMethod(QScriptContext *context, QScriptEngine *engine)
{
    const int id = static_cast<int>(context->callee().data().toUInt32() & 0xFFFFu);
    QSvgGenerator *self = generatorFromThis(context);
    if (!self)
        return qtscript_svg::typeError(context, QStringLiteral("QSvgGenerator method called on an invalid object"));

    switch (id) {
    case 0:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->title());
        break;
    case 1:
        if (context->argumentCount() == 1) {
            self->setTitle(context->argument(0).toString());
            return engine->undefinedValue();
        }
        break;
    case 2:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->description());
        break;
    case 3:
        if (context->argumentCount() == 1) {
            self->setDescription(context->argument(0).toString());
            return engine->undefinedValue();
        }
        break;
    case 4:
        if (context->argumentCount() == 0)
            return qtscript_svg::value(engine, self->size());
        break;
    case 5:
        if (context->argumentCount() == 1) {
            self->setSize(qscriptvalue_cast<QSize>(context->argument(0)));
            return engine->undefinedValue();
        }
        break;
    case 6:
        if (context->argumentCount() == 0)
            return qtscript_svg::value(engine, self->viewBox());
        break;
    case 7:
        if (context->argumentCount() == 0)
            return qtscript_svg::value(engine, self->viewBoxF());
        break;
    case 8:
        if (context->argumentCount() == 1) {
            const QVariant value = context->argument(0).toVariant();
            if (value.userType() == qMetaTypeId<QRect>())
                self->setViewBox(qvariant_cast<QRect>(value));
            else if (value.userType() == qMetaTypeId<QRectF>())
                self->setViewBox(qvariant_cast<QRectF>(value));
            else
                break;
            return engine->undefinedValue();
        }
        break;
    case 9:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->fileName());
        break;
    case 10:
        if (context->argumentCount() == 1) {
            self->setFileName(context->argument(0).toString());
            return engine->undefinedValue();
        }
        break;
    case 11:
        if (context->argumentCount() == 0)
            return qtscript_svg::wrapDevice(engine, self->outputDevice());
        break;
    case 12:
        if (context->argumentCount() == 1) {
            QIODevice *device = qscriptvalue_cast<QIODevice *>(context->argument(0));
            if (!device && !context->argument(0).isNull() && !context->argument(0).isUndefined())
                return qtscript_svg::typeError(context,
                                               QStringLiteral("QSvgGenerator::setOutputDevice() needs a QIODevice"));
            self->setOutputDevice(device);
            // QSvgGenerator is not a QObject and does not take ownership of
            // its output device. Keep the script wrapper alive for as long as
            // the generator may write to it, matching the Qt 5 generated
            // binding's reference-count annotation.
            context->thisObject().setProperty(QStringLiteral("__qtscript_svg_output_device"),
                                              context->argument(0),
                                              QScriptValue::SkipInEnumeration);
            return engine->undefinedValue();
        }
        break;
    case 13:
        if (context->argumentCount() == 1) {
            self->setResolution(context->argument(0).toInt32());
            return engine->undefinedValue();
        }
        break;
    case 14:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->resolution());
        break;
    case 15:
        if (context->argumentCount() == 0)
            return engine->newVariant(QVariant::fromValue(self->svgVersion()));
        break;
    case 16:
        if (context->argumentCount() == 0) {
            QString result;
            QDebug debug(&result);
            debug << self;
            return QScriptValue(engine, result);
        }
        break;
    default:
        break;
    }

    return qtscript_svg::invalidArguments(context, QStringLiteral("QSvgGenerator"));
}

static QScriptValue generatorConstructor(QScriptContext *context, QScriptEngine *engine)
{
    if (context->thisObject().strictlyEquals(engine->globalObject()))
        return context->throwError(QStringLiteral("QSvgGenerator(): Did you forget to construct with 'new'?"));

    QSvgGenerator *result = nullptr;
    if (context->argumentCount() == 0) {
        result = new QSvgGenerator();
    } else if (context->argumentCount() == 1) {
        const int value = context->argument(0).toInt32();
        if (value >= 0 && value < 2)
            result = new QSvgGenerator(versionValues[value]);
    }
    if (!result)
        return qtscript_svg::invalidArguments(context, QStringLiteral("QSvgGenerator"));

    QScriptValue wrapper = engine->newVariant(context->thisObject(),
                                               QVariant::fromValue(result));
    wrapper.setPrototype(context->callee().property(QStringLiteral("prototype")));
    return wrapper;
}

static QScriptValue generatorToScriptValue(QScriptEngine *engine, QSvgGenerator * const &value)
{
    if (!value)
        return engine->nullValue();
    return engine->newVariant(QVariant::fromValue(value));
}

static void generatorFromScriptValue(const QScriptValue &value, QSvgGenerator *&out)
{
    out = qtscript_svg::generator(value);
}

} // namespace

QScriptValue qtscript_create_QSvgGenerator_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSvgGenerator *>(), QScriptValue());
    QScriptValue prototype = engine->newVariant(QVariant::fromValue(static_cast<QSvgGenerator *>(nullptr)));
    prototype.setPrototype(engine->defaultPrototype(qMetaTypeId<QPaintDevice *>()));
    for (int i = 0; i < static_cast<int>(sizeof(generatorMethodNames) / sizeof(generatorMethodNames[0])); ++i) {
        QScriptValue function = engine->newFunction(generatorMethod, generatorMethodLengths[i]);
        function.setData(QScriptValue(engine, kGeneratorTag | static_cast<uint>(i)));
        prototype.setProperty(QString::fromLatin1(generatorMethodNames[i]), function,
                              QScriptValue::SkipInEnumeration);
    }

    QScriptValue versionPrototype = engine->newObject();
    versionPrototype.setProperty(QStringLiteral("valueOf"), engine->newFunction(versionValueOf),
                                 QScriptValue::SkipInEnumeration);
    versionPrototype.setProperty(QStringLiteral("toString"), engine->newFunction(versionToString),
                                 QScriptValue::SkipInEnumeration);
    const QScriptValue versionClass = engine->newFunction(constructVersion, versionPrototype, 1);
    qScriptRegisterMetaType<QSvgGenerator::SvgVersion>(engine, versionToScriptValue,
                                                       versionFromScriptValue, versionPrototype);
    for (int i = 0; i < 2; ++i) {
        prototype.setProperty(QString::fromLatin1(versionNames[i]),
                              engine->newVariant(QVariant::fromValue(versionValues[i])),
                              QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }

    engine->setDefaultPrototype(qMetaTypeId<QSvgGenerator *>(), prototype);
    qScriptRegisterMetaType<QSvgGenerator *>(engine, generatorToScriptValue,
                                             generatorFromScriptValue, prototype);
    QScriptValue constructor = engine->newFunction(generatorConstructor, prototype, 1);
    constructor.setData(QScriptValue(engine, kGeneratorTag));
    constructor.setProperty(QStringLiteral("SvgVersion"), versionClass,
                            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    // The unscoped aliases are convenient and match the style of the older
    // generated bindings while the nested enum remains canonical.
    constructor.setProperty(QStringLiteral("SvgTiny12"),
                            engine->newVariant(QVariant::fromValue(versionValues[0])),
                            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    constructor.setProperty(QStringLiteral("Svg11"),
                            engine->newVariant(QVariant::fromValue(versionValues[1])),
                            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    return constructor;
}
