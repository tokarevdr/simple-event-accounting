#include "SqliteEventsRepository.h"

#include <QDebug>
#include <QMutexLocker>
#include <QSqlError>
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

    QString queryStr = QString(R"(PRAGMA foreign_keys = ON;)");

    if (!query.exec(queryStr)) {
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS events (
                          event_id INTEGER NOT NULL,
                          title TEXT NOT NULL,
                          start_date TEXT,
                          end_date TEXT,
                          PRIMARY KEY(event_id AUTOINCREMENT))
                        )");

    if (!query.exec(queryStr)) {
        qDebug() << "Events table was not created.";
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS participants (
                          participant_id INTEGER NOT NULL,
                          name TEXT NOT NULL,
                          PRIMARY KEY(participant_id AUTOINCREMENT))
                        )");

    if (!query.exec(queryStr)) {
        qDebug() << "Participants table was not created.";
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS events_participants (
                          event_id INTEGER NOT NULL,
                          participant_id INTEGER NOT NULL,
                          PRIMARY KEY (event_id, participant_id)
                          FOREIGN KEY (event_id) REFERENCES events(event_id) ON DELETE CASCADE
                          FOREIGN KEY (participant_id) REFERENCES participants(participant_id) ON DELETE CASCADE)
                        )");

    if (!query.exec(queryStr)) {
        qDebug() << "Events participants table was not created.";
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS receipts (
                          receipt_id INTEGER NOT NULL,
                          event_id INTEGER NOT NULL,
                          buyer_id INTEGER,
                          title TEXT NOT NULL,
                          purchase_datetime INTEGER NOT NULL,
                          PRIMARY KEY (receipt_id AUTOINCREMENT)
                          FOREIGN KEY (event_id) REFERENCES events(event_id) ON DELETE CASCADE
                          FOREIGN KEY (buyer_id) REFERENCES participants(participant_id) ON DELETE CASCADE)
                        )");

    if (!query.exec(queryStr)) {
        qDebug() << "Receipts table was not created.";
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS receipt_items (
                          receipt_item_id INTEGER NOT NULL,
                          receipt_id INTEGER NOT NULL,
                          name TEXT NOT NULL,
                          price INTEGER NOT NULL,
                          count INTEGER NOT NULL,
                          PRIMARY KEY (receipt_item_id AUTOINCREMENT)
                          FOREIGN KEY (receipt_id) REFERENCES receipts(receipt_id) ON DELETE CASCADE)
                        )");

    if (!query.exec(queryStr)) {
        qDebug() << "Receipt items table was not created.";
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS receipt_items_participants (
                          receipt_item_id INTEGER NOT NULL,
                          participant_id INTEGER NOT NULL,
                          consumption_ratio INTEGER NOT NULL DEFAULT 1,
                          PRIMARY KEY (receipt_item_id, participant_id)
                          FOREIGN KEY (participant_id) REFERENCES participants(participant_id) ON DELETE CASCADE
                          FOREIGN KEY (receipt_item_id) REFERENCES receipt_items(receipt_item_id) ON DELETE CASCADE))");

    if (!query.exec(queryStr)) {
        qDebug() << "Receipt items participants table was not created.";
        qDebug() << query.lastError().text();
    }
}

Utils::Result<qint32, QString> SqliteEventsRepository::createEvent(const Domain::Event &event)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(INSERT INTO events (title, start_date, end_date)
                                  VALUES (:title, :start_date, :end_date))");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать событие.");
    }

    query.bindValue(":title", event.title());
    query.bindValue(":start_date",
                    event.startDate().has_value() ? event.startDate().value().toString("dd.MM.yyyy")
                                                  : QVariant());
    query.bindValue(":end_date",
                    event.endDate().has_value() ? event.endDate().value().toString("dd.MM.yyyy")
                                                : QVariant());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать событие.");
    }

    auto id = query.lastInsertId();

    if (!id.isValid()) {
        qDebug() << Q_FUNC_INFO << "Last insert id is invalid.";
        return QString("Не удалось получить созданное событие.");
    }

    return query.lastInsertId().toInt();
}

