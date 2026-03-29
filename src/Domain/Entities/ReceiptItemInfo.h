#ifndef RECEIPTITEMINFO_H
#define RECEIPTITEMINFO_H

#include <QString>
#include <QVector>

#include "Consumer.h"
#include "Domain_global.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT ReceiptItemInfo
{
public:
    ReceiptItemInfo();

    qint32 id() const;
    void setId(qint32 newId);
    qint32 receiptId() const;
    void setReceiptId(qint32 newReceiptId);
    QString name() const;
    void setName(const QString &newName);
    qint32 price() const;
    void setPrice(qint32 newPrice);
    qint32 count() const;
    void setCount(qint32 newCount);

private:
    qint32 m_id = 0;
    qint32 m_receiptId = 0;
    QString m_name;
    qint32 m_price = 0;
    qint32 m_count = 0;
};

} // namespace Domain
} // namespace Sea

#endif // RECEIPTITEMINFO_H
