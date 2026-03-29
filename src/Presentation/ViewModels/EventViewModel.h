#ifndef EVENTVIEWMODEL_H
#define EVENTVIEWMODEL_H

#include <optional>

#include <QObject>

#include "Entities/EventInfo.h"
#include "ParticipantsViewModel.h"
#include "ReceiptsInfoViewModel.h"

namespace Sea {
namespace Presentation {
class EventViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate NOTIFY startDateChanged FINAL)
    Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate NOTIFY endDateChanged FINAL)
public:
    explicit EventViewModel(ParticipantsViewModel &participantsViewModel,
                            ReceiptsInfoViewModel &receiptsInfoViewModel,
                            QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);

    QDate startDate() const;
    void setStartDate(const QDate &newStartDate);

    QDate endDate() const;
    void setEndDate(const QDate &newEndDate);

    void setEventInfo(const std::optional<Domain::EventInfo> &eventInfo);

signals:
    void titleChanged();

    void startDateChanged();

    void endDateChanged();

private:
    QString m_title;
    QDate m_startDate;
    QDate m_endDate;

    ParticipantsViewModel &m_participantsViewModel;
    ReceiptsInfoViewModel &m_receiptsInfoViewModel;
};
} // namespace Presentation
} // namespace Sea

#endif // EVENTVIEWMODEL_H
