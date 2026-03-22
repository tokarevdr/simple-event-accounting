#ifndef IEVENTPARTICIPANTSREPOSITORY_H
#define IEVENTPARTICIPANTSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/Participant.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IEventParticipantsRepository
{
public:
    IEventParticipantsRepository();

    virtual ~IEventParticipantsRepository() = default;

    virtual Utils::Result<Utils::Unit, QString> createEventParticipant(qint32 eventId,
                                                                       qint32 participantId)
        = 0;

    virtual Utils::Result<QVector<Domain::Participant>, QString> readEventParticipants(qint32 eventId)
        = 0;

    virtual Utils::Result<Utils::Unit, QString> deleteEventParticipant(qint32 participantId) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IEVENTPARTICIPANTSREPOSITORY_H
