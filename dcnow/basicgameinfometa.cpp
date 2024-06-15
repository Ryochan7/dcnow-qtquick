#include "basicgameinfometa.h"

BasicGameInfoMeta::BasicGameInfoMeta(QObject *parent) : QObject(parent)
{

}

QString BasicGameInfoMeta::getId()
{
    return gameId;
}

void BasicGameInfoMeta::setId(QString id)
{
    if (id != gameId)
    {
        gameId = id;
    }
}

QString BasicGameInfoMeta::getDescription()
{
    return description;
}

void BasicGameInfoMeta::setDescription(QString desc)
{
    if (desc != description)
    {
        description = desc;
    }
}
