#include "ReceiptItem.h"

namespace Sea {
namespace Domain {

ReceiptItem::ReceiptItem() {}

ReceiptItemInfo ReceiptItem::info() const
{
    return m_info;
}

void ReceiptItem::setInfo(const ReceiptItemInfo &newInfo)
{
    m_info = newInfo;
}

QVector<Consumer> ReceiptItem::consumers() const
{
    return m_consumers;
}

void ReceiptItem::setConsumers(const QVector<Consumer> &newConsumers)
{
    m_consumers = newConsumers;
}

} // namespace Domain
} // namespace Sea
