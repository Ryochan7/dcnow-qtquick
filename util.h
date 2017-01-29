#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Util : public QObject
{
    Q_OBJECT
public:
    explicit Util(QObject *parent = 0);

    Q_INVOKABLE QString getJsonData();

protected:
    QString jsonData;
    QNetworkAccessManager *manager;

signals:
    void dataReady();
    void error(QNetworkReply::NetworkError replyError);

public slots:
    void queueRefresh();

private slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // UTIL_H
