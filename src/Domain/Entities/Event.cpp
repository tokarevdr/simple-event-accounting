#include "Event.h"

namespace Sea {
namespace Domain {

Event::Event() {}

qint32 Event::id() const
{
    return m_id;
}

void Event::setId(
    qint32 newId)
{
    m_id = newId;
}

QString Event::title() const
{
    return m_title;
}

void Event::setTitle(
    const QString &newTitle)
{
    m_title = newTitle;
}

std::optional<QDate> Event::startDate() const
{
    return m_startDate;
}

void Event::setStartDate(
    std::optional<QDate> newStartDate)
{
    m_startDate = newStartDate;
}

std::optional<QDate> Event::endDate() const
{
    return m_endDate;
}

void Event::setEndDate(
    std::optional<QDate> newEndDate)
{
    m_endDate = newEndDate;
}

} // namespace Domain
} // namespace Sea
