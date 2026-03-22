import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Dialogs"

Item {
    id: root

    property var receiptItemsViewModel: null
    signal receiptItemClicked(int receiptItemId)

    ColumnLayout {
        anchors.fill: root

        Button {
            Layout.preferredHeight: 50
            Layout.preferredWidth: 100

            text: "Create"

            onClicked: {
                createReceiptItemDialog.clear()
                createReceiptItemDialog.open()
            }
        }

        ListView {
            id: receiptItemsListView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: receiptItemsViewModel

            delegate: Item {
                height: receiptItemsListView.height / 10
                width: receiptItemsListView.width

                MouseArea {
                    anchors.fill: parent

                    onClicked: root.receiptItemClicked(idRole)
                }

                RowLayout {
                    anchors.fill: parent

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: nameRole
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: priceRole
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: countRole
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 50

                        Button {
                            anchors.fill: parent

                            text: "..."

                            onClicked: receiptItemMenu.open()
                        }
                    }
                }

                Menu {
                    id: receiptItemMenu

                    MenuItem {
                        text: "Edit"

                        onTriggered: {
                            editReceiptItemDialog.receiptItemName = nameRole
                            editReceiptItemDialog.receiptItemPrice = priceRole
                            editReceiptItemDialog.receiptItemCount = countRole
                            editReceiptItemDialog.open()
                        }
                    }

                    MenuItem {
                        text: "Delete"

                        onTriggered: receiptItemsViewModel.deleteReceiptItem(
                                         index)
                    }
                }

                ReceiptItemDialog {
                    id: editReceiptItemDialog

                    onAccepted: receiptItemsViewModel.updateReceiptItem(
                                    index, receiptItemName, receiptItemPrice,
                                    receiptItemCount)
                }
            }
        }
    }

    ReceiptItemDialog {
        id: createReceiptItemDialog

        onAccepted: receiptItemsViewModel.createReceiptItem(receiptItemName,
                                                            receiptItemPrice,
                                                            receiptItemCount)
    }
}
