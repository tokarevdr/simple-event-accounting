#include "ReceiptItem.h"

namespace Sea {
namespace Domain {

ReceiptItem::ReceiptItem() {}

qint32 ReceiptItem::id() const
{
    return m_id;
}

void ReceiptItem::setId(
    qint32 newId)
{
    m_id = newId;
}

qint32 ReceiptItem::receiptId() const
{
    return m_receiptId;
}

void ReceiptItem::setReceiptId(
    qint32 newReceiptId)
{
    m_receiptId = newReceiptId;
}

QString ReceiptItem::name() const
{
    return m_name;
}

void ReceiptItem::setName(
    const QString &newName)
{
    m_name = newName;
}

qint32 ReceiptItem::price() const
{
    return m_price;
}

void ReceiptItem::setPrice(
    qint32 newPrice)
{
    m_price = newPrice;
}

qint32 ReceiptItem::count() const
{
    return m_count;
}

void ReceiptItem::setCount(
    qint32 newCount)
{
    m_count = newCount;
}

} // namespace Domain
} // namespace Sea
