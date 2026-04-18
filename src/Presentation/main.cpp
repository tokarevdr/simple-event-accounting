#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QSortFilterProxyModel>

#include "Repositories/SqliteAccountingRepository.h"
#include "ViewModels/ConsumersViewModel.h"
#include "ViewModels/ParticipantsViewModel.h"
#include "ViewModels/EventsInfoViewModel.h"
#include "ViewModels/UsersViewModel.h"
#include "ViewModels/ReceiptItemsInfoViewModel.h"
#include "ViewModels/ReceiptsInfoViewModel.h"

int main(
    int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    Sea::Infrastructure::SqliteAccountingRepository repo;

    Sea::Presentation::ConsumersViewModel consumersViewModel(repo);
    Sea::Presentation::ReceiptItemsInfoViewModel receiptItemsInfoViewModel(consumersViewModel, repo);
    Sea::Presentation::ReceiptsInfoViewModel receiptsInfoViewModel(receiptItemsInfoViewModel, repo);
    Sea::Presentation::ParticipantsViewModel participantsViewModel(repo);
    Sea::Presentation::EventsInfoViewModel eventsInfoViewModel(participantsViewModel,
                                                               receiptsInfoViewModel,
                                                               repo);
    Sea::Presentation::UsersViewModel usersViewModel(repo);

    QSortFilterProxyModel usersProxyViewModel;
    usersProxyViewModel.setSourceModel(&usersViewModel);
    usersProxyViewModel.setFilterRole(Sea::Presentation::UsersViewModel::NameRole);
    usersProxyViewModel.setFilterCaseSensitivity(Qt::CaseInsensitive);

    QSortFilterProxyModel participantsProxyViewModel;
    participantsProxyViewModel.setSourceModel(&participantsViewModel);
    participantsProxyViewModel.setFilterRole(Sea::Presentation::UsersViewModel::NameRole);
    participantsProxyViewModel.setFilterCaseSensitivity(Qt::CaseInsensitive);

    repo.readEvent(2);

    QQuickStyle::setStyle("Fusion");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("eventsInfoVm", &eventsInfoViewModel);
    engine.rootContext()->setContextProperty("usersVm", &usersViewModel);
    engine.rootContext()->setContextProperty("usersProxyVm", &usersProxyViewModel);
    engine.rootContext()->setContextProperty("participantsVm", &participantsViewModel);
    engine.rootContext()->setContextProperty("participantsProxyVm", &participantsProxyViewModel);
    engine.rootContext()->setContextProperty("receiptsInfoVm", &receiptsInfoViewModel);
    engine.rootContext()->setContextProperty("receiptItemsInfoVm", &receiptItemsInfoViewModel);
    engine.rootContext()->setContextProperty("consumersVm", &consumersViewModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
