#ifndef IRECEIPTSINFOREPOSITORY_H
#define IRECEIPTSINFOREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/ReceiptInfo.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {
class APPLICATION_EXPORT IReceiptsInfoRepository
{
public:
    IReceiptsInfoRepository();

    virtual ~IReceiptsInfoRepository() = default;

    virtual Utils::Result<qint32, QString> createReceipt(const Domain::ReceiptInfo &receiptInfo) = 0;

    virtual Utils::Result<QVector<Domain::ReceiptInfo>, QString> readReceiptsInfo(qint32 eventId) = 0;

    virtual Utils::Result<Utils::Unit, QString>
    updateReceiptInfo(const Domain::ReceiptInfo &receiptInfo) = 0;

    virtual Utils::Result<Utils::Unit, QString> deleteReceipt(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IRECEIPTSINFOREPOSITORY_H
