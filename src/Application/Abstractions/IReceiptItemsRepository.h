#ifndef IRECEIPTITEMSREPOSITORY_H
#define IRECEIPTITEMSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/ReceiptItem.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IReceiptItemsRepository
{
public:
    IReceiptItemsRepository();

    virtual ~IReceiptItemsRepository() = default;

    virtual Utils::Result<qint32, QString> createReceiptItem(const Domain::ReceiptItem &receiptItem)
        = 0;

    virtual Utils::Result<QVector<Domain::ReceiptItem>, QString> readReceiptItems(qint32 receiptId)
        = 0;

    virtual Utils::Result<Utils::Unit, QString>
    updateReceiptItem(const Domain::ReceiptItem &receiptItem) = 0;

    virtual Utils::Result<Utils::Unit, QString> deleteReceiptItem(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IRECEIPTITEMSREPOSITORY_H
