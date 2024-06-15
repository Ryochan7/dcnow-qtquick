#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QStringList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QQmlEngine>

#include "userinfofiltermodel.h"
#include "userinfomodel.h"
#include "gameinfomodel.h"
#include "gameinfofiltermodel.h"

class Util : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    //Q_PROPERTY(UserInfoModel* usersModel READ getUsersModel NOTIFY usersModelChanged)
    Q_PROPERTY(UserInfoFilterModel *usersModel READ getUsersModel NOTIFY usersModelChanged)
    Q_PROPERTY(GameInfoModel *gamesModel READ getGamesModel NOTIFY gamesModelChanged)
    Q_PROPERTY(GameInfoFilterModel *gameFilterModel READ getGamesFilterModel NOTIFY gamesFilterModelChanged)
    //Q_PROPERTY(QStringList* followedGames READ getFollowedGames)

    explicit Util(QObject *parent = nullptr);
    ~Util();

    Q_INVOKABLE QString getJsonData();
    Q_INVOKABLE QString getJsonScheduleData();
    Q_INVOKABLE void addFollowedGame(QString gameName);
    Q_INVOKABLE void removeFollowGame(QString gameName);
    Q_INVOKABLE void clearFollowGames();
    Q_INVOKABLE QStringList getFollowedGames();
    Q_INVOKABLE bool isFollowingGame(QString gameName);
    Q_INVOKABLE UserInfoFilterModel *getUsersModel();
    Q_INVOKABLE GameInfoModel* getGamesModel();
    Q_INVOKABLE GameInfoFilterModel *getGamesFilterModel();
    Q_INVOKABLE void sendNotify(QString body);
    Q_INVOKABLE void sendNotify(QString summary, QString body);

    Q_INVOKABLE QVariant createUsersModel();
    Q_INVOKABLE QVariant createGamesModel();
    Q_INVOKABLE QUrl testPath();

protected:
    QString jsonData;
    QString jsonScheduleData;
    QNetworkAccessManager *manager;
    QStringList m_follwedGames;

    UserInfoModel *m_usersModel;
    UserInfoFilterModel *m_sortUsersModel;
    GameInfoModel *m_gamesModel;
    GameInfoFilterModel *m_sortGamesModel;

signals:
    void dataReady();
    void scheduleDataReady();
    void error(QNetworkReply::NetworkError replyError);
    //void usersModelChanged(UserInfoModel *model);
    void usersModelChanged(UserInfoFilterModel *model);
    void gamesModelChanged(GameInfoModel *model);
    void gamesFilterModelChanged(GameInfoModel *model);
    void updateQueued();

public slots:
    void queueRefresh();
    void refreshUsersModel();
    void refreshGamesModel();
    void queueScheduleRefresh();

private slots:
    void usersReplyFinished();
    void deleteUserModels();
    void deleteGamesModel();
    void scheduleReplyFinished();
};

#endif // UTIL_H
