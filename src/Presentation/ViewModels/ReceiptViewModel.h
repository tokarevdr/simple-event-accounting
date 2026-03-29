#ifndef RECEIPTVIEWMODEL_H
#define RECEIPTVIEWMODEL_H

#include <optional>

#include <QObject>

#include "Entities/ReceiptInfo.h"
#include "ReceiptItemsInfoViewModel.h"

namespace Sea {
namespace Presentation {
class ReceiptViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QDateTime purchaseDateTime READ purchaseDateTime WRITE setPurchaseDateTime NOTIFY
                   purchaseDateTimeChanged FINAL)
    Q_PROPERTY(QString buyerName READ buyerName WRITE setBuyerName NOTIFY buyerNameChanged FINAL)
public:
    explicit ReceiptViewModel(ReceiptItemsInfoViewModel &receiptItemsInfoViewModel,
                              QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);

    QDateTime purchaseDateTime() const;
    void setPurchaseDateTime(const QDateTime &newPurchaseDateTime);

    QString buyerName() const;
    void setBuyerName(const QString &newBuyerName);

    void setReceiptInfo(const std::optional<Domain::ReceiptInfo> &receiptInfo);

signals:
    void titleChanged();

    void purchaseDateTimeChanged();

    void buyerNameChanged();

private:
    QString m_title;
    QDateTime m_purchaseDateTime;
    QString m_buyerName;

    ReceiptItemsInfoViewModel &m_receiptItemsInfoViewModel;
};
} // namespace Presentation
} // namespace Sea

#endif // RECEIPTVIEWMODEL_H
