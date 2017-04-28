#ifndef USERINFOFILTERMODEL_H
#define USERINFOFILTERMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

#include "userinfomodel.h"

class UserInfoFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    Q_PROPERTY(int numberOnline READ getNumberOnline NOTIFY numberOnlineChanged)
    Q_PROPERTY(int numberPlayers READ getNumberPlayers NOTIFY numberPlayersChanged)

    UserInfoFilterModel(UserInfoModel *sourceModel, QObject *parent = 0);
    Q_INVOKABLE int getNumberOnline();
    Q_INVOKABLE int getNumberPlayers();

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

signals:
    void numberOnlineChanged(int numOnline);
    void numberPlayersChanged(int numPlayers);

private slots:
    void propogateNumberOnline(int numOnline);
    void propogateNumberPlayers(int numPlayers);
};

#endif // USERINFOFILTERMODEL_H
