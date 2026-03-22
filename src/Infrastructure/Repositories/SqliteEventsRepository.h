#ifndef SQLITEEVENTSREPOSITORY_H
#define SQLITEEVENTSREPOSITORY_H

#include <QSqlDatabase>

#include "Abstractions/IConsumersRepository.h"
#include "Abstractions/IEventParticipantsRepository.h"
#include "Abstractions/IEventsRepository.h"
#include "Abstractions/IParticipantsRepository.h"
#include "Abstractions/IReceiptItemsRepository.h"
#include "Abstractions/IReceiptsRepository.h"
#include "Infrastructure_global.h"

namespace Sea {
namespace Infrastructure {

class INFRASTRUCTURE_EXPORT SqliteEventsRepository
    : public Application::IEventsRepository,
      public Application::IParticipantsRepository,
      public Application::IEventParticipantsRepository,
      public Application::IReceiptsRepository,
      public Application::IReceiptItemsRepository,
      public Application::IConsumersRepository
{
public:
    SqliteEventsRepository();

    // IEventsRepository interface
    Utils::Result<qint32, QString> createEvent(const Domain::Event &event) override;
    Utils::Result<QVector<Domain::Event>, QString> readEvents() override;
    Utils::Result<Utils::Unit, QString> updateEvent(const Domain::Event &event) override;
    Utils::Result<Utils::Unit, QString> deleteEvent(qint32 id) override;

    // IParticipantsRepository interface
    Utils::Result<qint32, QString> createParticipant(const Domain::Participant &participant) override;
    Utils::Result<QVector<Domain::Participant>, QString> readParticipants() override;
    Utils::Result<Utils::Unit, QString> updateParticipant(
        const Domain::Participant &participant) override;
    Utils::Result<Utils::Unit, QString> deleteParticipant(qint32 id) override;

    // IEventParticipantsRepository interface
    Utils::Result<Utils::Unit, QString> createEventParticipant(qint32 eventId,
                                                               qint32 participantId) override;
    Utils::Result<QVector<Domain::Participant>, QString> readEventParticipants(
        qint32 eventId) override;
    Utils::Result<Utils::Unit, QString> deleteEventParticipant(qint32 participantId) override;

    // IReceiptsRepository interface
    Utils::Result<qint32, QString> createReceipt(const Domain::Receipt &receipt) override;
    Utils::Result<QVector<Domain::Receipt>, QString> readReceipts(qint32 eventId) override;
    Utils::Result<Utils::Unit, QString> updateReceipt(const Domain::Receipt &receipt) override;
    Utils::Result<Utils::Unit, QString> deleteReceipt(qint32 id) override;

    // IReceiptItemsRepository interface
    Utils::Result<qint32, QString> createReceiptItem(const Domain::ReceiptItem &receiptItem) override;
    Utils::Result<QVector<Domain::ReceiptItem>, QString> readReceiptItems(qint32 receiptId) override;
    Utils::Result<Utils::Unit, QString> updateReceiptItem(
        const Domain::ReceiptItem &receiptItem) override;
    Utils::Result<Utils::Unit, QString> deleteReceiptItem(qint32 id) override;

    // IConsumersRepository interface
    Utils::Result<Utils::Unit, QString> createConsumer(const Domain::Consumer &consumer) override;
    Utils::Result<QVector<Domain::Consumer>, QString> readConsumers(qint32 receiptItemId) override;

private:
    QSqlDatabase m_db;
};

} // namespace Infrastructure
} // namespace Sea

#endif // SQLITEEVENTSREPOSITORY_H
