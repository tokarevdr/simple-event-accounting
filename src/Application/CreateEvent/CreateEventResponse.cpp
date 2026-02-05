#include "CreateEventResponse.h"

namespace Sea {
namespace Application {

CreateEventResponse::CreateEventResponse() {}

qint32 CreateEventResponse::id() const
{
    return m_id;
}

void CreateEventResponse::setId(qint32 newId)
{
    m_id = newId;
}

} // namespace Application
} // namespace Sea
