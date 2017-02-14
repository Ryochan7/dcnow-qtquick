#ifndef GAMEINFOMODEL_H
#define GAMEINFOMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include <QList>
#include <QStringList>
#include <QVariant>

#include "gameinfo.h"

class GameInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum GameInfoRoles {
        NameRole = Qt::UserRole + 1,
        NumberOnlineRole,
        PlayersRole,
    };

    Q_ENUM(GameInfoRoles)

    explicit GameInfoModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void buildModel(QString jsonData);
    Q_INVOKABLE void clear();
    Q_INVOKABLE QVariant get(int index);

protected:
    QList<GameInfo*> m_gameList;
    static const QStringList gameNameList;

};

#endif // GAMEINFOMODEL_H
