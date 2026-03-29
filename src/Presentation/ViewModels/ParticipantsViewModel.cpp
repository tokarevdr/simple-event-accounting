#include "ParticipantsViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {

ParticipantsViewModel::ParticipantsViewModel(
    Application::IEventUsersRepository &repository, QObject *parent)
    : QAbstractListModel(parent)
    , m_repository{repository}
{}

int ParticipantsViewModel::rowCount(
    const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_participants.count();
}

QVariant ParticipantsViewModel::data(
    const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &participant = m_participants[index.row()];

    switch (role) {
        case IdRole:
            return participant.id();
        case NameRole:
            return participant.name();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ParticipantsViewModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IdRole] = "idRole";
    names[NameRole] = "nameRole";

    return names;
}

void ParticipantsViewModel::setEventId(qint32 id)
{
    if (id == m_eventId) {
        return;
    }

    m_eventId = id;

    if (id == -1) {
        beginResetModel();
        m_participants.clear();
        endResetModel();
        return;
    }

    auto result = m_repository.readEventUsers(id);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginResetModel();
    m_participants = result.value();
    endResetModel();
}

void ParticipantsViewModel::createParticipant(qint32 userId, const QString &name)
{
    Domain::User user;
    user.setId(userId);
    user.setName(name);

    auto result = m_repository.createEventUser(m_eventId, userId);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginInsertRows(QModelIndex(), m_participants.count(), m_participants.count());
    m_participants.append(user);
    endInsertRows();
}

void ParticipantsViewModel::deleteParticipant(int index)
{
    qint32 id = m_participants[index].id();

    auto result = m_repository.deleteEventUser(id);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_participants.removeAt(index);
    endRemoveRows();
}

} // namespace Presentation
} // namespace Sea
