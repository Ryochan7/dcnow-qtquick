#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>

#include "util.h"

Util::Util(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    queueRefresh();

    /*QStringList pathList;
#ifdef Q_OS_ANDROID
    pathList << "/storage/emulated/legacy";
#else
    pathList << QDir::homePath();
#endif

    pathList << "dcnow_users.json";

    QFile temp(pathList.join(QDir::separator()));
    QFileInfo tempInfo(temp);

    if (tempInfo.exists() && tempInfo.isReadable())
    {
        temp.open(QFile::ReadOnly | QFile::Text);
        QTextStream tempStream(&temp);
        jsonData = tempStream.readAll();
    }
    */
}

QString Util::getJsonData()
{
    return jsonData;
}

void Util::replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        jsonData = QString(reply->readAll());
        emit dataReady();
    }
    else
    {
        emit error(reply->error());
    }

    reply->deleteLater();
}

void Util::queueRefresh()
{
    QNetworkRequest request(QUrl("https://dl.dropboxusercontent.com/u/31073509/dcnow_users.json"));
    manager->get(request);
}
