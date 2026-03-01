#ifndef EVENTSVIEWMODEL_H
#define EVENTSVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IEventsRepository.h"
#include "AsyncExecutor.h"
#include "Entities/Event.h"

namespace Sea {
namespace Presentation {

class EventsViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, TitleRole, StartDateRole, EndDateRole };

    explicit EventsViewModel(Utils::AsyncExecutor &executor,
                             Application::IEventsRepository &repository,
                             QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void createEvent(const QString &title, const QDate &startDate, const QDate &endDate);

    Q_INVOKABLE void updateEvent(int index,
                                 const QString &title,
                                 const QDate &startDate,
                                 const QDate &endDate);

    Q_INVOKABLE void deleteEvent(int index);

private:
    Utils::AsyncExecutor &m_executor;
    QVector<Domain::Event> m_events;
    Application::IEventsRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // EVENTSVIEWMODEL_H
