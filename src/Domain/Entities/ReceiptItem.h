#ifndef RECEIPTITEM_H
#define RECEIPTITEM_H

#include <QVector>

#include "Consumer.h"
#include "ReceiptItemInfo.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT ReceiptItem
{
public:
    ReceiptItem();

    ReceiptItemInfo info() const;
    void setInfo(const ReceiptItemInfo &newInfo);
    QVector<Consumer> consumers() const;
    void setConsumers(const QVector<Consumer> &newConsumers);

private:
    ReceiptItemInfo m_info;
    QVector<Consumer> m_consumers;
};

} // namespace Domain
} // namespace Sea

#endif // RECEIPTITEM_H
