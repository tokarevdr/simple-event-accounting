#ifndef RECEIPTITEMSINFOVIEWMODEL_H
#define RECEIPTITEMSINFOVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IReceiptItemsInfoRepository.h"
#include "ReceiptItemViewModel.h"

namespace Sea {
namespace Presentation {
class ReceiptItemsInfoViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, NameRole, PriceRole, CountRole };

    explicit ReceiptItemsInfoViewModel(ReceiptItemViewModel &receiptItemViewModel,
                                       Application::IReceiptItemsInfoRepository &repository,
                                       QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setReceiptId(qint32 id);

    Q_INVOKABLE void createReceiptItem(const QString &name, int price, int count);

    Q_INVOKABLE void updateReceiptItemInfo(int index, const QString &name, int price, int count);

    Q_INVOKABLE void deleteReceiptItem(int index);

    Q_INVOKABLE void selectReceiptItem(int index);

private:
    qint32 m_receiptId = -1;
    QVector<Domain::ReceiptItemInfo> m_receiptItems;
    ReceiptItemViewModel &m_receiptItemViewModel;
    Application::IReceiptItemsInfoRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // RECEIPTITEMSINFOVIEWMODEL_H
