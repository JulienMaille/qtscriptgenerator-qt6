#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qevent.h>
#include <qeventpoint.h>
#include <qpointingdevice.h>
#include <qvariant.h>

QScriptValue qtscript_QEventPoint_value(QScriptEngine *engine, const QEventPoint &value);

static const char * const qtscript_QPointerEvent_function_names[] = {
    "QPointerEvent"
    // static
    // prototype
    , "allPointsAccepted"
    , "allPointsGrabbed"
    , "isBeginEvent"
    , "isEndEvent"
    , "isUpdateEvent"
    , "point"
    , "pointById"
    , "pointCount"
    , "points"
    , "pointingDevice"
    , "pointerType"
    , "setAccepted"
    , "setTimestamp"
    , "timestamp"
    , "toString"
};

static const char * const qtscript_QPointerEvent_function_signatures[] = {
    "Type type, QPointingDevice device, KeyboardModifiers modifiers, List points"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , "qsizetype index"
    , "int id"
    , ""
    , ""
    , ""
    , ""
    , "bool accepted"
    , "ulong timestamp"
    , ""
    , ""
};

static const int qtscript_QPointerEvent_function_lengths[] = {
    4
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QPointerEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QPointerEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QPointerEvent *)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(QEventPoint)
Q_DECLARE_METATYPE(QEventPoint *)

static bool qtscript_QPointerEvent_points(const QScriptValue &value, QList<QEventPoint> *points)
{
    if (!value.isArray())
        return false;
    const quint32 length = value.property(QString::fromLatin1("length")).toUInt32();
    points->reserve(static_cast<int>(length));
    for (quint32 i = 0; i < length; ++i) {
        const QScriptValue item = value.property(i);
        QEventPoint *pointer = qscriptvalue_cast<QEventPoint *>(item);
        if (pointer) {
            points->append(*pointer);
            continue;
        }
        if (item.toVariant().userType() == qMetaTypeId<QEventPoint>()) {
            points->append(qscriptvalue_cast<QEventPoint>(item));
            continue;
        }
        return false;
    }
    return true;
}

static QScriptValue qtscript_QPointerEvent_point_value(QScriptEngine *engine,
    const QEventPoint &point)
{
    return qtscript_QEventPoint_value(engine, point);
}

static QScriptValue qtscript_QPointerEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QPointerEvent *_q_self = qscriptvalue_cast<QPointerEvent *>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QPointerEvent.%0(): this object is not a QPointerEvent")
            .arg(qtscript_QPointerEvent_function_names[_id + 1]));
    }

    switch (_id) {
    case 0:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), _q_self->allPointsAccepted());
        break;
    case 1:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), _q_self->allPointsGrabbed());
        break;
    case 2:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), _q_self->isBeginEvent());
        break;
    case 3:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), _q_self->isEndEvent());
        break;
    case 4:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), _q_self->isUpdateEvent());
        break;
    case 5:
        if (context->argumentCount() == 1) {
            const qsizetype index = static_cast<qsizetype>(context->argument(0).toInteger());
            if (index < 0 || index >= _q_self->pointCount())
                return context->engine()->nullValue();
            return qtscript_QPointerEvent_point_value(context->engine(), _q_self->point(index));
        }
        break;
    case 6:
        if (context->argumentCount() == 1) {
            QEventPoint *point = _q_self->pointById(context->argument(0).toInt32());
            if (!point)
                return context->engine()->nullValue();
            return qtscript_QPointerEvent_point_value(context->engine(), *point);
        }
        break;
    case 7:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->pointCount());
        break;
    case 8:
        if (context->argumentCount() == 0) {
            const QList<QEventPoint> &points = _q_self->points();
            QScriptValue array = context->engine()->newArray(static_cast<uint>(points.size()));
            for (int i = 0; i < points.size(); ++i)
                array.setProperty(static_cast<quint32>(i),
                    qtscript_QPointerEvent_point_value(context->engine(), points.at(i)));
            return array;
        }
        break;
    case 9: {
        if (context->argumentCount() == 0) {
            const QPointingDevice *device = _q_self->pointingDevice();
            if (!device)
                return context->engine()->nullValue();
            return context->engine()->newQObject(const_cast<QPointingDevice *>(device),
                QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
        }
        break;
    }
    case 10:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(_q_self->pointerType()));
        break;
    case 11:
        if (context->argumentCount() == 0 || context->argumentCount() == 1) {
            _q_self->setAccepted(context->argumentCount() == 0 || context->argument(0).toBoolean());
            return context->engine()->undefinedValue();
        }
        break;
    case 12:
        if (context->argumentCount() == 1) {
            _q_self->setTimestamp(qscriptvalue_cast<quint64>(context->argument(0)));
            return context->engine()->undefinedValue();
        }
        break;
    case 13:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->timestamp());
        break;
    case 14: {
        QString result = QString::fromLatin1("QPointerEvent");
        return QScriptValue(context->engine(), result);
    }
    default:
        Q_ASSERT(false);
    }
    return qtscript_QPointerEvent_throw_ambiguity_error_helper(context,
        qtscript_QPointerEvent_function_names[_id + 1],
        qtscript_QPointerEvent_function_signatures[_id + 1]);
}

