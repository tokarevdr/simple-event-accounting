#include "Event.h"

namespace Sea {
namespace Domain {

Event::Event() {}

EventInfo Event::info() const
{
    return m_info;
}

void Event::setInfo(const EventInfo &newInfo)
{
    m_info = newInfo;
}

QVector<User> Event::participants() const
{
    return m_participants;
}

void Event::setParticipants(const QVector<User> &newParticipants)
{
    m_participants = newParticipants;
}

QVector<Receipt> Event::receipts() const
{
    return m_receipts;
}

void Event::setReceipts(const QVector<Receipt> &newReceipts)
{
    m_receipts = newReceipts;
}

} // namespace Domain
} // namespace Sea
