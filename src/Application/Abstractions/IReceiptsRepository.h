#ifndef IRECEIPTSREPOSITORY_H
#define IRECEIPTSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/Receipt.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IReceiptsRepository
{
public:
    IReceiptsRepository();

    virtual ~IReceiptsRepository() = default;

    virtual qint32 createReceipt(const Domain::Receipt &receipt) = 0;

    virtual QVector<Domain::Receipt> readReceipts(qint32 eventId) = 0;

    virtual bool updateReceipt(const Domain::Receipt &receipt) = 0;

    virtual bool deleteReceipt(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IRECEIPTSREPOSITORY_H
