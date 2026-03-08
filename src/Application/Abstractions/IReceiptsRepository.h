#ifndef IRECEIPTSREPOSITORY_H
#define IRECEIPTSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/Receipt.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IReceiptsRepository
{
public:
    IReceiptsRepository();

    virtual ~IReceiptsRepository() = default;

    virtual Utils::Result<qint32, QString> createReceipt(const Domain::Receipt &receipt) = 0;

    virtual Utils::Result<QVector<Domain::Receipt>, QString> readReceipts(qint32 eventId) = 0;

    virtual Utils::Result<Utils::Unit, QString> updateReceipt(const Domain::Receipt &receipt) = 0;

    virtual Utils::Result<Utils::Unit, QString> deleteReceipt(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IRECEIPTSREPOSITORY_H
