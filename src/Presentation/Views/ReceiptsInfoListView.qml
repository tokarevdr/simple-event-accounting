import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Dialogs"

Item {
    id: root

    property var receiptsInfoViewModel: null
    property var participantsViewModel: null
    property var formatDate: function (date) {
        return Qt.formatDate(date, "dd.MM.yyyy")
    }
    property var formatTime: function (date) {
        return Qt.formatTime(date, "hh:mm:ss")
    }
    signal receiptSelected

    ColumnLayout {
        anchors.fill: root

        Button {
            text: "Create"

            onClicked: {
                createReceiptDialog.clear()
                createReceiptDialog.open()
            }
        }

        ListView {
            id: receiptsListView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: receiptsInfoViewModel

            delegate: Item {
                height: receiptsListView.height / 10
                width: receiptsListView.width

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        receiptsInfoViewModel.selectReceipt(index)
                        root.receiptSelected()
                    }
                }

                RowLayout {
                    anchors.fill: parent

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: titleRole
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: root.formatDate(purchaseDateRole)
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: root.formatTime(purchaseTimeRole)
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: buyerNameRole
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 50

                        Button {
                            anchors.fill: parent

                            text: "..."

                            onClicked: receiptsMenu.open()
                        }
                    }
                }

                Menu {
                    id: receiptsMenu

                    MenuItem {
                        text: "Edit"

                        onTriggered: {
                            editReceiptDialog.receiptTitle = titleRole
                            editReceiptDialog.purchaseDate = purchaseDateRole
                            editReceiptDialog.purchaseTime = purchaseTimeRole
                            editReceiptDialog.buyerIndex
                                    = participantsViewModel.participantIndexById(
                                        buyerIdRole)
                            editReceiptDialog.open()
                        }
                    }

                    MenuItem {
                        text: "Delete"

                        onTriggered: receiptsInfoViewModel.deleteReceipt(index)
                    }
                }

                ReceiptDialog {
                    id: editReceiptDialog

                    onAccepted: receiptsInfoViewModel.updateReceipt(index,
                                                                receiptTitle,
                                                                purchaseDate,
                                                                purchaseTime,
                                                                buyerId,
                                                                buyerName)
                }
            }
        }
    }

    ReceiptDialog {
        id: createReceiptDialog

        onAccepted: receiptsInfoViewModel.createReceipt(receiptTitle, purchaseDate,
                                                    purchaseTime, buyerId,
                                                    buyerName)
    }
}
