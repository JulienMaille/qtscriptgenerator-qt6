#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtGui/QFont>
#include <QtGui/QPalette>
#include <QtCore/QPoint>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>
#include <QtWidgets/QWidget>

// QApplication owns the process-wide widget application.  Constructing a
// second instance from a script is unsafe, so this facade deliberately exposes
// only static APIs; the existing qApp global remains the instance wrapper.

static const char * const qtscript_QApplication_function_names[] = {
    "QApplication"
    // static
    , "aboutQt"
    , "activeModalWidget"
    , "activePopupWidget"
    , "activeWindow"
    , "alert"
    , "allWidgets"
    , "beep"
    , "closeAllWindows"
    , "cursorFlashTime"
    , "doubleClickInterval"
    , "focusWidget"
    , "font"
    , "isEffectEnabled"
    , "keyboardInputInterval"
    , "palette"
    , "setActiveWindow"
    , "setCursorFlashTime"
    , "setDoubleClickInterval"
    , "setEffectEnabled"
    , "setFont"
    , "setKeyboardInputInterval"
    , "setPalette"
    , "setStartDragDistance"
    , "setStartDragTime"
    , "setStyle"
    , "setWheelScrollLines"
    , "startDragDistance"
    , "startDragTime"
    , "style"
    , "topLevelAt"
    , "topLevelWidgets"
    , "widgetAt"
    , "wheelScrollLines"
    // prototype
    , "toString"
};

static const char * const qtscript_QApplication_function_signatures[] = {
    ""
    // static
    , ""
    , ""
    , ""
    , ""
    , "QWidget widget\nQWidget widget, int duration"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "\nQWidget widget\nString className"
    , "UIEffect effect"
    , ""
    , "\nQWidget widget\nString className"
    , "QWidget act"
    , "int msec"
    , "int msec"
    , "UIEffect effect\nUIEffect effect, bool enable"
    , "QFont font\nQFont font, String className"
    , "int msec"
    , "QPalette palette\nQPalette palette, String className"
    , "int distance"
    , "int ms"
    , "QStyle style\nString style"
    , "int lines"
    , ""
    , ""
    , ""
    , "QPoint p\nint x, int y"
    , ""
    , "QPoint p\nint x, int y"
    , ""
    // prototype
    , ""
};

static const int qtscript_QApplication_function_lengths[] = {
    0
    // static
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 2
    , 2
    , 1
    , 2
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 2
    , 0
    , 2
    , 0
    // prototype
    , 0
};

static QScriptValue qtscript_QApplication_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QApplication::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QStyle*)
Q_DECLARE_METATYPE(QFont)
Q_DECLARE_METATYPE(QPalette)
Q_DECLARE_METATYPE(QPoint)
Q_DECLARE_METATYPE(Qt::UIEffect)

static QScriptValue qtscript_QApplication_widget_value(QScriptEngine *engine, QWidget *widget)
{
    if (!widget)
        return engine->nullValue();
    return qScriptValueFromValue(engine, widget);
}

static QScriptValue qtscript_QApplication_style_value(QScriptEngine *engine, QStyle *style)
{
    if (!style)
        return engine->nullValue();
    return qScriptValueFromValue(engine, style);
}

static QScriptValue qtscript_QApplication_widget_list_value(
    QScriptEngine *engine, const QWidgetList &widgets)
{
    QScriptValue result = engine->newArray(static_cast<quint32>(widgets.size()));
    for (int i = 0; i < widgets.size(); ++i)
        result.setProperty(i, qtscript_QApplication_widget_value(engine, widgets.at(i)));
    return result;
}

static QWidget *qtscript_QApplication_widget_argument(const QScriptValue &value)
{
    return qobject_cast<QWidget *>(value.toQObject());
}

static QScriptValue qtscript_QApplication_prototype_call(QScriptContext *context, QScriptEngine *)
{
    const uint id = context->callee().data().toUInt32() & 0x0000FFFF;
    if (id == 0)
        return QScriptValue(context->engine(), QString::fromLatin1("QApplication"));
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QApplication.%0(): invalid prototype function")
            .arg(qtscript_QApplication_function_names[id + 34]));
}

