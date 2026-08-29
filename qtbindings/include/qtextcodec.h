#pragma once

#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QStringConverter>

#include <optional>

QT_BEGIN_NAMESPACE

class QTextDecoder;
class QTextEncoder;

// Qt 6 removed QTextCodec.  The generated bindings only need the public codec
// facade, so provide it locally on top of QStringEncoder/QStringDecoder rather
// than linking the removed-API compatibility module.
class QTextCodec : public QStringConverterBase
{
    Q_DISABLE_COPY(QTextCodec)
public:
    using ConversionFlags = QStringConverterBase::Flags;
    using ConverterState = QStringConverterBase::State;

    static constexpr Flag ConvertInvalidToNull = Flag::ConvertInvalidToNull;
    static constexpr Flag DefaultConversion = Flag::Default;
    static constexpr Flag IgnoreHeader = Flag::ConvertInitialBom;

    static QTextCodec *codecForName(const QByteArray &name);
    static QTextCodec *codecForName(const char *name) { return codecForName(QByteArray(name)); }
    static QTextCodec *codecForMib(int mib);
    static QList<QByteArray> availableCodecs();
    static QList<int> availableMibs();
    static QTextCodec *codecForLocale();
    static void setCodecForLocale(QTextCodec *codec);
    static QTextCodec *codecForTr() { return codecForMib(106); }
    static QTextCodec *codecForHtml(const QByteArray &data);
    static QTextCodec *codecForHtml(const QByteArray &data, QTextCodec *defaultCodec);
    static QTextCodec *codecForUtfText(const QByteArray &data);
    static QTextCodec *codecForUtfText(const QByteArray &data, QTextCodec *defaultCodec);

    bool canEncode(QChar character) const { return canEncode(QString(character)); }
    bool canEncode(const QString &text) const { return canEncode(QStringView(text)); }
    bool canEncode(QStringView text) const;

    QString toUnicode(const QByteArray &data) const
    { return toUnicode(data.constData(), data.size(), nullptr); }
    QString toUnicode(const char *characters) const
    { return characters ? toUnicode(characters, int(qstrlen(characters)), nullptr) : QString(); }
    QString toUnicode(const char *characters, int length, ConverterState *state = nullptr) const
    {
        if (!characters)
            return {};
        return convertToUnicode(characters, length, state);
    }

    QByteArray fromUnicode(const QString &text) const { return fromUnicode(QStringView(text)); }
    QByteArray fromUnicode(QStringView text) const
    { return convertFromUnicode(text.constData(), text.size(), nullptr); }
    QByteArray fromUnicode(const QChar *characters, int length, ConverterState *state = nullptr) const
    {
        if (!characters)
            return {};
        return convertFromUnicode(characters, length, state);
    }

    QTextDecoder *makeDecoder(ConversionFlags flags = DefaultConversion) const;
    QTextEncoder *makeEncoder(ConversionFlags flags = DefaultConversion) const;

    virtual QByteArray name() const = 0;
    virtual QList<QByteArray> aliases() const { return {}; }
    virtual int mibEnum() const = 0;

protected:
    QTextCodec() = default;
    virtual ~QTextCodec() = default;
    virtual QString convertToUnicode(const char *in, int length, ConverterState *state) const = 0;
    virtual QByteArray convertFromUnicode(const QChar *in, int length, ConverterState *state) const = 0;
    virtual std::optional<QStringConverter::Encoding> qtEncoding() const { return std::nullopt; }

private:
    friend class QTextDecoder;
    friend class QTextEncoder;
};

class QTextEncoder
{
    Q_DISABLE_COPY(QTextEncoder)
public:
    explicit QTextEncoder(const QTextCodec *codec)
        : QTextEncoder(codec, QTextCodec::DefaultConversion) {}
    QTextEncoder(const QTextCodec *codec, QTextCodec::ConversionFlags flags)
        : m_codec(codec), m_state(flags)
    {
        if (codec) {
            if (const auto encoding = codec->qtEncoding())
                m_encoder.emplace(*encoding, flags);
        }
    }
    QByteArray fromUnicode(const QString &text) { return fromUnicode(QStringView(text)); }
    QByteArray fromUnicode(QStringView text)
    {
        if (!m_codec)
            return {};
        if (m_encoder)
            return m_encoder->encode(text);
        return m_codec->fromUnicode(text.constData(), text.size(), &m_state);
    }
    QByteArray fromUnicode(const QChar *characters, int length)
    { return fromUnicode(QStringView(characters, length)); }
    bool hasFailure() const
    { return m_encoder ? m_encoder->hasError() : m_state.invalidChars != 0; }
    // True when the previous call left a partial multi-byte sequence buffered.
    bool needsMoreData() const
    { return m_encoder ? m_encoderPartialPending : m_state.remainingChars != 0; }

private:
    const QTextCodec *m_codec = nullptr;
    QTextCodec::ConverterState m_state;
    std::optional<QStringEncoder> m_encoder;
    bool m_encoderPartialPending = false;
};

