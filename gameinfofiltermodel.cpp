#include <QDebug>

#include "gameinfofiltermodel.h"

GameInfoFilterModel::GameInfoFilterModel(GameInfoModel *sourceModel, QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setSourceModel(sourceModel);
}

QVariant GameInfoFilterModel::get(int index)
{
    GameInfoModel *source = static_cast<GameInfoModel*>(sourceModel());
    return source->get(index);
}

bool GameInfoFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    bool result = false;
    GameInfoModel *source = static_cast<GameInfoModel*>(sourceModel());
    GameInfo *leftGame = source->get(source_left.row()).value<GameInfo*>();
    GameInfo *rightGame = source->get(source_right.row()).value<GameInfo*>();

    if (leftGame->getNumberOnline() > rightGame->getNumberOnline())
    {
        result = true;
    }
    else if (leftGame->getName().toLower() > rightGame->getName().toLower())
    {
        result = false;
    }

    return result;
}
