import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Dialogs"

Item {
    id: root

    property var participantsViewModel: null

    ColumnLayout {
        anchors.fill: root

        Button {
            Layout.preferredHeight: 50
            Layout.preferredWidth: 100

            text: "Add"

            onClicked: {
                addParticipantDialog.clear()
                addParticipantDialog.open()
            }
        }

        ListView {
            id: participantsListView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: participantsViewModel

            delegate: Item {
                height: participantsListView.height / 10
                width: participantsListView.width
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
                        Layout.preferredWidth: 50

                        Button {
                            anchors.fill: parent

                            text: "..."

                            onClicked: participantMenu.open()
                        }
                    }
                }

                Menu {
                    id: participantMenu

                    MenuItem {
                        text: "Delete"

                        onTriggered: participantsViewModel.deleteParticipant(
                                         index)
                    }
                }
            }
        }
    }

    ParticipantDialog {
        id: addParticipantDialog

        onAccepted: participantsViewModel.createParticipant(
                        participantId, participantName)
    }
}
