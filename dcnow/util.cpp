#include <QDebug>
#include <QProcess>
#include <QUrl>

#include "util.h"

Util::Util(QObject *parent)
    : QObject{parent}
{
    m_usersModel = nullptr;
    m_sortUsersModel = nullptr;
    m_gamesModel = nullptr;
    m_sortGamesModel = nullptr;

    manager = new QNetworkAccessManager(this);

    connect(this, &Util::dataReady, this, &Util::refreshUsersModel);
    connect(this, &Util::dataReady, this, &Util::refreshGamesModel);

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
    connect(reply, &QNetworkReply::finished, this, &Util::usersReplyFinished);
    emit updateQueued();
}

void Util::queueScheduleRefresh()
{
    QNetworkRequest request(QUrl("http://10.0.0.127:8080/extramedia/hamfest.json"));
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &Util::scheduleReplyFinished);
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
#endif
}

QVariant Util::createUsersModel()
{
    m_usersModel = new UserInfoModel();
    m_sortUsersModel = new UserInfoFilterModel(m_usersModel);
    connect(m_sortUsersModel, &UserInfoFilterModel::destroyed, m_usersModel, &UserInfoModel::deleteLater);
    connect(m_sortUsersModel, &UserInfoFilterModel::destroyed, this, &Util::deleteUserModels);
    refreshUsersModel();
    return QVariant::fromValue(m_sortUsersModel);
}

QVariant Util::createGamesModel()
{
    m_gamesModel = new GameInfoModel();
    m_sortGamesModel = new GameInfoFilterModel(m_gamesModel);
    connect(m_sortGamesModel, &GameInfoFilterModel::destroyed, m_gamesModel, &GameInfoModel::deleteLater);
    connect(m_sortGamesModel, &GameInfoFilterModel::destroyed, this, &Util::deleteGamesModel);
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


