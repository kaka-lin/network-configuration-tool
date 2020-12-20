#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QString program_name(argv[0]);

    // QML engine
    QQmlApplicationEngine engine;

    // Load QML scene
    engine.addImportPath(QStringLiteral("qrc:/resources"));
    engine.load(QUrl(QStringLiteral("qrc:/resources/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
