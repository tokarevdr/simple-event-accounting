#ifndef READEVENTSINFOREQUEST_H
#define READEVENTSINFOREQUEST_H

#include "Application_global.h"
#include "ReadEventsResponse.h"
#include "mediqt/irequest.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT ReadEventsRequest : public Mediqt::IRequest<ReadEventsResponse>
{
public:
    ReadEventsRequest();
};

} // namespace Application
} // namespace Sea

#endif // READEVENTSINFOREQUEST_H
