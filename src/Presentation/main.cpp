#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>

#include "Repositories/SqliteEventsRepository.h"
#include "ViewModels/ConsumersViewModel.h"
#include "ViewModels/EventsViewModel.h"
#include "ViewModels/ParticipantsViewModel.h"
#include "ViewModels/ReceiptItemsViewModel.h"
#include "ViewModels/ReceiptsViewModel.h"

int main(
    int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    Sea::Infrastructure::SqliteEventsRepository repo;
    Sea::Presentation::EventsViewModel eventsViewModel(repo);
    Sea::Presentation::ParticipantsViewModel participantsViewModel(repo);
    Sea::Presentation::ReceiptsViewModel receiptsViewModel(repo);
    Sea::Presentation::ReceiptItemsViewModel receiptItemsViewModel(repo);

    QSortFilterProxyModel participantsProxyViewModel;
    participantsProxyViewModel.setSourceModel(&participantsViewModel);
    participantsProxyViewModel.setFilterRole(Sea::Presentation::ParticipantsViewModel::NameRole);
    participantsProxyViewModel.setFilterCaseSensitivity(Qt::CaseInsensitive);

    Sea::Presentation::ConsumersViewModel consumersViewModel(repo);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("eventsVm", &eventsViewModel);
    engine.rootContext()->setContextProperty("participantsVm", &participantsViewModel);
    engine.rootContext()->setContextProperty("participantsProxyVm", &participantsProxyViewModel);
    engine.rootContext()->setContextProperty("receiptsVm", &receiptsViewModel);
    engine.rootContext()->setContextProperty("receiptItemsVm", &receiptItemsViewModel);
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
