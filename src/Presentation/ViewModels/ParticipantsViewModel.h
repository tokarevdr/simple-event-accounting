#ifndef PARTICIPANTSVIEWMODEL_H
#define PARTICIPANTSVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IParticipantsRepository.h"

namespace Sea {
namespace Presentation {

class ParticipantsViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, NameRole };

    explicit ParticipantsViewModel(Application::IParticipantsRepository &repository,
                                   QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void createParticipant(const QString &name);

    Q_INVOKABLE void updateParticipant(int index, const QString &name);

    Q_INVOKABLE void deleteParticipant(int index);

    Q_INVOKABLE int participantIndexById(int id) const;

private:
    QVector<Domain::Participant> m_participants;
    Application::IParticipantsRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // PARTICIPANTSVIEWMODEL_H
