#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <qevent.h>
#include <qinputdevice.h>
#include <qpointingdevice.h>
#include <qpoint.h>

#include <__package_shared.h>

// QWheelEvent changed substantially in Qt 6.  The old generated wrapper
// called the removed Qt 5 delta/orientation constructors.  Keep the useful
// legacy accessors as computed compatibility shims, but construct the event
// through the Qt 6 pixel/angle/phase API.

static const char * const qtscript_QWheelEvent_function_names[] = {
    "QWheelEvent"
    , "angleDelta"
    , "button"
    , "buttons"
    , "delta"
    , "device"
    , "deviceType"
    , "globalPos"
    , "globalPosF"
    , "globalPosition"
    , "globalX"
    , "globalY"
    , "hasPixelDelta"
    , "inverted"
    , "isBeginEvent"
    , "isEndEvent"
    , "isInverted"
    , "isUpdateEvent"
    , "orientation"
    , "phase"
    , "pixelDelta"
    , "pointCount"
    , "pointingDevice"
    , "pos"
    , "posF"
    , "position"
    , "scenePosition"
    , "source"
    , "x"
    , "y"
    , "toString"
};

static const char * const qtscript_QWheelEvent_function_signatures[] = {
    "QPointF pos, QPointF globalPos, QPoint pixelDelta, QPoint angleDelta, MouseButtons buttons, KeyboardModifiers modifiers, ScrollPhase phase, bool inverted\nQPointF pos, QPointF globalPos, QPoint pixelDelta, QPoint angleDelta, MouseButtons buttons, KeyboardModifiers modifiers, ScrollPhase phase, bool inverted, MouseEventSource source\nQPointF pos, QPointF globalPos, QPoint pixelDelta, QPoint angleDelta, MouseButtons buttons, KeyboardModifiers modifiers, ScrollPhase phase, bool inverted, MouseEventSource source, QPointingDevice device\nQPointF pos, QPointF globalPos, int delta, MouseButtons buttons, KeyboardModifiers modifiers\nQPointF pos, int delta, MouseButtons buttons, KeyboardModifiers modifiers"
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
""
};

static const int qtscript_QWheelEvent_function_lengths[] = {
    8
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
};

static QScriptValue qtscript_QWheelEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QWheelEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWheelEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(Qt::ScrollPhase)
Q_DECLARE_METATYPE(Qt::MouseEventSource)
Q_DECLARE_METATYPE(QEvent::Type)

static QScriptValue qtscript_wrap_input_device(QScriptContext *context,
                                                const QInputDevice *device)
{
    if (!device)
        return context->engine()->nullValue();
    return context->engine()->newQObject(
        const_cast<QInputDevice *>(device),
        QScriptEngine::QtOwnership,
        QScriptEngine::PreferExistingWrapperObject);
}

static QScriptValue qtscript_QWheelEvent_prototype_call(QScriptContext *context,
                                                         QScriptEngine *)
{
    Q_ASSERT(context->callee().isFunction());
    uint id = context->callee().data().toUInt32() & 0x0000FFFF;
    QWheelEvent *self = qscriptvalue_cast<QWheelEvent *>(context->thisObject());
    if (!self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QWheelEvent.%0(): this object is not a QWheelEvent")
            .arg(qtscript_QWheelEvent_function_names[id + 1]));
    }

    switch (id) {
    case 0:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->angleDelta());
        break;
    case 1:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->button());
        break;
    case 2:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->buttons());
        break;
    case 3: {
        if (context->argumentCount() == 0) {
            const QPoint angle = self->angleDelta();
            return QScriptValue(context->engine(), angle.y() != 0 ? angle.y() : angle.x());
        }
        break;
    }
    case 4:
        if (context->argumentCount() == 0)
            return qtscript_wrap_input_device(context, self->device());
        break;
    case 5:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(self->deviceType()));
        break;
    case 6:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->globalPosition().toPoint());
        break;
    case 7:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->globalPosition());
        break;
    case 8:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->globalPosition());
        break;
    case 9:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->globalPosition().x());
        break;
    case 10:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->globalPosition().y());
        break;
    case 11:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->hasPixelDelta());
        break;
    case 12:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->inverted());
        break;
    case 13:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->isBeginEvent());
        break;
    case 14:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->isEndEvent());
        break;
    case 15:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->isInverted());
        break;
    case 16:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self->isUpdateEvent());
        break;
    case 17:
        if (context->argumentCount() == 0) {
            const QPoint angle = self->angleDelta();
            return qScriptValueFromValue(context->engine(),
                angle.y() != 0 ? Qt::Vertical : Qt::Horizontal);
        }
        break;
    case 18:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->phase());
        break;
    case 19:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->pixelDelta());
        break;
    case 20:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(self->pointCount()));
        break;
    case 21:
        if (context->argumentCount() == 0)
            return qtscript_wrap_input_device(context, self->pointingDevice());
        break;
    case 22:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->position().toPoint());
        break;
    case 23:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->position());
        break;
    case 24:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->position());
        break;
    case 25:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->scenePosition());
        break;
    case 26:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self->source());
        break;
    case 27:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), qRound(self->position().x()));
        break;
    case 28:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), qRound(self->position().y()));
        break;
    case 29:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QString::fromLatin1("QWheelEvent"));
        break;
    default:
        Q_ASSERT(false);
    }

    return qtscript_QWheelEvent_throw_ambiguity_error_helper(context,
        qtscript_QWheelEvent_function_names[id + 1],
        qtscript_QWheelEvent_function_signatures[id + 1]);
}

