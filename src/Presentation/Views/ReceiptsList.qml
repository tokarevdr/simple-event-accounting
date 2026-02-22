import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property var receiptsViewModel: null
    property var formatDate: function (date) {
        return Qt.formatDate(date, "dd.MM.yyyy")
    }
    property var formatTime: function (date) {
        return Qt.formatTime(date, "hh:mm:ss")
    }

    ColumnLayout {
        anchors.fill: root

        Button {
            Layout.preferredHeight: 50
            Layout.preferredWidth: 100

            text: "Create"

            onClicked: createReceiptDialog.open()
        }

        ListView {
            id: receiptsListView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: receiptsViewModel

            delegate: Item {
                height: receiptsListView.height / 10
                width: receiptsListView.width
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
                            editReceiptDialog.open()
                        }
                    }

                    MenuItem {
                        text: "Delete"

                        onTriggered: receiptsViewModel.deleteReceipt(index)
                    }
                }

                ReceiptDialog {
                    id: editReceiptDialog

                    onAccepted: receiptsViewModel.updateReceipt(index,
                                                                receiptTitle,
                                                                purchaseDate,
                                                                purchaseTime,
                                                                -1)
                }
            }
        }
    }

    ReceiptDialog {
        id: createReceiptDialog

        onAccepted: receiptsViewModel.createReceipt(receiptTitle, purchaseDate,
                                                    purchaseTime, -1)
    }
}
