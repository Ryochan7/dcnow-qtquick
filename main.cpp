//#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QDir>
#include <QList>

#include "util.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    app.setOrganizationName("Ryochan7");
    app.setOrganizationDomain("kramericaindustries.com");
    app.setApplicationName("Dreamcast Now");

    QQmlApplicationEngine engine;
    Util utilObj;
    //QSettings settings2;
    //qDebug() << settings2.value("inGames") << " " << settings2.value("notifyGameList").toList();
    //QSettings settings(QString(QDir::homePath()).append("/").append("dctest.ini"), QSettings::IniFormat);

    engine.rootContext()->setContextProperty("util", &utilObj);
    //engine.rootContext()->setContextProperty("settings", &settings);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