static QWheelEvent *qtscript_new_QWheelEvent(const QPointF &pos,
                                              const QPointF &globalPos,
                                              const QPoint &pixelDelta,
                                              const QPoint &angleDelta,
                                              Qt::MouseButtons buttons,
                                              Qt::KeyboardModifiers modifiers,
                                              Qt::ScrollPhase phase,
                                              bool inverted,
                                              Qt::MouseEventSource source,
                                              const QPointingDevice *device)
{
    return new QWheelEvent(pos, globalPos, pixelDelta, angleDelta, buttons,
                           modifiers, phase, inverted, source, device);
}

static QScriptValue qtscript_QWheelEvent_static_call(QScriptContext *context,
                                                      QScriptEngine *)
{
    if (context->thisObject().strictlyEquals(context->engine()->globalObject()))
        return context->throwError(QString::fromLatin1("QWheelEvent(): Did you forget to construct with 'new'?"));

    QWheelEvent *result = nullptr;
    const int argc = context->argumentCount();
    if (argc == 8 || argc == 9 || argc == 10) {
        QPointF pos = qscriptvalue_cast<QPointF>(context->argument(0));
        QPointF globalPos = qscriptvalue_cast<QPointF>(context->argument(1));
        QPoint pixelDelta = qscriptvalue_cast<QPoint>(context->argument(2));
        QPoint angleDelta = qscriptvalue_cast<QPoint>(context->argument(3));
        Qt::MouseButtons buttons = qscriptvalue_cast<Qt::MouseButtons>(context->argument(4));
        Qt::KeyboardModifiers modifiers = qscriptvalue_cast<Qt::KeyboardModifiers>(context->argument(5));
        Qt::ScrollPhase phase = qscriptvalue_cast<Qt::ScrollPhase>(context->argument(6));
        const bool inverted = context->argument(7).toBoolean();
        Qt::MouseEventSource source = Qt::MouseEventNotSynthesized;
        if (argc >= 9)
            source = qscriptvalue_cast<Qt::MouseEventSource>(context->argument(8));
        const QPointingDevice *device = QPointingDevice::primaryPointingDevice();
        if (argc == 10) {
            QObject *object = context->argument(9).toQObject();
            device = qobject_cast<QPointingDevice *>(object);
            if (!device)
                return context->throwError(QScriptContext::TypeError,
                    QString::fromLatin1("QWheelEvent(): argument 9 is not a QPointingDevice"));
        }
        result = qtscript_new_QWheelEvent(pos, globalPos, pixelDelta, angleDelta,
                                          buttons, modifiers, phase, inverted,
                                          source, device);
    } else if (argc == 5 || argc == 4) {
        QPointF pos = qscriptvalue_cast<QPointF>(context->argument(0));
        QPointF globalPos = pos;
        int delta = 0;
        Qt::MouseButtons buttons;
        Qt::KeyboardModifiers modifiers;
        if (argc == 5) {
            globalPos = qscriptvalue_cast<QPointF>(context->argument(1));
            delta = context->argument(2).toInt32();
            buttons = qscriptvalue_cast<Qt::MouseButtons>(context->argument(3));
            modifiers = qscriptvalue_cast<Qt::KeyboardModifiers>(context->argument(4));
        } else {
            delta = context->argument(1).toInt32();
            buttons = qscriptvalue_cast<Qt::MouseButtons>(context->argument(2));
            modifiers = qscriptvalue_cast<Qt::KeyboardModifiers>(context->argument(3));
        }
        result = qtscript_new_QWheelEvent(pos, globalPos, QPoint(), QPoint(0, delta),
                                          buttons, modifiers, Qt::NoScrollPhase, false,
                                          Qt::MouseEventNotSynthesized,
                                          QPointingDevice::primaryPointingDevice());
    }

    if (result)
        return context->engine()->newVariant(context->thisObject(), qVariantFromValue(result));
    return qtscript_QWheelEvent_throw_ambiguity_error_helper(context,
        qtscript_QWheelEvent_function_names[0],
        qtscript_QWheelEvent_function_signatures[0]);
}

QScriptValue qtscript_create_QWheelEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QWheelEvent *>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue(static_cast<QWheelEvent *>(nullptr)));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QInputEvent *>()));
    for (int i = 0; i < 30; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QWheelEvent_prototype_call,
                                                qtscript_QWheelEvent_function_lengths[i + 1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QWheelEvent_function_names[i + 1]),
                          fun, QScriptValue::SkipInEnumeration);
    }
    engine->setDefaultPrototype(qMetaTypeId<QWheelEvent *>(), proto);
    QScriptValue ctor = engine->newFunction(qtscript_QWheelEvent_static_call,
                                             proto, qtscript_QWheelEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000)));
    return ctor;
}
