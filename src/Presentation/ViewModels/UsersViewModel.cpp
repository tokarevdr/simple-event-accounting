#include "UsersViewModel.h"

#include <QDebug>

namespace Sea {
namespace Presentation {
UsersViewModel::UsersViewModel(Application::IUsersRepository &repository, QObject *parent)
    : QAbstractListModel(parent)
    , m_repository{repository}
{
    auto result = m_repository.readUsers();

    if (!result.isOk()) {
        qDebug() << result.error();
    } else {
        beginResetModel();
        m_users = result.value();
        endResetModel();
    }
}

int UsersViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_users.count();
}

QVariant UsersViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &user = m_users[index.row()];

    switch (role) {
        case IdRole:
            return user.id();
        case NameRole:
            return user.name();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> UsersViewModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IdRole] = "idRole";
    names[NameRole] = "nameRole";

    return names;
}

void UsersViewModel::createUser(const QString &name)
{
    if (name.isEmpty()) {
        qDebug() << "Name should not be empty.";
        return;
    }

    Domain::User user;
    user.setName(name);

    auto result = m_repository.createUser(user);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    user.setId(result.value());

    beginInsertRows(QModelIndex(), m_users.count(), m_users.count());
    m_users.append(user);
    endInsertRows();
}

void UsersViewModel::updateUser(int index, const QString &name)
{
    if (name.isEmpty()) {
        qDebug() << "Name should not be empty.";
        return;
    }

    Domain::User user = m_users[index];
    user.setName(name);

    auto result = m_repository.updateUser(user);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    QModelIndex modelIndex = QAbstractListModel::index(index);

    m_users.replace(index, user);
    dataChanged(modelIndex, modelIndex);
}

void UsersViewModel::deleteUser(int index)
{
    qint32 id = m_users[index].id();

    auto result = m_repository.deleteUser(id);

    if (!result.isOk()) {
        qDebug() << result.error();
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_users.removeAt(index);
    endRemoveRows();
}

int UsersViewModel::userIndexById(int id) const
{
    Domain::User user;
    user.setId(id);

    return m_users.indexOf(user);
}

} // namespace Presentation
} // namespace Sea
