#include <functional>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSharedPointer>

#include <flux_qt/dispatcher.h>
#include <action/actionprovider.h>
#include <middleware/ftpmiddleware.h>
#include <store/mainstore.h>

using namespace flux_qt;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<ActionProvider>("Flux", 1, 0, "ActionProvider",
                                             [](QQmlEngine* engine, QJSEngine* scriptEngine) -> QObject* {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        QQmlEngine::setObjectOwnership(&ActionProvider::instance(), QQmlEngine::CppOwnership);
        return &ActionProvider::instance();
    });

    qmlRegisterSingletonType<MainStore>("Flux", 1, 0, "MainStore",
                                        [](QQmlEngine* engine, QJSEngine* scriptEngine) -> QObject* {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        QQmlEngine::setObjectOwnership(&MainStore::instance(), QQmlEngine::CppOwnership);
        return &MainStore::instance();
    });

    Dispatcher::instance().registerMiddleware(new FtpMiddleware);
    Dispatcher::instance().registerStore(QSharedPointer<flux_qt::Store>(&MainStore::instance(),
                                                                        [](flux_qt::Store*) {}));

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
