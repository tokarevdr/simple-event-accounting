#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QString>

#include "Domain_global.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT Participant
{
public:
    Participant();

    qint32 id() const;
    void setId(qint32 newId);
    QString name() const;
    void setName(const QString &newName);

private:
    qint32 m_id = -1;
    QString m_name = "-";
};

} // namespace Domain
} // namespace Sea

#endif // PARTICIPANT_H
