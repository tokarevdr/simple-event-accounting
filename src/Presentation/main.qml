import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Views"
import "Views/Controls"

ApplicationWindow {
       id: window
       width: 1600
       height: 800
       visible: true
       title: qsTr("Hello World")

       NavigationController {
              id: navigationController
       }

       header: TabBar {
              id: tabBar
              TabButton {
                     text: "События"
              }

              TabButton {
                     text: "Люди"
              }
       }

       StackLayout {
              anchors.fill: parent

              currentIndex: tabBar.currentIndex

              Item {
                     StackLayout {
                            id: stackLayout
                            anchors.fill: parent
                            currentIndex: navigationController.currentView

                            EventsInfoListView {
                                   eventsInfoViewModel: eventsInfoVm
                                   onEventSelected: navigationController.currentView = NavigationController.Event
                            }

                            EventView {
                                   eventViewModel: eventVm
                                   navController: navigationController
                            }

                            ReceiptView {
                                   receiptViewModel : receiptVm
                                   navController: navigationController
                            }

                            ReceiptItemView {
                                   consumersViewModel: consumersVm
                                   navController: navigationController
                            }
                     }
              }

              UsersListView {
                     usersViewModel: usersVm
              }
       }
}
