#include "EventsInfoViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {
EventsInfoViewModel::EventsInfoViewModel(ParticipantsViewModel &participantsViewModel,
                                         ReceiptsInfoViewModel &receiptsInfoViewModel,
                                         Application::IEventsInfoRepository &repository,
                                         QObject *parent)
    : QAbstractListModel(parent)
    , m_participantsViewModel{participantsViewModel}
    , m_receiptsInfoViewModel{receiptsInfoViewModel}
    , m_repository{repository}
{
    auto result = m_repository.readEventsInfo();

    if (!result.isOk()) {
        qDebug() << result.error();
    } else {
        beginResetModel();
        m_events = result.value();
        endResetModel();
        qDebug() << m_events.count();
    }
}

int EventsInfoViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_events.count();
}

QVariant EventsInfoViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &event = m_events[index.row()];

    switch (role) {
        case IdRole:
            return event.id();
        case TitleRole:
            return event.title();
        case StartDateRole:
            return event.startDate();
        case EndDateRole:
            return event.endDate();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> EventsInfoViewModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IdRole] = "idRole";
    names[TitleRole] = "titleRole";
    names[StartDateRole] = "startDateRole";
    names[EndDateRole] = "endDateRole";

    return names;
}

void EventsInfoViewModel::createEvent(const QString &title,
                                      const QDate &startDate,
                                      const QDate &endDate)
{
    if (title.isEmpty()) {
        qDebug() << "Title should not be empty.";
        return;
    }

    if (!startDate.isValid()) {
        qDebug() << "Start date is invalid.";
        return;
    }

    if (!endDate.isValid()) {
        qDebug() << "End date is invalid.";
        return;
    }

    if (endDate < startDate) {
        qDebug() << "Start date should be earlier than end date.";
        return;
    }

    Domain::EventInfo event;
    event.setTitle(title);
    event.setStartDate(startDate);
    event.setEndDate(endDate);

    auto result = m_repository.createEvent(event);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    event.setId(result.value());
    beginInsertRows(QModelIndex(), m_events.count(), m_events.count());
    m_events.append(event);
    endInsertRows();
}

void EventsInfoViewModel::updateEventInfo(int index,
                                          const QString &title,
                                          const QDate &startDate,
                                          const QDate &endDate)
{
    if (title.isEmpty()) {
        qDebug() << "Title should not be empty.";
        return;
    }

    if (!startDate.isValid()) {
        qDebug() << "Start date is invalid.";
        return;
    }

    if (!endDate.isValid()) {
        qDebug() << "End date is invalid.";
        return;
    }

    if (endDate < startDate) {
        qDebug() << "Start date should be earlier than end date.";
        return;
    }

    Domain::EventInfo event = m_events[index];
    event.setTitle(title);
    event.setStartDate(startDate);
    event.setEndDate(endDate);

    auto result = m_repository.updateEventInfo(event);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    QModelIndex modelIndex = QAbstractListModel::index(index);

    m_events.replace(index, event);
    dataChanged(modelIndex, modelIndex);
}

void EventsInfoViewModel::deleteEvent(int index)
{
    qint32 id = m_events[index].id();

    auto result = m_repository.deleteEvent(id);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_events.removeAt(index);
    endRemoveRows();
}

void EventsInfoViewModel::selectEvent(int index)
{
    if (index < 0 || index >= m_events.count()) {
        m_receiptsInfoViewModel.setEventId(-1);
        m_participantsViewModel.setEventId(-1);
        return;
    }

    m_participantsViewModel.setEventId(m_events[index].id());
    m_receiptsInfoViewModel.setEventId(m_events[index].id());
}
} // namespace Presentation
} // namespace Sea
