#include "ReceiptViewModel.h"

namespace Sea {
namespace Presentation {
ReceiptViewModel::ReceiptViewModel(ReceiptItemsInfoViewModel &receiptItemsInfoViewModel,
                                   QObject *parent)
    : QObject{parent}
    , m_receiptItemsInfoViewModel{receiptItemsInfoViewModel}
{}

QString ReceiptViewModel::title() const
{
    return m_title;
}

void ReceiptViewModel::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

QDateTime ReceiptViewModel::purchaseDateTime() const
{
    return m_purchaseDateTime;
}

void ReceiptViewModel::setPurchaseDateTime(const QDateTime &newPurchaseDateTime)
{
    if (m_purchaseDateTime == newPurchaseDateTime)
        return;
    m_purchaseDateTime = newPurchaseDateTime;
    emit purchaseDateTimeChanged();
}

QString ReceiptViewModel::buyerName() const
{
    return m_buyerName;
}

void ReceiptViewModel::setBuyerName(const QString &newBuyerName)
{
    if (m_buyerName == newBuyerName)
        return;
    m_buyerName = newBuyerName;
    emit buyerNameChanged();
}

void ReceiptViewModel::setReceiptInfo(const std::optional<Domain::ReceiptInfo> &receiptInfo)
{
    if (!receiptInfo.has_value()) {
        setTitle("");
        setPurchaseDateTime(QDateTime());
        setBuyerName("");
        m_receiptItemsInfoViewModel.setReceiptId(-1);
        return;
    }

    setTitle(receiptInfo.value().title());
    setPurchaseDateTime(receiptInfo.value().purchaseDateTime());

    auto buyer = receiptInfo.value().buyer();

    if (buyer.has_value()) {
        setBuyerName(buyer.value().name());
    } else {
        setBuyerName("-");
    }

    m_receiptItemsInfoViewModel.setReceiptId(receiptInfo.value().id());
}
} // namespace Presentation
} // namespace Sea
