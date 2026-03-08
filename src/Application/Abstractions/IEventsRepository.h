#ifndef IEVENTSREPOSITORY_H
#define IEVENTSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/Event.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IEventsRepository
{
    Q_DISABLE_COPY_MOVE(IEventsRepository)
public:
    IEventsRepository();

    virtual ~IEventsRepository() = default;

    virtual Utils::Result<qint32, QString> createEvent(const Domain::Event &event) = 0;

    virtual Utils::Result<QVector<Domain::Event>, QString> readEvents() = 0;

    virtual Utils::Result<Utils::Unit, QString> updateEvent(const Domain::Event &event) = 0;

    virtual Utils::Result<Utils::Unit, QString> deleteEvent(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IEVENTSREPOSITORY_H
