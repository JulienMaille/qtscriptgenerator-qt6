#pragma once

#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>

#include <QtCore/QByteArray>
#include <QtCore/QIODevice>
#include <QtCore/QMetaType>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QXmlStreamReader>
#include <QtGui/QPainter>
#include <QtGui/QPaintDevice>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QWidget>
#include <QtSvg/QSvgGenerator>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/qtsvgglobal.h>
#include <QtSvgWidgets/QGraphicsSvgItem>
#include <QtSvgWidgets/QSvgWidget>

Q_DECLARE_METATYPE(QtSvg::Option)
Q_DECLARE_METATYPE(QtSvg::Options)
Q_DECLARE_METATYPE(QIODevice *)
Q_DECLARE_METATYPE(QPaintDevice *)
Q_DECLARE_METATYPE(QPainter *)
Q_DECLARE_METATYPE(QXmlStreamReader *)
Q_DECLARE_METATYPE(QWidget *)
Q_DECLARE_METATYPE(QSvgGenerator::SvgVersion)
Q_DECLARE_METATYPE(QSvgRenderer *)
Q_DECLARE_METATYPE(QSvgGenerator *)
Q_DECLARE_METATYPE(QSvgWidget *)
Q_DECLARE_METATYPE(QGraphicsSvgItem *)

namespace qtscript_svg {

inline QScriptValue variant(QScriptEngine *engine, const QVariant &value)
{
    return engine->newVariant(value);
}

template <typename T>
inline QScriptValue value(QScriptEngine *engine, const T &object)
{
    return qScriptValueFromValue(engine, object);
}

inline bool isByteArray(const QScriptValue &value)
{
    return value.toVariant().userType() == qMetaTypeId<QByteArray>();
}

inline QByteArray byteArray(const QScriptValue &value)
{
    return qvariant_cast<QByteArray>(value.toVariant());
}

inline QtSvg::Option option(const QScriptValue &value)
{
    const QVariant variantValue = value.toVariant();
    if (variantValue.userType() == qMetaTypeId<QtSvg::Option>())
        return qvariant_cast<QtSvg::Option>(variantValue);
    return static_cast<QtSvg::Option>(value.toUInt32());
}

inline QtSvg::Options options(const QScriptValue &value)
{
    const QVariant variantValue = value.toVariant();
    if (variantValue.userType() == qMetaTypeId<QtSvg::Options>())
        return qvariant_cast<QtSvg::Options>(variantValue);
    if (variantValue.userType() == qMetaTypeId<QtSvg::Option>())
        return QtSvg::Options(qvariant_cast<QtSvg::Option>(variantValue));
    return QtSvg::Options::fromInt(value.toInt32());
}

inline QScriptValue optionsValue(QScriptEngine *engine, QtSvg::Options value)
{
    return variant(engine, QVariant::fromValue(value));
}

inline QScriptValue optionValue(QScriptEngine *engine, QtSvg::Option value)
{
    return variant(engine, QVariant::fromValue(value));
}

inline QObject *object(const QScriptValue &value)
{
    return value.toQObject();
}

inline QSvgRenderer *renderer(const QScriptValue &value)
{
    return qobject_cast<QSvgRenderer *>(object(value));
}

inline QSvgGenerator *generator(const QScriptValue &value)
{
    const QVariant variantValue = value.toVariant();
    if (variantValue.userType() == qMetaTypeId<QSvgGenerator *>())
        return qvariant_cast<QSvgGenerator *>(variantValue);
    return nullptr;
}

inline QSvgWidget *widget(const QScriptValue &value)
{
    return qobject_cast<QSvgWidget *>(object(value));
}

inline QGraphicsSvgItem *graphicsSvgItem(const QScriptValue &value)
{
    const QScriptValue data = value.data();
    const QVariant dataVariant = data.toVariant();
    if (dataVariant.userType() == qMetaTypeId<QGraphicsSvgItem *>())
        return qvariant_cast<QGraphicsSvgItem *>(dataVariant);
    return qobject_cast<QGraphicsSvgItem *>(object(value));
}

inline QSvgRenderer *rendererArgument(const QScriptValue &value)
{
    return renderer(value);
}

inline QScriptValue wrapRenderer(QScriptEngine *engine, QSvgRenderer *renderer,
                                 QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership)
{
    if (!renderer)
        return engine->nullValue();
    return engine->newQObject(renderer, ownership, QScriptEngine::PreferExistingWrapperObject);
}

inline QScriptValue wrapDevice(QScriptEngine *engine, QIODevice *device)
{
    if (!device)
        return engine->nullValue();
    return engine->newQObject(device, QScriptEngine::QtOwnership,
                              QScriptEngine::PreferExistingWrapperObject);
}

inline QScriptValue attachPrototype(QScriptValue object, const QScriptValue &prototype)
{
    if (prototype.isValid())
        object.setPrototype(prototype);
    return object;
}

inline QScriptValue typeError(QScriptContext *context, const QString &message)
{
    return context->throwError(QScriptContext::TypeError, message);
}

inline QScriptValue invalidArguments(QScriptContext *context, const QString &className,
                                     const QString &signature = QString())
{
    QString message = className + QLatin1String(": could not find a matching overload");
    if (!signature.isEmpty())
        message += QLatin1String(" (expected ") + signature + QLatin1Char(')');
    return context->throwError(QScriptContext::TypeError, message);
}

inline QScriptValue toQObject(QScriptContext *context, QObject *object,
                              QScriptEngine::ValueOwnership ownership,
                              const QScriptValue &prototype)
{
    if (!object)
        return context->engine()->nullValue();
    QScriptValue result = context->engine()->newQObject(context->thisObject(), object, ownership);
    return attachPrototype(result, prototype);
}

} // namespace qtscript_svg

QScriptValue qtscript_create_QSvgRenderer_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSvgGenerator_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSvgWidget_class(QScriptEngine *engine);
QScriptValue qtscript_create_QGraphicsSvgItem_class(QScriptEngine *engine);
void qtscript_initialize_QtSvg_namespace(QScriptValue &extensionObject);
