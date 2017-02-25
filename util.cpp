#include <QDebug>
#include <QProcess>
#include <QUrl>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniObject>
#endif

#include "util.h"

Util::Util(QObject *parent) : QObject(parent)
{
    m_usersModel = 0;
    m_sortUsersModel = 0;
    m_gamesModel = 0;

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(this, SIGNAL(dataReady()), this, SLOT(refreshUsersModel()));
    connect(this, SIGNAL(dataReady()), this, SLOT(refreshGamesModel()));

    queueRefresh();
}

Util::~Util()
{
    if (m_sortUsersModel)
    {
        delete m_sortUsersModel;
        m_sortUsersModel = 0;
    }

    if (m_usersModel)
    {
        delete m_usersModel;
        m_usersModel = 0;
    }

    if (m_sortGamesModel)
    {
        delete m_sortGamesModel;
        m_sortGamesModel = 0;
    }

    if (m_gamesModel)
    {
        delete m_gamesModel;
        m_gamesModel = 0;
    }
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
    emit updateQueued();
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
    m_usersModel = 0;
    m_sortUsersModel = 0;
}

void Util::deleteGamesModel()
{
    m_gamesModel = 0;
    m_sortGamesModel = 0;
}


QUrl Util::testPath()
{
    return QUrl::fromLocalFile("/home/ryochan7/hamfest.txt");
}
