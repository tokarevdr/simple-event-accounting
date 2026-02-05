#ifndef IEVENTSREPOSITORY_H
#define IEVENTSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/Event.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IEventsRepository
{
public:
    IEventsRepository();

    virtual ~IEventsRepository() = default;

    virtual QVector<Domain::Event> readEvents() const = 0;

    virtual qint32 createEvent(const Domain::Event &event) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IEVENTSREPOSITORY_H
