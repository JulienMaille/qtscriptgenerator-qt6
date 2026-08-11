#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <qevent.h>
#include <qinputdevice.h>
#include <qpoint.h>
#include <qpointingdevice.h>

#include <__package_shared.h>

// Qt 6 replaced QTabletEvent's Qt 5 device/pointer enums and constructor
// with a QPointingDevice.  Keep the historical coordinate spellings where
// they are still meaningful, and expose the modern pointer-event metadata.

static const char * const qtscript_QTabletEvent_function_names[] = {
    "QTabletEvent"
    , "button"
    , "buttons"
    , "device"
    , "deviceType"
    , "globalPos"
    , "globalPosF"
    , "globalPosition"
    , "globalX"
    , "globalY"
    , "hiResGlobalX"
    , "hiResGlobalY"
    , "isBeginEvent"
    , "isEndEvent"
    , "isUpdateEvent"
    , "pointCount"
    , "pointingDevice"
    , "pointerType"
    , "pos"
    , "posF"
    , "position"
    , "pressure"
    , "rotation"
    , "scenePosition"
    , "tangentialPressure"
    , "uniqueId"
    , "x"
    , "xTilt"
    , "y"
    , "yTilt"
    , "z"
    , "toString"
};

static const char * const qtscript_QTabletEvent_function_signatures[] = {
    "Type type, QPointF pos, QPointF globalPos, qreal pressure, float xTilt, float yTilt, float tangentialPressure, qreal rotation, float z, KeyboardModifiers modifiers, MouseButton button, MouseButtons buttons\nType type, QPointingDevice device, QPointF pos, QPointF globalPos, qreal pressure, float xTilt, float yTilt, float tangentialPressure, qreal rotation, float z, KeyboardModifiers modifiers, MouseButton button, MouseButtons buttons"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
""
};

static const int qtscript_QTabletEvent_function_lengths[] = {
    13
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QTabletEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTabletEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTabletEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QEvent::Type)

static QScriptValue qtscript_wrap_tablet_device(QScriptContext *context,
                                                 const QInputDevice *device)
{
    if (!device)
        return context->engine()->nullValue();
    return context->engine()->newQObject(
        const_cast<QInputDevice *>(device),
        QScriptEngine::QtOwnership,
        QScriptEngine::PreferExistingWrapperObject);
}

static QScriptValue qtscript_QTabletEvent_prototype_call(QScriptContext *context,
                                                          QScriptEngine *)
{
    Q_ASSERT(context->callee().isFunction());
    uint id = context->callee().data().toUInt32() & 0x0000FFFF;
    QTabletEvent *self = qscriptvalue_cast<QTabletEvent *>(context->thisObject());
    if (!self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QTabletEvent.%0(): this object is not a QTabletEvent")
            .arg(qtscript_QTabletEvent_function_names[id + 1]));
    }

    switch (id) {
    case 0:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->button());
        break;
    case 1:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->buttons());
        break;
    case 2:
        if (context->argumentCount() == 0)
            return qtscript_wrap_tablet_device(context, self->device());
        break;
    case 3:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(self->deviceType()));
        break;
    case 4:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->globalPosition().toPoint());
        break;
    case 5:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->globalPosition());
        break;
    case 6:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->globalPosition());
        break;
    case 7:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->globalPosition().x());
        break;
    case 8:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->globalPosition().y());
        break;
    case 9:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->globalPosition().x());
        break;
    case 10:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->globalPosition().y());
        break;
    case 11:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->isBeginEvent());
        break;
    case 12:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->isEndEvent());
        break;
    case 13:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->isUpdateEvent());
        break;
    case 14:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(self->pointCount()));
        break;
    case 15:
        if (context->argumentCount() == 0)
            return qtscript_wrap_tablet_device(context, self->pointingDevice());
        break;
    case 16:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(self->pointerType()));
        break;
    case 17:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->position().toPoint());
        break;
    case 18:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->position());
        break;
    case 19:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->position());
        break;
    case 20:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->pressure());
        break;
    case 21:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->rotation());
        break;
    case 22:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->scenePosition());
        break;
    case 23:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->tangentialPressure());
        break;
    case 24:
        if (context->argumentCount() == 0) {
            const QPointingDevice *device = self->pointingDevice();
            return qScriptValueFromValue(context->engine(),
                device ? device->uniqueId().numericId() : qint64(-1));
        }
        break;
    case 25:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), qRound(self->position().x()));
        break;
    case 26:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->xTilt());
        break;
    case 27:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), qRound(self->position().y()));
        break;
    case 28:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->yTilt());
        break;
    case 29:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->z());
        break;
    case 30:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QString::fromLatin1("QTabletEvent"));
        break;
    default:
        Q_ASSERT(false);
    }

    return qtscript_QTabletEvent_throw_ambiguity_error_helper(context,
        qtscript_QTabletEvent_function_names[id + 1],
        qtscript_QTabletEvent_function_signatures[id + 1]);
}

