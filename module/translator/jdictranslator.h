#ifndef JDICTRANSLATOR_H
#define JDICTRANSLATOR_H

// jdictranslator.h
// 8/11/2012

#include "module/translator/networktranslator.h"

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QTextEncoder;
class QTextDecoder;
QT_END_NAMESPACE

class JdicTranslator : public NetworkTranslator
{
  Q_OBJECT
  Q_DISABLE_COPY(JdicTranslator)
  typedef JdicTranslator Self;
  typedef NetworkTranslator Base;

  QNetworkReply *reply_;
  QTextDecoder *decoder_;
  QTextEncoder *encoder_;

  // - Constructions -
public:
  explicit JdicTranslator(QObject *parent = nullptr);

  static const char *dictionaryForLanguage(const QString &lang);

public slots:
  void translate(const QString &text, const QString &to, const QString &from = QString()) override
  { Q_UNUSED(from) translate(text, dictionaryForLanguage(to)); }

  void translate(const QString &text, const char *dict = 0);

protected slots:
  void processReply(QNetworkReply *reply) override;

protected:
  QByteArray postData(const QString &text, const char *dict) const;

  QString decodeText(const QByteArray &data) const;
  QByteArray encodeText(const QString &text) const;
};

#endif // JDICTRANSLATOR_H
