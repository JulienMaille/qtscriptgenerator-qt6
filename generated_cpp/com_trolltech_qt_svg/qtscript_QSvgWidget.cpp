#include "qtscript_svg_shared.h"

#include <QtCore/QDebug>
#include <QtCore/QSize>

namespace {

static constexpr uint kWidgetTag = 0x53580000u;

static const char * const widgetMethodNames[] = {
    "renderer",
    "sizeHint",
    "options",
    "setOptions",
    "load",
    "toString"
};

static const int widgetMethodLengths[] = { 0, 0, 0, 1, 1, 0 };

static QSvgWidget *widgetFromThis(QScriptContext *context)
{
    return qtscript_svg::widget(context->thisObject());
}

static QScriptValue widgetMethod(QScriptContext *context, QScriptEngine *engine)
{
    const int id = static_cast<int>(context->callee().data().toUInt32() & 0xFFFFu);
    QSvgWidget *self = widgetFromThis(context);
    if (!self)
        return qtscript_svg::typeError(context, QStringLiteral("QSvgWidget method called on an invalid object"));

    switch (id) {
    case 0:
        if (context->argumentCount() == 0) {
            QScriptValue result = qtscript_svg::wrapRenderer(engine, self->renderer());
            return qtscript_svg::attachPrototype(result,
                                                  engine->defaultPrototype(qMetaTypeId<QSvgRenderer *>()));
        }
        break;
    case 1:
        if (context->argumentCount() == 0)
            return qtscript_svg::value(engine, self->sizeHint());
        break;
    case 2:
        if (context->argumentCount() == 0)
            return qtscript_svg::optionsValue(engine, self->options());
        break;
    case 3:
        if (context->argumentCount() == 1) {
            self->setOptions(qtscript_svg::options(context->argument(0)));
            return engine->undefinedValue();
        }
        break;
    case 4:
        if (context->argumentCount() == 1) {
            if (qtscript_svg::isByteArray(context->argument(0))) {
                self->load(qtscript_svg::byteArray(context->argument(0)));
                return engine->undefinedValue();
            }
            if (context->argument(0).isString()) {
                self->load(context->argument(0).toString());
                return engine->undefinedValue();
            }
        }
        break;
    case 5:
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

    return qtscript_svg::invalidArguments(context, QStringLiteral("QSvgWidget"));
}

static QScriptValue widgetConstructor(QScriptContext *context, QScriptEngine *engine)
{
    if (context->thisObject().strictlyEquals(engine->globalObject()))
        return context->throwError(QStringLiteral("QSvgWidget(): Did you forget to construct with 'new'?"));

    QSvgWidget *result = nullptr;
    const int count = context->argumentCount();
    if (count == 0) {
        result = new QSvgWidget();
    } else if (count == 1) {
        if (context->argument(0).isString())
            result = new QSvgWidget(context->argument(0).toString());
        else if (QWidget *parent = qscriptvalue_cast<QWidget *>(context->argument(0)))
            result = new QSvgWidget(parent);
    } else if (count == 2 && context->argument(0).isString()) {
        QWidget *parent = qscriptvalue_cast<QWidget *>(context->argument(1));
        if (parent)
            result = new QSvgWidget(context->argument(0).toString(), parent);
    }
    if (!result)
        return qtscript_svg::invalidArguments(context, QStringLiteral("QSvgWidget"));

    QScriptValue wrapper = engine->newQObject(context->thisObject(), result,
                                               QScriptEngine::AutoOwnership);
    wrapper.setPrototype(context->callee().property(QStringLiteral("prototype")));
    return wrapper;
}

static QScriptValue widgetToScriptValue(QScriptEngine *engine, QSvgWidget * const &value)
{
    if (!value)
        return engine->nullValue();
    return engine->newQObject(value, QScriptEngine::QtOwnership,
                               QScriptEngine::PreferExistingWrapperObject);
}

static void widgetFromScriptValue(const QScriptValue &value, QSvgWidget *&out)
{
    out = qtscript_svg::widget(value);
}

} // namespace

QScriptValue qtscript_create_QSvgWidget_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSvgWidget *>(), QScriptValue());
    QScriptValue prototype = engine->newVariant(QVariant::fromValue(static_cast<QSvgWidget *>(nullptr)));
    prototype.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget *>()));
    for (int i = 0; i < static_cast<int>(sizeof(widgetMethodNames) / sizeof(widgetMethodNames[0])); ++i) {
        QScriptValue function = engine->newFunction(widgetMethod, widgetMethodLengths[i]);
        function.setData(QScriptValue(engine, kWidgetTag | static_cast<uint>(i)));
        prototype.setProperty(QString::fromLatin1(widgetMethodNames[i]), function,
                              QScriptValue::SkipInEnumeration);
    }
    engine->setDefaultPrototype(qMetaTypeId<QSvgWidget *>(), prototype);
    qScriptRegisterMetaType<QSvgWidget *>(engine, widgetToScriptValue,
                                          widgetFromScriptValue, prototype);
    return engine->newFunction(widgetConstructor, prototype, 2);
}
