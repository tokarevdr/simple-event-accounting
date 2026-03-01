#include "ParticipantsViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {

ParticipantsViewModel::ParticipantsViewModel(
    Utils::AsyncExecutor &executor,
    Application::IParticipantsRepository &repository,
    QObject *parent)
    : QAbstractListModel(parent)
    , m_executor{executor}
    , m_repository{repository}
{
    m_executor
        .exec<QVector<Domain::Participant>>([this]() { return m_repository.readParticipants(); },
                                            [this](
                                                const QVector<Domain::Participant> &participants) {
                                                beginResetModel();
                                                m_participants = participants;
                                                endResetModel();
                                            });
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

    m_executor.exec<qint32>([this,
                             participant]() { return m_repository.createParticipant(participant); },
                            [this, &participant](const qint32 &id) {
                                participant.setId(id);

                                beginInsertRows(QModelIndex(),
                                                m_participants.count(),
                                                m_participants.count());
                                m_participants.append(participant);
                                endInsertRows();
                            });
}

void ParticipantsViewModel::updateParticipant(int index, const QString &name)
{
    if (name.isEmpty()) {
        qDebug() << "Name should not be empty.";
        return;
    }

    Domain::Participant participant = m_participants[index];
    participant.setName(name);

    m_executor.exec<bool>([this,
                           participant]() { return m_repository.updateParticipant(participant); },
                          [this, &participant, index](const bool &isOk) {
                              if (!isOk) {
                                  qDebug() << "Participant was not updated.";
                                  return;
                              }

                              QModelIndex modelIndex = QAbstractListModel::index(index);

                              m_participants.replace(index, participant);
                              dataChanged(modelIndex, modelIndex);
                          });
}

void ParticipantsViewModel::deleteParticipant(int index)
{
    qint32 id = m_participants[index].id();

    m_executor.exec<bool>([this, id]() { return m_repository.deleteParticipant(id); },
                          [this, index](const bool &isOk) {
                              if (!isOk) {
                                  qDebug() << "Participant was not deleted.";
                                  return;
                              }

                              beginRemoveRows(QModelIndex(), index, index);
                              m_participants.removeAt(index);
                              endRemoveRows();
                          });
}

} // namespace Presentation
} // namespace Sea
