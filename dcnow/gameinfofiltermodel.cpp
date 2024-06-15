#include <QDebug>

#include "gameinfofiltermodel.h"

GameInfoFilterModel::GameInfoFilterModel(GameInfoModel *sourceModel, QObject *parent) :
    QSortFilterProxyModel(parent)
{
    sortMode = DefaultSort;
    setSourceModel(sourceModel);
}

QVariant GameInfoFilterModel::get(int index)
{
    GameInfoModel *source = static_cast<GameInfoModel*>(sourceModel());
    return source->get(index);
}

void GameInfoFilterModel::setSortMode(int mode)
{
    switch (mode)
    {
        case DefaultSort:
        case AlphabeticalSort:
        case NumberPlayersSort:
        {
            sortMode = static_cast<ModelSortModes>(mode);
            break;
        }
        default:
            sortMode = DefaultSort;
    }
}

int GameInfoFilterModel::getSortMode()
{
    return static_cast<int>(sortMode);
}

void GameInfoFilterModel::sortModel()
{
    beginResetModel();
    this->sort(0);
    endResetModel();
}

bool GameInfoFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    bool result = false;
    GameInfoModel *source = static_cast<GameInfoModel*>(sourceModel());
    GameInfo *leftGame = source->get(source_left.row()).value<GameInfo*>();
    GameInfo *rightGame = source->get(source_right.row()).value<GameInfo*>();

    if (sortMode == DefaultSort)
    {
        if (leftGame->getNumberOnline() > rightGame->getNumberOnline())
        {
            result = true;
        }
        else if (leftGame->getName().toLower() > rightGame->getName().toLower())
        {
            result = false;
        }
    }
    else if (sortMode == AlphabeticalSort)
    {
        if (leftGame->getName().toLower() < rightGame->getName().toLower())
        {
            result = true;
        }
    }
    else if (sortMode == NumberPlayersSort)
    {
        if (leftGame->getNumberOnline() > rightGame->getNumberOnline())
        {
            result = true;
        }
    }

    return result;
}
