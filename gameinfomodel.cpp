#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QListIterator>

#include "gameinfomodel.h"

struct tempGameStats {
    int numberOnline;
    QStringList players;

    tempGameStats() {
        numberOnline = 0;
    }
};

static QStringList buildGameNameList() {
    QStringList temp;
    temp << "4x4 Evolution"
         << "Alien Front Online"
         << "ChuChu Rocket"
         << "Crazy Taxi 2"
         << "Ferarri F355 Challenge"
         << "Maximum Pool"
         << "Metropolis Speed Racer"
         << "Monaco/POD Online"
         << "Phantasy Star Online"
         << "Planet Ring"
         << "Quake 3 Arena"
         << "Sega GT"
         << "Sonic Adventure"
         << "Sonic Adventure 2"
         << "Starlancer"
         << "The Next Tetris"
         << "Toy Racer"
         << "Worms World Party";

    return temp;
}

const QStringList GameInfoModel::gameNameList = buildGameNameList();

GameInfoModel::GameInfoModel(QObject *parent) :
    QAbstractListModel(parent)
{
    for (int i = 0; i < gameNameList.size(); i++)
    {
        GameInfo *tempGame = new GameInfo(this);
        QString tempName = gameNameList.at(i);
        tempGame->setName(tempName);
        m_gameList.append(tempGame);
    }
}

int GameInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_gameList.size();
}

QVariant GameInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_gameList.size())
    {
        return QVariant();
    }

    GameInfo *val = m_gameList.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return QVariant::fromValue(val->getName());
    case NumberOnlineRole:
        return QVariant::fromValue(val->getNumberOnline());
    case PlayersRole:
        return QVariant::fromValue(val->getPlayers());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> GameInfoModel::roleNames() const
{
    static QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    static bool rolesPopulated = false;
    if (!rolesPopulated)
    {
        roles[NameRole] = "name";
        roles[NumberOnlineRole] = "numberOnline";
        roles[PlayersRole] = "players";
        rolesPopulated = true;
    }

    return roles;
}

void GameInfoModel::buildModel(QString jsonData)
{
    beginResetModel();

    QHash<QString, int> lookupNameHash;
    QHash<QString, struct tempGameStats> statsHash;
    int index = 0;
    QListIterator<GameInfo*> iter(m_gameList);
    while (iter.hasNext())
    {
        GameInfo *temp = iter.next();
        temp->setNumberOnline(0);
        temp->setPlayers("");
        /*if (!lookupNameHash.contains(temp->getName()))
        {
            lookupNameHash.insert(temp->getName(), index);
        }
        */

        lookupNameHash.insert(temp->getName(), index);
        struct tempGameStats tempStats;
        statsHash.insert(temp->getName(), tempStats);
        index++;
    }

    QByteArray tempbytes = jsonData.toUtf8();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(tempbytes);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArray = jsonObj.value("users").toArray();
    for (int i = 0; i < jsonArray.size(); i++)
    {
        QJsonObject userObject = jsonArray.at(i).toObject();

        QString username = userObject.value("username").toString();
        QString currentGame = userObject.value("current_game").toString();
        bool online = userObject.value("online").toBool();

        if (statsHash.contains(currentGame) && online)
        {
            //int gameIndex = lookupNameHash.value(currentGame);
            struct tempGameStats tempStats = statsHash.value(currentGame);
            tempStats.numberOnline++;
            tempStats.players.append(username);
            statsHash.insert(currentGame, tempStats);
            //GameInfo *tempInfo = m_gameList.at(gameIndex);
            //tempInfo->setNumberOnline(tempInfo->getNumberOnline() + 1);
            //tempInfo->setPlayers(username);
        }
    }

    iter.toFront();
    while (iter.hasNext())
    {
        GameInfo *temp = iter.next();
        struct tempGameStats gameStats = statsHash.value(temp->getName());
        temp->setNumberOnline(gameStats.numberOnline);
        temp->setPlayers(gameStats.players.join(", "));
    }

    endResetModel();
}

void GameInfoModel::clear()
{
    beginResetModel();

    QListIterator<GameInfo*> iter(m_gameList);
    while (iter.hasNext())
    {
        GameInfo *temp = iter.next();
        if (temp)
        {
            delete temp;
            temp = 0;
        }
    }

    m_gameList.clear();

    endResetModel();
}

QVariant GameInfoModel::get(int index)
{
    GameInfo *result = 0;
    if (index >= 0 && index < m_gameList.size())
    {
        result = m_gameList.at(index);
    }

    return QVariant::fromValue(result);
}
