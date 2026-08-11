#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qdom.h>
#include <QVariant>
#include <qbytearray.h>
#include <qdom.h>
#include <qiodevice.h>
#include <qtextstream.h>
#include <qanystringview.h>
#include <QXmlStreamReader>

static const char * const qtscript_QDomDocument_function_names[] = {
    "QDomDocument"
    // static
    // prototype
    , "createAttribute"
    , "createAttributeNS"
    , "createCDATASection"
    , "createComment"
    , "createDocumentFragment"
    , "createElement"
    , "createElementNS"
    , "createEntityReference"
    , "createProcessingInstruction"
    , "createTextNode"
    , "doctype"
    , "documentElement"
    , "elementById"
    , "elementsByTagName"
    , "elementsByTagNameNS"
    , "implementation"
    , "importNode"
    , "setContent"
    , "toByteArray"
    , "toString"
};

static const char * const qtscript_QDomDocument_function_signatures[] = {
    "\nQDomDocument x\nQDomDocumentType doctype, String name"
    // static
    // prototype
    , "String name"
    , "String nsURI, String qName"
    , "String data"
    , "String data"
    , ""
    , "String tagName"
    , "String nsURI, String qName"
    , "String name"
    , "String target, String data"
    , "String data"
    , ""
    , ""
    , "String elementId"
    , "String tagname"
    , "String nsURI, String localName"
    , ""
    , "QDomNode importedNode, bool deep"
    , "QIODevice dev\nQIODevice dev, QDomDocument.ParseOptions options\nQByteArray text\nQByteArray text, QDomDocument.ParseOptions options\nString text\nString text, QDomDocument.ParseOptions options\nQXmlStreamReader reader\nQXmlStreamReader reader, QDomDocument.ParseOptions options"
    , "int arg__1"
    , "int arg__1"
};

static const int qtscript_QDomDocument_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 2
    , 1
    , 1
    , 0
    , 1
    , 2
    , 1
    , 2
    , 1
    , 0
    , 0
    , 1
    , 1
    , 2
    , 0
    , 2
    , 2
    , 1
    , 1
};

static QScriptValue qtscript_QDomDocument_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QDomDocument::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QDomDocument)
Q_DECLARE_METATYPE(QDomDocument*)
Q_DECLARE_METATYPE(QDomAttr)
Q_DECLARE_METATYPE(QDomCDATASection)
Q_DECLARE_METATYPE(QDomComment)
Q_DECLARE_METATYPE(QDomDocumentFragment)
Q_DECLARE_METATYPE(QDomElement)
Q_DECLARE_METATYPE(QDomEntityReference)
Q_DECLARE_METATYPE(QDomProcessingInstruction)
Q_DECLARE_METATYPE(QDomText)
Q_DECLARE_METATYPE(QDomDocumentType)
Q_DECLARE_METATYPE(QDomNodeList)
Q_DECLARE_METATYPE(QDomImplementation)
Q_DECLARE_METATYPE(QDomNode)
Q_DECLARE_METATYPE(QIODevice*)
Q_DECLARE_METATYPE(QDomDocument::ParseOption)
Q_DECLARE_METATYPE(QDomDocument::ParseOptions)
Q_DECLARE_METATYPE(QXmlStreamReader*)
Q_DECLARE_METATYPE(QDomNode*)

static bool qtscript_QDomDocument_parse_options(const QScriptValue &value,
                                                QDomDocument::ParseOptions *options)
{
    if (value.isBoolean()) {
        *options = value.toBoolean()
            ? QDomDocument::ParseOptions(QDomDocument::ParseOption::UseNamespaceProcessing)
            : QDomDocument::ParseOptions();
        return true;
    }

    const QVariant variant = value.toVariant();
    if (variant.userType() == qMetaTypeId<QDomDocument::ParseOptions>()) {
        *options = qvariant_cast<QDomDocument::ParseOptions>(variant);
        return true;
    }
    if (variant.userType() == qMetaTypeId<QDomDocument::ParseOption>()) {
        *options = qvariant_cast<QDomDocument::ParseOption>(variant);
        return true;
    }
    if (value.isNumber()) {
        *options = QDomDocument::ParseOptions::fromInt(value.toInt32());
        return true;
    }
    return false;
}

static QScriptValue qtscript_QDomDocument_parse_result(QScriptContext *context,
                                                       const QDomDocument::ParseResult &result)
{
    QScriptEngine *engine = context->engine();
    QScriptValue object = engine->newObject();
    object.setProperty(QStringLiteral("ok"), QScriptValue(engine, bool(result)),
                       QScriptValue::ReadOnly | QScriptValue::Undeletable);
    object.setProperty(QStringLiteral("errorMessage"), QScriptValue(engine, result.errorMessage),
                       QScriptValue::ReadOnly | QScriptValue::Undeletable);
    object.setProperty(QStringLiteral("errorLine"), QScriptValue(engine, qreal(result.errorLine)),
                       QScriptValue::ReadOnly | QScriptValue::Undeletable);
    object.setProperty(QStringLiteral("errorColumn"), QScriptValue(engine, qreal(result.errorColumn)),
                       QScriptValue::ReadOnly | QScriptValue::Undeletable);
    return object;
}

