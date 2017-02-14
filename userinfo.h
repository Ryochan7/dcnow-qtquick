#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>

class UserInfo : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool currentlyOnline READ isCurrentlyOnline WRITE setCurrentlyOnline NOTIFY currentlyOnlineChanged)
    Q_PROPERTY(QString currentGame READ getCurrentGame WRITE setCurrentGame NOTIFY currentGameChanged)
    explicit UserInfo(QObject *parent = 0);

    QString getName();
    void setName(QString name);
    bool isCurrentlyOnline();
    void setCurrentlyOnline(bool online);
    QString getCurrentGame();
    void setCurrentGame(QString game);

protected:
    QString m_name;
    bool m_currentlyOnline;
    QString m_currentGame;

signals:
    void nameChanged(QString name);
    void currentlyOnlineChanged(bool status);
    void currentGameChanged(QString game);

public slots:
};

#endif // USERINFO_H
