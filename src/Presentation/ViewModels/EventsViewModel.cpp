#include "EventsViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {

EventsViewModel::EventsViewModel(AsyncExecutor &executor,
                                 Application::IEventsRepository &repository,
                                 QObject *parent)
    : QAbstractListModel(parent)
    , m_executor{executor}
    , m_repository{repository}
{
    m_executor.exec<QVector<Domain::Event>>([this]() { return m_repository.readEvents(); },
                                            [this](const QVector<Domain::Event> &events) {
                                                beginResetModel();
                                                m_events = events;
                                                endResetModel();
                                                qDebug() << events.count();
                                            });
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
            return event.startDate().has_value() ? event.startDate().value().toString(DATE_FORMAT)
                                                 : "~";
        case EndDateRole:
            return event.endDate().has_value() ? event.endDate().value().toString(DATE_FORMAT)
                                               : "~";
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

void EventsViewModel::createEvent(const QString &title,
                                  const QString &startDate,
                                  const QString &endDate)
{
    if (title.isEmpty()) {
        qDebug() << "Title should not be empty.";
        return;
    }

    QDate start = QDate::fromString(startDate, DATE_FORMAT);

    if (!start.isValid()) {
        qDebug() << "Start date is invalid.";
        return;
    }

    QDate end = QDate::fromString(endDate, DATE_FORMAT);

    if (!end.isValid()) {
        qDebug() << "End date is invalid.";
        return;
    }

    if (end < start) {
        qDebug() << "Start date should be earlier than end date.";
        return;
    }

    Domain::Event event;
    event.setTitle(title);
    event.setStartDate(start);
    event.setEndDate(end);

    m_executor.exec<qint32>([this, event]() { return m_repository.createEvent(event); },
                            [this, &event](const qint32 &id) {
                                event.setId(id);

                                beginInsertRows(QModelIndex(), m_events.count(), m_events.count());
                                m_events.append(event);
                                endInsertRows();
                            });
}

void EventsViewModel::updateEvent(qint32 id,
                                  const QString &title,
                                  const QString &startDate,
                                  const QString &endDate)
{}

void EventsViewModel::deleteEvent(qint32 id) {}

} // namespace Presentation
} // namespace Sea
