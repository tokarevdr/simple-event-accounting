#ifndef RECEIPTSVIEWMODEL_H
#define RECEIPTSVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IReceiptsRepository.h"
#include "AsyncExecutor.h"
#include "Entities/Receipt.h"

namespace Sea {
namespace Presentation {

class ReceiptsViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, TitleRole, PurchaseDateRole, PurchaseTimeRole, BuyerNameRole };

    explicit ReceiptsViewModel(Utils::AsyncExecutor &executor,
                               Application::IReceiptsRepository &repository,
                               QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setEventId(qint32 id);

    Q_INVOKABLE void createReceipt(const QString &title,
                                   const QDate &purchaseDate,
                                   const QTime &purchaseTime,
                                   qint32 buyerId,
                                   const QString &buyerName);

    Q_INVOKABLE void updateReceipt(int index,
                                   const QString &title,
                                   const QDate &purchaseDate,
                                   const QTime &purchaseTime,
                                   qint32 buyerId,
                                   const QString &buyerName);

    Q_INVOKABLE void deleteReceipt(int index);

private:
    Utils::AsyncExecutor &m_executor;
    qint32 m_eventId = -1;
    QVector<Domain::Receipt> m_receipts;
    Application::IReceiptsRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // RECEIPTSVIEWMODEL_H
