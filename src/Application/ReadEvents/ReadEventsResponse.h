#ifndef READEVENTSRESPONSE_H
#define READEVENTSRESPONSE_H

#include <QVector>

#include "Application_global.h"
#include "Entities/Event.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT ReadEventsResponse
{
public:
    ReadEventsResponse();

    QVector<Domain::Event> events() const;
    void setEvents(const QVector<Domain::Event> &newEvents);

private:
    QVector<Domain::Event> m_events;
};

} // namespace Application
} // namespace Sea

#endif // READEVENTSRESPONSE_H
