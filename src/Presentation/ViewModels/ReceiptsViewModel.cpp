#include "ReceiptsViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {

ReceiptsViewModel::ReceiptsViewModel(AsyncExecutor &executor,
                                     Application::IReceiptsRepository &repository,
                                     QObject *parent)
    : QAbstractListModel(parent)
    , m_executor{executor}
    , m_repository{repository}
{}

int ReceiptsViewModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    return m_receipts.count();
}

QVariant ReceiptsViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &receipt = m_receipts[index.row()];

    switch (role) {
        case IdRole:
            return receipt.id();
        case TitleRole:
            return receipt.title();
        case PurchaseDateRole:
            return receipt.purchaseDateTime().date();
        case PurchaseTimeRole:
            return receipt.purchaseDateTime().time();
        case BuyerNameRole:
            return receipt.buyer().has_value() ? receipt.buyer().value().name() : "";
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ReceiptsViewModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IdRole] = "idRole";
    names[TitleRole] = "titleRole";
    names[PurchaseDateRole] = "purchaseDateRole";
    names[PurchaseTimeRole] = "purchaseTimeRole";
    names[BuyerNameRole] = "buyerNameRole";

    return names;
}

void ReceiptsViewModel::setEventId(qint32 id)
{
    m_eventId = id;

    if (id == -1) {
        beginResetModel();
        m_receipts.clear();
        endResetModel();
        return;
    }

    m_executor.exec<QVector<Domain::Receipt>>([this, id]() { return m_repository.readReceipts(id); },
                                              [this](const QVector<Domain::Receipt> &receipts) {
                                                  beginResetModel();
                                                  m_receipts = receipts;
                                                  endResetModel();
                                                  qDebug() << receipts.count();
                                              });
}

void ReceiptsViewModel::createReceipt(const QString &title,
                                      const QDate &purchaseDate,
                                      const QTime &purchaseTime,
                                      qint32 buyerId)
{
    if (m_eventId == -1) {
        qDebug() << "No event selected.";
        return;
    }

    if (title.isEmpty()) {
        qDebug() << "Title should not be empty.";
        return;
    }

    if (!purchaseDate.isValid()) {
        qDebug() << "Purchase date is invalid.";
        return;
    }

    if (!purchaseTime.isValid()) {
        qDebug() << "Purchase time is invalid.";
        return;
    }

    Domain::Receipt receipt;
    receipt.setEventId(m_eventId);
    receipt.setTitle(title);
    receipt.setPurchaseDateTime(QDateTime(purchaseDate, purchaseTime));

    if (buyerId == -1) {
        receipt.setBuyer(std::nullopt);
    } else {
        Domain::Participant buyer;
        buyer.setId(buyerId);
        receipt.setBuyer(buyer);
    }

    m_executor.exec<qint32>([this, receipt]() { return m_repository.createReceipt(receipt); },
                            [this, &receipt](const qint32 &id) {
                                receipt.setId(id);

                                beginInsertRows(QModelIndex(),
                                                m_receipts.count(),
                                                m_receipts.count());
                                m_receipts.append(receipt);
                                endInsertRows();
                            });
}

void ReceiptsViewModel::updateReceipt(int index,
                                      const QString &title,
                                      const QDate &purchaseDate,
                                      const QTime &purchaseTime,
                                      qint32 buyerId)
{}

void ReceiptsViewModel::deleteReceipt(int index) {}

} // namespace Presentation
} // namespace Sea
