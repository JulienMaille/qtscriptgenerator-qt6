#pragma once

#include <QtCore/QVariant>
#include <QtCore/QRegularExpression>
#include <QtScript/QRegExp>

template <typename T>
inline QVariant qVariantFromValue(const T &value)
{
    return QVariant::fromValue(value);
}

inline QRegularExpression qtscriptRegularExpression(const QRegExp &expression)
{
    QRegularExpression::PatternOptions options;
    if (expression.caseSensitivity() == Qt::CaseInsensitive)
        options |= QRegularExpression::CaseInsensitiveOption;
    return QRegularExpression(expression.pattern(), options);
}
