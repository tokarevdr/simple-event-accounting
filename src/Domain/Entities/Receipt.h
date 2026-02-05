#ifndef RECEIPT_H
#define RECEIPT_H

#include <QDateTime>
#include <QString>

#include "Domain_global.h"
#include "Participant.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT Receipt
{
public:
    Receipt();

    qint32 id() const;
    void setId(qint32 newId);
    QString title() const;
    void setTitle(const QString &newTitle);
    QDateTime purchaseDateTime() const;
    void setPurchaseDateTime(const QDateTime &newPurchaseDateTime);
    Participant buyer() const;
    void setBuyer(const Participant &newBuyer);

private:
    qint32 m_id = 0;
    QString m_title;
    QDateTime m_purchaseDateTime;
    Participant m_buyer;
};

} // namespace Domain
} // namespace Sea

#endif // RECEIPT_H