static QScriptValue qtscript_QPointerEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    if (_id != 0)
        return context->engine()->undefinedValue();
    if (context->thisObject().strictlyEquals(context->engine()->globalObject()))
        return context->throwError(QString::fromLatin1("QPointerEvent(): Did you forget to construct with 'new'?"));

    if (context->argumentCount() < 1 || context->argumentCount() > 4)
        return qtscript_QPointerEvent_throw_ambiguity_error_helper(context,
            qtscript_QPointerEvent_function_names[0],
            qtscript_QPointerEvent_function_signatures[0]);

    const QEvent::Type type = qscriptvalue_cast<QEvent::Type>(context->argument(0));
    const QPointingDevice *device = QPointingDevice::primaryPointingDevice();
    Qt::KeyboardModifiers modifiers = Qt::NoModifier;
    QList<QEventPoint> points;
    bool valid = true;
    if (context->argumentCount() == 1) {
        // Defaults are intentional: this makes a useful synthetic event while
        // retaining Qt's primary pointing device semantics.
    } else if (context->argumentCount() == 2) {
        valid = qtscript_QPointerEvent_points(context->argument(1), &points);
    } else if (context->argumentCount() == 3) {
        modifiers = qscriptvalue_cast<Qt::KeyboardModifiers>(context->argument(1));
        valid = qtscript_QPointerEvent_points(context->argument(2), &points);
    } else {
        device = qobject_cast<QPointingDevice *>(context->argument(1).toQObject());
        modifiers = qscriptvalue_cast<Qt::KeyboardModifiers>(context->argument(2));
        valid = device && qtscript_QPointerEvent_points(context->argument(3), &points);
    }
    if (!valid)
        return qtscript_QPointerEvent_throw_ambiguity_error_helper(context,
            qtscript_QPointerEvent_function_names[0],
            qtscript_QPointerEvent_function_signatures[0]);

    QPointerEvent *result = new QPointerEvent(type, device, modifiers, points);
    return context->engine()->newVariant(context->thisObject(),
        qVariantFromValue(result));
}

QScriptValue qtscript_create_QPointerEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QPointerEvent *>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue(static_cast<QPointerEvent *>(nullptr)));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QInputEvent *>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QPointerEvent_prototype_call,
            qtscript_QPointerEvent_function_lengths[i + 1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QPointerEvent_function_names[i + 1]),
            fun, QScriptValue::SkipInEnumeration);
    }
    engine->setDefaultPrototype(qMetaTypeId<QPointerEvent *>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QPointerEvent_static_call, proto,
        qtscript_QPointerEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000)));
    return ctor;
}
