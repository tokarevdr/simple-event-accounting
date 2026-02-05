#include "ReadEventsRequestHandler.h"

namespace Sea {
namespace Application {

ReadEventsRequestHandler::ReadEventsRequestHandler(std::shared_ptr<IEventsRepository> repository)
    : m_repository{repository}
{}

ReadEventsResponse ReadEventsRequestHandler::handle(const ReadEventsRequest &request) {}

} // namespace Application
} // namespace Sea
