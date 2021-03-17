#include <QDebug>
#include <QProcess>
#include <QUrl>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniObject>
#endif

#include "util.h"

Util::Util(QObject *parent) : QObject(parent)
{
    m_usersModel = nullptr;
    m_sortUsersModel = nullptr;
    m_gamesModel = nullptr;
    m_sortGamesModel = nullptr;

    manager = new QNetworkAccessManager(this);
    //connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(this, SIGNAL(dataReady()), this, SLOT(refreshUsersModel()));
    connect(this, SIGNAL(dataReady()), this, SLOT(refreshGamesModel()));

    queueRefresh();
}

Util::~Util()
{
    if (m_sortUsersModel)
    {
        delete m_sortUsersModel;
        m_sortUsersModel = nullptr;
    }

    if (m_usersModel)
    {
        delete m_usersModel;
        m_usersModel = nullptr;
    }

    if (m_sortGamesModel)
    {
        delete m_sortGamesModel;
        m_sortGamesModel = nullptr;
    }

    if (m_gamesModel)
    {
        delete m_gamesModel;
        m_gamesModel = nullptr;
    }
}

QString Util::getJsonData()
{
    return jsonData;
}

QString Util::getJsonScheduleData()
{
    return jsonScheduleData;
}

void Util::usersReplyFinished()
{
    QNetworkReply *reply = (QNetworkReply*)QObject::sender();
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

void Util::scheduleReplyFinished()
{
    QNetworkReply *reply = (QNetworkReply*)QObject::sender();
    if (reply->error() == QNetworkReply::NoError)
    {
        jsonScheduleData = QString(reply->readAll());

        emit scheduleDataReady();
    }
    else
    {
        emit error(reply->error());
    }

    reply->deleteLater();
}

void Util::queueRefresh()
{
    QNetworkRequest request(QUrl("http://10.0.0.127:8080/extramedia/dcnow_users.json"));
    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(usersReplyFinished()));
    emit updateQueued();
}

void Util::queueScheduleRefresh()
{
    QNetworkRequest request(QUrl("http://10.0.0.127:8080/extramedia/hamfest.json"));
    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(scheduleReplyFinished()));
}

void Util::addFollowedGame(QString gameName)
{
    if (!m_follwedGames.contains(gameName))
    {
        m_follwedGames.append(gameName);
    }
}

QStringList Util::getFollowedGames()
{
    return m_follwedGames;
}

void Util::removeFollowGame(QString gameName)
{
    m_follwedGames.removeAll(gameName);
}

void Util::clearFollowGames()
{
    m_follwedGames.clear();
}

bool Util::isFollowingGame(QString gameName)
{
    bool result = m_follwedGames.contains(gameName);
    return result;
}

UserInfoFilterModel* Util::getUsersModel()
{
    return m_sortUsersModel;
}

void Util::refreshUsersModel()
{
    if (m_usersModel)
    {
        m_usersModel->buildModel(jsonData);
        m_sortUsersModel->sort(0);
    }
}

void Util::refreshGamesModel()
{
    if (m_gamesModel)
    {
        m_gamesModel->buildModel(jsonData);
        m_sortGamesModel->sort(0);
    }
}

GameInfoModel* Util::getGamesModel()
{
    return m_gamesModel;
}

GameInfoFilterModel* Util::getGamesFilterModel()
{
    return m_sortGamesModel;
}

void Util::sendNotify(QString body)
{
    sendNotify("Dreamcast Now", body);
}

void Util::sendNotify(QString summary, QString body)
{
#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
    QProcess::startDetached("notify-send",
                            QStringList() << "-a" << "Dreamcast Now" << "-i"
                            << "/home/ryochan7/Downloads/feelsguy.jpeg" << summary << body);

#elif defined(Q_OS_ANDROID)

    QAndroidJniObject javaNotificationSummary = QAndroidJniObject::fromString(summary);
    QAndroidJniObject javaNotificationBody = QAndroidJniObject::fromString(body);
    QAndroidJniObject::callStaticMethod<void>("org/ryochan7/dcnow/NotificationClient",
                                              "notify",
                                              "(Ljava/lang/String;Ljava/lang/String;)V",
                                              javaNotificationSummary.object<jstring>(),
                                              javaNotificationBody.object<jstring>());
#endif
}

QVariant Util::createUsersModel()
{
    m_usersModel = new UserInfoModel();
    m_sortUsersModel = new UserInfoFilterModel(m_usersModel);
    connect(m_sortUsersModel, SIGNAL(destroyed(QObject*)), m_usersModel, SLOT(deleteLater()));
    connect(m_sortUsersModel, SIGNAL(destroyed(QObject*)), this, SLOT(deleteUserModels()));
    refreshUsersModel();
    return QVariant::fromValue(m_sortUsersModel);
}

QVariant Util::createGamesModel()
{
    m_gamesModel = new GameInfoModel();
    m_sortGamesModel = new GameInfoFilterModel(m_gamesModel);
    connect(m_sortGamesModel, SIGNAL(destroyed(QObject*)), m_gamesModel, SLOT(deleteLater()));
    connect(m_sortGamesModel, SIGNAL(destroyed(QObject*)), this, SLOT(deleteGamesModel()));
    refreshGamesModel();
    return QVariant::fromValue(m_sortGamesModel);
}

void Util::deleteUserModels()
{
    m_usersModel = nullptr;
    m_sortUsersModel = nullptr;
}

void Util::deleteGamesModel()
{
    m_gamesModel = nullptr;
    m_sortGamesModel = nullptr;
}


QUrl Util::testPath()
{
    return QUrl::fromLocalFile("/home/ryochan7/hamfest.txt");
}
