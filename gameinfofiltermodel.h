#ifndef GAMEINFOFILTERMODEL_H
#define GAMEINFOFILTERMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

#include "gameinfomodel.h"

class GameInfoFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    enum ModelSortModes {
        DefaultSort = 0,
        AlphabeticalSort,
        NumberPlayersSort,
    };

    GameInfoFilterModel(GameInfoModel *sourceModel, QObject *parent = 0);
    Q_INVOKABLE QVariant get(int index);
    Q_INVOKABLE void setSortMode(int mode);
    Q_INVOKABLE int getSortMode();
    Q_INVOKABLE void sortModel();

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

    ModelSortModes sortMode;
};

#endif // GAMEINFOFILTERMODEL_H
