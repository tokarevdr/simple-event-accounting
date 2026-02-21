import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4 as OldControls
import QtQuick.Controls.Styles 1.4 as OldControlsStyles

Button {
    id: root

    property var formatDate: function (date) {
        return Qt.formatDate(date, "dd/MM/yyyy")
    }
    property alias selectedDate: calendar.selectedDate
    property alias minimumDate: calendar.minimumDate
    property alias maximumDate: calendar.maximumDate

    text: root.formatDate(calendar.selectedDate)

    onClicked: popup.open()

    Popup {
        id: popup

        OldControls.Calendar {
            id: calendar

            style: OldControlsStyles.CalendarStyle {
                navigationBar: Item {
                    height: 30
                    RowLayout {
                        anchors.fill: parent

                        Button {
                            Layout.fillHeight: true
                            Layout.preferredWidth: 40

                            text: "<<"

                            onClicked: calendar.showPreviousYear()
                        }

                        Button {
                            Layout.fillHeight: true
                            Layout.preferredWidth: 20

                            text: "<"

                            onClicked: calendar.showPreviousMonth()
                        }

                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            text: styleData.title

                            horizontalAlignment: Qt.AlignHCenter
                            verticalAlignment: Qt.AlignVCenter
                        }

                        Button {
                            Layout.fillHeight: true
                            Layout.preferredWidth: 20

                            text: ">"

                            onClicked: calendar.showNextMonth()
                        }

                        Button {
                            Layout.fillHeight: true
                            Layout.preferredWidth: 40

                            text: ">>"

                            onClicked: calendar.showNextYear()
                        }
                    }
                }
            }

            onClicked: {
                root.text = root.formatDate(date)
                popup.close()
            }

            onMinimumDateChanged: {
                if (selectedDate < minimumDate) {
                    selectedDate = minimumDate
                }
            }

            onMaximumDateChanged: {
                if (selectedDate > maximumDate) {
                    selectedDate = maximumDate
                }
            }

            onSelectedDateChanged: root.text = root.formatDate(selectedDate)
        }

        enter: Transition {
            NumberAnimation {
                property: "opacity"
                from: 0.0
                to: 1.0
                duration: 100
            }
        }

        exit: Transition {
            NumberAnimation {
                property: "opacity"
                from: 1.0
                to: 0.0
                duration: 100
            }
        }
    }
}
