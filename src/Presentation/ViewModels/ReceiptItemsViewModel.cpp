#include "ReceiptItemsViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {

ReceiptItemsViewModel::ReceiptItemsViewModel(
    Utils::AsyncExecutor &executor,
    Application::IReceiptItemsRepository &repository,
    QObject *parent)
    : QAbstractListModel(parent)
    , m_executor{executor}
    , m_repository{repository}
{}

int ReceiptItemsViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_receiptItems.count();
}

QVariant ReceiptItemsViewModel::data(const QModelIndex &index, int role) const
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
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ReceiptItemsViewModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IdRole] = "idRole";
    names[NameRole] = "nameRole";
    names[PriceRole] = "priceRole";
    names[CountRole] = "countRole";

    return names;
}

void ReceiptItemsViewModel::setReceiptId(qint32 id)
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

    m_executor
        .exec<QVector<Domain::ReceiptItem>>([this,
                                             id]() { return m_repository.readReceiptItems(id); },
                                            [this](
                                                const QVector<Domain::ReceiptItem> &receiptItems) {
                                                beginResetModel();
                                                m_receiptItems = receiptItems;
                                                endResetModel();
                                                qDebug() << receiptItems.count();
                                            });
}

void ReceiptItemsViewModel::createReceiptItem(const QString &name, int price, int count)
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

    Domain::ReceiptItem receiptItem;
    receiptItem.setReceiptId(m_receiptId);
    receiptItem.setName(name);
    receiptItem.setPrice(price);
    receiptItem.setCount(count);

    m_executor.exec<qint32>([this,
                             receiptItem]() { return m_repository.createReceiptItem(receiptItem); },
                            [this, &receiptItem](const qint32 &id) {
                                receiptItem.setId(id);

                                beginInsertRows(QModelIndex(),
                                                m_receiptItems.count(),
                                                m_receiptItems.count());
                                m_receiptItems.append(receiptItem);
                                endInsertRows();
                            });
}

void ReceiptItemsViewModel::updateReceiptItem(int index, const QString &name, int price, int count)
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

    Domain::ReceiptItem receiptItem = m_receiptItems[index];
    receiptItem.setReceiptId(m_receiptId);
    receiptItem.setName(name);
    receiptItem.setPrice(price);
    receiptItem.setCount(count);

    m_executor.exec<bool>([this,
                           receiptItem]() { return m_repository.updateReceiptItem(receiptItem); },
                          [this, &receiptItem, index](const bool &isOk) {
                              if (!isOk) {
                                  qDebug() << "Receipt item was not updated.";
                                  return;
                              }

                              QModelIndex modelIndex = QAbstractListModel::index(index);

                              m_receiptItems.replace(index, receiptItem);
                              dataChanged(modelIndex, modelIndex);
                          });
}

void ReceiptItemsViewModel::deleteReceiptItem(int index)
{
    qint32 id = m_receiptItems[index].id();

    m_executor.exec<bool>([this, id]() { return m_repository.deleteReceiptItem(id); },
                          [this, index](const bool &isOk) {
                              if (!isOk) {
                                  qDebug() << "Receipt item was not deleted.";
                                  return;
                              }

                              beginRemoveRows(QModelIndex(), index, index);
                              m_receiptItems.removeAt(index);
                              endRemoveRows();
                          });
}

} // namespace Presentation
} // namespace Sea
