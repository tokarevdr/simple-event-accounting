#ifndef IEVENTUSERSREPOSITORY_H
#define IEVENTUSERSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/User.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {
class APPLICATION_EXPORT IEventUsersRepository
{
public:
    IEventUsersRepository();

    virtual ~IEventUsersRepository() = default;

    virtual Utils::Result<Utils::Unit, QString> createEventUser(qint32 eventId, qint32 userId) = 0;

    virtual Utils::Result<QVector<Domain::User>, QString> readEventUsers(qint32 eventId) = 0;

    virtual Utils::Result<Utils::Unit, QString> deleteEventUser(qint32 userId) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IEVENTUSERSREPOSITORY_H
