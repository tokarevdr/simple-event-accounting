#ifndef CREATEEVENTRESPONSE_H
#define CREATEEVENTRESPONSE_H

#include "Application_global.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT CreateEventResponse
{
public:
    CreateEventResponse();

    qint32 id() const;
    void setId(qint32 newId);

private:
    qint32 m_id = 0;
};

} // namespace Application
} // namespace Sea

#endif // CREATEEVENTRESPONSE_H
