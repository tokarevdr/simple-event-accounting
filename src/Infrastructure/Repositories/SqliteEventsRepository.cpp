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

    // PRAGMA foreign_keys = ON; ???

    query.exec(R"(CREATE TABLE IF NOT EXISTS events (
                    event_id INTEGER,
                    title TEXT NOT NULL,
                    start_date TEXT,
                    end_date TEXT,
                    PRIMARY KEY(event_id AUTOINCREMENT))
                )");

    query.exec(R"(CREATE TABLE IF NOT EXISTS participants (
                    participant_id INTEGER,
                    name TEXT NOT NULL,
                    PRIMARY KEY(participant_id AUTOINCREMENT))
                )");

    query.exec(R"(CREATE TABLE IF NOT EXISTS receipts (
                    receipt_id INTEGER,
                    event_id INTEGER,
                    participant_id INTEGER,
                    title TEXT NOT NULL,
                    purchase_datetime INTEGER NOT NULL,
                    PRIMARY KEY(receipt_id AUTOINCREMENT))
                    FOREIGN KEY (event_id) REFERENCES events(event_id) ON DELETE CASCADE
                    FOREIGN KEY (participant_id) REFERENCES participants(participant_id) ON DELETE SET NULL
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

qint32 SqliteEventsRepository::createReceipt(const Domain::Receipt &receipt)
{
    QSqlQuery query(m_db);

    query.prepare(R"(INSERT INTO receipts (event_id, participant_id, title, purchase_datetime)
                     VALUES (:event_id, :participant_id, :title, :purchase_datetime))");
    query.bindValue(":event_id", receipt.eventId());
    query.bindValue(":participant_id",
                    receipt.buyer().has_value() ? receipt.buyer().value().id() : QVariant());
    query.bindValue(":title", receipt.title());
    query.bindValue(":purchase_datetime", receipt.purchaseDateTime().toSecsSinceEpoch());
    query.exec();

    return query.lastInsertId().toInt();
}

QVector<Domain::Receipt> SqliteEventsRepository::readReceipts(qint32 eventId) const
{
    QSqlQuery query(m_db);
    QVector<Domain::Receipt> receipts;

    query.prepare(
        R"(SELECT r.receipt_id, r.event_id, r.title, r.purchase_datetime, p.participant_id, p.name
            FROM receipts r WHERE R.event_id = :event_id
            JOIN participants p ON r.participant_id = p.participant_id
            OREDER BY r.purchase_datetime DESC)");
    query.bindValue(":event_id", eventId);
    query.exec();

    while (query.next()) {
        Domain::Receipt receipt;
        receipt.setId(query.value(0).toInt());
        receipt.setEventId(query.value(1).toInt());
        receipt.setTitle(query.value(2).toString());
        receipt.setPurchaseDateTime(QDateTime::fromSecsSinceEpoch(query.value(3).toLongLong()));

        Domain::Participant participant;
        participant.setId(query.value(4).toInt());
        participant.setName(query.value(5).toString());

        receipt.setBuyer(participant);

        receipts.append(receipt);
    }

    return receipts;
}

bool SqliteEventsRepository::updateReceipt(const Domain::Receipt &receipt) {}

bool SqliteEventsRepository::deleteReceipt(qint32 id) {}

qint32 SqliteEventsRepository::createParticipant(const Domain::Participant &participant)
{
    QSqlQuery query(m_db);

    query.prepare(R"(INSERT INTO participants (name)
                    VALUES (:name))");

    query.bindValue(":name", participant.name());

    query.exec();

    return query.lastInsertId().toInt();
}

QVector<Domain::Participant> SqliteEventsRepository::readParticipants() const
{
    QSqlQuery query(m_db);
    QVector<Domain::Participant> participants;

    query.exec(R"(SELECT * FROM participants)");

    while (query.next()) {
        Domain::Participant participant;
        participant.setId(query.value(0).toInt());
        participant.setName(query.value(1).toString());

        participants.append(participant);
    }

    return participants;
}

bool SqliteEventsRepository::updateParticipant(const Domain::Participant &participant)
{
    QSqlQuery query(m_db);

    query.prepare(R"(UPDATE participants SET name = :name WHERE participant_id = :participant_id)");
    query.bindValue(":participant_id", participant.id());
    query.bindValue(":name", participant.name());

    return query.exec();
}

bool SqliteEventsRepository::deleteParticipant(qint32 id)
{
    QSqlQuery query(m_db);

    query.prepare(R"(DELETE FROM participants WHERE participant_id = :participant_id)");
    query.bindValue(":participant_id", id);

    return query.exec();
}

} // namespace Infrastructure
} // namespace Sea
