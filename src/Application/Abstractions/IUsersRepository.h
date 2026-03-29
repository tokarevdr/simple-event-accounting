#ifndef IUSERSREPOSITORY_H
#define IUSERSREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/User.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {
class APPLICATION_EXPORT IUsersRepository
{
public:
    IUsersRepository();

    virtual ~IUsersRepository() = default;

    virtual Utils::Result<qint32, QString> createUser(const Domain::User &user) = 0;

    virtual Utils::Result<QVector<Domain::User>, QString> readUsers() = 0;

    virtual Utils::Result<Utils::Unit, QString> updateUser(const Domain::User &user) = 0;

    virtual Utils::Result<Utils::Unit, QString> deleteUser(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IUSERSREPOSITORY_H
