#include "EventsViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {

EventsViewModel::EventsViewModel(Application::IEventsRepository &repository, QObject *parent)
    : QAbstractListModel(parent)
    , m_repository{repository}
{
    auto result = m_repository.readEvents();

    if (!result.isOk()) {
        qDebug() << result.error();
    } else {
        beginResetModel();
        m_events = result.value();
        endResetModel();
        qDebug() << m_events.count();
    }
}

int EventsViewModel::rowCount(
    const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_events.count();
}

QVariant EventsViewModel::data(
    const QModelIndex &index, int role) const
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
            return event.startDate().has_value() ? event.startDate().value() : QDate();
        case EndDateRole:
            return event.endDate().has_value() ? event.endDate().value() : QDate();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> EventsViewModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IdRole] = "idRole";
    names[TitleRole] = "titleRole";
    names[StartDateRole] = "startDateRole";
    names[EndDateRole] = "endDateRole";

    return names;
}

void EventsViewModel::createEvent(const QString &title, const QDate &startDate, const QDate &endDate)
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

    Domain::Event event;
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

void EventsViewModel::updateEvent(int index,
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

    Domain::Event event = m_events[index];
    event.setTitle(title);
    event.setStartDate(startDate);
    event.setEndDate(endDate);

    auto result = m_repository.updateEvent(event);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    QModelIndex modelIndex = QAbstractListModel::index(index);

    m_events.replace(index, event);
    dataChanged(modelIndex, modelIndex);
}

void EventsViewModel::deleteEvent(int index)
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

} // namespace Presentation
} // namespace Sea
