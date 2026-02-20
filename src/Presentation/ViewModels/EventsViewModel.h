#ifndef EVENTSVIEWMODEL_H
#define EVENTSVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IEventsRepository.h"
#include "Entities/Event.h"
#include "Utils/AsyncExecutor.h"

namespace Sea {
namespace Presentation {

class EventsViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, TitleRole, StartDateRole, EndDateRole };

    explicit EventsViewModel(AsyncExecutor &executor,
                             Application::IEventsRepository &repository,
                             QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void createEvent(const QString &title,
                                 const QString &startDate,
                                 const QString &endDate);

    Q_INVOKABLE void updateEvent(qint32 id,
                                 const QString &title,
                                 const QString &startDate,
                                 const QString &endDate);

    Q_INVOKABLE void deleteEvent(qint32 id);

private:
    AsyncExecutor &m_executor;
    QVector<Domain::Event> m_events;
    Application::IEventsRepository &m_repository;
    const QString DATE_FORMAT = "dd.MM.yyyy";
};

} // namespace Presentation
} // namespace Sea

#endif // EVENTSVIEWMODEL_H
