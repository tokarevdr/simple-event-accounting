#include "SqliteAccountingRepository.h"

#include <QDebug>
#include <QMutexLocker>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

namespace Sea {
namespace Infrastructure {

SqliteAccountingRepository::SqliteAccountingRepository()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "default");
    m_db.setHostName("sea");
    m_db.setDatabaseName("events_accounting");
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
                          title TEXT UNIQUE NOT NULL,
                          start_date INTEGER NOT NULL,
                          end_date INTEGER NOT NULL,
                          PRIMARY KEY(event_id AUTOINCREMENT))
                        )");

    if (!query.exec(queryStr)) {
        qDebug() << "Events table was not created.";
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS users (
                          user_id INTEGER NOT NULL,
                          name TEXT UNIQUE NOT NULL,
                          PRIMARY KEY(user_id AUTOINCREMENT))
                        )");

    if (!query.exec(queryStr)) {
        qDebug() << "Users table was not created.";
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS events_users (
                          event_id INTEGER NOT NULL,
                          user_id INTEGER NOT NULL,
                          PRIMARY KEY (event_id, user_id)
                          FOREIGN KEY (event_id) REFERENCES events(event_id) ON DELETE CASCADE
                          FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE)
                        )");

    if (!query.exec(queryStr)) {
        qDebug() << "Events users table was not created.";
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS receipts (
                          receipt_id INTEGER NOT NULL,
                          event_id INTEGER NOT NULL,
                          user_id INTEGER,
                          title TEXT NOT NULL,
                          purchase_datetime INTEGER NOT NULL,
                          PRIMARY KEY (receipt_id AUTOINCREMENT)
                          FOREIGN KEY (event_id) REFERENCES events(event_id) ON DELETE CASCADE
                          FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE)
                        )");

    if (!query.exec(queryStr)) {
        qDebug() << "Receipts table was not created.";
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS receipt_items (
                          receipt_item_id INTEGER NOT NULL,
                          receipt_id INTEGER NOT NULL,
                          name TEXT NOT NULL,
                          price INTEGER NOT NULL DEFAULT 0,
                          count INTEGER NOT NULL DEFAULT 1,
                          PRIMARY KEY (receipt_item_id AUTOINCREMENT)
                          FOREIGN KEY (receipt_id) REFERENCES receipts(receipt_id) ON DELETE CASCADE)
                        )");

    if (!query.exec(queryStr)) {
        qDebug() << "Receipt items table was not created.";
        qDebug() << query.lastError().text();
    }

    queryStr = QString(R"(CREATE TABLE IF NOT EXISTS receipt_items_users (
                          receipt_item_id INTEGER NOT NULL,
                          user_id INTEGER NOT NULL,
                          consumption_ratio INTEGER NOT NULL DEFAULT 1,
                          PRIMARY KEY (receipt_item_id, user_id)
                          FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE
                          FOREIGN KEY (receipt_item_id) REFERENCES receipt_items(receipt_item_id) ON DELETE CASCADE))");

    if (!query.exec(queryStr)) {
        qDebug() << "Receipt items users table was not created.";
        qDebug() << query.lastError().text();
    }
}

Utils::Result<qint32, QString> SqliteAccountingRepository::createEvent(
    const Domain::EventInfo &eventInfo)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(INSERT INTO events (title, start_date, end_date)
                                  VALUES (:title, :start_date, :end_date))");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать событие.");
    }

    query.bindValue(":title", eventInfo.title());
    query.bindValue(":start_date", eventInfo.startDate().toJulianDay());
    query.bindValue(":end_date", eventInfo.endDate().toJulianDay());

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

Utils::Result<QVector<Domain::EventInfo>, QString> SqliteAccountingRepository::readEventsInfo()
{
    QVector<Domain::EventInfo> eventsInfo;
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(SELECT * FROM events)");

    if (!query.exec(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список событий.");
    }

    while (query.next()) {
        Domain::EventInfo eventInfo;
        eventInfo.setId(query.value(0).toInt());
        eventInfo.setTitle(query.value(1).toString());
        eventInfo.setStartDate(QDate::fromJulianDay(query.value(2).toInt()));
        eventInfo.setEndDate(QDate::fromJulianDay(query.value(3).toInt()));
        eventsInfo.append(eventInfo);
    }

    return eventsInfo;
}

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::updateEventInfo(
    const Domain::EventInfo &eventInfo)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(
        R"(UPDATE events SET title = :title, start_date = :start_date, end_date = :end_date
           WHERE event_id = :event_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить событие.");
    }

    query.bindValue(":event_id", eventInfo.id());
    query.bindValue(":title", eventInfo.title());
    query.bindValue(":start_date", eventInfo.startDate().toJulianDay());
    query.bindValue(":end_date", eventInfo.endDate().toJulianDay());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить данные события.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::deleteEvent(qint32 id)
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

Utils::Result<qint32, QString> SqliteAccountingRepository::createUser(const Domain::User &user)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(INSERT INTO users (name)
                                  VALUES (:name))");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать участника.");
    }

    query.bindValue(":name", user.name());

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

