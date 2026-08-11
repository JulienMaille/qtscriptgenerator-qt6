#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <qdatetime.h>
#include <qlocale.h>
#include <qtimezone.h>

#include <__package_shared.h>

// QTimeZone is a Qt 6 value type with no Qt 5 generated binding.  This
// focused wrapper covers IANA/fixed zones, offsets, daylight-saving queries,
// and the static discovery helpers used by date/time consumers.

static const char * const qtscript_QTimeZone_function_names[] = {
    "QTimeZone"
    // static
    , "availableTimeZoneIds"
    , "fromSecondsAheadOfUtc"
    , "ianaIdToWindowsId"
    , "isTimeZoneIdAvailable"
    , "systemTimeZone"
    , "systemTimeZoneId"
    , "utc"
    , "windowsIdToDefaultIanaId"
    // prototype
    , "abbreviation"
    , "comment"
    , "daylightTimeOffset"
    , "displayName"
    , "equals"
    , "fixedSecondsAheadOfUtc"
    , "hasDaylightTime"
    , "hasTransitions"
    , "id"
    , "isDaylightTime"
    , "isValid"
    , "isUtcOrFixedOffset"
    , "offsetFromUtc"
    , "standardTimeOffset"
    , "territory"
    , "timeSpec"
    , "swap"
    , "toString"
};

static const char * const qtscript_QTimeZone_function_signatures[] = {
    "\nint offsetSeconds\nString ianaId"
    // static
    , "\nint offsetSeconds"
    , "int offsetSeconds"
    , "String ianaId"
    , "String ianaId"
    , ""
    , ""
    , ""
    , "String windowsId"
    // prototype
    , "QDateTime atDateTime"
    , ""
    , "QDateTime atDateTime"
    , "\nTimeType timeType, NameType nameType\nQDateTime atDateTime, NameType nameType\nQDateTime atDateTime, NameType nameType, QLocale locale"
    , "QTimeZone other"
    , ""
    , ""
    , ""
    , ""
    , "QDateTime atDateTime"
    , ""
    , ""
    , "QDateTime atDateTime"
    , "QDateTime atDateTime"
    , ""
    , ""
    , "QTimeZone other"
    , ""
};

static const int qtscript_QTimeZone_function_lengths[] = {
    1
    // static
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 1
    // prototype
    , 1
    , 0
    , 1
    , 3
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QTimeZone_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QTimeZone::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QTimeZone)
Q_DECLARE_METATYPE(QTimeZone::TimeType)
Q_DECLARE_METATYPE(QTimeZone::NameType)
Q_DECLARE_METATYPE(QTimeZone::OffsetData)
Q_DECLARE_METATYPE(QLocale::Country)

static QScriptValue qtscript_QTimeZone_value(QScriptEngine *engine,
                                              const QTimeZone &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static QScriptValue qtscript_QTimeZone_byte_array_list(QScriptContext *context,
                                                        const QList<QByteArray> &ids)
{
    QScriptValue result = context->engine()->newArray(static_cast<uint>(ids.size()));
    for (int i = 0; i < ids.size(); ++i)
        result.setProperty(static_cast<quint32>(i),
                           QScriptValue(context->engine(), QString::fromUtf8(ids.at(i))));
    return result;
}

static QScriptValue qtscript_QTimeZone_prototype_call(QScriptContext *context,
                                                       QScriptEngine *)
{
    Q_ASSERT(context->callee().isFunction());
    uint id = context->callee().data().toUInt32() & 0x0000FFFF;
    QTimeZone self = qscriptvalue_cast<QTimeZone>(context->thisObject());

    switch (id) {
    case 0:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), QString::fromUtf8(self.abbreviation(qscriptvalue_cast<QDateTime>(context->argument(0))).toUtf8()));
        break;
    case 1:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.comment());
        break;
    case 2:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self.daylightTimeOffset(qscriptvalue_cast<QDateTime>(context->argument(0))));
        break;
    case 3:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.displayName(QDateTime::currentDateTime()));
        if (context->argumentCount() == 1) {
            if (qMetaTypeId<QDateTime>() == context->argument(0).toVariant().userType())
                return QScriptValue(context->engine(), self.displayName(qscriptvalue_cast<QDateTime>(context->argument(0))));
            return QScriptValue(context->engine(), self.displayName(static_cast<QTimeZone::TimeType>(context->argument(0).toInt32())));
        }
        if (context->argumentCount() == 2) {
            if (qMetaTypeId<QDateTime>() == context->argument(0).toVariant().userType())
                return QScriptValue(context->engine(), self.displayName(qscriptvalue_cast<QDateTime>(context->argument(0)),
                    static_cast<QTimeZone::NameType>(context->argument(1).toInt32())));
            return QScriptValue(context->engine(), self.displayName(static_cast<QTimeZone::TimeType>(context->argument(0).toInt32()),
                static_cast<QTimeZone::NameType>(context->argument(1).toInt32())));
        }
        if (context->argumentCount() == 3) {
            return QScriptValue(context->engine(), self.displayName(
                qscriptvalue_cast<QDateTime>(context->argument(0)),
                static_cast<QTimeZone::NameType>(context->argument(1).toInt32()),
                qscriptvalue_cast<QLocale>(context->argument(2))));
        }
        break;
    case 4:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self == qscriptvalue_cast<QTimeZone>(context->argument(0)));
        break;
    case 5:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.fixedSecondsAheadOfUtc());
        break;
    case 6:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.hasDaylightTime());
        break;
    case 7:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.hasTransitions());
        break;
    case 8:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QString::fromUtf8(self.id()));
        break;
    case 9:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self.isDaylightTime(qscriptvalue_cast<QDateTime>(context->argument(0))));
        break;
    case 10:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.isValid());
        break;
    case 11:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.isUtcOrFixedOffset());
        break;
    case 12:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self.offsetFromUtc(qscriptvalue_cast<QDateTime>(context->argument(0))));
        break;
    case 13:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self.standardTimeOffset(qscriptvalue_cast<QDateTime>(context->argument(0))));
        break;
    case 14:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self.territory());
        break;
    case 15:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self.timeSpec());
        break;
    case 16:
        if (context->argumentCount() == 1) {
            QTimeZone other = qscriptvalue_cast<QTimeZone>(context->argument(0));
            self.swap(other);
            return qtscript_QTimeZone_value(context->engine(), self);
        }
        break;
    case 17:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QString::fromUtf8(self.id()));
        break;
    default:
        Q_ASSERT(false);
    }
    return qtscript_QTimeZone_throw_ambiguity_error_helper(context,
        qtscript_QTimeZone_function_names[id + 9],
        qtscript_QTimeZone_function_signatures[id + 9]);
}

