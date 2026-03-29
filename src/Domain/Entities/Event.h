#ifndef EVENT_H
#define EVENT_H

#include <QVector>

#include "Domain_global.h"
#include "EventInfo.h"
#include "Receipt.h"
#include "User.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT Event
{
public:
    Event();

    EventInfo info() const;
    void setInfo(const EventInfo &newInfo);
    QVector<User> participants() const;
    void setParticipants(const QVector<User> &newParticipants);
    QVector<Receipt> receipts() const;
    void setReceipts(const QVector<Receipt> &newReceipts);

private:
    EventInfo m_info;
    QVector<User> m_participants;
    QVector<Receipt> m_receipts;
};

} // namespace Domain
} // namespace Sea

#endif // EVENT_H
