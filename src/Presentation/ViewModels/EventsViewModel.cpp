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

    m_executor.exec<qint32>([this, event]() { return m_repository.createEvent(event); },
                            [this, &event](const qint32 &id) {
                                event.setId(id);

                                beginInsertRows(QModelIndex(), m_events.count(), m_events.count());
                                m_events.append(event);
                                endInsertRows();
                            });
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

    m_executor.exec<bool>([this, event]() { return m_repository.updateEvent(event); },
                          [this, &event, index](const bool &isOk) {
                              if (!isOk) {
                                  qDebug() << "Event was not updated.";
                                  return;
                              }

                              QModelIndex modelIndex = QAbstractListModel::index(index);

                              m_events.replace(index, event);
                              dataChanged(modelIndex, modelIndex);
                          });
}

void EventsViewModel::deleteEvent(int index)
{
    qint32 id = m_events[index].id();

    m_executor.exec<bool>([this, id]() { return m_repository.deleteEvent(id); },
                          [this, index](const bool &isOk) {
                              if (!isOk) {
                                  qDebug() << "Event was not deleted.";
                                  return;
                              }

                              beginRemoveRows(QModelIndex(), index, index);
                              m_events.removeAt(index);
                              endRemoveRows();
                          });
}

} // namespace Presentation
} // namespace Sea
