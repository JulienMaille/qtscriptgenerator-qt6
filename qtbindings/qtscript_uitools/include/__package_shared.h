
#pragma once

#include <QtCore/QVariant>

template <typename T>
inline QVariant qVariantFromValue(const T &value)
{
    return QVariant::fromValue(value);
}