Utils::Result<QVector<Domain::Event>, QString> SqliteEventsRepository::readEvents()
{
    QVector<Domain::Event> events;
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(SELECT * FROM events)");

    if (!query.exec(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список событий.");
    }

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

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::updateEvent(const Domain::Event &event)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(
        R"(UPDATE events SET title = :title, start_date = :start_date, end_date = :end_date
           WHERE event_id = :event_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить событие.");
    }

    query.bindValue(":event_id", event.id());
    query.bindValue(":title", event.title());
    query.bindValue(":start_date",
                    event.startDate().has_value() ? event.startDate().value().toString("dd.MM.yyyy")
                                                  : QVariant());
    query.bindValue(":end_date",
                    event.endDate().has_value() ? event.endDate().value().toString("dd.MM.yyyy")
                                                : QVariant());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить данные события.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::deleteEvent(qint32 id)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(DELETE FROM events
                                  WHERE event_id = :event_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить запрос.");
    }
    query.bindValue(":event_id", id);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить запрос.");
    }

    return Utils::Unit();
}

Utils::Result<qint32, QString> SqliteEventsRepository::createParticipant(
    const Domain::Participant &participant)
{
    QSqlQuery query(m_db);

    if (!query.prepare(R"(INSERT INTO participants (name)
                    VALUES (:name))")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать участника.");
    }

    query.bindValue(":name", participant.name());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать участника.");
    }

    auto id = query.lastInsertId();

    if (!id.isValid()) {
        qDebug() << Q_FUNC_INFO << "Last insert id is invalid.";
        return QString("Не удалось получить созданного участника.");
    }

    return query.lastInsertId().toInt();
}

Utils::Result<QVector<Domain::Participant>, QString> SqliteEventsRepository::readParticipants()
{
    QSqlQuery query(m_db);
    QVector<Domain::Participant> participants;

    if (!query.exec(R"(SELECT * FROM participants)")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список участников.");
    }

    while (query.next()) {
        Domain::Participant participant;
        participant.setId(query.value(0).toInt());
        participant.setName(query.value(1).toString());

        participants.append(participant);
    }

    return participants;
}

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::updateParticipant(
    const Domain::Participant &participant)
{
    QSqlQuery query(m_db);

    if (!query.prepare(
            R"(UPDATE participants SET name = :name WHERE participant_id = :participant_id)")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить данные участника.");
    }

    query.bindValue(":participant_id", participant.id());
    query.bindValue(":name", participant.name());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить данные участника.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::deleteParticipant(qint32 id)
{
    QSqlQuery query(m_db);

    if (!query.prepare(R"(DELETE FROM participants WHERE participant_id = :participant_id)")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить участника.");
    }

    query.bindValue(":participant_id", id);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить участника.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::createEventParticipant(
    qint32 eventId, qint32 participantId)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(INSERT INTO events_participants (event_id, participant_id)
                                  VALUES (:event_id, :participant_id))");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось добавить участника события.");
    }

    query.bindValue(":event_id", eventId);
    query.bindValue(":participant_id", participantId);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось добавить участника события.");
    }

    return Utils::Unit();
}

Utils::Result<QVector<Domain::Participant>, QString> SqliteEventsRepository::readEventParticipants(
    qint32 eventId)
{
    QSqlQuery query(m_db);
    QVector<Domain::Participant> participants;

    QString queryStr = QString(R"(SELECT p.* FROM events_participants AS ep
                                  LEFT JOIN participants AS p ON ep.participant_id = p.participant_id
                                  WHERE event_id = :event_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список участников.");
    }

    query.bindValue(":event_id", eventId);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список участников.");
    }

    while (query.next()) {
        Domain::Participant participant;
        participant.setId(query.value(0).toInt());
        participant.setName(query.value(1).toString());

        participants.append(participant);
    }

    return participants;
}

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::deleteEventParticipant(
    qint32 participantId)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(DELETE FROM events_participants
                                  WHERE participant_id = :participant_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить участника события.");
    }

    query.bindValue(":participant_id", participantId);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить участника события.");
    }

    return Utils::Unit();
}

