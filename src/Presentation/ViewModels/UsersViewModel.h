#ifndef USERSVIEWMODEL_H
#define USERSVIEWMODEL_H

#include <QAbstractListModel>

#include "Abstractions/IUsersRepository.h"

namespace Sea {
namespace Presentation {
class UsersViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { IdRole, NameRole };

    explicit UsersViewModel(Application::IUsersRepository &repository, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void createUser(const QString &name);

    Q_INVOKABLE void updateUser(int index, const QString &name);

    Q_INVOKABLE void deleteUser(int index);

    Q_INVOKABLE int userIndexById(int id) const;

private:
    QVector<Domain::User> m_users;
    Application::IUsersRepository &m_repository;
};

} // namespace Presentation
} // namespace Sea

#endif // USERSVIEWMODEL_H
