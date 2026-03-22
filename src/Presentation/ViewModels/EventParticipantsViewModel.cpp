#include "EventParticipantsViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {

EventParticipantsViewModel::EventParticipantsViewModel(
    Application::IEventParticipantsRepository &repository, QObject *parent)
    : QAbstractListModel(parent)
    , m_repository{repository}
{}

int EventParticipantsViewModel::rowCount(
    const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_participants.count();
}

QVariant EventParticipantsViewModel::data(
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

QHash<int, QByteArray> EventParticipantsViewModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IdRole] = "idRole";
    names[NameRole] = "nameRole";

    return names;
}

void EventParticipantsViewModel::setEventId(qint32 id)
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

    auto result = m_repository.readEventParticipants(id);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginResetModel();
    m_participants = result.value();
    endResetModel();
}

void EventParticipantsViewModel::createEventParticipant(qint32 participantId, const QString &name)
{
    Domain::Participant participant;
    participant.setId(participantId);
    participant.setName(name);

    auto result = m_repository.createEventParticipant(m_eventId, participantId);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginInsertRows(QModelIndex(), m_participants.count(), m_participants.count());
    m_participants.append(participant);
    endInsertRows();
}

void EventParticipantsViewModel::deleteEventParticipant(int index)
{
    qint32 id = m_participants[index].id();

    auto result = m_repository.deleteEventParticipant(id);

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
