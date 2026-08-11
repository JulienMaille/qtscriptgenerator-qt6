#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qmutex.h>
#include <QVariant>
#include <qmutex.h>

static const char * const qtscript_QMutex_function_names[] = {
    "QMutex"
    // static
    // prototype
    , "lock"
    , "tryLock"
    , "unlock"
    , "toString"
};

static const char * const qtscript_QMutex_function_signatures[] = {
    ""
    // static
    // prototype
    , ""
    , "\nint timeout"
    , ""
""
};

static const int qtscript_QMutex_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QMutex_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QMutex::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QMutex*)
Q_DECLARE_METATYPE(QBasicMutex*)

//
// QMutex
//

static QScriptValue qtscript_QMutex_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QMutex* _q_self = qscriptvalue_cast<QMutex*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QMutex.%0(): this object is not a QMutex")
            .arg(qtscript_QMutex_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->lock();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->tryLock();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->tryLock(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->unlock();
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QMutex");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMutex_throw_ambiguity_error_helper(context,
        qtscript_QMutex_function_names[_id+1],
        qtscript_QMutex_function_signatures[_id+1]);
}

static QScriptValue qtscript_QMutex_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QMutex(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QMutex* _q_cpp_result = new QMutex();
        QScriptValue _q_result = context->engine()->newVariant(context->thisObject(), qVariantFromValue(_q_cpp_result));
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QMutex_throw_ambiguity_error_helper(context,
        qtscript_QMutex_function_names[_id],
        qtscript_QMutex_function_signatures[_id]);
}

QScriptValue qtscript_create_QMutex_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QMutex*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QMutex*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QBasicMutex*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QMutex_prototype_call, qtscript_QMutex_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QMutex_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QMutex*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QMutex_static_call, proto, qtscript_QMutex_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
