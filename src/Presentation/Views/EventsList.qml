import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property var eventsViewModel: null
    property var formatDate: function (date) {
        return Qt.formatDate(date, "dd.MM.yyyy")
    }

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
                height: eventsListView.height / 10
                width: eventsListView.width
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

                        text: root.formatDate(startDateRole)
                    }

                    Text {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        text: root.formatDate(endDateRole)
                    }

                    Button {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 30

                        text: "..."

                        onClicked: eventMenu.open()
                    }
                }

                Menu {
                    id: eventMenu

                    MenuItem {
                        text: "Edit"

                        onTriggered: {
                            editEventDialog.eventTitle = titleRole
                            editEventDialog.eventStartDate = startDateRole
                            editEventDialog.eventEndDate = endDateRole
                            editEventDialog.open()
                        }
                    }

                    MenuItem {
                        text: "Delete"

                        onTriggered: eventsViewModel.deleteEvent(index)
                    }
                }

                EventDialog {
                    id: editEventDialog

                    onAccepted: eventsViewModel.updateEvent(index, eventTitle,
                                                            eventStartDate,
                                                            eventEndDate)
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
