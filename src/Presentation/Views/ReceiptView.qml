import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Controls"

Item {
    id: root

    property var receiptViewModel: null
    required property NavigationController navController

    ColumnLayout {
        anchors.fill: parent

        Button {
            text: "К событию"

            onClicked: navController.currentView = NavigationController.Event
        }

        Label {
            text: receiptViewModel.title
        }

        Label {
            text: receiptViewModel.purchaseDateTime
        }

        Label {
            text: receiptViewModel.buyerName
        }

        ReceiptItemsInfoListView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            receiptItemsInfoViewModel: receiptItemsInfoVm

            onReceiptItemSelected: navController.currentView = NavigationController.ReceiptItem
        }
    }
}

