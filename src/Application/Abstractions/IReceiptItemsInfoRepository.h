#ifndef IRECEIPTITEMSINFOREPOSITORY_H
#define IRECEIPTITEMSINFOREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/ReceiptItemInfo.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {
class APPLICATION_EXPORT IReceiptItemsInfoRepository
{
public:
    IReceiptItemsInfoRepository();

    virtual ~IReceiptItemsInfoRepository() = default;

    virtual Utils::Result<qint32, QString>
    createReceiptItem(const Domain::ReceiptItemInfo &receiptItemInfo) = 0;

    virtual Utils::Result<QVector<Domain::ReceiptItemInfo>, QString>
    readReceiptItemsInfo(qint32 receiptId) = 0;

    virtual Utils::Result<Utils::Unit, QString>
    updateReceiptItemInfo(const Domain::ReceiptItemInfo &receiptItemInfo) = 0;

    virtual Utils::Result<Utils::Unit, QString> deleteReceiptItem(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IRECEIPTITEMSINFOREPOSITORY_H
