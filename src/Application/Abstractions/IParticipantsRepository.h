#ifndef IPARTICIPANTSREPOSITORY_H
#define IPARTICIPANTSREPOSITORY_H

#include <QVector>

#include <Application_global.h>
#include <Entities/Participant.h>

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IParticipantsRepository
{
public:
    IParticipantsRepository();

    virtual ~IParticipantsRepository() = default;

    virtual qint32 createParticipant(const Domain::Participant &participant) = 0;

    virtual QVector<Domain::Participant> readParticipants() = 0;

    virtual bool updateParticipant(const Domain::Participant &participant) = 0;

    virtual bool deleteParticipant(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IPARTICIPANTSREPOSITORY_H
