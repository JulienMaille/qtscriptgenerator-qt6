#include "qtscript_svg_shared.h"

#include <QtCore/QDebug>
#include <QtCore/QRect>
#include <QtCore/QSize>
#include <QtGui/QTransform>

namespace {

static constexpr uint kRendererTag = 0x53560000u;

static const char * const rendererMethodNames[] = {
    "isValid",
    "defaultSize",
    "viewBox",
    "viewBoxF",
    "setViewBox",
    "aspectRatioMode",
    "setAspectRatioMode",
    "options",
    "setOptions",
    "animated",
    "framesPerSecond",
    "setFramesPerSecond",
    "currentFrame",
    "setCurrentFrame",
    "animationDuration",
    "isAnimationEnabled",
    "setAnimationEnabled",
    "boundsOnElement",
    "elementExists",
    "transformForElement",
    "load",
    "render",
    "toString"
};

static const int rendererMethodLengths[] = {
    0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1,
    1, 1, 1, 1, 3, 0
};

static QSvgRenderer *rendererFromThis(QScriptContext *context)
{
    return qtscript_svg::renderer(context->thisObject());
}

static QScriptValue rendererMethod(QScriptContext *context, QScriptEngine *engine)
{
    const uint data = context->callee().data().toUInt32();
    const int id = static_cast<int>(data & 0xFFFFu);
    QSvgRenderer *self = rendererFromThis(context);
    if (!self)
        return qtscript_svg::typeError(context, QStringLiteral("QSvgRenderer method called on an invalid object"));

    switch (id) {
    case 0:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->isValid());
        break;
    case 1:
        if (context->argumentCount() == 0)
            return qtscript_svg::value(engine, self->defaultSize());
        break;
    case 2:
        if (context->argumentCount() == 0)
            return qtscript_svg::value(engine, self->viewBox());
        break;
    case 3:
        if (context->argumentCount() == 0)
            return qtscript_svg::value(engine, self->viewBoxF());
        break;
    case 4:
        if (context->argumentCount() == 1) {
            const QVariant value = context->argument(0).toVariant();
            if (value.userType() == qMetaTypeId<QRect>()) {
                self->setViewBox(qvariant_cast<QRect>(value));
                return engine->undefinedValue();
            }
            if (value.userType() == qMetaTypeId<QRectF>()) {
                self->setViewBox(qvariant_cast<QRectF>(value));
                return engine->undefinedValue();
            }
        }
        break;
    case 5:
        if (context->argumentCount() == 0)
            return qtscript_svg::value(engine, self->aspectRatioMode());
        break;
    case 6:
        if (context->argumentCount() == 1) {
            self->setAspectRatioMode(qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(0)));
            return engine->undefinedValue();
        }
        break;
    case 7:
        if (context->argumentCount() == 0)
            return qtscript_svg::optionsValue(engine, self->options());
        break;
    case 8:
        if (context->argumentCount() == 1) {
            self->setOptions(qtscript_svg::options(context->argument(0)));
            return engine->undefinedValue();
        }
        break;
    case 9:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->animated());
        break;
    case 10:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->framesPerSecond());
        break;
    case 11:
        if (context->argumentCount() == 1) {
            self->setFramesPerSecond(context->argument(0).toInt32());
            return engine->undefinedValue();
        }
        break;
    case 12:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->currentFrame());
        break;
    case 13:
        if (context->argumentCount() == 1) {
            self->setCurrentFrame(context->argument(0).toInt32());
            return engine->undefinedValue();
        }
        break;
    case 14:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->animationDuration());
        break;
    case 15:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->isAnimationEnabled());
        break;
    case 16:
        if (context->argumentCount() == 1) {
            self->setAnimationEnabled(context->argument(0).toBool());
            return engine->undefinedValue();
        }
        break;
    case 17:
        if (context->argumentCount() == 1)
            return qtscript_svg::value(engine, self->boundsOnElement(context->argument(0).toString()));
        break;
    case 18:
        if (context->argumentCount() == 1)
            return QScriptValue(engine, self->elementExists(context->argument(0).toString()));
        break;
    case 19:
        if (context->argumentCount() == 1)
            return qtscript_svg::value(engine, self->transformForElement(context->argument(0).toString()));
        break;
    case 20:
        if (context->argumentCount() == 1) {
            if (qtscript_svg::isByteArray(context->argument(0)))
                return QScriptValue(engine, self->load(qtscript_svg::byteArray(context->argument(0))));
            if (context->argument(0).isString())
                return QScriptValue(engine, self->load(context->argument(0).toString()));
            if (QXmlStreamReader *reader = qscriptvalue_cast<QXmlStreamReader *>(context->argument(0)))
                return QScriptValue(engine, self->load(reader));
        }
        break;
    case 21: {
        QPainter *painter = nullptr;
        if (context->argumentCount() >= 1)
            painter = qscriptvalue_cast<QPainter *>(context->argument(0));
        if (!painter)
            return qtscript_svg::typeError(context, QStringLiteral("QSvgRenderer::render() needs a QPainter"));
        if (context->argumentCount() == 1) {
            self->render(painter);
            return engine->undefinedValue();
        }
        if (context->argumentCount() == 2) {
            const QVariant value = context->argument(1).toVariant();
            if (value.userType() == qMetaTypeId<QRectF>()) {
                self->render(painter, qvariant_cast<QRectF>(value));
                return engine->undefinedValue();
            }
            if (context->argument(1).isString()) {
                self->render(painter, context->argument(1).toString());
                return engine->undefinedValue();
            }
        }
        if (context->argumentCount() == 3) {
            const QVariant value = context->argument(2).toVariant();
            if (context->argument(1).isString() && value.userType() == qMetaTypeId<QRectF>()) {
                self->render(painter, context->argument(1).toString(), qvariant_cast<QRectF>(value));
                return engine->undefinedValue();
            }
        }
        break;
    }
    case 22: {
        if (context->argumentCount() == 0) {
            QString result;
            QDebug debug(&result);
            debug << self;
            return QScriptValue(engine, result);
        }
        break;
    }
    default:
        break;
    }

    return qtscript_svg::invalidArguments(context, QStringLiteral("QSvgRenderer"));
}