static QScriptValue qtscript_QTimeZone_static_call(QScriptContext *context,
                                                    QScriptEngine *)
{
    uint id = context->callee().data().toUInt32() & 0x0000FFFF;
    if (id == 0) {
        if (context->thisObject().strictlyEquals(context->engine()->globalObject()))
            return context->throwError(QString::fromLatin1("QTimeZone(): Did you forget to construct with 'new'?"));
        QTimeZone result;
        if (context->argumentCount() == 0) {
            result = QTimeZone();
        } else if (context->argumentCount() == 1 && context->argument(0).isNumber()) {
            result = QTimeZone(context->argument(0).toInt32());
        } else if (context->argumentCount() == 1) {
            result = QTimeZone(context->argument(0).toString().toUtf8());
        } else {
            return qtscript_QTimeZone_throw_ambiguity_error_helper(context,
                qtscript_QTimeZone_function_names[0], qtscript_QTimeZone_function_signatures[0]);
        }
        return qtscript_QTimeZone_value(context->engine(), result);
    }

    switch (id - 1) {
    case 0:
        if (context->argumentCount() == 0)
            return qtscript_QTimeZone_byte_array_list(context, QTimeZone::availableTimeZoneIds());
        if (context->argumentCount() == 1)
            return qtscript_QTimeZone_byte_array_list(context,
                QTimeZone::availableTimeZoneIds(context->argument(0).toInt32()));
        break;
    case 1:
        if (context->argumentCount() == 1)
            return qtscript_QTimeZone_value(context->engine(),
                QTimeZone::fromSecondsAheadOfUtc(context->argument(0).toInt32()));
        break;
    case 2:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), QString::fromUtf8(
                QTimeZone::ianaIdToWindowsId(context->argument(0).toString().toUtf8())));
        break;
    case 3:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), QTimeZone::isTimeZoneIdAvailable(
                context->argument(0).toString().toUtf8()));
        break;
    case 4:
        if (context->argumentCount() == 0)
            return qtscript_QTimeZone_value(context->engine(), QTimeZone::systemTimeZone());
        break;
    case 5:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), QString::fromUtf8(QTimeZone::systemTimeZoneId()));
        break;
    case 6:
        if (context->argumentCount() == 0)
            return qtscript_QTimeZone_value(context->engine(), QTimeZone::utc());
        break;
    case 7:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), QString::fromUtf8(
                QTimeZone::windowsIdToDefaultIanaId(context->argument(0).toString().toUtf8())));
        break;
    default:
        Q_ASSERT(false);
    }
    return qtscript_QTimeZone_throw_ambiguity_error_helper(context,
        qtscript_QTimeZone_function_names[id], qtscript_QTimeZone_function_signatures[id]);
}

QScriptValue qtscript_create_QTimeZone_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QTimeZone>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue(QTimeZone()));
    for (int i = 0; i < 18; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTimeZone_prototype_call,
                                                qtscript_QTimeZone_function_lengths[i + 9]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QTimeZone_function_names[i + 9]),
                          fun, QScriptValue::SkipInEnumeration);
    }
    engine->setDefaultPrototype(qMetaTypeId<QTimeZone>(), proto);
    QScriptValue ctor = engine->newFunction(qtscript_QTimeZone_static_call, proto,
                                             qtscript_QTimeZone_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000)));
    for (int i = 0; i < 8; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QTimeZone_static_call,
                                                qtscript_QTimeZone_function_lengths[i + 1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i + 1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QTimeZone_function_names[i + 1]),
                         fun, QScriptValue::SkipInEnumeration);
    }
    return ctor;
}
