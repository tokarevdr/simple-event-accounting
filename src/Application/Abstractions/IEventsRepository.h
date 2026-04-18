#ifndef IEVENTSREPOSITORY_H
#define IEVENTSREPOSITORY_H

#include "Application_global.h"
#include "Entities/Event.h"
#include "Result.h"

namespace Sea {
namespace Application {
class APPLICATION_EXPORT IEventsRepository
{
public:
    IEventsRepository();

    virtual ~IEventsRepository() = default;

    virtual Utils::Result<Domain::Event, QString> readEvent(qint32 eventId) = 0;
};
} // namespace Application
} // namespace Sea

#endif // IEVENTSREPOSITORY_H
