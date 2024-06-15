#include <QDebug>
#include <QHashIterator>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariantList>

#include "userinfomodel.h"

UserInfoModel::UserInfoModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_numberOnline = 0;
    m_numberPlayers = 0;
}

int UserInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_data.size();
}

QVariant UserInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_data.size())
    {
        return QVariant();
    }

    UserInfo *val = m_indexes.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return QVariant::fromValue(val->getName());
    case OnlineRole:
        return QVariant::fromValue(val->isCurrentlyOnline());
    case CurrentGameRole:
        return QVariant::fromValue(val->getCurrentGame());
    case GamerLevelRole:
        return QVariant::fromValue(val->getGamerLevel());
    case RecentGames:
        return QVariant::fromValue(val->getRecentGames());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> UserInfoModel::roleNames() const
{
    static QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    static bool rolesPopulated = false;
    if (!rolesPopulated)
    {
        roles[NameRole] = "name";
        roles[OnlineRole] = "online";
        roles[CurrentGameRole] = "current_game";
        roles[GamerLevelRole] = "level";
        roles[RecentGames] = "recent_games";
        rolesPopulated = true;
    }

    return roles;
}

void UserInfoModel::buildModel(QString jsonData)
{
    beginResetModel();

    QHashIterator<QString, UserInfo*> iter(m_data);
    while (iter.hasNext())
    {
        iter.next();
        UserInfo *temp = iter.value();
        if (temp)
        {
            delete temp;
            temp = 0;
        }
    }

    m_data.clear();
    m_indexes.clear();

    QByteArray tempbytes = jsonData.toUtf8();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(tempbytes);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArray = jsonObj.value("users").toArray();
    int arsize = jsonArray.size();
    for (int i = 0; i < arsize; i++)
    {
        QJsonObject userObject = jsonArray.at(i).toObject();
        UserInfo *temp = new UserInfo(this);
        temp->setName(userObject.value("username").toString());
        temp->setCurrentGame(userObject.value("current_game_display").toString());
        temp->setCurrentlyOnline(userObject.value("online").toBool());
        temp->setGamerLevel(userObject.value("level").toString());
        QList<BasicGameInfoMeta*> recentGameList;
        QJsonArray recentGamesArray = userObject.value("recent_games").toArray();
        for (int j = 0; j < recentGamesArray.size(); j++)
        {
            QJsonObject recentGame = recentGamesArray.at(j).toObject();
            BasicGameInfoMeta* meta = new BasicGameInfoMeta(temp);
            meta->setId(recentGame.value("id").toString());
            meta->setDescription(recentGame.value("description").toString());
            recentGameList.append(meta);
        }

        temp->setRecentGames(recentGameList);

        m_data.insert(temp->getName(), temp);
        m_indexes.append(temp);
    }

    setNumberPlayers(arsize);
    calculateNumberOnline();

    endResetModel();
}

void UserInfoModel::clear()
{
    beginResetModel();

    QHashIterator<QString, UserInfo*> iter(m_data);
    while (iter.hasNext())
    {
        iter.next();
        UserInfo *temp = iter.value();
        if (temp)
        {
            delete temp;
            temp = 0;
        }
    }

    m_data.clear();

    m_indexes.clear();
    setNumberOnline(0);
    setNumberPlayers(0);
    endResetModel();
}

int UserInfoModel::getNumberOnline()
{
    return m_numberOnline;
}

int UserInfoModel::getNumberPlayers()
{
    return m_numberPlayers;
}

void UserInfoModel::setNumberOnline(int numOnline)
{
    if (numOnline != m_numberOnline)
    {
        m_numberOnline = numOnline;
        emit numberOnlineChanged(numOnline);
    }
}

void UserInfoModel::setNumberPlayers(int numPlayers)
{
    if (numPlayers != m_numberPlayers)
    {
        m_numberPlayers = numPlayers;
        emit numberPlayersChanged(numPlayers);
    }
}

void UserInfoModel::calculateNumberOnline()
{
    int result = 0;

    QHashIterator<QString, UserInfo*> iter(m_data);
    while (iter.hasNext())
    {
        iter.next();
        UserInfo *temp = iter.value();
        if (temp->isCurrentlyOnline())
        {
            result++;
        }
    }

    setNumberOnline(result);
}

UserInfo* UserInfoModel::getInfo(int row)
{
    UserInfo *result = 0;
    result = m_indexes.at(row);
    return result;
}
