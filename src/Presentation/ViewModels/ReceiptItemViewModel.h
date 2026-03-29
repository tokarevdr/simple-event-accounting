#ifndef RECEIPTITEMVIEWMODEL_H
#define RECEIPTITEMVIEWMODEL_H

#include <optional>

#include <QObject>

#include "Entities/ReceiptItemInfo.h"
#include "ViewModels/ConsumersViewModel.h"

namespace Sea {
namespace Presentation {
class ReceiptItemViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(qint32 price READ price WRITE setPrice NOTIFY priceChanged FINAL)
    Q_PROPERTY(qint32 count READ count WRITE setCount NOTIFY countChanged FINAL)
public:
    explicit ReceiptItemViewModel(ConsumersViewModel &consumersViewModel, QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &newName);

    qint32 price() const;
    void setPrice(qint32 newPrice);

    qint32 count() const;
    void setCount(qint32 newCount);

    void setReceiptItemInfo(const std::optional<Domain::ReceiptItemInfo> &receiptItemInfo);

signals:
    void nameChanged();

    void priceChanged();

    void countChanged();

private:
    QString m_name;
    qint32 m_price;
    qint32 m_count;

    ConsumersViewModel &m_consumersViewModel;
};
} // namespace Presentation
} // namespace Sea

#endif // RECEIPTITEMVIEWMODEL_H