Utils::Result<qint32, QString> SqliteEventsRepository::createReceipt(const Domain::Receipt &receipt)
{
    QSqlQuery query(m_db);

    if (!query.prepare(R"(INSERT INTO receipts (event_id, buyer_id, title, purchase_datetime)
                     VALUES (:event_id, :buyer_id, :title, :purchase_datetime))")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать чек.");
    }

    query.bindValue(":event_id", receipt.eventId());
    query.bindValue(":buyer_id",
                    receipt.buyer().has_value() ? receipt.buyer().value().id() : QVariant());
    query.bindValue(":title", receipt.title());
    query.bindValue(":purchase_datetime", receipt.purchaseDateTime().toSecsSinceEpoch());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать чек.");
    }

    auto id = query.lastInsertId();

    if (!id.isValid()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить созданный чек.");
    }

    return query.lastInsertId().toInt();
}

Utils::Result<QVector<Domain::Receipt>, QString> SqliteEventsRepository::readReceipts(qint32 eventId)
{
    QSqlQuery query(m_db);
    QVector<Domain::Receipt> receipts;

    if (!query.prepare(
            R"(SELECT r.receipt_id, r.event_id, r.title, r.purchase_datetime, p.participant_id, p.name
            FROM receipts as r
            LEFT JOIN participants AS p ON r.buyer_id = p.participant_id
            WHERE r.event_id = :event_id
            ORDER BY r.purchase_datetime ASC)")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список чеков.");
    }

    query.bindValue(":event_id", eventId);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список чеков.");
    }

    while (query.next()) {
        Domain::Receipt receipt;
        receipt.setId(query.value(0).toInt());
        receipt.setEventId(query.value(1).toInt());
        receipt.setTitle(query.value(2).toString());
        receipt.setPurchaseDateTime(QDateTime::fromSecsSinceEpoch(query.value(3).toLongLong()));

        if (query.value(4).isValid()) {
            Domain::Participant participant;
            participant.setId(query.value(4).toInt());
            participant.setName(query.value(5).toString());
            receipt.setBuyer(participant);
        } else {
            receipt.setBuyer(std::nullopt);
        }

        receipts.append(receipt);
    }

    return receipts;
}

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::updateReceipt(
    const Domain::Receipt &receipt)
{
    QSqlQuery query(m_db);

    if (!query.prepare(
            R"(UPDATE receipts SET event_id = :event_id, buyer_id = :buyer_id, title = :title, purchase_datetime = :purchase_datetime
            WHERE receipt_id = :receipt_id)")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить данные чека.");
    }
    query.bindValue(":receipt_id", receipt.id());
    query.bindValue(":event_id", receipt.eventId());
    query.bindValue(":buyer_id",
                    receipt.buyer().has_value() ? receipt.buyer().value().id() : QVariant());
    query.bindValue(":title", receipt.title());
    query.bindValue(":purchase_datetime", receipt.purchaseDateTime().toSecsSinceEpoch());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить данные чека.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::deleteReceipt(qint32 id)
{
    QSqlQuery query(m_db);

    if (!query.prepare(R"(DELETE FROM receipts WHERE receipt_id = :receipt_id)")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить удалить чек.");
    }

    query.bindValue(":receipt_id", id);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить удалить чек.");
    }

    return Utils::Unit();
}

