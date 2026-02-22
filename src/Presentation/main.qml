import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Views"

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    header: TabBar {
        id: bar

        TabButton {
            text: qsTr("Events")
        }

        TabButton {
            text: qsTr("Participants")
        }

        TabButton {
            text: qsTr("Receipts")
        }
    }

    StackLayout {
        anchors.fill: parent
        currentIndex: bar.currentIndex

        Item {
            id: eventsTab

            EventsList {
                id: eventsList

                anchors.fill: parent
                anchors.margins: 5
                eventsViewModel: eventsVm

                onEventClicked: receiptsVm.setEventId(eventId)
            }
        }

        Item {
            id: participantsTab

            ParticipantsList {
                id: participantsList

                anchors.fill: parent
                anchors.margins: 5
                participantsViewModel: participantsVm
            }
        }

        Item {
            id: receiptsTab

            ReceiptsList {
                id: receiptsList

                anchors.fill: parent
                anchors.margins: 5
                receiptsViewModel: receiptsVm
            }
        }
    }
}
