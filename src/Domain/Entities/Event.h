#ifndef EVENT_H
#define EVENT_H

#include <optional>

#include <QDate>
#include <QString>

#include "Domain_global.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT Event
{
public:
    Event();

    qint32 id() const;
    void setId(qint32 newId);
    QString title() const;
    void setTitle(const QString &newTitle);
    std::optional<QDate> startDate() const;
    void setStartDate(std::optional<QDate> newStartDate);
    std::optional<QDate> endDate() const;
    void setEndDate(std::optional<QDate> newEndDate);

private:
    qint32 m_id = 0;
    QString m_title;
    std::optional<QDate> m_startDate = std::nullopt;
    std::optional<QDate> m_endDate = std::nullopt;
};

} // namespace Domain
} // namespace Sea

#endif // EVENT_H
