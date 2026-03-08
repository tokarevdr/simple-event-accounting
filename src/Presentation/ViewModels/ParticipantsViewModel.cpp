#include "ParticipantsViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {

ParticipantsViewModel::ParticipantsViewModel(Application::IParticipantsRepository &repository,
                                             QObject *parent)
    : QAbstractListModel(parent)
    , m_repository{repository}
{
    auto result = m_repository.readParticipants();

    if (!result.isOk()) {
        qDebug() << result.error();
    } else {
        beginResetModel();
        m_participants = result.value();
        endResetModel();
    }
}

int ParticipantsViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_participants.count();
}

QVariant ParticipantsViewModel::data(const QModelIndex &index, int role) const
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

void ParticipantsViewModel::createParticipant(const QString &name)
{
    if (name.isEmpty()) {
        qDebug() << "Name should not be empty.";
        return;
    }

    Domain::Participant participant;
    participant.setName(name);

    auto result = m_repository.createParticipant(participant);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    participant.setId(result.value());

    beginInsertRows(QModelIndex(), m_participants.count(), m_participants.count());
    m_participants.append(participant);
    endInsertRows();
}

void ParticipantsViewModel::updateParticipant(int index, const QString &name)
{
    if (name.isEmpty()) {
        qDebug() << "Name should not be empty.";
        return;
    }

    Domain::Participant participant = m_participants[index];
    participant.setName(name);

    auto result = m_repository.updateParticipant(participant);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    QModelIndex modelIndex = QAbstractListModel::index(index);

    m_participants.replace(index, participant);
    dataChanged(modelIndex, modelIndex);
}

void ParticipantsViewModel::deleteParticipant(int index)
{
    qint32 id = m_participants[index].id();

    auto result = m_repository.deleteParticipant(id);

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
