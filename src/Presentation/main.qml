import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Views"
import "Views/Controls"

ApplicationWindow {
       id: window
       width: 600
       height: 800
       visible: true
       title: qsTr("Hello World")

       NavigationController {
              id: navigationController
       }

       RowLayout {
              anchors.fill: parent

              ColumnLayout {
                     id: sideBar
                     Layout.fillHeight: true
                     Layout.preferredWidth: 50
                     Layout.maximumWidth: 50

                     property int currentIndex: 0
                     spacing: 0

                     Button {
                            Layout.preferredHeight: 50
                            Layout.fillWidth: true
                            text: "С"

                            checked: sideBar.currentIndex === 0

                            onClicked: sideBar.currentIndex = 0
                     }

                     Button {
                            Layout.preferredHeight: 50
                            Layout.fillWidth: true
                            text: "Л"

                            checked: sideBar.currentIndex === 1

                            onClicked: sideBar.currentIndex = 1
                     }

                     Item {
                            Layout.fillHeight: true
                     }
              }

              StackLayout {
                     Layout.fillHeight: true
                     Layout.fillWidth: true

                     currentIndex: sideBar.currentIndex

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
}
