#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgraphicssceneevent.h>
#include <QVariant>
#include <qgraphicssceneevent.h>
#include <qpoint.h>
#include <qwidget.h>

static const char * const qtscript_QGraphicsSceneWheelEvent_function_names[] = {
    "QGraphicsSceneWheelEvent"
    // static
    // prototype
    , "buttons"
    , "delta"
    , "modifiers"
    , "orientation"
    , "pos"
    , "scenePos"
    , "screenPos"
    , "setButtons"
    , "setDelta"
    , "setModifiers"
    , "setOrientation"
    , "setPos"
    , "setScenePos"
    , "setScreenPos"
    , "phase"
    , "pixelDelta"
    , "isInverted"
    , "setPhase"
    , "setPixelDelta"
    , "setInverted"
    , "toString"
};

static const char * const qtscript_QGraphicsSceneWheelEvent_function_signatures[] = {
    "Type type"
    // static
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "MouseButtons buttons"
    , "int delta"
    , "KeyboardModifiers modifiers"
    , "Orientation orientation"
    , "QPointF pos"
    , "QPointF pos"
    , "QPoint pos"
    , ""
    , ""
    , ""
    , "ScrollPhase phase"
    , "QPoint delta"
    , "bool inverted"
""
};

static const int qtscript_QGraphicsSceneWheelEvent_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QGraphicsSceneWheelEvent_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsSceneWheelEvent::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsSceneWheelEvent*)
Q_DECLARE_METATYPE(QFlags<Qt::MouseButton>)
Q_DECLARE_METATYPE(QFlags<Qt::KeyboardModifier>)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(Qt::ScrollPhase)
Q_DECLARE_METATYPE(QEvent::Type)
Q_DECLARE_METATYPE(QGraphicsSceneEvent*)

//
// QGraphicsSceneWheelEvent
//

static QScriptValue qtscript_QGraphicsSceneWheelEvent_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsSceneWheelEvent* _q_self = qscriptvalue_cast<QGraphicsSceneWheelEvent*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsSceneWheelEvent.%0(): this object is not a QGraphicsSceneWheelEvent")
            .arg(qtscript_QGraphicsSceneWheelEvent_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QFlags<Qt::MouseButton> _q_result = _q_self->buttons();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->delta();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QFlags<Qt::KeyboardModifier> _q_result = _q_self->modifiers();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        Qt::Orientation _q_result = _q_self->orientation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->pos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QPointF _q_result = _q_self->scenePos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QPoint _q_result = _q_self->screenPos();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QFlags<Qt::MouseButton> _q_arg0 = qscriptvalue_cast<QFlags<Qt::MouseButton> >(context->argument(0));
        _q_self->setButtons(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setDelta(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QFlags<Qt::KeyboardModifier> _q_arg0 = qscriptvalue_cast<QFlags<Qt::KeyboardModifier> >(context->argument(0));
        _q_self->setModifiers(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        Qt::Orientation _q_arg0 = qscriptvalue_cast<Qt::Orientation>(context->argument(0));
        _q_self->setOrientation(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
        _q_self->setScenePos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        _q_self->setScreenPos(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0)
        return qScriptValueFromValue(context->engine(), _q_self->phase());
    break;

    case 15:
    if (context->argumentCount() == 0)
        return qScriptValueFromValue(context->engine(), _q_self->pixelDelta());
    break;

    case 16:
    if (context->argumentCount() == 0)
        return QScriptValue(context->engine(), _q_self->isInverted());
    break;

    case 17:
    if (context->argumentCount() == 1) {
        _q_self->setPhase(qscriptvalue_cast<Qt::ScrollPhase>(context->argument(0)));
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        _q_self->setPixelDelta(qscriptvalue_cast<QPoint>(context->argument(0)));
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        _q_self->setInverted(context->argument(0).toBoolean());
        return context->engine()->undefinedValue();
    }
    break;

    case 20: {
    QString result = QString::fromLatin1("QGraphicsSceneWheelEvent");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneWheelEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneWheelEvent_function_names[_id+1],
        qtscript_QGraphicsSceneWheelEvent_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsSceneWheelEvent_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsSceneWheelEvent(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QGraphicsSceneWheelEvent* _q_cpp_result = new QGraphicsSceneWheelEvent();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), QVariant::fromValue(_q_cpp_result));
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QEvent::Type _q_arg0 = qscriptvalue_cast<QEvent::Type>(context->argument(0));
        QGraphicsSceneWheelEvent* _q_cpp_result = new QGraphicsSceneWheelEvent(_q_arg0);
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), QVariant::fromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsSceneWheelEvent_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsSceneWheelEvent_function_names[_id],
        qtscript_QGraphicsSceneWheelEvent_function_signatures[_id]);
}

QScriptValue qtscript_create_QGraphicsSceneWheelEvent_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneWheelEvent*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(QVariant::fromValue((QGraphicsSceneWheelEvent*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QGraphicsSceneEvent*>()));
    for (int i = 0; i < 21; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsSceneWheelEvent_prototype_call, qtscript_QGraphicsSceneWheelEvent_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsSceneWheelEvent_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QGraphicsSceneWheelEvent*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsSceneWheelEvent_static_call, proto, qtscript_QGraphicsSceneWheelEvent_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
