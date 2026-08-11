#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <qdatetime.h>
#include <qlocale.h>

#include <__package_shared.h>

// Qt 6 renamed QLocale::Country to Territory and added code-conversion and
// BCP-47 helpers.  The old generated file depended on removed QStringRef and
// Qt 5 overloads, so this wrapper intentionally targets the stable, useful
// value and formatting API while exposing both country/territory spellings.

static const char * const qtscript_QLocale_function_names[] = {
    "QLocale"
    // static
    , "c"
    , "codeToLanguage"
    , "codeToScript"
    , "codeToTerritory"
    , "languageToCode"
    , "languageToString"
    , "scriptToCode"
    , "scriptToString"
    , "setDefault"
    , "system"
    , "territoryToCode"
    , "territoryToString"
    // prototype
    , "bcp47Name"
    , "country"
    , "createSeparatedList"
    , "currencySymbol"
    , "dateFormat"
    , "dateTimeFormat"
    , "decimalPoint"
    , "groupSeparator"
    , "language"
    , "measurementSystem"
    , "name"
    , "nativeCountryName"
    , "nativeLanguageName"
    , "nativeTerritoryName"
    , "quoteString"
    , "script"
    , "territory"
    , "toCurrencyString"
    , "toDate"
    , "toDateTime"
    , "toDouble"
    , "toInt"
    , "toString"
    , "toTime"
    , "uiLanguages"
    , "zeroDigit"
};

static const char * const qtscript_QLocale_function_signatures[] = {
    "\nString name\nLanguage language, Country country\nQLocale other"
    // static
    , ""
    , "String languageCode"
    , "String scriptCode"
    , "String territoryCode"
    , "Language language"
    , "Language language"
    , "Script script"
    , "Script script"
    , "QLocale locale"
    , ""
    , "Country territory"
    , "Country territory"
    // prototype
    , "\nTagSeparator separator"
    , ""
    , "List strings"
    , "\nCurrencySymbolFormat format"
    , "\nFormatType format"
    , "\nFormatType format"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String string\nString string, QuotationStyle style"
    , ""
    , ""
    , "\nString symbol"
    , "String string\nString string, FormatType format"
    , "String string\nString string, FormatType format"
    , "String string"
    , "String string"
    , "QDate date\nQDate date, FormatType format\nQDateTime dateTime\nQDateTime dateTime, FormatType format\nQTime time\nQTime time, FormatType format\ndouble value"
    , "String string\nString string, FormatType format"
    , ""
    , ""
};

static const int qtscript_QLocale_function_lengths[] = {
    2
    // static
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 1
    , 1
    // prototype
    , 1
    , 0
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 2
    , 0
    , 0
    , 1
    , 2
    , 2
    , 1
    , 1
    , 3
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QLocale_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QLocale::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QLocale)
Q_DECLARE_METATYPE(QLocale::Language)
Q_DECLARE_METATYPE(QLocale::Script)
Q_DECLARE_METATYPE(QLocale::Country)
Q_DECLARE_METATYPE(QLocale::FormatType)
Q_DECLARE_METATYPE(QLocale::CurrencySymbolFormat)
Q_DECLARE_METATYPE(QLocale::QuotationStyle)
Q_DECLARE_METATYPE(QLocale::TagSeparator)

static QScriptValue qtscript_QLocale_value(QScriptEngine *engine, const QLocale &value)
{
    return engine->newVariant(qVariantFromValue(value));
}

static QScriptValue qtscript_QLocale_string_list(QScriptContext *context,
                                                  const QStringList &values)
{
    QScriptValue result = context->engine()->newArray(static_cast<uint>(values.size()));
    for (int i = 0; i < values.size(); ++i)
        result.setProperty(static_cast<quint32>(i), QScriptValue(context->engine(), values.at(i)));
    return result;
}

