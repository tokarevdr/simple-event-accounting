#ifndef RECEIPTITEMSVIEWMODEL_H
#define RECEIPTITEMSVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IReceiptItemsRepository.h"
#include "AsyncExecutor.h"
#include "Entities/ReceiptItem.h"

namespace Sea {
namespace Presentation {

class ReceiptItemsViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, NameRole, PriceRole, CountRole };

    explicit ReceiptItemsViewModel(Utils::AsyncExecutor &executor,
                                   Application::IReceiptItemsRepository &repository,
                                   QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setReceiptId(qint32 id);

    Q_INVOKABLE void createReceiptItem(const QString &name, int price, int count);

    Q_INVOKABLE void updateReceiptItem(int index, const QString &name, int price, int count);

    Q_INVOKABLE void deleteReceiptItem(int index);

private:
    Utils::AsyncExecutor &m_executor;
    qint32 m_receiptId = -1;
    QVector<Domain::ReceiptItem> m_receiptItems;
    Application::IReceiptItemsRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // RECEIPTITEMSVIEWMODEL_H
