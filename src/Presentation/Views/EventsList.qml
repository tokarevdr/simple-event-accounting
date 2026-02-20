import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property var eventsViewModel: null

    ColumnLayout {
        anchors.fill: root

        Button {
            Layout.preferredHeight: 50
            Layout.preferredWidth: 100

            text: "Create"

            onClicked: createEventDialog.open()
        }

        ListView {
            id: eventsListView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: eventsViewModel

            delegate: Item {
                height: 50
                width: 200
                RowLayout {
                    anchors.fill: parent

                    Text {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        text: titleRole
                    }

                    Text {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        text: startDateRole
                    }

                    Text {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        text: endDateRole
                    }
                }
            }
        }
    }

    EventDialog {
        id: createEventDialog

        onAccepted: eventsViewModel.createEvent(eventTitle, eventStartDate,
                                                eventEndDate)
    }
}
