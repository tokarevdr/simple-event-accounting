#include "SqliteEventsRepository.h"

namespace Sea {
namespace Infrastructure {

SqliteEventsRepository::SqliteEventsRepository() {}

QVector<Domain::Event> SqliteEventsRepository::readEvents() const {}

qint32 SqliteEventsRepository::createEvent(const Domain::Event &event) {}

} // namespace Infrastructure
} // namespace Sea
