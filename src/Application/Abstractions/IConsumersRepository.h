#ifndef ICONSUMERSREPOSITORY_H
#define ICONSUMERSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/Consumer.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {

class APPLICATION_EXPORT IConsumersRepository
{
public:
    IConsumersRepository();

    virtual ~IConsumersRepository() = default;

    virtual Utils::Result<Utils::Unit, QString> createConsumer(const Domain::Consumer &consumer) = 0;

    virtual Utils::Result<QVector<Domain::Consumer>, QString> readConsumers(qint32 receiptItemId) = 0;
};

} // namespace Application
} // namespace Sea

#endif // ICONSUMERSREPOSITORY_H
