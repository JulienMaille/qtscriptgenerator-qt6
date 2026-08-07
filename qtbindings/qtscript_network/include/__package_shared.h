
#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariant>

template <typename T>
inline QVariant qVariantFromValue(const T &value)
{
    return QVariant::fromValue(value);
}

#ifdef QT_NO_SSL
class QSslError : public QObject {
	Q_OBJECT
public:
	QSslError(): QObject() {}
	QSslError(const QSslError &) : QObject() {}
};
class QSslConfiguration : public QObject {
	Q_OBJECT
public:
	QSslConfiguration() : QObject() {}
	QSslConfiguration(const QSslConfiguration &) : QObject() {}
};
#endif

