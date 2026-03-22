import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Dialogs"

Item {
    id: root

    property var consumersViewModel: null
    property var participantsViewModel: null

    ColumnLayout {
        anchors.fill: root

        Button {
            Layout.preferredHeight: 50
            Layout.preferredWidth: 100

            text: "Create"

            onClicked: {
                createConsumerDialog.clear()
                createConsumerDialog.open()
            }
        }

        ListView {
            id: consumersListView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: consumersViewModel

            delegate: Item {
                height: consumersListView.height / 10
                width: consumersListView.width

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

                            text: consumptionRatioRole
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 50

                        Button {
                            anchors.fill: parent

                            text: "..."

                            onClicked: consumerMenu.open()
                        }
                    }
                }

                Menu {
                    id: consumerMenu

                    MenuItem {
                        text: "Edit"

                        onTriggered: {
                            editConsumerDialog.consumerIndex
                                    = participantsViewModel.participantIndexById(
                                        buyerIdRole)
                            editConsumerDialog.consumptionRatio = consumptionRationRole
                            editConsumerDialog.open()
                        }
                    }

                    MenuItem {
                        text: "Delete"

                        onTriggered: console.log("DELETE")
                    }
                }

                ConsumerDialog {
                    id: editConsumerDialog

                    onAccepted: console.log("UPDATE")
                }
            }
        }
    }

    ConsumerDialog {
        id: createConsumerDialog

        onAccepted: consumersViewModel.createConsumer(consumerId, consumerName,
                                                      consumptionRatio)
    }
}
