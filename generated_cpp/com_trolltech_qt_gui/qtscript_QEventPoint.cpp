#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qeventpoint.h>
#include <qpointingdevice.h>
#include <qsize.h>
#include <qvariant.h>

static const char * const qtscript_QEventPoint_function_names[] = {
    "QEventPoint"
    // static
    // prototype
    , "device"
    , "ellipseDiameters"
    , "globalGrabPosition"
    , "globalLastPosition"
    , "globalPosition"
    , "globalPressPosition"
    , "grabPosition"
    , "id"
    , "isAccepted"
    , "lastPosition"
    , "normalizedPosition"
    , "position"
    , "pressPosition"
    , "pressure"
    , "rotation"
    , "sceneGrabPosition"
    , "sceneLastPosition"
    , "scenePosition"
    , "scenePressPosition"
    , "setAccepted"
    , "state"
    , "timestamp"
    , "lastTimestamp"
    , "pressTimestamp"
    , "timeHeld"
    , "uniqueId"
    , "velocity"
    // Qt 5 TouchPoint spellings retained as Qt 6 aliases.
    , "pos"
    , "startPos"
    , "scenePos"
    , "startScenePos"
    , "screenPos"
    , "startScreenPos"
    , "startNormalizedPos"
    , "normalizedPos"
    , "lastPos"
    , "lastScenePos"
    , "lastScreenPos"
    , "toString"
};

static const char * const qtscript_QEventPoint_function_signatures[] = {
    "int id\nint pointId, State state, QPointF scenePosition, QPointF globalPosition\nint id, QPointingDevice device"
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
    , "bool accepted"
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
};

static const int qtscript_QEventPoint_function_lengths[] = {
    4
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
    , 1
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

static QScriptValue qtscript_QEventPoint_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QEventPoint::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QEventPoint)
Q_DECLARE_METATYPE(QEventPoint *)

QScriptValue qtscript_QEventPoint_value(QScriptEngine *engine, const QEventPoint &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static QScriptValue qtscript_QEventPoint_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id = 0xBABE0000 + 38;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QEventPoint *_q_self = qscriptvalue_cast<QEventPoint *>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QEventPoint.%0(): this object is not a QEventPoint")
            .arg(qtscript_QEventPoint_function_names[_id + 1]));
    }

    switch (_id) {
    case 0:
        if (context->argumentCount() == 0) {
            const QPointingDevice *result = _q_self->device();
            if (!result)
                return context->engine()->nullValue();
            return context->engine()->newQObject(const_cast<QPointingDevice *>(result),
                QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
        }
        break;
    case 1:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->ellipseDiameters());
        break;
    case 2:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->globalGrabPosition());
        break;
    case 3:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->globalLastPosition());
        break;
    case 4:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->globalPosition());
        break;
    case 5:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->globalPressPosition());
        break;
    case 6:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->grabPosition());
        break;
    case 7:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), _q_self->id());
        break;
    case 8:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), _q_self->isAccepted());
        break;
    case 9:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->lastPosition());
        break;
    case 10:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->normalizedPosition());
        break;
    case 11:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->position());
        break;
    case 12:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->pressPosition());
        break;
    case 13:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->pressure());
        break;
    case 14:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->rotation());
        break;
    case 15:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->sceneGrabPosition());
        break;
    case 16:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->sceneLastPosition());
        break;
    case 17:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->scenePosition());
        break;
    case 18:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->scenePressPosition());
        break;
    case 19:
        if (context->argumentCount() == 0 || context->argumentCount() == 1) {
            _q_self->setAccepted(context->argumentCount() == 0 || context->argument(0).toBoolean());
            return context->engine()->undefinedValue();
        }
        break;
    case 20:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(_q_self->state()));
        break;
    case 21:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->timestamp());
        break;
    case 22:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->lastTimestamp());
        break;
    case 23:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->pressTimestamp());
        break;
    case 24:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->timeHeld());
        break;
    case 25:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), qreal(_q_self->uniqueId().numericId()));
        break;
    case 26:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->velocity());
        break;
    case 27:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->position());
        break;
    case 28:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->pressPosition());
        break;
    case 29:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->scenePosition());
        break;
    case 30:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->scenePressPosition());
        break;
    case 31:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->globalPosition());
        break;
    case 32:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->globalPressPosition());
        break;
    case 33:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->globalPressPosition());
        break;
    case 34:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->normalizedPosition());
        break;
    case 35:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->lastPosition());
        break;
    case 36:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->sceneLastPosition());
        break;
    case 37:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->globalLastPosition());
        break;
    case 38: {
        QString result = QString::fromLatin1("QEventPoint");
        return QScriptValue(context->engine(), result);
    }
    default:
        Q_ASSERT(false);
    }
    return qtscript_QEventPoint_throw_ambiguity_error_helper(context,
        qtscript_QEventPoint_function_names[_id + 1],
        qtscript_QEventPoint_function_signatures[_id + 1]);
}

