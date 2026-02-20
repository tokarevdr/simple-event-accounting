#ifndef SQLITEEVENTSREPOSITORY_H
#define SQLITEEVENTSREPOSITORY_H

#include <QSqlDatabase>

#include "Abstractions/IEventsRepository.h"
#include "Infrastructure_global.h"

namespace Sea {
namespace Infrastructure {

class INFRASTRUCTURE_EXPORT SqliteEventsRepository : public Application::IEventsRepository
{
public:
    SqliteEventsRepository();

    // IEventsRepository interface
    qint32 createEvent(const Domain::Event &event) override;
    QVector<Domain::Event> readEvents() const override;
    bool updateEvent(const Domain::Event &event) override;
    bool deleteEvent(int id) override;

private:
    QSqlDatabase m_db;
};

} // namespace Infrastructure
} // namespace Sea

#endif // SQLITEEVENTSREPOSITORY_H
