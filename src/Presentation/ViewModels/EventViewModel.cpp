#include "EventViewModel.h"

namespace Sea {
namespace Presentation {
EventViewModel::EventViewModel(ParticipantsViewModel &participantsViewModel,
                               ReceiptsInfoViewModel &receiptsInfoViewModel,
                               QObject *parent)
    : QObject{parent}
    , m_participantsViewModel{participantsViewModel}
    , m_receiptsInfoViewModel{receiptsInfoViewModel}
{}

QString EventViewModel::title() const
{
    return m_title;
}

void EventViewModel::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

QDate EventViewModel::startDate() const
{
    return m_startDate;
}

void EventViewModel::setStartDate(const QDate &newStartDate)
{
    if (m_startDate == newStartDate)
        return;
    m_startDate = newStartDate;
    emit startDateChanged();
}

QDate EventViewModel::endDate() const
{
    return m_endDate;
}

void EventViewModel::setEndDate(const QDate &newEndDate)
{
    if (m_endDate == newEndDate)
        return;
    m_endDate = newEndDate;
    emit endDateChanged();
}

void EventViewModel::setEventInfo(const std::optional<Domain::EventInfo> &eventInfo)
{
    if (!eventInfo.has_value()) {
        setTitle("");
        setStartDate(QDate());
        setEndDate(QDate());
        m_participantsViewModel.setEventId(-1);
        m_receiptsInfoViewModel.setEventId(-1);
        return;
    }

    setTitle(eventInfo.value().title());
    setStartDate(eventInfo.value().startDate());
    setEndDate(eventInfo.value().endDate());
    m_participantsViewModel.setEventId(eventInfo.value().id());
    m_receiptsInfoViewModel.setEventId(eventInfo.value().id());
}
} // namespace Presentation
} // namespace Sea
