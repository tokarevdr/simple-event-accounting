#ifndef EVENTINFO_H
#define EVENTINFO_H

#include <QDate>
#include <QString>

#include "Domain_global.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT EventInfo
{
public:
    EventInfo();

    qint32 id() const;
    void setId(qint32 newId);
    QString title() const;
    void setTitle(const QString &newTitle);
    QDate startDate() const;
    void setStartDate(const QDate &newStartDate);
    QDate endDate() const;
    void setEndDate(const QDate &newEndDate);

private:
    qint32 m_id = 0;
    QString m_title;
    QDate m_startDate;
    QDate m_endDate;
};

} // namespace Domain
} // namespace Sea

#endif // EVENTINFO_H
