#ifndef CONSUMER_H
#define CONSUMER_H

#include <QString>

#include "Domain_global.h"

namespace Sea {
namespace Domain {

class DOMAIN_EXPORT Consumer
{
public:
    Consumer();

    qint32 participantId() const;
    void setParticipantId(qint32 newParticipantId);
    qint32 receiptItemId() const;
    void setReceiptItemId(qint32 newReceiptItemId);
    QString name() const;
    void setName(const QString &newName);
    qint32 consumptionRatio() const;
    void setConsumptionRatio(qint32 newConsumptionRatio);

private:
    qint32 m_participantId = 0;
    qint32 m_receiptItemId = 0;
    QString m_name;
    qint32 m_consumptionRatio = 1;
};

} // namespace Domain
} // namespace Sea

#endif // CONSUMER_H
