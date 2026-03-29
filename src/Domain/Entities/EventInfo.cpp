#include "EventInfo.h"

namespace Sea {
namespace Domain {

EventInfo::EventInfo() {}

qint32 EventInfo::id() const
{
    return m_id;
}

void EventInfo::setId(
    qint32 newId)
{
    m_id = newId;
}

QString EventInfo::title() const
{
    return m_title;
}

void EventInfo::setTitle(
    const QString &newTitle)
{
    m_title = newTitle;
}

QDate EventInfo::startDate() const
{
    return m_startDate;
}

void EventInfo::setStartDate(const QDate &newStartDate)
{
    m_startDate = newStartDate;
}

QDate EventInfo::endDate() const
{
    return m_endDate;
}

void EventInfo::setEndDate(const QDate &newEndDate)
{
    m_endDate = newEndDate;
}

} // namespace Domain
} // namespace Sea
