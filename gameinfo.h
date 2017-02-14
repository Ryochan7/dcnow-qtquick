#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QObject>
#include <QString>

class GameInfo : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int numberOnline READ getNumberOnline WRITE setNumberOnline NOTIFY numberOnlineChanged)
    Q_PROPERTY(QString players READ getPlayers WRITE setPlayers NOTIFY playersChanged)

    explicit GameInfo(QObject *parent = 0);
    QString getName();
    void setName(QString name);
    Q_INVOKABLE int getNumberOnline();
    void setNumberOnline(int numOnline);
    QString getPlayers();
    void setPlayers(QString players);

protected:
    QString m_name;
    int m_numberOnline;
    QString m_players;

signals:
    void nameChanged(QString name);
    void numberOnlineChanged(int numberOnline);
    void playersChanged(QString players);

public slots:
};

Q_DECLARE_METATYPE(GameInfo*)

#endif // GAMEINFO_H
