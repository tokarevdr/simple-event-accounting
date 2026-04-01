#ifndef EVENTSINFOVIEWMODEL_H
#define EVENTSINFOVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IEventsInfoRepository.h"
#include "ViewModels/ParticipantsViewModel.h"
#include "ViewModels/ReceiptsInfoViewModel.h"

namespace Sea {
namespace Presentation {
class EventsInfoViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, TitleRole, StartDateRole, EndDateRole };

    explicit EventsInfoViewModel(ParticipantsViewModel &participantsViewModel,
                                 ReceiptsInfoViewModel &receiptsInfoViewModel,
                                 Application::IEventsInfoRepository &repository,
                                 QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void createEvent(const QString &title, const QDate &startDate, const QDate &endDate);

    Q_INVOKABLE void updateEventInfo(int index,
                                     const QString &title,
                                     const QDate &startDate,
                                     const QDate &endDate);

    Q_INVOKABLE void deleteEvent(int index);

    Q_INVOKABLE void selectEvent(int index);

private:
    QVector<Domain::EventInfo> m_events;
    ParticipantsViewModel &m_participantsViewModel;
    ReceiptsInfoViewModel &m_receiptsInfoViewModel;
    Application::IEventsInfoRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // EVENTSINFOVIEWMODEL_H
