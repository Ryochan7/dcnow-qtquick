#include <QDebug>

#include "userinfofiltermodel.h"

UserInfoFilterModel::UserInfoFilterModel(UserInfoModel *sourceModel, QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setSourceModel(sourceModel);
    connect(sourceModel, &UserInfoModel::numberOnlineChanged, this, &UserInfoFilterModel::propogateNumberOnline);
    connect(sourceModel, &UserInfoModel::numberPlayersChanged, this, &UserInfoFilterModel::propogateNumberPlayers);
}

int UserInfoFilterModel::getNumberOnline()
{
    int result = 0;
    if (sourceModel())
    {
        result = static_cast<UserInfoModel*>(sourceModel())->getNumberOnline();
    }

    return result;
}

int UserInfoFilterModel::getNumberPlayers()
{
    int result = 0;
    if (sourceModel())
    {
        result = static_cast<UserInfoModel*>(sourceModel())->getNumberPlayers();
    }

    return result;
}

void UserInfoFilterModel::propogateNumberOnline(int numOnline)
{
    emit numberOnlineChanged(numOnline);
}

void UserInfoFilterModel::propogateNumberPlayers(int numPlayers)
{
    emit numberPlayersChanged(numPlayers);
}

bool UserInfoFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    bool result = false;

    UserInfoModel *model = static_cast<UserInfoModel*>(sourceModel());
    UserInfo *leftUser = model->getInfo(source_left.row());
    UserInfo *rightUser = model->getInfo(source_right.row());

    if (leftUser->isCurrentlyOnline() != rightUser->isCurrentlyOnline())
    {
        if (leftUser->isCurrentlyOnline())
        {
            result = true;
        }
    }
    else if (leftUser->getName().toLower() < rightUser->getName().toLower())
    {
        result = true;
    }
    else if (leftUser->getName().toLower() > leftUser->getName().toLower())
    {
        result = false;
    }

    return result;
}
