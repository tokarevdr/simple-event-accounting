#ifndef SQLITEEVENTSREPOSITORY_H
#define SQLITEEVENTSREPOSITORY_H

#include <QMutex>
#include <QSqlDatabase>

#include "Abstractions/IEventsRepository.h"
#include "Abstractions/IParticipantsRepository.h"
#include "Abstractions/IReceiptsRepository.h"
#include "Infrastructure_global.h"

namespace Sea {
namespace Infrastructure {

class INFRASTRUCTURE_EXPORT SqliteEventsRepository : public Application::IEventsRepository,
                                                     public Application::IParticipantsRepository,
                                                     public Application::IReceiptsRepository
{
public:
    SqliteEventsRepository();

    // IEventsRepository interface
    qint32 createEvent(const Domain::Event &event) override;
    QVector<Domain::Event> readEvents() override;
    bool updateEvent(const Domain::Event &event) override;
    bool deleteEvent(int id) override;

    // IReceiptsRepository interface
    qint32 createReceipt(const Domain::Receipt &receipt) override;
    QVector<Domain::Receipt> readReceipts(qint32 eventId) override;
    bool updateReceipt(const Domain::Receipt &receipt) override;
    bool deleteReceipt(qint32 id) override;

    // IParticipantsRepository interface
    qint32 createParticipant(const Domain::Participant &participant) override;
    QVector<Domain::Participant> readParticipants() override;
    bool updateParticipant(const Domain::Participant &participant) override;
    bool deleteParticipant(qint32 id) override;

private:
    QSqlDatabase m_db;
    QMutex m_mutex;
};

} // namespace Infrastructure
} // namespace Sea

#endif // SQLITEEVENTSREPOSITORY_H
