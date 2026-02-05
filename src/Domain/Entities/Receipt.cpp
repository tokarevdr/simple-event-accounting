#include "Receipt.h"

namespace Sea {
namespace Domain {

Receipt::Receipt() {}

qint32 Receipt::id() const
{
    return m_id;
}

void Receipt::setId(qint32 newId)
{
    m_id = newId;
}

QString Receipt::title() const
{
    return m_title;
}

void Receipt::setTitle(const QString &newTitle)
{
    m_title = newTitle;
}

QDateTime Receipt::purchaseDateTime() const
{
    return m_purchaseDateTime;
}

void Receipt::setPurchaseDateTime(const QDateTime &newPurchaseDateTime)
{
    m_purchaseDateTime = newPurchaseDateTime;
}

Participant Receipt::buyer() const
{
    return m_buyer;
}

void Receipt::setBuyer(const Participant &newBuyer)
{
    m_buyer = newBuyer;
}

} // namespace Domain
} // namespace Sea