static QTabletEvent *qtscript_new_QTabletEvent(QEvent::Type type,
                                                const QPointingDevice *device,
                                                const QPointF &pos,
                                                const QPointF &globalPos,
                                                qreal pressure,
                                                float xTilt,
                                                float yTilt,
                                                float tangentialPressure,
                                                qreal rotation,
                                                float z,
                                                Qt::KeyboardModifiers modifiers,
                                                Qt::MouseButton button,
                                                Qt::MouseButtons buttons)
{
    return new QTabletEvent(type, device, pos, globalPos, pressure, xTilt, yTilt,
                            tangentialPressure, rotation, z, modifiers, button, buttons);
}

static QScriptValue qtscript_QTabletEvent_static_call(QScriptContext *context,
                                                       QScriptEngine *)
{
    if (context->thisObject().strictlyEquals(context->engine()->globalObject()))
        return context->throwError(QString::fromLatin1("QTabletEvent(): Did you forget to construct with 'new'?"));

    const int argc = context->argumentCount();
    if (argc != 12 && argc != 13)
        return qtscript_QTabletEvent_throw_ambiguity_error_helper(context,
            qtscript_QTabletEvent_function_names[0],
            qtscript_QTabletEvent_function_signatures[0]);

    int offset = 0;
    const QPointingDevice *device = QPointingDevice::primaryPointingDevice();
    if (argc == 13) {
        QObject *object = context->argument(1).toQObject();
        device = qobject_cast<QPointingDevice *>(object);
        if (!device)
            return context->throwError(QScriptContext::TypeError,
                QString::fromLatin1("QTabletEvent(): argument 1 is not a QPointingDevice"));
        offset = 1;
    }

    QEvent::Type type = qscriptvalue_cast<QEvent::Type>(context->argument(0));
    QPointF pos = qscriptvalue_cast<QPointF>(context->argument(1 + offset));
    QPointF globalPos = qscriptvalue_cast<QPointF>(context->argument(2 + offset));
    qreal pressure = context->argument(3 + offset).toNumber();
    float xTilt = static_cast<float>(context->argument(4 + offset).toNumber());
    float yTilt = static_cast<float>(context->argument(5 + offset).toNumber());
    float tangential = static_cast<float>(context->argument(6 + offset).toNumber());
    qreal rotation = context->argument(7 + offset).toNumber();
    float z = static_cast<float>(context->argument(8 + offset).toNumber());
    Qt::KeyboardModifiers modifiers = qscriptvalue_cast<Qt::KeyboardModifiers>(context->argument(9 + offset));
    Qt::MouseButton button = qscriptvalue_cast<Qt::MouseButton>(context->argument(10 + offset));
    Qt::MouseButtons buttons = qscriptvalue_cast<Qt::MouseButtons>(context->argument(11 + offset));

    QTabletEvent *result = qtscript_new_QTabletEvent(type, device, pos, globalPos,
                                                      pressure, xTilt, yTilt,
                                                      tangential, rotation, z,
                                                      modifiers, button, buttons);
    return context->engine()->newVariant(context->thisObject(), qVariantFromValue(result));
}

QScriptValue qtscript_create_QTabletEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTabletEvent *>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue(static_cast<QTabletEvent *>(nullptr)));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QInputEvent *>()));
    for (int i = 0; i < 31; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTabletEvent_prototype_call,
                                                qtscript_QTabletEvent_function_lengths[i + 1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTabletEvent_function_names[i + 1]),
                          fun, QScriptValue::SkipInEnumeration);
    }
    engine->setDefaultPrototype(qMetaTypeId<QTabletEvent *>(), proto);
    QScriptValue ctor = engine->newFunction(qtscript_QTabletEvent_static_call,
                                             proto, qtscript_QTabletEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000)));
    return ctor;
}
