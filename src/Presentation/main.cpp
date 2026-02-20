#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Repositories/SqliteEventsRepository.h"
#include "ViewModels/EventsViewModel.h"

int main(
    int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    Sea::Infrastructure::SqliteEventsRepository repo;
    Sea::Presentation::AsyncExecutor asyncExecutor;
    Sea::Presentation::EventsViewModel eventsViewModel(asyncExecutor, repo);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("eventsVm", &eventsViewModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
