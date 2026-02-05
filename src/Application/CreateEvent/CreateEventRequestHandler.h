#ifndef CREATEEVENTREQUESTHANDLER_H
#define CREATEEVENTREQUESTHANDLER_H

#include <memory>

#include "Abstractions/IEventsRepository.h"
#include "Application_global.h"
#include "CreateEventRequest.h"
#include "mediqt/irequesthandler.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT CreateEventRequestHandler
    : public Mediqt::IRequestHandler<CreateEventRequest, CreateEventResponse>
{
public:
    CreateEventRequestHandler(std::shared_ptr<IEventsRepository> repository);

    // IRequestHandler interface
    CreateEventResponse handle(const CreateEventRequest &request) override;

private:
    std::shared_ptr<IEventsRepository> m_repository;
};

} // namespace Application
} // namespace Sea

#endif // CREATEEVENTREQUESTHANDLER_H
