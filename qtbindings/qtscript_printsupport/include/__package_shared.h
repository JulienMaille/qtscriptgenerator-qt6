#pragma once

#include <QtCore/QVariant>

// Qt 5's generated sources used qVariantFromValue(). Keep the compatibility
// local to this generated package while using Qt 6's QVariant API underneath.
template <typename T>
inline QVariant qVariantFromValue(const T &value)
{
    return QVariant::fromValue(value);
}
