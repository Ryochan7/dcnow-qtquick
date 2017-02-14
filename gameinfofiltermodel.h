#ifndef GAMEINFOFILTERMODEL_H
#define GAMEINFOFILTERMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

#include "gameinfomodel.h"

class GameInfoFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    GameInfoFilterModel(GameInfoModel *sourceModel, QObject *parent = 0);
    Q_INVOKABLE QVariant get(int index);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

};

#endif // GAMEINFOFILTERMODEL_H
