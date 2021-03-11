#include "userinfo.h"

UserInfo::UserInfo(QObject *parent) : QObject(parent)
{

}

QString UserInfo::getName()
{
    return m_name;
}

void UserInfo::setName(QString name)
{
    if (name != m_name)
    {
        m_name = name;
        emit nameChanged(name);
    }
}

bool UserInfo::isCurrentlyOnline()
{
    return m_currentlyOnline;
}

void UserInfo::setCurrentlyOnline(bool online)
{
    if (online != m_currentlyOnline)
    {
        m_currentlyOnline = online;
        emit currentlyOnlineChanged(online);
    }
}

QString UserInfo::getCurrentGame()
{
    return m_currentGame;
}

void UserInfo::setCurrentGame(QString game)
{
    if (game != m_currentGame)
    {
        m_currentGame = game;
        emit currentGameChanged(game);
    }
}

QString UserInfo::getGamerLevel()
{
    return m_gamerLevel;
}

void UserInfo::setGamerLevel(QString level)
{
    if (level != m_gamerLevel)
    {
        m_gamerLevel = level;
        emit gamerLevelChanged(level);
    }
}

QVariantList UserInfo::getRecentGames()
{
    QVariantList returnList;
    for (int i = 0; i < m_recentGameInfo.size(); i++)
    {
        returnList.append(QVariant::fromValue(m_recentGameInfo.at(i)));
    }

    return returnList;
}

void UserInfo::setRecentGames(QList<BasicGameInfoMeta*> &gameList)
{
    m_recentGameInfo = gameList;
}
