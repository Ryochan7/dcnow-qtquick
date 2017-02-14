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

    UserInfoFilterModel(UserInfoModel *sourceModel, QObject *parent = 0);
    Q_INVOKABLE int getNumberOnline();

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

signals:
    void numberOnlineChanged(int numOnline);

private slots:
    void propogateNumberOnline(int numOnline);
};

#endif // USERINFOFILTERMODEL_H
