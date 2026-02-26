#ifndef IEVENTSREPOSITORY_H
#define IEVENTSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/Event.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IEventsRepository
{
    Q_DISABLE_COPY_MOVE(IEventsRepository)
public:
    IEventsRepository();

    virtual ~IEventsRepository() = default;

    virtual qint32 createEvent(const Domain::Event &event) = 0;

    virtual QVector<Domain::Event> readEvents() = 0;

    virtual bool updateEvent(const Domain::Event &event) = 0;

    virtual bool deleteEvent(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IEVENTSREPOSITORY_H
