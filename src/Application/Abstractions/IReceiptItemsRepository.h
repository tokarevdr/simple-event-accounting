#ifndef IRECEIPTITEMSREPOSITORY_H
#define IRECEIPTITEMSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/ReceiptItem.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IReceiptItemsRepository
{
public:
    IReceiptItemsRepository();

    virtual ~IReceiptItemsRepository() = default;

    virtual qint32 createReceiptItem(const Domain::ReceiptItem &receiptItem) = 0;

    virtual QVector<Domain::ReceiptItem> readReceiptItems(qint32 receiptId) = 0;

    virtual bool updateReceiptItem(const Domain::ReceiptItem &receiptItem) = 0;

    virtual bool deleteReceiptItem(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IRECEIPTITEMSREPOSITORY_H
