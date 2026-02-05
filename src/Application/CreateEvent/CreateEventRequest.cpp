#include "CreateEventRequest.h"

namespace Sea {
namespace Application {

CreateEventRequest::CreateEventRequest() {}

Domain::Event CreateEventRequest::event() const
{
    return m_event;
}

void CreateEventRequest::setEvent(const Domain::Event &newEvent)
{
    m_event = newEvent;
}

} // namespace Application
} // namespace Sea
