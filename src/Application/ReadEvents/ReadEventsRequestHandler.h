#ifndef READEVENTSREQUESTHANDLER_H
#define READEVENTSREQUESTHANDLER_H

#include <memory>

#include "Abstractions/IEventsRepository.h"
#include "Application_global.h"
#include "ReadEventsRequest.h"
#include "mediqt/irequesthandler.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT ReadEventsRequestHandler
    : public Mediqt::IRequestHandler<ReadEventsRequest, ReadEventsResponse>
{
public:
    ReadEventsRequestHandler(std::shared_ptr<IEventsRepository> repository);

    // IRequestHandler interface
    ReadEventsResponse handle(const ReadEventsRequest &request) override;

private:
    std::shared_ptr<IEventsRepository> m_repository;
};

} // namespace Application
} // namespace Sea

#endif // READEVENTSREQUESTHANDLER_H
