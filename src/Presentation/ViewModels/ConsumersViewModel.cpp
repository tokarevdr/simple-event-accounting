#include "ConsumersViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {

ConsumersViewModel::ConsumersViewModel(Application::IConsumersRepository &repository,
                                       QObject *parent)
    : QAbstractListModel(parent)
    , m_repository{repository}
{}

int ConsumersViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_consumers.count();
}

QVariant ConsumersViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &consumer = m_consumers[index.row()];

    switch (role) {
        case ParticipantIdRole:
            return consumer.participantId();
        case NameRole:
            return consumer.name();
        case ConsumtionRatioRole:
            return consumer.consumptionRatio();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ConsumersViewModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[ParticipantIdRole] = "participantIdRole";
    names[NameRole] = "nameRole";
    names[ConsumtionRatioRole] = "consumptionRatioRole";

    return names;
}

void ConsumersViewModel::setReceiptItemId(qint32 id)
{
    if (id == m_receiptItemId) {
        return;
    }

    m_receiptItemId = id;

    if (m_receiptItemId == -1) {
        beginResetModel();
        m_consumers.clear();
        endResetModel();
        return;
    }

    auto result = m_repository.readConsumers(m_receiptItemId);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginResetModel();
    m_consumers = result.value();
    endResetModel();
}

void ConsumersViewModel::createConsumer(qint32 participantId,
                                        const QString &name,
                                        qint32 consumptionRatio)
{
    if (m_receiptItemId == -1) {
        return;
    }

    Domain::Consumer consumer;
    consumer.setParticipantId(participantId);
    consumer.setName(name);
    consumer.setReceiptItemId(m_receiptItemId);
    consumer.setConsumptionRatio(consumptionRatio);

    auto result = m_repository.createConsumer(consumer);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginInsertRows(QModelIndex(), m_consumers.count(), m_consumers.count());
    m_consumers.append(consumer);
    endInsertRows();
}

} // namespace Presentation
} // namespace Sea
