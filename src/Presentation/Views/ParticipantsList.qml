import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property var participantsViewModel: null

    ColumnLayout {
        anchors.fill: root

        Button {
            Layout.preferredHeight: 50
            Layout.preferredWidth: 100

            text: "Create"

            onClicked: {
                createParticipantDialog.clear()
                createParticipantDialog.open()
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
                        text: "Edit"

                        onTriggered: {
                            editParticipantDialog.participantName = nameRole
                            editParticipantDialog.open()
                        }
                    }

                    MenuItem {
                        text: "Delete"

                        onTriggered: participantsViewModel.deleteParticipant(
                                         index)
                    }
                }

                ParticipantDialog {
                    id: editParticipantDialog

                    onAccepted: participantsViewModel.updateParticipant(
                                    index, participantName)
                }
            }
        }
    }

    ParticipantDialog {
        id: createParticipantDialog

        onAccepted: participantsViewModel.createParticipant(participantName)
    }
}
