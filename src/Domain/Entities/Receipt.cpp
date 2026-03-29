#include "Receipt.h"

namespace Sea {
namespace Domain {

Receipt::Receipt() {}

ReceiptInfo Receipt::info() const
{
    return m_info;
}

void Receipt::setInfo(
    const ReceiptInfo &newInfo)
{
    m_info = newInfo;
}

QVector<ReceiptItem> Receipt::items() const
{
    return m_items;
}

void Receipt::setItems(
    const QVector<ReceiptItem> &newItems)
{
    m_items = newItems;
}

} // namespace Domain
} // namespace Sea
