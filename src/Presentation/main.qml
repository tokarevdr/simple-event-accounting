import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Views"

ApplicationWindow {
    id: window
    width: 1600
    height: 800
    visible: true
    title: qsTr("Hello World")

    RowLayout {
        anchors.fill: parent

        Item {
            id: eventsTab

            Layout.fillHeight: true
            Layout.fillWidth: true

            EventsList {
                id: eventsList

                anchors.fill: parent
                anchors.margins: 5
                eventsViewModel: eventsVm

                onEventClicked: {
                    eventParticipantsVm.setEventId(eventId)
                    receiptsVm.setEventId(eventId)
                    receiptItemsVm.setReceiptId(-1)
                    consumersVm.setReceiptItemId(-1)
                }
            }
        }

        Item {
            id: participantsTab

            Layout.fillHeight: true
            Layout.fillWidth: true

            ParticipantsList {
                id: participantsList

                anchors.fill: parent
                anchors.margins: 5
                participantsViewModel: participantsVm
            }
        }

        Item {
            id: eventParticipantsTab

            Layout.fillHeight: true
            Layout.fillWidth: true

            EventParticipantsList {
                id: eventParticipantsList

                anchors.fill: parent
                anchors.margins: 5
                eventParticipantsViewModel: eventParticipantsVm
            }
        }

        Item {
            id: receiptsTab

            Layout.fillHeight: true
            Layout.fillWidth: true

            ReceiptsList {
                id: receiptsList

                anchors.fill: parent
                anchors.margins: 5
                receiptsViewModel: receiptsVm
                participantsViewModel: participantsVm

                onReceiptClicked: {
                    receiptItemsVm.setReceiptId(receiptId)
                    consumersVm.setReceiptItemId(-1)
                }
            }
        }

        Item {
            id: receiptItemsTab

            Layout.fillHeight: true
            Layout.fillWidth: true

            ReceiptItemsList {
                id: receiptItemsList

                anchors.fill: parent
                anchors.margins: 5
                receiptItemsViewModel: receiptItemsVm

                onReceiptItemClicked: consumersVm.setReceiptItemId(
                                          receiptItemId)
            }
        }

        Item {
            id: consumersTab

            Layout.fillHeight: true
            Layout.fillWidth: true

            ConsumersList {
                id: consumersList

                anchors.fill: parent
                anchors.margins: 5
                consumersViewModel: consumersVm
                participantsViewModel: participantsVm
            }
        }
    }
}
