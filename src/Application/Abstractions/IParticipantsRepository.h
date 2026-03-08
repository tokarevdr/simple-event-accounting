#ifndef IPARTICIPANTSREPOSITORY_H
#define IPARTICIPANTSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/Participant.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IParticipantsRepository
{
public:
    IParticipantsRepository();

    virtual ~IParticipantsRepository() = default;

    virtual Utils::Result<qint32, QString> createParticipant(const Domain::Participant &participant)
        = 0;

    virtual Utils::Result<QVector<Domain::Participant>, QString> readParticipants() = 0;

    virtual Utils::Result<Utils::Unit, QString>
    updateParticipant(const Domain::Participant &participant) = 0;

    virtual Utils::Result<Utils::Unit, QString> deleteParticipant(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IPARTICIPANTSREPOSITORY_H
