#ifndef USER_H
#define USER_H

#include <QString>

#include "Domain_global.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT User
{
public:
    User();

    qint32 id() const;
    void setId(qint32 newId);
    QString name() const;
    void setName(const QString &newName);

    bool operator==(const User &other) const;

private:
    qint32 m_id = -1;
    QString m_name = "-";
};

} // namespace Domain
} // namespace Sea

#endif // USER_H
