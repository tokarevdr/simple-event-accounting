#include "ReceiptsInfoViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {
ReceiptsInfoViewModel::ReceiptsInfoViewModel(ReceiptViewModel &receiptViewModel,
                                             Application::IReceiptsInfoRepository &repository,
                                             QObject *parent)
    : QAbstractListModel(parent)
    , m_receiptViewModel{receiptViewModel}
    , m_repository{repository}
{}

int ReceiptsInfoViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_receipts.count();
}

QVariant ReceiptsInfoViewModel::data(const QModelIndex &index, int role) const
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
            return receipt.buyer().has_value() ? receipt.buyer().value().name() : "-";
        case BuyerIdRole:
            return receipt.buyer().has_value() ? receipt.buyer().value().id() : -1;
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ReceiptsInfoViewModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IdRole] = "idRole";
    names[TitleRole] = "titleRole";
    names[PurchaseDateRole] = "purchaseDateRole";
    names[PurchaseTimeRole] = "purchaseTimeRole";
    names[BuyerNameRole] = "buyerNameRole";
    names[BuyerIdRole] = "buyerIdRole";

    return names;
}

void ReceiptsInfoViewModel::setEventId(qint32 id)
{
    if (id == m_eventId) {
        return;
    }

    m_eventId = id;

    if (id == -1) {
        beginResetModel();
        m_receipts.clear();
        endResetModel();
        return;
    }

    auto result = m_repository.readReceiptsInfo(id);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginResetModel();
    m_receipts = result.value();
    endResetModel();
}

void ReceiptsInfoViewModel::createReceipt(const QString &title,
                                      const QDate &purchaseDate,
                                      const QTime &purchaseTime,
                                      qint32 buyerId,
                                      const QString &buyerName)
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

    Domain::ReceiptInfo receipt;
    receipt.setEventId(m_eventId);
    receipt.setTitle(title);
    receipt.setPurchaseDateTime(QDateTime(purchaseDate, purchaseTime));

    if (buyerId == -1) {
        receipt.setBuyer(std::nullopt);
    } else {
        Domain::User buyer;
        buyer.setId(buyerId);
        buyer.setName(buyerName);
        receipt.setBuyer(buyer);
    }

    auto result = m_repository.createReceipt(receipt);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    receipt.setId(result.value());

    beginInsertRows(QModelIndex(), m_receipts.count(), m_receipts.count());
    m_receipts.append(receipt);
    endInsertRows();
}

void ReceiptsInfoViewModel::updateReceiptInfo(int index,
                                              const QString &title,
                                              const QDate &purchaseDate,
                                              const QTime &purchaseTime,
                                              qint32 buyerId,
                                              const QString &buyerName)
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

    Domain::ReceiptInfo receipt = m_receipts[index];
    receipt.setEventId(m_eventId);
    receipt.setTitle(title);
    receipt.setPurchaseDateTime(QDateTime(purchaseDate, purchaseTime));

    if (buyerId == -1) {
        receipt.setBuyer(std::nullopt);
    } else {
        Domain::User buyer;
        buyer.setId(buyerId);
        buyer.setName(buyerName);
        receipt.setBuyer(buyer);
    }

    auto result = m_repository.updateReceiptInfo(receipt);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    QModelIndex modelIndex = QAbstractListModel::index(index);

    m_receipts.replace(index, receipt);
    dataChanged(modelIndex, modelIndex);
}

void ReceiptsInfoViewModel::deleteReceipt(int index)
{
    qint32 id = m_receipts[index].id();

    auto result = m_repository.deleteReceipt(id);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_receipts.removeAt(index);
    endRemoveRows();
}

void ReceiptsInfoViewModel::selectReceipt(int index)
{
    if (index < 0 || index >= m_receipts.count()) {
        m_receiptViewModel.setReceiptInfo(std::nullopt);
        return;
    }

    m_receiptViewModel.setReceiptInfo(m_receipts[index]);
}
} // namespace Presentation
} // namespace Sea
