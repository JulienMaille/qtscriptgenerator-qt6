#include "qtscript_svg_shared.h"

#include <QtCore/QDebug>
#include <QtCore/QSize>

namespace {

static constexpr uint kGraphicsItemTag = 0x53590000u;

static const char * const graphicsItemMethodNames[] = {
    "setSharedRenderer",
    "renderer",
    "setElementId",
    "elementId",
    "setCachingEnabled",
    "isCachingEnabled",
    "setMaximumCacheSize",
    "maximumCacheSize",
    "boundingRect",
    "type",
    "toString"
};

static const int graphicsItemMethodLengths[] = { 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0 };

static QGraphicsSvgItem *itemFromThis(QScriptContext *context)
{
    return qtscript_svg::graphicsSvgItem(context->thisObject());
}

static QScriptValue itemMethod(QScriptContext *context, QScriptEngine *engine)
{
    const int id = static_cast<int>(context->callee().data().toUInt32() & 0xFFFFu);
    QGraphicsSvgItem *self = itemFromThis(context);
    if (!self)
        return qtscript_svg::typeError(context,
                                       QStringLiteral("QGraphicsSvgItem method called on an invalid object"));

    switch (id) {
    case 0:
        if (context->argumentCount() == 1) {
            QSvgRenderer *renderer = qtscript_svg::rendererArgument(context->argument(0));
            if (!renderer)
                return qtscript_svg::typeError(context,
                                               QStringLiteral("QGraphicsSvgItem::setSharedRenderer() needs a QSvgRenderer"));
            self->setSharedRenderer(renderer);
            // QGraphicsSvgItem observes, but does not own, its shared
            // renderer. Retain the script wrapper so a garbage collection
            // cannot invalidate the item behind the user's back.
            context->thisObject().setProperty(QStringLiteral("__qtscript_svg_shared_renderer"),
                                              context->argument(0),
                                              QScriptValue::SkipInEnumeration);
            return engine->undefinedValue();
        }
        break;
    case 1:
        if (context->argumentCount() == 0) {
            QScriptValue result = qtscript_svg::wrapRenderer(engine, self->renderer());
            return qtscript_svg::attachPrototype(result,
                                                  engine->defaultPrototype(qMetaTypeId<QSvgRenderer *>()));
        }
        break;
    case 2:
        if (context->argumentCount() == 1) {
            self->setElementId(context->argument(0).toString());
            return engine->undefinedValue();
        }
        break;
    case 3:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->elementId());
        break;
    case 4:
        if (context->argumentCount() == 1) {
            self->setCachingEnabled(context->argument(0).toBool());
            return engine->undefinedValue();
        }
        break;
    case 5:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->isCachingEnabled());
        break;
    case 6:
        if (context->argumentCount() == 1) {
            self->setMaximumCacheSize(qscriptvalue_cast<QSize>(context->argument(0)));
            return engine->undefinedValue();
        }
        break;
    case 7:
        if (context->argumentCount() == 0)
            return qtscript_svg::value(engine, self->maximumCacheSize());
        break;
    case 8:
        if (context->argumentCount() == 0)
            return qtscript_svg::value(engine, self->boundingRect());
        break;
    case 9:
        if (context->argumentCount() == 0)
            return QScriptValue(engine, self->type());
        break;
    case 10:
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

    return qtscript_svg::invalidArguments(context, QStringLiteral("QGraphicsSvgItem"));
}

static QScriptValue itemConstructor(QScriptContext *context, QScriptEngine *engine)
{
    if (context->thisObject().strictlyEquals(engine->globalObject()))
        return context->throwError(QStringLiteral("QGraphicsSvgItem(): Did you forget to construct with 'new'?"));

    QGraphicsSvgItem *result = nullptr;
    const int count = context->argumentCount();
    if (count == 0) {
        result = new QGraphicsSvgItem();
    } else if (count == 1) {
        if (context->argument(0).isString())
            result = new QGraphicsSvgItem(context->argument(0).toString());
        else
            result = new QGraphicsSvgItem(qscriptvalue_cast<QGraphicsItem *>(context->argument(0)));
    } else if (count == 2 && context->argument(0).isString()) {
        QGraphicsItem *parent = qscriptvalue_cast<QGraphicsItem *>(context->argument(1));
        if (parent)
            result = new QGraphicsSvgItem(context->argument(0).toString(), parent);
    }
    if (!result)
        return qtscript_svg::invalidArguments(context, QStringLiteral("QGraphicsSvgItem"));

    // Store the base pointer as the actual variant so existing QGraphicsItem
    // bindings (for example QGraphicsScene::addItem) can consume it. The
    // derived pointer in data() keeps the SVG-specific dispatch type-safe.
    QScriptValue wrapper = engine->newVariant(
        context->thisObject(), QVariant::fromValue(static_cast<QGraphicsItem *>(result)));
    wrapper.setData(engine->newVariant(QVariant::fromValue(result)));
    wrapper.setPrototype(context->callee().property(QStringLiteral("prototype")));
    return wrapper;
}

} // namespace

QScriptValue qtscript_create_QGraphicsSvgItem_class(QScriptEngine *engine)
{
    QScriptValue prototype = engine->newVariant(QVariant::fromValue(static_cast<QGraphicsItem *>(nullptr)));
    prototype.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsItem *>()));
    for (int i = 0; i < static_cast<int>(sizeof(graphicsItemMethodNames)
                                           / sizeof(graphicsItemMethodNames[0])); ++i) {
        QScriptValue function = engine->newFunction(itemMethod, graphicsItemMethodLengths[i]);
        function.setData(QScriptValue(engine, kGraphicsItemTag | static_cast<uint>(i)));
        prototype.setProperty(QString::fromLatin1(graphicsItemMethodNames[i]), function,
                              QScriptValue::SkipInEnumeration);
    }
    QScriptValue constructor = engine->newFunction(itemConstructor, prototype, 2);
    constructor.setProperty(QStringLiteral("Type"), QScriptValue(engine, 13),
                            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    return constructor;
}
