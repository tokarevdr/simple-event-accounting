#ifndef SQLITEEVENTSREPOSITORY_H
#define SQLITEEVENTSREPOSITORY_H

#include "Abstractions/IEventsRepository.h"
#include "Infrastructure_global.h"

namespace Sea {
namespace Infrastructure {

class INFRASTRUCTURE_EXPORT SqliteEventsRepository : public Application::IEventsRepository
{
public:
    SqliteEventsRepository();

    // IEventsRepository interface
    QVector<Domain::Event> readEvents() const override;
    qint32 createEvent(const Domain::Event &event) override;
};

} // namespace Infrastructure
} // namespace Sea

#endif // SQLITEEVENTSREPOSITORY_H
