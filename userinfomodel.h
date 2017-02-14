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

    Q_INVOKABLE void buildModel(QString jsonData);
    Q_INVOKABLE void clear();
    Q_INVOKABLE UserInfo* getInfo(int row);

protected:
    void setNumberOnline(int numOnline);
    void calculateNumberOnline();

    QHash<QString, UserInfo*> m_data;
    QList<UserInfo*> m_indexes;
    int m_numberOnline;

signals:
    void numberOnlineChanged(int numOnline);

};

#endif // USERINFOMODEM_H