static QDomNode qtscript_QDomDocument_node_value(const QScriptValue &scriptValue)
{
    if (QDomNode *pointer = qscriptvalue_cast<QDomNode *>(scriptValue))
        return *pointer;
    const QVariant value = scriptValue.toVariant();
    const int type = value.userType();
    if (type == qMetaTypeId<QDomNode>())
        return qvariant_cast<QDomNode>(value);
    if (type == qMetaTypeId<QDomElement>())
        return qvariant_cast<QDomElement>(value);
    if (type == qMetaTypeId<QDomDocument>())
        return qvariant_cast<QDomDocument>(value);
    if (type == qMetaTypeId<QDomAttr>())
        return qvariant_cast<QDomAttr>(value);
    if (type == qMetaTypeId<QDomCDATASection>())
        return qvariant_cast<QDomCDATASection>(value);
    if (type == qMetaTypeId<QDomCharacterData>())
        return qvariant_cast<QDomCharacterData>(value);
    if (type == qMetaTypeId<QDomComment>())
        return qvariant_cast<QDomComment>(value);
    if (type == qMetaTypeId<QDomDocumentFragment>())
        return qvariant_cast<QDomDocumentFragment>(value);
    if (type == qMetaTypeId<QDomDocumentType>())
        return qvariant_cast<QDomDocumentType>(value);
    if (type == qMetaTypeId<QDomEntity>())
        return qvariant_cast<QDomEntity>(value);
    if (type == qMetaTypeId<QDomEntityReference>())
        return qvariant_cast<QDomEntityReference>(value);
    if (type == qMetaTypeId<QDomNotation>())
        return qvariant_cast<QDomNotation>(value);
    if (type == qMetaTypeId<QDomProcessingInstruction>())
        return qvariant_cast<QDomProcessingInstruction>(value);
    if (type == qMetaTypeId<QDomText>())
        return qvariant_cast<QDomText>(value);
    return qscriptvalue_cast<QDomNode>(scriptValue);
}

//
// QDomDocument
//

static QScriptValue qtscript_QDomDocument_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 20;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QDomDocument* _q_self = qscriptvalue_cast<QDomDocument*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QDomDocument.%0(): this object is not a QDomDocument")
            .arg(qtscript_QDomDocument_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
        if (context->argumentCount() == 1) {
            const QDomAttr result = _q_self->createAttribute(context->argument(0).toString());
            return qScriptValueFromValue(context->engine(), result);
        }
        break;
    case 1:
        if (context->argumentCount() == 2) {
            const QDomAttr result = _q_self->createAttributeNS(context->argument(0).toString(),
                                                               context->argument(1).toString());
            return qScriptValueFromValue(context->engine(), result);
        }
        break;
    case 2:
        if (context->argumentCount() == 1)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->createCDATASection(context->argument(0).toString()));
        break;
    case 3:
        if (context->argumentCount() == 1)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->createComment(context->argument(0).toString()));
        break;
    case 4:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->createDocumentFragment());
        break;
    case 5:
        if (context->argumentCount() == 1)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->createElement(context->argument(0).toString()));
        break;
    case 6:
        if (context->argumentCount() == 2)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->createElementNS(context->argument(0).toString(),
                                                                  context->argument(1).toString()));
        break;
    case 7:
        if (context->argumentCount() == 1)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->createEntityReference(context->argument(0).toString()));
        break;
    case 8:
        if (context->argumentCount() == 2)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->createProcessingInstruction(context->argument(0).toString(),
                                                                              context->argument(1).toString()));
        break;
    case 9:
        if (context->argumentCount() == 1)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->createTextNode(context->argument(0).toString()));
        break;
    case 10:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->doctype());
        break;
    case 11:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->documentElement());
        break;
    case 12:
        if (context->argumentCount() == 1)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->elementById(context->argument(0).toString()));
        break;
    case 13:
        if (context->argumentCount() == 1)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->elementsByTagName(context->argument(0).toString()));
        break;
    case 14:
        if (context->argumentCount() == 2)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->elementsByTagNameNS(context->argument(0).toString(),
                                                                      context->argument(1).toString()));
        break;
    case 15:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->implementation());
        break;
    case 16:
        if (context->argumentCount() == 2) {
            const QDomNode imported = qtscript_QDomDocument_node_value(context->argument(0));
            return qScriptValueFromValue(context->engine(),
                                         _q_self->importNode(imported, context->argument(1).toBoolean()));
        }
        break;
    case 17: {
        const int argumentCount = context->argumentCount();
        if (argumentCount != 1 && argumentCount != 2)
            break;

        QDomDocument::ParseOptions options;
        if (argumentCount == 2
            && !qtscript_QDomDocument_parse_options(context->argument(1), &options)) {
            return context->throwError(QScriptContext::TypeError,
                                       QStringLiteral("QDomDocument.setContent(): invalid ParseOptions"));
        }

        QDomDocument::ParseResult result;
        const QScriptValue source = context->argument(0);
        if (QIODevice *device = qscriptvalue_cast<QIODevice *>(source)) {
            result = _q_self->setContent(device, options);
        } else if (source.toVariant().userType() == qMetaTypeId<QByteArray>()) {
            result = _q_self->setContent(qscriptvalue_cast<QByteArray>(source), options);
        } else if (QXmlStreamReader *reader = qscriptvalue_cast<QXmlStreamReader *>(source)) {
            result = _q_self->setContent(reader, options);
        } else if (source.isString()) {
            result = _q_self->setContent(QAnyStringView(QStringView(source.toString())), options);
        } else {
            break;
        }
        return qtscript_QDomDocument_parse_result(context, result);
    }
    case 18:
        if (context->argumentCount() == 0)
            return qScriptValueFromValue(context->engine(), _q_self->toByteArray());
        if (context->argumentCount() == 1)
            return qScriptValueFromValue(context->engine(),
                                         _q_self->toByteArray(context->argument(0).toInt32()));
        break;
    case 19:
        if (context->argumentCount() == 0)
            return QScriptValue(context->engine(), _q_self->toString());
        if (context->argumentCount() == 1)
            return QScriptValue(context->engine(),
                                _q_self->toString(context->argument(0).toInt32()));
        break;
    default:
        Q_ASSERT(false);
    }
    return qtscript_QDomDocument_throw_ambiguity_error_helper(context,
        qtscript_QDomDocument_function_names[_id+1],
        qtscript_QDomDocument_function_signatures[_id+1]);
}