class QTextDecoder
{
    Q_DISABLE_COPY(QTextDecoder)
public:
    explicit QTextDecoder(const QTextCodec *codec)
        : QTextDecoder(codec, QTextCodec::DefaultConversion) {}
    QTextDecoder(const QTextCodec *codec, QTextCodec::ConversionFlags flags)
        : m_codec(codec), m_state(flags)
    {
        if (codec) {
            if (const auto encoding = codec->qtEncoding())
                m_decoder.emplace(*encoding, flags);
        }
    }
    QString toUnicode(const char *characters, int length)
    {
        if (!m_codec || !characters)
            return {};
        if (m_decoder) {
            m_decoderPartialPending = endsWithPartialSequence(
                reinterpret_cast<const uchar *>(characters), length);
            return m_decoder->decode(QByteArrayView(characters, length));
        }
        return m_codec->toUnicode(characters, length, &m_state);
    }
    QString toUnicode(const QByteArray &data) { return toUnicode(data.constData(), data.size()); }
    void toUnicode(QString *target, const char *characters, int length)
    {
        if (target)
            target->append(toUnicode(characters, length));
    }
    bool hasFailure() const
    { return m_decoder ? m_decoder->hasError() : m_state.invalidChars != 0; }
    bool needsMoreData() const
    { return m_decoder ? m_decoderPartialPending : m_state.remainingChars != 0; }

private:
    static bool endsWithPartialSequence(const uchar *bytes, int length)
    {
        if (!bytes || length <= 0)
            return false;
        // A trailing multi-byte encoding state is meaningful only for the
        // multi-byte converters; single-byte encodings never need more data.
        const int i = length - 1;
        // UTF-8 continuation: 0x80..0xBF may be part of an incomplete sequence
        // interrupted at the end of this buffer.
        if (bytes[i] >= 0x80 && bytes[i] <= 0xBF) {
            int continuation = 0;
            int j = i;
            while (j >= 0 && bytes[j] >= 0x80 && bytes[j] <= 0xBF && continuation < 3) {
                --j;
                ++continuation;
            }
            if (j < 0)
                return true; // buffer began mid-sequence; cannot know
            const uchar lead = bytes[j];
            const int expected = (lead >= 0xF0) ? 3 : (lead >= 0xE0) ? 2 : (lead >= 0xC2) ? 1 : -1;
            return expected >= 0 && continuation < expected;
        }
        // UTF-16/UTF-32: a lone lead surrogate at the end is an incomplete pair.
        if (bytes[i] >= 0xD8 && bytes[i] <= 0xDB)
            return true;
        return false;
    }

    const QTextCodec *m_codec = nullptr;
    QTextCodec::ConverterState m_state;
    std::optional<QStringDecoder> m_decoder;
    bool m_decoderPartialPending = false;
};

class QtBindingsBuiltinTextCodec final : public QTextCodec
{
public:
    QtBindingsBuiltinTextCodec(QStringConverter::Encoding encoding, int mib)
        : m_encoding(encoding), m_mib(mib) {}
    QByteArray name() const override
    { return QByteArray(QStringConverter::nameForEncoding(m_encoding)); }
    int mibEnum() const override { return m_mib; }

protected:
    QString convertToUnicode(const char *in, int length, ConverterState *state) const override
    {
        QStringDecoder decoder(m_encoding, state ? state->flags : Flag::Default);
        QString result = decoder.decode(QByteArrayView(in, length));
        if (state) {
            if (decoder.hasError())
                ++state->invalidChars;
            // Report any trailing partial multi-byte sequence so an
            // incremental consumer learns more data is required.
            if (endsWithPartialSequence(reinterpret_cast<const uchar *>(in), length))
                ++state->remainingChars;
        }
        return result;
    }
    QByteArray convertFromUnicode(const QChar *in, int length, ConverterState *state) const override
    {
        QStringEncoder encoder(m_encoding, state ? state->flags : Flag::Default);
        QByteArray result = encoder.encode(QStringView(in, length));
        if (state) {
            if (encoder.hasError())
                ++state->invalidChars;
            if (length > 0 && in[length - 1].isHighSurrogate())
                ++state->remainingChars;
        }
        return result;
    }
    std::optional<QStringConverter::Encoding> qtEncoding() const override { return m_encoding; }

private:
    static bool endsWithPartialSequence(const uchar *bytes, int length)
    {
        if (!bytes || length <= 0)
            return false;
        const int i = length - 1;
        if (bytes[i] >= 0x80 && bytes[i] <= 0xBF) {
            int continuation = 0;
            int j = i;
            while (j >= 0 && bytes[j] >= 0x80 && bytes[j] <= 0xBF && continuation < 3) {
                --j;
                ++continuation;
            }
            if (j < 0)
                return true;
            const uchar lead = bytes[j];
            const int expected = (lead >= 0xF0) ? 3 : (lead >= 0xE0) ? 2 : (lead >= 0xC2) ? 1 : -1;
            return expected >= 0 && continuation < expected;
        }
        if (bytes[i] >= 0xD8 && bytes[i] <= 0xDB)
            return true;
        return false;
    }

