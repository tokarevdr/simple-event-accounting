import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Controls"

Item {
    id: root

    property var consumersViewModel: null
    required property NavigationController navController

    ColumnLayout {
        anchors.fill: parent

        Button {
            text: "К чеку"

            onClicked: navController.currentView = NavigationController.Receipt
        }

        Label {
            text: receiptItemVm.name
        }

        Label {
            text: receiptItemVm.price
        }

        Label {
            text: receiptItemVm.count
        }

        ConsumersListView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            consumersViewModel: root.consumersViewModel
            participantsViewModel: participantsVm
        }
    }
}