static QScriptValue qtscript_QDomDocument_static_call(QScriptContext *context, QScriptEngine *)
{
    const uint id = context->callee().data().toUInt32();
    Q_ASSERT((id & 0xFFFF0000) == 0xBABE0000);
    if ((id & 0x0000FFFF) != 0)
        return qtscript_QDomDocument_throw_ambiguity_error_helper(
            context, qtscript_QDomDocument_function_names[id & 0x0000FFFF],
            qtscript_QDomDocument_function_signatures[id & 0x0000FFFF]);

    if (context->thisObject().strictlyEquals(context->engine()->globalObject()))
        return context->throwError(QString::fromLatin1("QDomDocument(): Did you forget to construct with 'new'?"));

    if (context->argumentCount() == 0) {
        const QDomDocument result;
        return context->engine()->newVariant(context->thisObject(), qVariantFromValue(result));
    }
    if (context->argumentCount() == 1) {
        if (context->argument(0).toVariant().userType() == qMetaTypeId<QDomDocument>()) {
            return context->engine()->newVariant(context->thisObject(),
                                                  qVariantFromValue(qscriptvalue_cast<QDomDocument>(context->argument(0))));
        }
        if (context->argument(0).toVariant().userType() == qMetaTypeId<QDomDocumentType>()) {
            return context->engine()->newVariant(context->thisObject(),
                                                  qVariantFromValue(QDomDocument(qscriptvalue_cast<QDomDocumentType>(context->argument(0)))));
        }
        if (context->argument(0).isString()) {
            return context->engine()->newVariant(context->thisObject(),
                                                  qVariantFromValue(QDomDocument(context->argument(0).toString())));
        }
    }
    return qtscript_QDomDocument_throw_ambiguity_error_helper(context,
        qtscript_QDomDocument_function_names[0],
        qtscript_QDomDocument_function_signatures[0]);
}

QScriptValue qtscript_create_QDomDocument_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QDomDocument*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QDomDocument*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QDomNode*>()));
    for (int i = 0; i < 20; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QDomDocument_prototype_call,
                                               qtscript_QDomDocument_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QDomDocument_function_names[i+1]),
                          fun, QScriptValue::SkipInEnumeration);
    }

    engine->setDefaultPrototype(qMetaTypeId<QDomDocument>(), proto);
    engine->setDefaultPrototype(qMetaTypeId<QDomDocument*>(), proto);

    QScriptValue ctor = engine->newFunction(qtscript_QDomDocument_static_call, proto,
                                            qtscript_QDomDocument_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000)));
    return ctor;
}