static QScriptValue qtscript_QEventPoint_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    if (_id != 0)
        return context->engine()->undefinedValue();
    if (context->thisObject().strictlyEquals(context->engine()->globalObject()))
        return context->throwError(QString::fromLatin1("QEventPoint(): Did you forget to construct with 'new'?"));

    QEventPoint *result = nullptr;
    if (context->argumentCount() == 0) {
        result = new QEventPoint;
    } else if (context->argumentCount() == 1) {
        QEventPoint *other = qscriptvalue_cast<QEventPoint *>(context->argument(0));
        if (other)
            result = new QEventPoint(*other);
        else if (context->argument(0).isNumber())
            result = new QEventPoint(context->argument(0).toInt32());
    } else if (context->argumentCount() == 2 && context->argument(0).isNumber()) {
        const QPointingDevice *device = qobject_cast<QPointingDevice *>(context->argument(1).toQObject());
        result = new QEventPoint(context->argument(0).toInt32(), device);
    } else if (context->argumentCount() == 4) {
        const int pointId = context->argument(0).toInt32();
        const QEventPoint::State state = static_cast<QEventPoint::State>(context->argument(1).toInt32());
        const QPointF scenePosition = qscriptvalue_cast<QPointF>(context->argument(2));
        const QPointF globalPosition = qscriptvalue_cast<QPointF>(context->argument(3));
        result = new QEventPoint(pointId, state, scenePosition, globalPosition);
    }
    if (!result)
        return qtscript_QEventPoint_throw_ambiguity_error_helper(context,
            qtscript_QEventPoint_function_names[0],
            qtscript_QEventPoint_function_signatures[0]);

    QScriptValue wrapped = context->engine()->newVariant(context->thisObject(),
        qVariantFromValue(result));
    return wrapped;
}

QScriptValue qtscript_create_QEventPoint_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QEventPoint *>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue(static_cast<QEventPoint *>(nullptr)));
    for (int i = 0; i < 39; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QEventPoint_prototype_call,
            qtscript_QEventPoint_function_lengths[i + 1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QEventPoint_function_names[i + 1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QEventPoint>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QEventPoint *>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QEventPoint_static_call, proto,
        qtscript_QEventPoint_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000)));
    ctor.setProperty(QString::fromLatin1("Unknown"),
        QScriptValue(engine, static_cast<int>(QEventPoint::Unknown)));
    ctor.setProperty(QString::fromLatin1("Stationary"),
        QScriptValue(engine, static_cast<int>(QEventPoint::Stationary)));
    ctor.setProperty(QString::fromLatin1("Pressed"),
        QScriptValue(engine, static_cast<int>(QEventPoint::Pressed)));
    ctor.setProperty(QString::fromLatin1("Updated"),
        QScriptValue(engine, static_cast<int>(QEventPoint::Updated)));
    ctor.setProperty(QString::fromLatin1("Released"),
        QScriptValue(engine, static_cast<int>(QEventPoint::Released)));
    return ctor;
}
