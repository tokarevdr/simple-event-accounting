import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Dialogs"

Item {
    id: root

    property var eventParticipantsViewModel: null

    ColumnLayout {
        anchors.fill: root

        Button {
            Layout.preferredHeight: 50
            Layout.preferredWidth: 100

            text: "Add"

            onClicked: {
                addEventParticipantDialog.clear()
                addEventParticipantDialog.open()
            }
        }

        ListView {
            id: eventParticipantsListView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: eventParticipantsViewModel

            delegate: Item {
                height: eventParticipantsListView.height / 10
                width: eventParticipantsListView.width
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

                            onClicked: eventParticipantMenu.open()
                        }
                    }
                }

                Menu {
                    id: eventParticipantMenu

                    MenuItem {
                        text: "Delete"

                        onTriggered: eventParticipantsViewModel.deleteEventParticipant(
                                         index)
                    }
                }
            }
        }
    }

    EventParticipantDialog {
        id: addEventParticipantDialog

        onAccepted: eventParticipantsViewModel.createEventParticipant(
                        participantId, participantName)
    }
}
