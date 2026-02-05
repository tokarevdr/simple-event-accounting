#ifndef CREATEEVENTREQUEST_H
#define CREATEEVENTREQUEST_H

#include "Application_global.h"
#include "CreateEventResponse.h"
#include "Entities/Event.h"
#include "mediqt/irequest.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT CreateEventRequest : public Mediqt::IRequest<CreateEventResponse>
{
public:
    CreateEventRequest();

    Domain::Event event() const;
    void setEvent(const Domain::Event &newEvent);

private:
    Domain::Event m_event;
};

} // namespace Application
} // namespace Sea

#endif // CREATEEVENTREQUEST_H
