#ifndef PARTICIPANTSVIEWMODEL_H
#define PARTICIPANTSVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IEventUsersRepository.h"

namespace Sea {
namespace Presentation {
class ParticipantsViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, NameRole };

    explicit ParticipantsViewModel(Application::IEventUsersRepository &repository,
                                   QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setEventId(qint32 id);

    Q_INVOKABLE void createParticipant(qint32 userId, const QString &name);

    Q_INVOKABLE void deleteParticipant(int index);

private:
    qint32 m_eventId = -1;
    QVector<Domain::User> m_participants;
    Application::IEventUsersRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // PARTICIPANTSVIEWMODEL_H
