#ifndef EVENTPARTICIPANTSVIEWMODEL_H
#define EVENTPARTICIPANTSVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IEventParticipantsRepository.h"

namespace Sea {
namespace Presentation {

class EventParticipantsViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, NameRole };

    explicit EventParticipantsViewModel(Application::IEventParticipantsRepository &repository,
                                        QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setEventId(qint32 id);

    Q_INVOKABLE void createEventParticipant(qint32 participantId, const QString &name);

    Q_INVOKABLE void deleteEventParticipant(int index);

private:
    qint32 m_eventId = -1;
    QVector<Domain::Participant> m_participants;
    Application::IEventParticipantsRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // EVENTPARTICIPANTSVIEWMODEL_H
