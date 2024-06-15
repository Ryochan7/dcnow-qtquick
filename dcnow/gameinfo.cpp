#include "gameinfo.h"

GameInfo::GameInfo(QObject *parent) : QObject(parent)
{
    m_numberOnline = 0;
}

QString GameInfo::getName()
{
    return m_name;
}

void GameInfo::setName(QString name)
{
    if (name != m_name)
    {
        m_name = name;
        emit nameChanged(name);
    }
}

int GameInfo::getNumberOnline()
{
    return m_numberOnline;
}

void GameInfo::setNumberOnline(int numOnline)
{
    if (numOnline != m_numberOnline)
    {
        m_numberOnline = numOnline;
        emit numberOnlineChanged(numOnline);
    }
}

QString GameInfo::getPlayers()
{
    return m_players;
}

void GameInfo::setPlayers(QString players)
{
    if (players != m_players)
    {
        m_players = players;
        emit playersChanged(players);
    }
}
