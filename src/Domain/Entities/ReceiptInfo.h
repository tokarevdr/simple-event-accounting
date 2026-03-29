#ifndef RECEIPTINFO_H
#define RECEIPTINFO_H

#include <optional>

#include <QDateTime>
#include <QString>

#include "Domain_global.h"
#include "User.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT ReceiptInfo
{
public:
    ReceiptInfo();

    qint32 id() const;
    void setId(qint32 newId);
    qint32 eventId() const;
    void setEventId(qint32 newEventId);
    QString title() const;
    void setTitle(const QString &newTitle);
    QDateTime purchaseDateTime() const;
    void setPurchaseDateTime(const QDateTime &newPurchaseDateTime);
    std::optional<User> buyer() const;
    void setBuyer(std::optional<User> newBuyer);

private:
    qint32 m_id = 0;
    qint32 m_eventId = 0;
    QString m_title;
    QDateTime m_purchaseDateTime;
    std::optional<User> m_buyer;
};

} // namespace Domain
} // namespace Sea

#endif // RECEIPTINFO_H
