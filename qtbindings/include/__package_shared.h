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
// The generated qtscript_network bindings call the full QtNetwork SSL surface
// (QSslError, QSslConfiguration, QSslCertificate, QSslCipher, QSslKey,
// QSslSocket, and their enums).  A Qt built without SSL support cannot satisfy
// that surface, and a partial stand-in here would only turn a missing-module
// build into a confusion of missing-member errors across a dozen files.  Fail
// loudly at the source of the dependency instead.
#error "The qtscript_network bindings require Qt with SSL support; build Qt with OpenSSL or drop qtscript_network from QTSCRIPT_NETWORK_PACKAGE."
#endif