static QScriptValue qtscript_QApplication_static_call(QScriptContext *context, QScriptEngine *)
{
    const uint id = context->callee().data().toUInt32() & 0x0000FFFF;
    switch (id) {
    case 0:
        return context->throwError(QScriptContext::UnknownError,
            QString::fromLatin1("QApplication cannot be constructed from a script; use qApp"));

    case 1:
        if (context->argumentCount() == 0) {
            QApplication::aboutQt();
            return context->engine()->undefinedValue();
        }
        break;

    case 2:
        if (context->argumentCount() == 0)
            return qtscript_QApplication_widget_value(context->engine(), QApplication::activeModalWidget());
        break;

    case 3:
        if (context->argumentCount() == 0)
            return qtscript_QApplication_widget_value(context->engine(), QApplication::activePopupWidget());
        break;

    case 4:
        if (context->argumentCount() == 0)
            return qtscript_QApplication_widget_value(context->engine(), QApplication::activeWindow());
        break;

    case 5:
        if (context->argumentCount() == 1 || context->argumentCount() == 2) {
            QWidget *widget = qtscript_QApplication_widget_argument(context->argument(0));
            int duration = context->argumentCount() == 2 ? context->argument(1).toInt32() : 0;
            QApplication::alert(widget, duration);
            return context->engine()->undefinedValue();
        }
        break;

    case 6:
        if (context->argumentCount() == 0)
            return qtscript_QApplication_widget_list_value(context->engine(), QApplication::allWidgets());
        break;

    case 7:
        if (context->argumentCount() == 0) {
            QApplication::beep();
            return context->engine()->undefinedValue();
        }
        break;

    case 8:
        if (context->argumentCount() == 0) {
            QApplication::closeAllWindows();
            return context->engine()->undefinedValue();
        }
        break;

    case 9:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QApplication::cursorFlashTime());
        break;

    case 10:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QApplication::doubleClickInterval());
        break;

    case 11:
        if (context->argumentCount() == 0)
            return qtscript_QApplication_widget_value(context->engine(), QApplication::focusWidget());
        break;

    case 12:
        if (context->argumentCount() == 0) {
            QFont result = QApplication::font();
            return qScriptValueFromValue(context->engine(), result);
        }
        if (context->argumentCount() == 1) {
            if (context->argument(0).isQObject()) {
                QFont result = QApplication::font(qtscript_QApplication_widget_argument(context->argument(0)));
                return qScriptValueFromValue(context->engine(), result);
            }
            QByteArray className = context->argument(0).toString().toLatin1();
            QFont result = QApplication::font(className.constData());
            return qScriptValueFromValue(context->engine(), result);
        }
        break;

    case 13:
        if (context->argumentCount() == 1) {
            Qt::UIEffect effect = qscriptvalue_cast<Qt::UIEffect>(context->argument(0));
            return QScriptValue(context->engine(), QApplication::isEffectEnabled(effect));
        }
        break;

    case 14:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QApplication::keyboardInputInterval());
        break;

    case 15:
        if (context->argumentCount() == 0) {
            QPalette result = QApplication::palette();
            return qScriptValueFromValue(context->engine(), result);
        }
        if (context->argumentCount() == 1) {
            if (context->argument(0).isQObject()) {
                QPalette result = QApplication::palette(qtscript_QApplication_widget_argument(context->argument(0)));
                return qScriptValueFromValue(context->engine(), result);
            }
            QByteArray className = context->argument(0).toString().toLatin1();
            QPalette result = QApplication::palette(className.constData());
            return qScriptValueFromValue(context->engine(), result);
        }
        break;

    case 16:
        if (context->argumentCount() == 1) {
            QApplication::setActiveWindow(qtscript_QApplication_widget_argument(context->argument(0)));
            return context->engine()->undefinedValue();
        }
        break;

    case 17:
        if (context->argumentCount() == 1) {
            QApplication::setCursorFlashTime(context->argument(0).toInt32());
            return context->engine()->undefinedValue();
        }
        break;

    case 18:
        if (context->argumentCount() == 1) {
            QApplication::setDoubleClickInterval(context->argument(0).toInt32());
            return context->engine()->undefinedValue();
        }
        break;

    case 19:
        if (context->argumentCount() == 1 || context->argumentCount() == 2) {
            Qt::UIEffect effect = qscriptvalue_cast<Qt::UIEffect>(context->argument(0));
            bool enable = context->argumentCount() == 2 ? context->argument(1).toBoolean() : true;
            QApplication::setEffectEnabled(effect, enable);
            return context->engine()->undefinedValue();
        }
        break;

    case 20:
        if (context->argumentCount() == 1 || context->argumentCount() == 2) {
            QFont font = qscriptvalue_cast<QFont>(context->argument(0));
            if (context->argumentCount() == 1) {
                QApplication::setFont(font);
            } else {
                QByteArray className = context->argument(1).toString().toLatin1();
                QApplication::setFont(font, className.constData());
            }
            return context->engine()->undefinedValue();
        }
        break;

    case 21:
        if (context->argumentCount() == 1) {
            QApplication::setKeyboardInputInterval(context->argument(0).toInt32());
            return context->engine()->undefinedValue();
        }
        break;

    case 22:
        if (context->argumentCount() == 1 || context->argumentCount() == 2) {
            QPalette palette = qscriptvalue_cast<QPalette>(context->argument(0));
            if (context->argumentCount() == 1) {
                QApplication::setPalette(palette);
            } else {
                QByteArray className = context->argument(1).toString().toLatin1();
                QApplication::setPalette(palette, className.constData());
            }
            return context->engine()->undefinedValue();
        }
        break;

    case 23:
        if (context->argumentCount() == 1) {
            QApplication::setStartDragDistance(context->argument(0).toInt32());
            return context->engine()->undefinedValue();
        }
        break;

    case 24:
        if (context->argumentCount() == 1) {
            QApplication::setStartDragTime(context->argument(0).toInt32());
            return context->engine()->undefinedValue();
        }
        break;

    case 25:
        if (context->argumentCount() == 1) {
            if (context->argument(0).isQObject()) {
                QApplication::setStyle(qobject_cast<QStyle *>(context->argument(0).toQObject()));
                return context->engine()->undefinedValue();
            }
            QStyle *result = QApplication::setStyle(context->argument(0).toString());
            return qtscript_QApplication_style_value(context->engine(), result);
        }
        break;

    case 26:
        if (context->argumentCount() == 1) {
            QApplication::setWheelScrollLines(context->argument(0).toInt32());
            return context->engine()->undefinedValue();
        }
        break;

    case 27:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QApplication::startDragDistance());
        break;

    case 28:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QApplication::startDragTime());
        break;

    case 29:
        if (context->argumentCount() == 0)
            return qtscript_QApplication_style_value(context->engine(), QApplication::style());
        break;

    case 30:
        if (context->argumentCount() == 1) {
            QPoint point = qscriptvalue_cast<QPoint>(context->argument(0));
            return qtscript_QApplication_widget_value(context->engine(), QApplication::topLevelAt(point));
        }
        if (context->argumentCount() == 2) {
            return qtscript_QApplication_widget_value(context->engine(),
                QApplication::topLevelAt(context->argument(0).toInt32(), context->argument(1).toInt32()));
        }
        break;

    case 31:
        if (context->argumentCount() == 0)
            return qtscript_QApplication_widget_list_value(context->engine(), QApplication::topLevelWidgets());
        break;

    case 32:
        if (context->argumentCount() == 1) {
            QPoint point = qscriptvalue_cast<QPoint>(context->argument(0));
            return qtscript_QApplication_widget_value(context->engine(), QApplication::widgetAt(point));
        }
        if (context->argumentCount() == 2) {
            return qtscript_QApplication_widget_value(context->engine(),
                QApplication::widgetAt(context->argument(0).toInt32(), context->argument(1).toInt32()));
        }
        break;

    case 33:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QApplication::wheelScrollLines());
        break;

    default:
        break;
    }

    return qtscript_QApplication_throw_ambiguity_error_helper(
        context,
        qtscript_QApplication_function_names[id],
        qtscript_QApplication_function_signatures[id]);
}

QScriptValue qtscript_create_QApplication_class(QScriptEngine *engine)
{
    QScriptValue proto = engine->newObject();
    QScriptValue toString = engine->newFunction(qtscript_QApplication_prototype_call);
    toString.setData(QScriptValue(engine, uint(0xBABE0000)));
    proto.setProperty(QString::fromLatin1("toString"), toString, QScriptValue::SkipInEnumeration);

    QScriptValue ctor = engine->newFunction(
        qtscript_QApplication_static_call, proto, qtscript_QApplication_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000)));
    for (int i = 0; i < 33; ++i) {
        QScriptValue fun = engine->newFunction(
            qtscript_QApplication_static_call, qtscript_QApplication_function_lengths[i + 1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i + 1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QApplication_function_names[i + 1]),
            fun, QScriptValue::SkipInEnumeration);
    }
    return ctor;
}
