#ifndef IEVENTSINFOREPOSITORY_H
#define IEVENTSINFOREPOSITORY_H

#include <QVector>

#include "Application_global.h"
#include "Entities/EventInfo.h"
#include "Result.h"
#include "Unit.h"

namespace Sea {
namespace Application {
class APPLICATION_EXPORT IEventsInfoRepository
{
    Q_DISABLE_COPY_MOVE(IEventsInfoRepository)
public:
    IEventsInfoRepository();

    virtual ~IEventsInfoRepository() = default;

    virtual Utils::Result<qint32, QString> createEvent(const Domain::EventInfo &eventInfo) = 0;

    virtual Utils::Result<QVector<Domain::EventInfo>, QString> readEventsInfo() = 0;

    virtual Utils::Result<Utils::Unit, QString> updateEventInfo(const Domain::EventInfo &eventInfo)
        = 0;

    virtual Utils::Result<Utils::Unit, QString> deleteEvent(qint32 id) = 0;
};

} // namespace Application
} // namespace Sea

#endif // IEVENTSINFOREPOSITORY_H