Utils::Result<QVector<Domain::User>, QString> SqliteAccountingRepository::readUsers()
{
    QSqlQuery query(m_db);
    QVector<Domain::User> users;

    QString queryStr = QString(R"(SELECT * FROM users)");

    if (!query.exec(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список участников.");
    }

    while (query.next()) {
        Domain::User user;
        user.setId(query.value(0).toInt());
        user.setName(query.value(1).toString());

        users.append(user);
    }

    return users;
}

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::updateUser(const Domain::User &user)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(UPDATE users SET name = :name
                                  WHERE user_id = :user_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить данные участника.");
    }

    query.bindValue(":user_id", user.id());
    query.bindValue(":name", user.name());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить данные участника.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::deleteUser(qint32 id)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(DELETE FROM users WHERE user_id = :user_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить участника.");
    }

    query.bindValue(":user_id", id);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить участника.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::createEventUser(qint32 eventId,
                                                                                qint32 userId)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(INSERT INTO events_users (event_id, user_id)
                                  VALUES (:event_id, :user_id))");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось добавить участника события.");
    }

    query.bindValue(":event_id", eventId);
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось добавить участника события.");
    }

    return Utils::Unit();
}

Utils::Result<QVector<Domain::User>, QString> SqliteAccountingRepository::readEventUsers(
    qint32 eventId)
{
    QSqlQuery query(m_db);
    QVector<Domain::User> users;

    QString queryStr = QString(R"(SELECT u.* FROM events_users AS eu
                                  LEFT JOIN users AS u ON eu.user_id = u.user_id
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
        Domain::User user;
        user.setId(query.value(0).toInt());
        user.setName(query.value(1).toString());

        users.append(user);
    }

    return users;
}

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::deleteEventUser(qint32 userId)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(DELETE FROM events_users
                                  WHERE user_id = :user_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить участника события.");
    }

    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось удалить участника события.");
    }

    return Utils::Unit();
}

Utils::Result<qint32, QString> SqliteAccountingRepository::createReceipt(
    const Domain::ReceiptInfo &receiptInfo)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(INSERT INTO receipts (event_id, user_id, title, purchase_datetime)
                                  VALUES (:event_id, :user_id, :title, :purchase_datetime))");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать чек.");
    }

    query.bindValue(":event_id", receiptInfo.eventId());
    query
        .bindValue(":user_id",
                   receiptInfo.buyer().has_value() ? receiptInfo.buyer().value().id() : QVariant());
    query.bindValue(":title", receiptInfo.title());
    query.bindValue(":purchase_datetime", receiptInfo.purchaseDateTime().toSecsSinceEpoch());

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

Utils::Result<QVector<Domain::ReceiptInfo>, QString> SqliteAccountingRepository::readReceiptsInfo(
    qint32 eventId)
{
    QSqlQuery query(m_db);
    QVector<Domain::ReceiptInfo> receiptsInfo;

    QString queryStr = QString(
        R"(SELECT r.receipt_id, r.event_id, r.title, r.purchase_datetime, u.user_id, u.name
           FROM receipts as r
           LEFT JOIN users AS u ON r.user_id = u.user_id
           WHERE r.event_id = :event_id
           ORDER BY r.purchase_datetime ASC)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список чеков.");
    }

    query.bindValue(":event_id", eventId);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список чеков.");
    }

    while (query.next()) {
        Domain::ReceiptInfo receiptInfo;
        receiptInfo.setId(query.value(0).toInt());
        receiptInfo.setEventId(query.value(1).toInt());
        receiptInfo.setTitle(query.value(2).toString());
        receiptInfo.setPurchaseDateTime(QDateTime::fromSecsSinceEpoch(query.value(3).toLongLong()));

        if (query.value(4).isValid()) {
            Domain::User user;
            user.setId(query.value(4).toInt());
            user.setName(query.value(5).toString());
            receiptInfo.setBuyer(user);
        } else {
            receiptInfo.setBuyer(std::nullopt);
        }

        receiptsInfo.append(receiptInfo);
    }

    return receiptsInfo;
}

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::updateReceiptInfo(
    const Domain::ReceiptInfo &receiptInfo)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(
        R"(UPDATE receipts SET event_id = :event_id, user_id = :user_id, title = :title, purchase_datetime = :purchase_datetime
           WHERE receipt_id = :receipt_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить данные чека.");
    }
    query.bindValue(":receipt_id", receiptInfo.id());
    query.bindValue(":event_id", receiptInfo.eventId());
    query
        .bindValue(":user_id",
                   receiptInfo.buyer().has_value() ? receiptInfo.buyer().value().id() : QVariant());
    query.bindValue(":title", receiptInfo.title());
    query.bindValue(":purchase_datetime", receiptInfo.purchaseDateTime().toSecsSinceEpoch());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить данные чека.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::deleteReceipt(qint32 id)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(DELETE FROM receipts
                                  WHERE receipt_id = :receipt_id)");

    if (!query.prepare(queryStr)) {
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

Utils::Result<qint32, QString> SqliteAccountingRepository::createReceiptItem(
    const Domain::ReceiptItemInfo &receiptItemInfo)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(INSERT INTO receipt_items (receipt_id, name, price, count)
                                  VALUES (:receipt_id, :name, :price, :count))");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать запись в чеке.");
    }

    query.bindValue(":receipt_id", receiptItemInfo.receiptId());
    query.bindValue(":name", receiptItemInfo.name());
    query.bindValue(":price", receiptItemInfo.price());
    query.bindValue(":count", receiptItemInfo.count());

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

