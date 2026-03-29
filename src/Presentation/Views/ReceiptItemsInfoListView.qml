import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Dialogs"

Item {
    id: root

    property var receiptItemsInfoViewModel: null
    signal receiptItemSelected

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
            id: receiptItemsInfoListView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: receiptItemsInfoViewModel

            delegate: Item {
                height: receiptItemsInfoListView.height / 10
                width: receiptItemsInfoListView.width

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        receiptItemsInfoViewModel.selectReceiptItem(index)
                        root.receiptItemSelected()
                    }
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

                        onTriggered: receiptItemsInfoViewModel.deleteReceiptItem(
                                         index)
                    }
                }

                ReceiptItemDialog {
                    id: editReceiptItemDialog

                    onAccepted: receiptItemsInfoViewModel.updateReceiptItemInfo(
                                    index, receiptItemName, receiptItemPrice,
                                    receiptItemCount)
                }
            }
        }
    }

    ReceiptItemDialog {
        id: createReceiptItemDialog

        onAccepted: receiptItemsInfoViewModel.createReceiptItem(receiptItemName,
                                                            receiptItemPrice,
                                                            receiptItemCount)
    }
}