static QScriptValue qtscript_QLocale_prototype_call(QScriptContext *context,
                                                    QScriptEngine *)
{
    Q_ASSERT(context->callee().isFunction());
    uint id = context->callee().data().toUInt32() & 0x0000FFFF;
    QLocale self = qscriptvalue_cast<QLocale>(context->thisObject());

    switch (id) {
    case 0:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.bcp47Name());
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self.bcp47Name(
                static_cast<QLocale::TagSeparator>(context->argument(0).toInt32())));
        break;
    case 1:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(self.country()));
        break;
    case 2: {
        if (context->argumentCount() == 1) {
            QStringList strings;
            qScriptValueToSequence(context->argument(0), strings);
            return QScriptValue(context->engine(), self.createSeparatedList(strings));
        }
        break;
    }
    case 3:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.currencySymbol());
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self.currencySymbol(
                static_cast<QLocale::CurrencySymbolFormat>(context->argument(0).toInt32())));
        break;
    case 4:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.dateFormat());
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self.dateFormat(
                static_cast<QLocale::FormatType>(context->argument(0).toInt32())));
        break;
    case 5:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.dateTimeFormat());
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self.dateTimeFormat(
                static_cast<QLocale::FormatType>(context->argument(0).toInt32())));
        break;
    case 6:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self.decimalPoint());
        break;
    case 7:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self.groupSeparator());
        break;
    case 8:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(self.language()));
        break;
    case 9:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(self.measurementSystem()));
        break;
    case 10:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.name());
        break;
    case 11:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.nativeCountryName());
        break;
    case 12:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.nativeLanguageName());
        break;
    case 13:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), self.nativeTerritoryName());
        break;
    case 14:
        if (context->argumentCount() >= 1 && context->argumentCount() <= 2)
            return QScriptValue(context->engine(), self.quoteString(context->argument(0).toString(),
                static_cast<QLocale::QuotationStyle>(context->argumentCount() == 2
                    ? context->argument(1).toInt32() : QLocale::StandardQuotation)));
        break;
    case 15:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(self.script()));
        break;
    case 16:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), static_cast<int>(self.territory()));
        break;
    case 17:
        if (context->argumentCount() == 1 || context->argumentCount() == 2) {
            double value = context->argument(0).toNumber();
            QString symbol = context->argumentCount() == 2 ? context->argument(1).toString() : QString();
            return QScriptValue(context->engine(), self.toCurrencyString(value, symbol));
        }
        break;
    case 18:
        if (context->argumentCount() == 1 || context->argumentCount() == 2) {
            QString string = context->argument(0).toString();
            if (context->argumentCount() == 2)
                return qScriptValueFromValue(context->engine(), self.toDate(string,
                    static_cast<QLocale::FormatType>(context->argument(1).toInt32())));
            return qScriptValueFromValue(context->engine(), self.toDate(string));
        }
        break;
    case 19:
        if (context->argumentCount() == 1 || context->argumentCount() == 2) {
            QString string = context->argument(0).toString();
            if (context->argumentCount() == 2)
                return qScriptValueFromValue(context->engine(), self.toDateTime(string,
                    static_cast<QLocale::FormatType>(context->argument(1).toInt32())));
            return qScriptValueFromValue(context->engine(), self.toDateTime(string));
        }
        break;
    case 20:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self.toDouble(context->argument(0).toString()));
        break;
    case 21:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), self.toInt(context->argument(0).toString()));
        break;
    case 22:
        if (context->argumentCount() == 1) {
            QScriptValue arg = context->argument(0);
            if (qMetaTypeId<QDate>() == arg.toVariant().userType())
                return QScriptValue(context->engine(), self.toString(qscriptvalue_cast<QDate>(arg)));
            if (qMetaTypeId<QDateTime>() == arg.toVariant().userType())
                return QScriptValue(context->engine(), self.toString(arg.toDateTime()));
            if (qMetaTypeId<QTime>() == arg.toVariant().userType())
                return QScriptValue(context->engine(), self.toString(qscriptvalue_cast<QTime>(arg)));
            return QScriptValue(context->engine(), self.toString(arg.toNumber()));
        }
        if (context->argumentCount() == 2) {
            QScriptValue arg = context->argument(0);
            QLocale::FormatType format = static_cast<QLocale::FormatType>(context->argument(1).toInt32());
            if (qMetaTypeId<QDate>() == arg.toVariant().userType())
                return QScriptValue(context->engine(), self.toString(qscriptvalue_cast<QDate>(arg), format));
            if (qMetaTypeId<QDateTime>() == arg.toVariant().userType())
                return QScriptValue(context->engine(), self.toString(arg.toDateTime(), format));
            if (qMetaTypeId<QTime>() == arg.toVariant().userType())
                return QScriptValue(context->engine(), self.toString(qscriptvalue_cast<QTime>(arg), format));
        }
        break;
    case 23:
        if (context->argumentCount() == 1 || context->argumentCount() == 2) {
            QString string = context->argument(0).toString();
            if (context->argumentCount() == 2)
                return qScriptValueFromValue(context->engine(), self.toTime(string,
                    static_cast<QLocale::FormatType>(context->argument(1).toInt32())));
            return qScriptValueFromValue(context->engine(), self.toTime(string));
        }
        break;
    case 24:
        if (context->argumentCount() == 0)
            return qtscript_QLocale_string_list(context, self.uiLanguages());
        break;
    case 25:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), self.zeroDigit());
        break;
    default:
        Q_ASSERT(false);
    }
    return qtscript_QLocale_throw_ambiguity_error_helper(context,
        qtscript_QLocale_function_names[id + 13],
        qtscript_QLocale_function_signatures[id + 13]);
}

