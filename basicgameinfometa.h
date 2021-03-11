#ifndef BASICGAMEINFOMETA_H
#define BASICGAMEINFOMETA_H

#include <QObject>

class BasicGameInfoMeta : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString id READ getId CONSTANT)
    Q_PROPERTY(QString desc READ getDescription CONSTANT)

    explicit BasicGameInfoMeta(QObject *parent = nullptr);

    QString getId();
    void setId(QString id);
    QString getDescription();
    void setDescription(QString desc);

protected:
    QString gameId;
    QString description;

signals:

};


#endif // BASICGAMEINFOMETA_H
