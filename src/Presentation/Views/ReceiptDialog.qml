import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Controls"

Dialog {
    id: root

    property alias receiptTitle: titleTextField.text
    property alias purchaseDate: purchaseDatePicker.selectedDate
    property alias purchaseTime: purchaseTimePicker.selectedTime

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

            placeholderText: "Пятерочка"
        }

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Дата покупки:"
        }

        DatePicker {
            id: purchaseDatePicker

            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Время покупки:"
        }

        TimePicker {
            id: purchaseTimePicker

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    function clear() {
        titleTextField.text = ""
        purchaseDatePicker.selectedDate = new Date()
        purchaseTimePicker.selectedTime = new Date()
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
