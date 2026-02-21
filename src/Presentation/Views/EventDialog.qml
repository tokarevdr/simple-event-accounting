import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Controls"

Dialog {
    id: root

    property alias eventTitle: titleTextField.text
    property alias eventStartDate: startDatePicker.selectedDate
    property alias eventEndDate: endDatePicker.selectedDate

    standardButtons: Dialog.Ok | Dialog.Cancel

    GridLayout {
        anchors.fill: parent

        columns: 2

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Название:"
        }

        TextField {
            id: titleTextField

            Layout.fillHeight: true
            Layout.fillWidth: true

            placeholderText: "Бухич"
        }

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Начало:"
        }

        DatePicker {
            id: startDatePicker

            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Конец:"
        }

        DatePicker {
            id: endDatePicker

            Layout.fillHeight: true
            Layout.fillWidth: true

            minimumDate: startDatePicker.selectedDate
        }
    }

    function clear() {
        titleTextField.text = ""
        startDatePicker.selectedDate = new Date()
        endDatePicker.selectedDate = new Date()
    }
}
