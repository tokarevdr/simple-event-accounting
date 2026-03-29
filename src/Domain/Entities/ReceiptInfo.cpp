#include "ReceiptInfo.h"

namespace Sea {
namespace Domain {

ReceiptInfo::ReceiptInfo() {}

qint32 ReceiptInfo::id() const
{
    return m_id;
}

void ReceiptInfo::setId(qint32 newId)
{
    m_id = newId;
}

qint32 ReceiptInfo::eventId() const
{
    return m_eventId;
}

void ReceiptInfo::setEventId(qint32 newEventId)
{
    m_eventId = newEventId;
}

QString ReceiptInfo::title() const
{
    return m_title;
}

void ReceiptInfo::setTitle(const QString &newTitle)
{
    m_title = newTitle;
}

QDateTime ReceiptInfo::purchaseDateTime() const
{
    return m_purchaseDateTime;
}

void ReceiptInfo::setPurchaseDateTime(const QDateTime &newPurchaseDateTime)
{
    m_purchaseDateTime = newPurchaseDateTime;
}

std::optional<User> ReceiptInfo::buyer() const
{
    return m_buyer;
}

void ReceiptInfo::setBuyer(std::optional<User> newBuyer)
{
    m_buyer = newBuyer;
}

} // namespace Domain
} // namespace Sea