Utils::Result<QVector<Domain::ReceiptItemInfo>, QString> SqliteAccountingRepository::
    readReceiptItemsInfo(qint32 receiptId)
{
    QSqlQuery query(m_db);
    QVector<Domain::ReceiptItemInfo> receiptItemsInfo;

    QString queryStr = QString(R"(SELECT ri.*
                                  FROM receipt_items as ri
                                  WHERE ri.receipt_id = :receipt_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список записей в чеке.");
    }

    query.bindValue(":receipt_id", receiptId);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось получить список записей в чеке.");
    }

    while (query.next()) {
        Domain::ReceiptItemInfo receiptItemInfo;
        receiptItemInfo.setId(query.value(0).toInt());
        receiptItemInfo.setReceiptId(query.value(1).toInt());
        receiptItemInfo.setName(query.value(2).toString());
        receiptItemInfo.setPrice(query.value(3).toInt());
        receiptItemInfo.setCount(query.value(4).toInt());

        receiptItemsInfo.append(receiptItemInfo);
    }

    return receiptItemsInfo;
}

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::updateReceiptItemInfo(
    const Domain::ReceiptItemInfo &receiptItemInfo)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(
        R"(UPDATE receipt_items SET receipt_id = :receipt_id, name = :name, price = :price, count = :count
           WHERE receipt_item_id = :receipt_item_id)");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить даннные записи в чеке.");
    }

    query.bindValue(":receipt_item_id", receiptItemInfo.id());
    query.bindValue(":receipt_id", receiptItemInfo.receiptId());
    query.bindValue(":name", receiptItemInfo.name());
    query.bindValue(":price", receiptItemInfo.price());
    query.bindValue(":count", receiptItemInfo.count());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось обновить даннные записи в чеке.");
    }

    return Utils::Unit();
}

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::deleteReceiptItem(qint32 id)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(R"(DELETE FROM receipt_items
                                  WHERE receipt_item_id = :receipt_item_id)");

    if (!query.prepare(queryStr)) {
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

Utils::Result<Utils::Unit, QString> SqliteAccountingRepository::createConsumer(
    const Domain::Consumer &consumer)
{
    QSqlQuery query(m_db);

    QString queryStr = QString(
        R"(INSERT INTO receipt_items_users (receipt_item_id, user_id, consumption_ratio)
           VALUES (:receipt_item_id, :user_id, :consumption_ratio))");

    if (!query.prepare(queryStr)) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать потребителей.");
    }

    query.bindValue(":receipt_item_id", consumer.receiptItemId());
    query.bindValue(":user_id", consumer.participantId());
    query.bindValue(":consumption_ratio", consumer.consumptionRatio());

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return QString("Не удалось создать потребителя.");
    }

    return Utils::Unit();
}

Utils::Result<QVector<Domain::Consumer>, QString> SqliteAccountingRepository::readConsumers(
    qint32 receiptItemId)
{
    QVector<Domain::Consumer> consumers;

    QSqlQuery query(m_db);

    QString queryStr = QString(
        R"(SELECT u.name, riu.*
           FROM users AS u
           LEFT JOIN receipt_items_users AS riu ON u.user_id = riu.user_id
           WHERE riu.receipt_item_id = :receipt_item_id)");

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