static QScriptValue rendererStaticSetDefaultOptions(QScriptContext *context, QScriptEngine *engine)
{
    if (context->argumentCount() != 1)
        return qtscript_svg::invalidArguments(context, QStringLiteral("QSvgRenderer::setDefaultOptions"));
    QSvgRenderer::setDefaultOptions(qtscript_svg::options(context->argument(0)));
    return engine->undefinedValue();
}

static QScriptValue rendererConstructor(QScriptContext *context, QScriptEngine *engine)
{
    if (context->thisObject().strictlyEquals(engine->globalObject()))
        return context->throwError(QStringLiteral("QSvgRenderer(): Did you forget to construct with 'new'?"));

    QSvgRenderer *result = nullptr;
    const int count = context->argumentCount();
    if (count == 0) {
        result = new QSvgRenderer();
    } else if (count == 1) {
        const QScriptValue argument = context->argument(0);
        if (qtscript_svg::isByteArray(argument))
            result = new QSvgRenderer(qtscript_svg::byteArray(argument));
        else if (argument.isString())
            result = new QSvgRenderer(argument.toString());
        else if (QXmlStreamReader *reader = qscriptvalue_cast<QXmlStreamReader *>(argument))
            result = new QSvgRenderer(reader);
        else if (QObject *parent = qtscript_svg::object(argument))
            result = new QSvgRenderer(parent);
    } else if (count == 2) {
        QObject *parent = qtscript_svg::object(context->argument(1));
        if (parent) {
            const QScriptValue argument = context->argument(0);
            if (qtscript_svg::isByteArray(argument))
                result = new QSvgRenderer(qtscript_svg::byteArray(argument), parent);
            else if (argument.isString())
                result = new QSvgRenderer(argument.toString(), parent);
            else if (QXmlStreamReader *reader = qscriptvalue_cast<QXmlStreamReader *>(argument))
                result = new QSvgRenderer(reader, parent);
        }
    }

    if (!result)
        return qtscript_svg::invalidArguments(context, QStringLiteral("QSvgRenderer"));

    QScriptValue wrapper = engine->newQObject(context->thisObject(), result,
                                               QScriptEngine::AutoOwnership);
    wrapper.setPrototype(context->callee().property(QStringLiteral("prototype")));
    return wrapper;
}

static QScriptValue rendererToScriptValue(QScriptEngine *engine, QSvgRenderer * const &value)
{
    return qtscript_svg::wrapRenderer(engine, value);
}

static void rendererFromScriptValue(const QScriptValue &value, QSvgRenderer *&out)
{
    out = qtscript_svg::renderer(value);
}

} // namespace

QScriptValue qtscript_create_QSvgRenderer_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSvgRenderer *>(), QScriptValue());
    QScriptValue prototype = engine->newVariant(QVariant::fromValue(static_cast<QSvgRenderer *>(nullptr)));
    prototype.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject *>()));
    for (int i = 0; i < static_cast<int>(sizeof(rendererMethodNames) / sizeof(rendererMethodNames[0])); ++i) {
        QScriptValue function = engine->newFunction(rendererMethod, rendererMethodLengths[i]);
        function.setData(QScriptValue(engine, kRendererTag | static_cast<uint>(i)));
        prototype.setProperty(QString::fromLatin1(rendererMethodNames[i]), function,
                              QScriptValue::SkipInEnumeration);
    }
    engine->setDefaultPrototype(qMetaTypeId<QSvgRenderer *>(), prototype);
    qScriptRegisterMetaType<QSvgRenderer *>(engine, rendererToScriptValue,
                                            rendererFromScriptValue, prototype);

    QScriptValue constructor = engine->newFunction(rendererConstructor, prototype, 2);
    constructor.setData(QScriptValue(engine, kRendererTag));
    constructor.setProperty(QStringLiteral("setDefaultOptions"),
                            engine->newFunction(rendererStaticSetDefaultOptions, 1),
                            QScriptValue::SkipInEnumeration);
    return constructor;
}
