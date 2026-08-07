#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>

#include <QtGui/qkeysequence.h>
#include <QtWidgets/qkeysequenceedit.h>

Q_DECLARE_METATYPE(QKeySequenceEdit*)

static QScriptValue qtscript_QKeySequenceEdit_construct(QScriptContext *context, QScriptEngine *engine)
{
    if (!context->isCalledAsConstructor())
        return context->throwError(QStringLiteral("QKeySequenceEdit(): Did you forget to construct with 'new'?"));

    QKeySequenceEdit *editor = nullptr;
    if (context->argumentCount() == 0) {
        editor = new QKeySequenceEdit();
    } else if (context->argumentCount() == 1 && context->argument(0).isQObject()) {
        editor = new QKeySequenceEdit(qobject_cast<QWidget *>(context->argument(0).toQObject()));
    } else {
        const QKeySequence sequence = QKeySequence::fromString(context->argument(0).toString());
        QWidget *parent = context->argumentCount() > 1
            ? qobject_cast<QWidget *>(context->argument(1).toQObject()) : nullptr;
        editor = new QKeySequenceEdit(sequence, parent);
    }
    return engine->newQObject(context->thisObject(), editor, QScriptEngine::AutoOwnership);
}

static QScriptValue qtscript_QKeySequenceEdit_toScriptValue(QScriptEngine *engine,
                                                             QKeySequenceEdit *const &editor)
{
    return engine->newQObject(editor, QScriptEngine::QtOwnership,
                              QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QKeySequenceEdit_fromScriptValue(const QScriptValue &value,
                                                       QKeySequenceEdit *&editor)
{
    editor = qobject_cast<QKeySequenceEdit *>(value.toQObject());
}

QScriptValue qtscript_create_QKeySequenceEdit_class(QScriptEngine *engine)
{
    QScriptValue proto = engine->newVariant(QVariant::fromValue(static_cast<QKeySequenceEdit *>(nullptr)));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget *>()));
    qScriptRegisterMetaType<QKeySequenceEdit *>(engine, qtscript_QKeySequenceEdit_toScriptValue,
                                                qtscript_QKeySequenceEdit_fromScriptValue, proto);
    return engine->newFunction(qtscript_QKeySequenceEdit_construct, proto, 2);
}
