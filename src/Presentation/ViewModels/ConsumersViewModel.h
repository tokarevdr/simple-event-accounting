#ifndef CONSUMERSVIEWMODEL_H
#define CONSUMERSVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IConsumersRepository.h"
#include "Entities/Consumer.h"

namespace Sea {
namespace Presentation {

class ConsumersViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { ParticipantIdRole, NameRole, ConsumtionRatioRole };

    explicit ConsumersViewModel(Application::IConsumersRepository &repository,
                                QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setReceiptItemId(qint32 id);

    Q_INVOKABLE void createConsumer(qint32 participantId,
                                    const QString &name,
                                    qint32 consumptionRatio);

private:
    qint32 m_receiptItemId = -1;
    QVector<Domain::Consumer> m_consumers;
    Application::IConsumersRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // CONSUMERSVIEWMODEL_H