Utils::Result<qint32, QString> SqliteEventsRepository::createReceiptItem(
    const Domain::ReceiptItem &receiptItem)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(INSERT INTO receipt_items (receipt_id, name, price, count)
                                  VALUES (:receipt_id, :name, :price, :count))");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать запись в чеке.");
    }

    query.bindValue(":receipt_id", receiptItem.receiptId());
    query.bindValue(":name", receiptItem.name());
    query.bindValue(":price", receiptItem.price());
    query.bindValue(":count", receiptItem.count());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать запись в чеке.");
    }

    auto id = query.lastInsertId();

    if (!id.isValid()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить созданную запись в чеке.");
    }

    return query.lastInsertId().toInt();
}

Utils::Result<QVector<Domain::ReceiptItem>, QString> SqliteEventsRepository::readReceiptItems(
    qint32 receiptId)
{
    QSqlQuery query(m_db);
    QVector<Domain::ReceiptItem> receiptItems;

    if (!query.prepare(
            R"(SELECT i.receipt_item_id, i.receipt_id, i.name, i.price, i.count
            FROM receipt_items as i
            WHERE i.receipt_id = :receipt_id)")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список записей в чеке.");
    }

    query.bindValue(":receipt_id", receiptId);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список записей в чеке.");
    }

    while (query.next()) {
        Domain::ReceiptItem receiptItem;
        receiptItem.setId(query.value(0).toInt());
        receiptItem.setReceiptId(query.value(1).toInt());
        receiptItem.setName(query.value(2).toString());
        receiptItem.setPrice(query.value(3).toInt());
        receiptItem.setCount(query.value(4).toInt());

        receiptItems.append(receiptItem);
    }

    return receiptItems;
}

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::updateReceiptItem(
    const Domain::ReceiptItem &receiptItem)
{
    QSqlQuery query(m_db);

    if (!query.prepare(
            R"(UPDATE receipt_items SET receipt_id = :receipt_id, name = :name, price = :price, count = :count
            WHERE receipt_item_id = :receipt_item_id)")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить даннные записи в чеке.");
    }

    query.bindValue(":receipt_item_id", receiptItem.id());
    query.bindValue(":receipt_id", receiptItem.receiptId());
    query.bindValue(":name", receiptItem.name());
    query.bindValue(":price", receiptItem.price());
    query.bindValue(":count", receiptItem.count());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить даннные записи в чеке.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::deleteReceiptItem(qint32 id)
{
    QSqlQuery query(m_db);

    if (!query.prepare(R"(DELETE FROM receipt_items WHERE receipt_item_id = :receipt_item_id)")) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить запись в чеке.");
    }

    query.bindValue(":receipt_item_id", id);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить запись в чеке.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteEventsRepository::createConsumer(
    const Domain::Consumer &consumer)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(
        R"(INSERT INTO receipt_items_participants (receipt_item_id, participant_id, consumption_ratio)
           VALUES (:receipt_item_id, :participant_id, :consumption_ratio))");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать потребителей.");
    }

    query.bindValue(":receipt_item_id", consumer.receiptItemId());
    query.bindValue(":participant_id", consumer.participantId());
    query.bindValue(":consumption_ratio", consumer.consumptionRatio());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать потребителя.");
    }

    return Utils::Unit();
}

Utils::Result<QVector<Domain::Consumer>, QString> SqliteEventsRepository::readConsumers(
    qint32 receiptItemId)
{
    QVector<Domain::Consumer> consumers;

    QSqlQuery query(m_db);

    QString queryStr = QString(
        R"(SELECT p.name, ric.*
           FROM participants AS p
           LEFT JOIN receipt_items_participants AS ric ON p.participant_id = ric.participant_id
           WHERE ric.receipt_item_id = :receipt_item_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить потребителей.");
    }

    query.bindValue(":receipt_item_id", receiptItemId);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить потребителей.");
    }

    while (query.next()) {
        Domain::Consumer consumer;
        consumer.setName(query.value(0).toString());
        consumer.setReceiptItemId(query.value(1).toInt());
        consumer.setParticipantId(query.value(2).toInt());
        consumer.setConsumptionRatio(query.value(3).toInt());
        consumers.append(consumer);
    }

    return consumers;
}

} // namespace Infrastructure
} // namespace Sea
