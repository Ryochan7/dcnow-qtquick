#include <QDebug>
#include <QHashIterator>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "userinfomodel.h"

UserInfoModel::UserInfoModel(QObject *parent) :
    QAbstractListModel(parent)
{

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
    for (int i = 0; i < jsonArray.size(); i++)
    {
        QJsonObject userObject = jsonArray.at(i).toObject();
        UserInfo *temp = new UserInfo(this);
        temp->setName(userObject.value("username").toString());
        temp->setCurrentGame(userObject.value("current_game").toString());
        temp->setCurrentlyOnline(userObject.value("online").toBool());

        m_data.insert(temp->getName(), temp);
        m_indexes.append(temp);
    }

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
    endResetModel();
}

int UserInfoModel::getNumberOnline()
{
    return m_numberOnline;
}

void UserInfoModel::setNumberOnline(int numOnline)
{
    if (numOnline != m_numberOnline)
    {
        m_numberOnline = numOnline;
        emit numberOnlineChanged(numOnline);
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
