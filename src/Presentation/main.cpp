#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>

#include "Repositories/SqliteEventsRepository.h"

int main(
    int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("sea");
    db.setDatabaseName("events");
    db.setUserName("drunkdwarf");
    db.setPassword("6$mAkEbEeRnOtWaR6$");
    db.open();

    Sea::Infrastructure::SqliteEventsRepository repo;

    auto events = repo.readEvents();

    for (auto ev : events) {
        qDebug() << ev.id() << ev.title()
                 << (ev.startDate().has_value() ? ev.startDate().value() : QDate())
                 << (ev.endDate().has_value() ? ev.endDate().value() : QDate());
    }

    QQmlApplicationEngine engine;
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
