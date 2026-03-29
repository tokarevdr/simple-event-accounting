#ifndef RECEIPTSINFOVIEWMODEL_H
#define RECEIPTSINFOVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IReceiptsInfoRepository.h"
#include "ReceiptViewModel.h"

namespace Sea {
namespace Presentation {
class ReceiptsInfoViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, TitleRole, PurchaseDateRole, PurchaseTimeRole, BuyerNameRole, BuyerIdRole };

    explicit ReceiptsInfoViewModel(ReceiptViewModel &receiptViewModel,
                                   Application::IReceiptsInfoRepository &repository,
                                   QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setEventId(qint32 id);

    Q_INVOKABLE void createReceipt(const QString &title,
                                   const QDate &purchaseDate,
                                   const QTime &purchaseTime,
                                   qint32 buyerId,
                                   const QString &buyerName);

    Q_INVOKABLE void updateReceiptInfo(int index,
                                       const QString &title,
                                       const QDate &purchaseDate,
                                       const QTime &purchaseTime,
                                       qint32 buyerId,
                                       const QString &buyerName);

    Q_INVOKABLE void deleteReceipt(int index);

    Q_INVOKABLE void selectReceipt(int index);

private:
    qint32 m_eventId = -1;
    QVector<Domain::ReceiptInfo> m_receipts;
    ReceiptViewModel &m_receiptViewModel;
    Application::IReceiptsInfoRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // RECEIPTSINFOVIEWMODEL_H
