#ifndef SQLITEACCOUNTINGREPOSITORY_H
#define SQLITEACCOUNTINGREPOSITORY_H

#include <QSqlDatabase>

#include "Abstractions/IConsumersRepository.h"
#include "Abstractions/IEventUsersRepository.h"
#include "Abstractions/IEventsInfoRepository.h"
#include "Abstractions/IEventsRepository.h"
#include "Abstractions/IReceiptItemsInfoRepository.h"
#include "Abstractions/IReceiptsInfoRepository.h"
#include "Abstractions/IUsersRepository.h"
#include "Infrastructure_global.h"

namespace Sea {
namespace Infrastructure {
class INFRASTRUCTURE_EXPORT SqliteAccountingRepository
    : public Application::IEventsInfoRepository,
      public Application::IUsersRepository,
      public Application::IEventUsersRepository,
      public Application::IEventsRepository,
      public Application::IReceiptsInfoRepository,
      public Application::IReceiptItemsInfoRepository,
      public Application::IConsumersRepository
{
public:
    SqliteAccountingRepository();

    // IEventsRepository interface
    Utils::Result<qint32, QString> createEvent(const Domain::EventInfo &eventInfo) override;
    Utils::Result<QVector<Domain::EventInfo>, QString> readEventsInfo() override;
    Utils::Result<Utils::Unit, QString> updateEventInfo(const Domain::EventInfo &eventInfo) override;
    Utils::Result<Utils::Unit, QString> deleteEvent(qint32 id) override;

    // IEventsRepository interface
    Utils::Result<Domain::Event, QString> readEvent(qint32 eventId) override;

    // IParticipantsRepository interface
    Utils::Result<qint32, QString> createUser(const Domain::User &user) override;
    Utils::Result<QVector<Domain::User>, QString> readUsers() override;
    Utils::Result<Utils::Unit, QString> updateUser(const Domain::User &user) override;
    Utils::Result<Utils::Unit, QString> deleteUser(qint32 id) override;

    // IEventParticipantsRepository interface
    Utils::Result<Utils::Unit, QString> createEventUser(qint32 eventId, qint32 userId) override;
    Utils::Result<QVector<Domain::User>, QString> readEventUsers(qint32 eventId) override;
    Utils::Result<Utils::Unit, QString> deleteEventUser(qint32 userId) override;

    // IReceiptsRepository interface
    Utils::Result<qint32, QString> createReceipt(const Domain::ReceiptInfo &receiptInfo) override;
    Utils::Result<QVector<Domain::ReceiptInfo>, QString> readReceiptsInfo(qint32 eventId) override;
    Utils::Result<Utils::Unit, QString> updateReceiptInfo(
        const Domain::ReceiptInfo &receiptInfo) override;
    Utils::Result<Utils::Unit, QString> deleteReceipt(qint32 id) override;

    // IReceiptItemsRepository interface
    Utils::Result<qint32, QString> createReceiptItem(
        const Domain::ReceiptItemInfo &receiptItemInfo) override;
    Utils::Result<QVector<Domain::ReceiptItemInfo>, QString> readReceiptItemsInfo(
        qint32 receiptId) override;
    Utils::Result<Utils::Unit, QString> updateReceiptItemInfo(
        const Domain::ReceiptItemInfo &receiptItemInfo) override;
    Utils::Result<Utils::Unit, QString> deleteReceiptItem(qint32 id) override;

    // IConsumersRepository interface
    Utils::Result<Utils::Unit, QString> createConsumer(const Domain::Consumer &consumer) override;
    Utils::Result<QVector<Domain::Consumer>, QString> readConsumers(qint32 receiptItemId) override;

private:
    QSqlDatabase m_db;
};
} // namespace Infrastructure
} // namespace Sea

#endif // SQLITEACCOUNTINGREPOSITORY_H