    QStringConverter::Encoding m_encoding;
    int m_mib;
};

inline QList<QTextCodec *> qtBindingsTextCodecs()
{
    static QtBindingsBuiltinTextCodec codecs[] = {
        { QStringConverter::Utf8, 106 },
        { QStringConverter::Utf16, 1015 },
        { QStringConverter::Utf16BE, 1013 },
        { QStringConverter::Utf16LE, 1014 },
        { QStringConverter::Utf32, 1017 },
        { QStringConverter::Utf32BE, 1018 },
        { QStringConverter::Utf32LE, 1019 },
        { QStringConverter::Latin1, 4 },
        { QStringConverter::System, 0 }
    };
    QList<QTextCodec *> result;
    for (QTextCodec &codec : codecs)
        result.append(&codec);
    return result;
}

inline QTextCodec *QTextCodec::codecForName(const QByteArray &name)
{
    const auto encoding = QStringConverter::encodingForName(QString::fromLatin1(name));
    if (!encoding)
        return nullptr;
    for (QTextCodec *codec : qtBindingsTextCodecs()) {
        if (codec->qtEncoding() == encoding)
            return codec;
    }
    return nullptr;
}

inline QTextCodec *QTextCodec::codecForMib(int mib)
{
    for (QTextCodec *codec : qtBindingsTextCodecs()) {
        if (codec->mibEnum() == mib)
            return codec;
    }
    return nullptr;
}

inline QList<QByteArray> QTextCodec::availableCodecs()
{
    QList<QByteArray> result;
    for (QTextCodec *codec : qtBindingsTextCodecs())
        result.append(codec->name());
    return result;
}

inline QList<int> QTextCodec::availableMibs()
{
    QList<int> result;
    for (QTextCodec *codec : qtBindingsTextCodecs())
        result.append(codec->mibEnum());
    return result;
}

inline QTextCodec *&qtBindingsLocaleCodec()
{
    static QTextCodec *codec = QTextCodec::codecForName("System");
    return codec;
}

inline QTextCodec *QTextCodec::codecForLocale() { return qtBindingsLocaleCodec(); }
inline void QTextCodec::setCodecForLocale(QTextCodec *codec)
{ qtBindingsLocaleCodec() = codec ? codec : codecForName("System"); }

inline QTextCodec *QTextCodec::codecForHtml(const QByteArray &data, QTextCodec *defaultCodec)
{
    const auto encoding = QStringConverter::encodingForHtml(QByteArrayView(data));
    return encoding ? codecForName(QStringConverter::nameForEncoding(*encoding)) : defaultCodec;
}
inline QTextCodec *QTextCodec::codecForHtml(const QByteArray &data)
{ return codecForHtml(data, codecForName("ISO-8859-1")); }

inline QTextCodec *QTextCodec::codecForUtfText(const QByteArray &data, QTextCodec *defaultCodec)
{
    const auto encoding = QStringConverter::encodingForData(QByteArrayView(data));
    return encoding ? codecForName(QStringConverter::nameForEncoding(*encoding)) : defaultCodec;
}
inline QTextCodec *QTextCodec::codecForUtfText(const QByteArray &data)
{ return codecForUtfText(data, codecForName("ISO-8859-1")); }

inline bool QTextCodec::canEncode(QStringView text) const
{
    ConverterState state(ConvertInvalidToNull);
    convertFromUnicode(text.constData(), text.size(), &state);
    return state.invalidChars == 0;
}

inline QTextDecoder *QTextCodec::makeDecoder(ConversionFlags flags) const
{ return new QTextDecoder(this, flags); }
inline QTextEncoder *QTextCodec::makeEncoder(ConversionFlags flags) const
{ return new QTextEncoder(this, flags); }

namespace Qt {
inline QTextCodec *codecForHtml(const QByteArray &data) { return QTextCodec::codecForHtml(data); }
}

QT_END_NAMESPACE
