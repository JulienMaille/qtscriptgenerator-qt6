#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>

#include <QtWidgets/qrhiwidget.h>

Q_DECLARE_METATYPE(QRhiWidget*)
Q_DECLARE_METATYPE(QRhiWidget::Api)
Q_DECLARE_METATYPE(QRhiWidget::TextureFormat)

static QRhiWidget *qtscript_QRhiWidget_self(QScriptContext *context)
{
    return qobject_cast<QRhiWidget *>(context->thisObject().toQObject());
}

static QScriptValue qtscript_QRhiWidget_api(QScriptContext *context, QScriptEngine *engine)
{
    QRhiWidget *self = qtscript_QRhiWidget_self(context);
    if (!self)
        return context->throwError(QScriptContext::TypeError, QStringLiteral("QRhiWidget.api(): invalid receiver"));
    return QScriptValue(engine, static_cast<int>(self->api()));
}

static QScriptValue qtscript_QRhiWidget_setApi(QScriptContext *context, QScriptEngine *engine)
{
    QRhiWidget *self = qtscript_QRhiWidget_self(context);
    if (!self)
        return context->throwError(QScriptContext::TypeError, QStringLiteral("QRhiWidget.setApi(): invalid receiver"));
    const QVariant value = context->argument(0).toVariant();
    const QRhiWidget::Api api = value.metaType() == QMetaType::fromType<QRhiWidget::Api>()
        ? value.value<QRhiWidget::Api>()
        : static_cast<QRhiWidget::Api>(context->argument(0).toInt32());
    self->setApi(api);
    return engine->undefinedValue();
}

static QScriptValue qtscript_QRhiWidget_debugLayerEnabled(QScriptContext *context, QScriptEngine *engine)
{
    QRhiWidget *self = qtscript_QRhiWidget_self(context);
    if (!self)
        return context->throwError(QScriptContext::TypeError, QStringLiteral("QRhiWidget.isDebugLayerEnabled(): invalid receiver"));
    return QScriptValue(engine, self->isDebugLayerEnabled());
}

static QScriptValue qtscript_QRhiWidget_setDebugLayerEnabled(QScriptContext *context, QScriptEngine *engine)
{
    QRhiWidget *self = qtscript_QRhiWidget_self(context);
    if (!self)
        return context->throwError(QScriptContext::TypeError, QStringLiteral("QRhiWidget.setDebugLayerEnabled(): invalid receiver"));
    self->setDebugLayerEnabled(context->argument(0).toBoolean());
    return engine->undefinedValue();
}

static QScriptValue qtscript_QRhiWidget_grabFramebuffer(QScriptContext *context, QScriptEngine *engine)
{
    QRhiWidget *self = qtscript_QRhiWidget_self(context);
    if (!self)
        return context->throwError(QScriptContext::TypeError, QStringLiteral("QRhiWidget.grabFramebuffer(): invalid receiver"));
    return engine->newVariant(QVariant::fromValue(self->grabFramebuffer()));
}

static QScriptValue qtscript_QRhiWidget_construct(QScriptContext *context, QScriptEngine *engine)
{
    if (!context->isCalledAsConstructor())
        return context->throwError(QStringLiteral("QRhiWidget(): Did you forget to construct with 'new'?"));

    QWidget *parent = nullptr;
    Qt::WindowFlags flags;
    if (context->argumentCount() >= 1)
        parent = qobject_cast<QWidget *>(context->argument(0).toQObject());
    if (context->argumentCount() >= 2)
        flags = Qt::WindowFlags::fromInt(context->argument(1).toInt32());

    QRhiWidget *widget = new QRhiWidget(parent, flags);
    return engine->newQObject(context->thisObject(), widget, QScriptEngine::AutoOwnership);
}

static QScriptValue qtscript_QRhiWidget_toScriptValue(QScriptEngine *engine, QRhiWidget *const &widget)
{
    return engine->newQObject(widget, QScriptEngine::QtOwnership,
                              QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QRhiWidget_fromScriptValue(const QScriptValue &value, QRhiWidget *&widget)
{
    widget = qobject_cast<QRhiWidget *>(value.toQObject());
}

QScriptValue qtscript_create_QRhiWidget_class(QScriptEngine *engine)
{
    QScriptValue proto = engine->newVariant(QVariant::fromValue(static_cast<QRhiWidget *>(nullptr)));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget *>()));
    proto.setProperty(QStringLiteral("api"), engine->newFunction(qtscript_QRhiWidget_api, 0),
                      QScriptValue::SkipInEnumeration);
    proto.setProperty(QStringLiteral("setApi"), engine->newFunction(qtscript_QRhiWidget_setApi, 1),
                      QScriptValue::SkipInEnumeration);
    proto.setProperty(QStringLiteral("isDebugLayerEnabled"), engine->newFunction(qtscript_QRhiWidget_debugLayerEnabled, 0),
                      QScriptValue::SkipInEnumeration);
    proto.setProperty(QStringLiteral("setDebugLayerEnabled"), engine->newFunction(qtscript_QRhiWidget_setDebugLayerEnabled, 1),
                      QScriptValue::SkipInEnumeration);
    proto.setProperty(QStringLiteral("grabFramebuffer"), engine->newFunction(qtscript_QRhiWidget_grabFramebuffer, 0),
                      QScriptValue::SkipInEnumeration);

    qScriptRegisterMetaType<QRhiWidget *>(engine, qtscript_QRhiWidget_toScriptValue,
                                         qtscript_QRhiWidget_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QRhiWidget_construct, proto, 2);
    const struct { const char *name; QRhiWidget::Api value; } apis[] = {
        { "Null", QRhiWidget::Api::Null },
        { "OpenGL", QRhiWidget::Api::OpenGL },
        { "Metal", QRhiWidget::Api::Metal },
        { "Vulkan", QRhiWidget::Api::Vulkan },
        { "Direct3D11", QRhiWidget::Api::Direct3D11 },
        { "Direct3D12", QRhiWidget::Api::Direct3D12 }
    };
    for (const auto &entry : apis)
        ctor.setProperty(QString::fromLatin1(entry.name), QScriptValue(engine, static_cast<int>(entry.value)),
                         QScriptValue::ReadOnly | QScriptValue::Undeletable);

    const struct { const char *name; QRhiWidget::TextureFormat value; } formats[] = {
        { "RGBA8", QRhiWidget::TextureFormat::RGBA8 },
        { "RGBA16F", QRhiWidget::TextureFormat::RGBA16F },
        { "RGBA32F", QRhiWidget::TextureFormat::RGBA32F },
        { "RGB10A2", QRhiWidget::TextureFormat::RGB10A2 }
    };
    for (const auto &entry : formats)
        ctor.setProperty(QString::fromLatin1(entry.name), QScriptValue(engine, static_cast<int>(entry.value)),
                         QScriptValue::ReadOnly | QScriptValue::Undeletable);
    return ctor;
}
