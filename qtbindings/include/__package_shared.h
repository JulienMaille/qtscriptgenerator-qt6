#pragma once

#include <QtCore/QRegularExpression>
#include <QtCore/QVariant>
#include <QtCore/QThread>
#include <QtScript/QScriptValue>
#include <QtScript/QRegExp>

template <typename T>
inline QVariant qVariantFromValue(const T &value)
{
    return QVariant::fromValue(value);
}

inline bool qtscriptIsRegExp(const QScriptValue &value)
{
    return value.isRegExp()
        || qMetaTypeId<QRegExp>() == value.toVariant().userType();
}

inline QRegExp qtscriptToRegExp(const QScriptValue &value)
{
    if (value.isRegExp())
        return value.toRegExp();
    return qvariant_cast<QRegExp>(value.toVariant());
}

inline QRegularExpression qtscriptRegularExpression(const QRegExp &expression)
{
    QRegularExpression::PatternOptions options;
    if (expression.caseSensitivity() == Qt::CaseInsensitive)
        options |= QRegularExpression::CaseInsensitiveOption;
    return QRegularExpression(expression.pattern(), options);
}

#if defined(QT_NO_SSL) && defined(QTSCRIPT_NETWORK_PACKAGE)
#include <QtCore/QObject>

class QSslError : public QObject {
    Q_OBJECT
public:
    QSslError() : QObject() {}
    QSslError(const QSslError &) : QObject() {}
};

class QSslConfiguration : public QObject {
    Q_OBJECT
public:
    QSslConfiguration() : QObject() {}
    QSslConfiguration(const QSslConfiguration &) : QObject() {}
};
#endif
