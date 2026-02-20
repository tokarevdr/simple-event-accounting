#include "SqliteEventsRepository.h"

#include <QSqlQuery>
#include <QVariant>

namespace Sea {
namespace Infrastructure {

SqliteEventsRepository::SqliteEventsRepository()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "events");
    m_db.setHostName("sea");
    m_db.setDatabaseName("events");
    m_db.setUserName("drunkdwarf");
    m_db.setPassword("6$mAkEbEeRnOtWaR6$");
    m_db.open();

    QSqlQuery query(m_db);

    query.exec(R"(CREATE TABLE IF NOT EXISTS events (
                    event_id INTEGER,
                    title TEXT NOT NULL,
                    start_date TEXT,
                    end_date TEXT,
                    PRIMARY KEY(event_id AUTOINCREMENT))
                )");
}

qint32 SqliteEventsRepository::createEvent(const Domain::Event &event)
{
    QSqlQuery query(m_db);

    query.prepare(R"(INSERT INTO events (title, start_date, end_date)
                     VALUES (:title, :start_date, :end_date))");
    query.bindValue(":title", event.title());
    query.bindValue(":start_date",
                    event.startDate().has_value() ? event.startDate().value().toString("dd.MM.yyyy")
                                                  : QVariant());
    query.bindValue(":end_date",
                    event.endDate().has_value() ? event.endDate().value().toString("dd.MM.yyyy")
                                                : QVariant());
    query.exec();

    return query.lastInsertId().toInt();
}

QVector<Domain::Event> SqliteEventsRepository::readEvents() const
{
    QVector<Domain::Event> events;
    QSqlQuery query(m_db);

    query.exec(R"(SELECT * FROM events)");

    while (query.next()) {
        Domain::Event event;
        event.setId(query.value(0).toInt());
        event.setTitle(query.value(1).toString());

        QVariant startDate = query.value(2);
        if (!startDate.isNull()) {
            event.setStartDate(QDate::fromString(startDate.toString(), "dd.MM.yyyy"));
        }

        QVariant endDate = query.value(3);
        if (!endDate.isNull()) {
            event.setEndDate(QDate::fromString(endDate.toString(), "dd.MM.yyyy"));
        }

        events.append(event);
    }

    return events;
}

bool SqliteEventsRepository::updateEvent(const Domain::Event &event)
{
    QSqlQuery query(m_db);

    query.prepare(
        R"(UPDATE events SET title = :title, start_date = :start_date, end_date = :end_date WHERE event_id = :event_id)");
    query.bindValue(":event_id", event.id());
    query.bindValue(":title", event.title());
    query.bindValue(":start_date",
                    event.startDate().has_value() ? event.startDate().value().toString("dd.MM.yyyy")
                                                  : QVariant());
    query.bindValue(":end_date",
                    event.endDate().has_value() ? event.endDate().value().toString("dd.MM.yyyy")
                                                : QVariant());

    return query.exec();
}

bool SqliteEventsRepository::deleteEvent(int id)
{
    QSqlQuery query(m_db);

    query.prepare(R"(DELETE FROM events WHERE event_id = :event_id)");
    query.bindValue(":event_id", id);

    return query.exec();
}

} // namespace Infrastructure
} // namespace Sea
