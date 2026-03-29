#include "ReceiptItemViewModel.h"

namespace Sea {
namespace Presentation {
ReceiptItemViewModel::ReceiptItemViewModel(ConsumersViewModel &consumersViewModel, QObject *parent)
    : QObject{parent}
    , m_consumersViewModel{consumersViewModel}
{}

QString ReceiptItemViewModel::name() const
{
    return m_name;
}

void ReceiptItemViewModel::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

qint32 ReceiptItemViewModel::price() const
{
    return m_price;
}

void ReceiptItemViewModel::setPrice(qint32 newPrice)
{
    if (m_price == newPrice)
        return;
    m_price = newPrice;
    emit priceChanged();
}

qint32 ReceiptItemViewModel::count() const
{
    return m_count;
}

void ReceiptItemViewModel::setCount(qint32 newCount)
{
    if (m_count == newCount)
        return;
    m_count = newCount;
    emit countChanged();
}

void ReceiptItemViewModel::setReceiptItemInfo(
    const std::optional<Domain::ReceiptItemInfo> &receiptItemInfo)
{
    if (!receiptItemInfo.has_value()) {
        setName("");
        setCount(0);
        setPrice(0);
        m_consumersViewModel.setReceiptItemId(-1);
        return;
    }

    setName(receiptItemInfo.value().name());
    setCount(receiptItemInfo.value().count());
    setPrice(receiptItemInfo.value().price());
    m_consumersViewModel.setReceiptItemId(receiptItemInfo.value().id());
}
} // namespace Presentation
} // namespace Sea
