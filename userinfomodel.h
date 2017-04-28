#ifndef USERINFOMODEM_H
#define USERINFOMODEM_H

#include <QObject>
#include <QAbstractListModel>
#include <QString>
#include <QHash>
#include <QByteArray>

#include "userinfo.h"

class UserInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    Q_PROPERTY(int numberOnline READ getNumberOnline NOTIFY numberOnlineChanged)
    Q_PROPERTY(int numberPlayers READ getNumberPlayers NOTIFY numberPlayersChanged)

    enum UserInfoRoles {
        NameRole = Qt::UserRole + 1,
        OnlineRole,
        CurrentGameRole,
    };

    Q_ENUM(UserInfoRoles)

    UserInfoModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;

    int getNumberOnline();
    int getNumberPlayers();

    Q_INVOKABLE void buildModel(QString jsonData);
    Q_INVOKABLE void clear();
    Q_INVOKABLE UserInfo* getInfo(int row);

protected:
    void setNumberOnline(int numOnline);
    void setNumberPlayers(int numPlayers);
    void calculateNumberOnline();

    QHash<QString, UserInfo*> m_data;
    QList<UserInfo*> m_indexes;
    int m_numberOnline;
    int m_numberPlayers;

signals:
    void numberOnlineChanged(int numOnline);
    void numberPlayersChanged(int numPlayers);

};

#endif // USERINFOMODEM_H
