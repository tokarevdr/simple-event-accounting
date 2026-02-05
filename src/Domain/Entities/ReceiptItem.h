#ifndef RECEIPTITEM_H
#define RECEIPTITEM_H

#include <QString>

#include "Domain_global.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT ReceiptItem
{
public:
    ReceiptItem();

private:
    qint32 m_id = 0;
    QString m_name;
    qint32 m_price = 0;
    qint32 m_count = 0;
};

} // namespace Domain
} // namespace Sea

#endif // RECEIPTITEM_H
