#include "Consumer.h"

namespace Sea {
namespace Domain {

Consumer::Consumer() {}

qint32 Consumer::participantId() const
{
    return m_participantId;
}

void Consumer::setParticipantId(qint32 newParticipantId)
{
    m_participantId = newParticipantId;
}

qint32 Consumer::receiptItemId() const
{
    return m_receiptItemId;
}

void Consumer::setReceiptItemId(qint32 newReceiptItemId)
{
    m_receiptItemId = newReceiptItemId;
}

QString Consumer::name() const
{
    return m_name;
}

void Consumer::setName(const QString &newName)
{
    m_name = newName;
}

qint32 Consumer::consumptionRatio() const
{
    return m_consumptionRatio;
}

void Consumer::setConsumptionRatio(qint32 newConsumptionRatio)
{
    m_consumptionRatio = newConsumptionRatio;
}

} // namespace Domain
} // namespace Sea
