#include <QGuiApplication>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Ryochan7");
    app.setOrganizationDomain("kramericaindustries.com");
    app.setApplicationName("Dreamcast Now");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/dcnow/dcnow/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    //engine.addImportPath(":/");
    engine.load(url);

    return app.exec();
}
