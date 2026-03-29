import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Dialogs"

Item {
    id: root

    property var eventsInfoViewModel: null
    property var formatDate: function (date) {
        return Qt.formatDate(date, "dd.MM.yyyy")
    }
    signal eventSelected()

    ColumnLayout {
        anchors.fill: root

        Button {
            text: "Create"

            onClicked: {
                createEventDialog.clear()
                createEventDialog.open()
            }
        }

        ListView {
            id: eventsListView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: eventsInfoViewModel

            delegate: Item {
                height: eventsListView.height / 10
                width: eventsListView.width

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        eventsInfoViewModel.selectEvent(index)
                        root.eventSelected()
                    }
                }

                RowLayout {
                    anchors.fill: parent

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: titleRole
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: root.formatDate(startDateRole)
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: root.formatDate(endDateRole)
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 50

                        Button {
                            anchors.fill: parent

                            text: "..."

                            onClicked: eventMenu.open()
                        }
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

                        onTriggered: eventsInfoViewModel.deleteEvent(index)
                    }
                }

                EventDialog {
                    id: editEventDialog

                    onAccepted: eventsInfoViewModel.updateEvent(index, eventTitle,
                                                            eventStartDate,
                                                            eventEndDate)
                }
            }
        }
    }

    EventDialog {
        id: createEventDialog

        onAccepted: eventsInfoViewModel.createEvent(eventTitle, eventStartDate,
                                                eventEndDate)
    }
}
