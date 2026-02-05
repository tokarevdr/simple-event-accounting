#include "ReadEventsResponse.h"

namespace Sea {
namespace Application {

ReadEventsResponse::ReadEventsResponse() {}

QVector<Domain::Event> ReadEventsResponse::events() const
{
    return m_events;
}

void ReadEventsResponse::setEvents(
    const QVector<Domain::Event> &newEvents)
{
    m_events = newEvents;
}

} // namespace Application
} // namespace Sea
