#ifndef RECEIPT_H
#define RECEIPT_H

#include <QVector>

#include "User.h"
#include "ReceiptInfo.h"
#include "ReceiptItem.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT Receipt
{
public:
    Receipt();

    ReceiptInfo info() const;
    void setInfo(const ReceiptInfo &newInfo);
    QVector<ReceiptItem> items() const;
    void setItems(const QVector<ReceiptItem> &newItems);

private:
    ReceiptInfo m_info;
    QVector<ReceiptItem> m_items;
};

} // namespace Domain
} // namespace Sea

#endif // RECEIPT_H
