#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>
#include <QVariantList>
#include "basicgameinfometa.h"

class UserInfo : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool currentlyOnline READ isCurrentlyOnline WRITE setCurrentlyOnline NOTIFY currentlyOnlineChanged)
    Q_PROPERTY(QString currentGame READ getCurrentGame WRITE setCurrentGame NOTIFY currentGameChanged)
    Q_PROPERTY(QString gamerLevel READ getGamerLevel WRITE setGamerLevel NOTIFY gamerLevelChanged)
    Q_PROPERTY(QVariantList recentGames READ getRecentGames CONSTANT)

    explicit UserInfo(QObject *parent = 0);

    QString getName();
    void setName(QString name);
    bool isCurrentlyOnline();
    void setCurrentlyOnline(bool online);
    QString getCurrentGame();
    void setCurrentGame(QString game);
    QString getGamerLevel();
    void setGamerLevel(QString level);
    QVariantList getRecentGames();
    void setRecentGames(QList<BasicGameInfoMeta*> &gameList);

protected:
    QString m_name;
    bool m_currentlyOnline;
    QString m_currentGame;
    QString m_gamerLevel;
    QList<BasicGameInfoMeta*> m_recentGameInfo;

signals:
    void nameChanged(QString name);
    void currentlyOnlineChanged(bool status);
    void currentGameChanged(QString game);
    void gamerLevelChanged(QString level);

public slots:
};

#endif // USERINFO_H
