#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "threads/main_thread.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QString program_name(argv[0]);

    // QML engine
    QQmlApplicationEngine engine;

    // QML context
    MainThread *mainApp = new MainThread;
    engine.rootContext()->setContextProperty("mainApp", mainApp);
    mainApp->prepareStart();

    // Load QML scene
    engine.addImportPath(QStringLiteral("qrc:/"));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
