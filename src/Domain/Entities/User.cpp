#include "User.h"

namespace Sea {
namespace Domain {

User::User() {}

qint32 User::id() const
{
    return m_id;
}

void User::setId(qint32 newId)
{
    m_id = newId;
}

QString User::name() const
{
    return m_name;
}

void User::setName(const QString &newName)
{
    m_name = newName;
}

bool User::operator==(const User &other) const
{
    return m_id == other.m_id;
}

} // namespace Domain
} // namespace Sea
