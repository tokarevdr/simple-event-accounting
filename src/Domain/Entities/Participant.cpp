#include "Participant.h"

namespace Sea {
namespace Domain {

Participant::Participant() {}

qint32 Participant::id() const
{
    return m_id;
}

void Participant::setId(qint32 newId)
{
    m_id = newId;
}

QString Participant::name() const
{
    return m_name;
}

void Participant::setName(const QString &newName)
{
    m_name = newName;
}

bool Participant::operator==(const Participant &other) const
{
    return m_id == other.m_id;
}

} // namespace Domain
} // namespace Sea
