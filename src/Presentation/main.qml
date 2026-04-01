import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Views"
import "Views/Controls"

ApplicationWindow {
       id: window
       width: 1000
       height: 800
       visible: true
       title: qsTr("Hello World")

       RowLayout {
              anchors.fill: parent

              ColumnLayout {
                     Layout.fillHeight: true
                     Layout.fillWidth: true

                     EventsInfoListView {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            eventsInfoViewModel: eventsInfoVm
                     }

                     UsersListView {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            usersViewModel: usersVm
                     }
              }


              ReceiptsInfoListView {
                     Layout.fillHeight: true
                     Layout.fillWidth: true

                     receiptsInfoViewModel: receiptsInfoVm
                     participantsViewModel: participantsVm
                     receiptItemsInfoViewModel: receiptItemsInfoVm
                     consumersViewModel: consumersVm
              }

              ParticipantsListView {
                     Layout.fillHeight: true
                     Layout.fillWidth: true

                     participantsViewModel: participantsVm
              }
       }
}
