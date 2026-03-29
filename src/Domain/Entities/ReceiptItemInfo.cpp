#include "ReceiptItemInfo.h"

namespace Sea {
namespace Domain {

ReceiptItemInfo::ReceiptItemInfo() {}

qint32 ReceiptItemInfo::id() const
{
    return m_id;
}

void ReceiptItemInfo::setId(qint32 newId)
{
    m_id = newId;
}

qint32 ReceiptItemInfo::receiptId() const
{
    return m_receiptId;
}

void ReceiptItemInfo::setReceiptId(qint32 newReceiptId)
{
    m_receiptId = newReceiptId;
}

QString ReceiptItemInfo::name() const
{
    return m_name;
}

void ReceiptItemInfo::setName(const QString &newName)
{
    m_name = newName;
}

qint32 ReceiptItemInfo::price() const
{
    return m_price;
}

void ReceiptItemInfo::setPrice(qint32 newPrice)
{
    m_price = newPrice;
}

qint32 ReceiptItemInfo::count() const
{
    return m_count;
}

void ReceiptItemInfo::setCount(qint32 newCount)
{
    m_count = newCount;
}

} // namespace Domain
} // namespace Sea
