#include "ReceiptItemsInfoViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {
ReceiptItemsInfoViewModel::ReceiptItemsInfoViewModel(
    ConsumersViewModel &consumersViewModel,
    Application::IReceiptItemsInfoRepository &repository,
    QObject *parent)
    : QAbstractListModel(parent)
    , m_consumersViewModel{consumersViewModel}
    , m_repository{repository}
{}

int ReceiptItemsInfoViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_receiptItems.count();
}

QVariant ReceiptItemsInfoViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &receiptItem = m_receiptItems[index.row()];

    switch (role) {
        case IdRole:
            return receiptItem.id();
        case NameRole:
            return receiptItem.name();
        case PriceRole:
            return receiptItem.price();
        case CountRole:
            return receiptItem.count();
        case ConsumersRole:
            return QVariant::fromValue(&m_consumersViewModel);
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ReceiptItemsInfoViewModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IdRole] = "idRole";
    names[NameRole] = "nameRole";
    names[PriceRole] = "priceRole";
    names[CountRole] = "countRole";
    names[ConsumersRole] = "consumersRole";

    return names;
}

void ReceiptItemsInfoViewModel::setReceiptId(qint32 id)
{
    if (id == m_receiptId) {
        return;
    }

    m_receiptId = id;

    if (id == -1) {
        beginResetModel();
        m_receiptItems.clear();
        endResetModel();
        return;
    }

    auto result = m_repository.readReceiptItemsInfo(id);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginResetModel();
    m_receiptItems = result.value();
    endResetModel();
}

void ReceiptItemsInfoViewModel::createReceiptItem(const QString &name, int price, int count)
{
    if (m_receiptId == -1) {
        qDebug() << "No receipt selected.";
        return;
    }

    if (name.isEmpty()) {
        qDebug() << "Name should not be empty.";
        return;
    }

    if (price <= 0) {
        qDebug() << "Price should be greater that zero.";
        return;
    }

    if (count < 1) {
        qDebug() << "Count should be greater that zero.";
        return;
    }

    Domain::ReceiptItemInfo receiptItem;
    receiptItem.setReceiptId(m_receiptId);
    receiptItem.setName(name);
    receiptItem.setPrice(price);
    receiptItem.setCount(count);

    auto result = m_repository.createReceiptItem(receiptItem);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    receiptItem.setId(result.value());

    beginInsertRows(QModelIndex(), m_receiptItems.count(), m_receiptItems.count());
    m_receiptItems.append(receiptItem);
    endInsertRows();
}

void ReceiptItemsInfoViewModel::updateReceiptItemInfo(int index, const QString &name, int price, int count)
{
    if (m_receiptId == -1) {
        qDebug() << "No receipt selected.";
        return;
    }

    if (name.isEmpty()) {
        qDebug() << "Name should not be empty.";
        return;
    }

    if (price <= 0) {
        qDebug() << "Price should be greater that zero.";
        return;
    }

    if (count < 1) {
        qDebug() << "Count should be greater that zero.";
        return;
    }

    Domain::ReceiptItemInfo receiptItem = m_receiptItems[index];
    receiptItem.setReceiptId(m_receiptId);
    receiptItem.setName(name);
    receiptItem.setPrice(price);
    receiptItem.setCount(count);

    auto result = m_repository.updateReceiptItemInfo(receiptItem);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    QModelIndex modelIndex = QAbstractListModel::index(index);

    m_receiptItems.replace(index, receiptItem);
    dataChanged(modelIndex, modelIndex);
}

void ReceiptItemsInfoViewModel::deleteReceiptItem(int index)
{
    qint32 id = m_receiptItems[index].id();

    auto result = m_repository.deleteReceiptItem(id);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_receiptItems.removeAt(index);
    endRemoveRows();
}

void ReceiptItemsInfoViewModel::selectReceiptItem(int index)
{
    if (index < 0 || index > m_receiptItems.count()) {
        m_consumersViewModel.setReceiptItemId(-1);
        return;
    }

    m_consumersViewModel.setReceiptItemId(m_receiptItems[index].id());
}
} // namespace Presentation
} // namespace Sea
