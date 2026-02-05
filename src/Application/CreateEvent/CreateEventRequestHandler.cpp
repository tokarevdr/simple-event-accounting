#include "CreateEventRequestHandler.h"

namespace Sea {
namespace Application {

CreateEventRequestHandler::CreateEventRequestHandler(std::shared_ptr<IEventsRepository> repository)
    : m_repository{repository}
{}

CreateEventResponse CreateEventRequestHandler::handle(const CreateEventRequest &request) {}

} // namespace Application
} // namespace Sea