static QScriptValue qtscript_QLocale_static_call(QScriptContext *context,
                                                 QScriptEngine *)
{
    uint id = context->callee().data().toUInt32() & 0x0000FFFF;
    if (id == 0) {
        if (context->thisObject().strictlyEquals(context->engine()->globalObject()))
            return context->throwError(QString::fromLatin1("QLocale(): Did you forget to construct with 'new'?"));
        QLocale result;
        if (context->argumentCount() == 0) {
            result = QLocale();
        } else if (context->argumentCount() == 1 && context->argument(0).isString()) {
            result = QLocale(context->argument(0).toString());
        } else if (context->argumentCount() == 1) {
            result = QLocale(static_cast<QLocale::Language>(context->argument(0).toInt32()));
        } else if (context->argumentCount() == 2) {
            result = QLocale(static_cast<QLocale::Language>(context->argument(0).toInt32()),
                             static_cast<QLocale::Territory>(context->argument(1).toInt32()));
        } else {
            return qtscript_QLocale_throw_ambiguity_error_helper(context,
                qtscript_QLocale_function_names[0], qtscript_QLocale_function_signatures[0]);
        }
        return qtscript_QLocale_value(context->engine(), result);
    }

    switch (id - 1) {
    case 0:
        if (context->argumentCount() == 0)
            return qtscript_QLocale_value(context->engine(), QLocale::c());
        break;
    case 1:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), static_cast<int>(QLocale::codeToLanguage(
                context->argument(0).toString())));
        break;
    case 2:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), static_cast<int>(QLocale::codeToScript(
                context->argument(0).toString())));
        break;
    case 3:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), static_cast<int>(QLocale::codeToTerritory(
                context->argument(0).toString())));
        break;
    case 4:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), QLocale::languageToCode(
                static_cast<QLocale::Language>(context->argument(0).toInt32())));
        break;
    case 5:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), QLocale::languageToString(
                static_cast<QLocale::Language>(context->argument(0).toInt32())));
        break;
    case 6:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), QLocale::scriptToCode(
                static_cast<QLocale::Script>(context->argument(0).toInt32())));
        break;
    case 7:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), QLocale::scriptToString(
                static_cast<QLocale::Script>(context->argument(0).toInt32())));
        break;
    case 8:
        if (context->argumentCount() == 1) {
            QLocale::setDefault(qscriptvalue_cast<QLocale>(context->argument(0)));
            return context->engine()->undefinedValue();
        }
        break;
    case 9:
        if (context->argumentCount() == 0)
            return qtscript_QLocale_value(context->engine(), QLocale::system());
        break;
    case 10:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), QLocale::territoryToCode(
                static_cast<QLocale::Territory>(context->argument(0).toInt32())));
        break;
    case 11:
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(), QLocale::territoryToString(
                static_cast<QLocale::Territory>(context->argument(0).toInt32())));
        break;
    default:
        Q_ASSERT(false);
    }
    return qtscript_QLocale_throw_ambiguity_error_helper(context,
        qtscript_QLocale_function_names[id], qtscript_QLocale_function_signatures[id]);
}

QScriptValue qtscript_create_QLocale_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QLocale>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue(QLocale()));
    for (int i = 0; i < 26; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLocale_prototype_call,
                                                qtscript_QLocale_function_lengths[i + 13]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QLocale_function_names[i + 13]),
                          fun, QScriptValue::SkipInEnumeration);
    }
    engine->setDefaultPrototype(qMetaTypeId<QLocale>(), proto);
    QScriptValue ctor = engine->newFunction(qtscript_QLocale_static_call, proto,
                                             qtscript_QLocale_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000)));
    for (int i = 0; i < 12; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QLocale_static_call,
                                                qtscript_QLocale_function_lengths[i + 1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i + 1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QLocale_function_names[i + 1]),
                         fun, QScriptValue::SkipInEnumeration);
    }

    // Common enum values keep existing scripts readable without carrying the
    // Qt 5-only QStringRef-based generated enum machinery.
    ctor.setProperty(QString::fromLatin1("AnyLanguage"), QScriptValue(engine, int(QLocale::AnyLanguage)));
    ctor.setProperty(QString::fromLatin1("C"), QScriptValue(engine, int(QLocale::C)));
    ctor.setProperty(QString::fromLatin1("English"), QScriptValue(engine, int(QLocale::English)));
    ctor.setProperty(QString::fromLatin1("French"), QScriptValue(engine, int(QLocale::French)));
    ctor.setProperty(QString::fromLatin1("German"), QScriptValue(engine, int(QLocale::German)));
    ctor.setProperty(QString::fromLatin1("AnyTerritory"), QScriptValue(engine, int(QLocale::AnyTerritory)));
    ctor.setProperty(QString::fromLatin1("UnitedStates"), QScriptValue(engine, int(QLocale::UnitedStates)));
    ctor.setProperty(QString::fromLatin1("UnitedKingdom"), QScriptValue(engine, int(QLocale::UnitedKingdom)));
    ctor.setProperty(QString::fromLatin1("France"), QScriptValue(engine, int(QLocale::France)));
    ctor.setProperty(QString::fromLatin1("Germany"), QScriptValue(engine, int(QLocale::Germany)));
    ctor.setProperty(QString::fromLatin1("ShortFormat"), QScriptValue(engine, int(QLocale::ShortFormat)));
    ctor.setProperty(QString::fromLatin1("LongFormat"), QScriptValue(engine, int(QLocale::LongFormat)));
    ctor.setProperty(QString::fromLatin1("NarrowFormat"), QScriptValue(engine, int(QLocale::NarrowFormat)));
    ctor.setProperty(QString::fromLatin1("StandardQuotation"), QScriptValue(engine, int(QLocale::StandardQuotation)));
    return ctor;
}
