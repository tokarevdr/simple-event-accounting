import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: root

    property alias eventTitle: titleTextField.text
    property alias eventStartDate: startDateTextField.text
    property alias eventEndDate: endDateTextField.text

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

        TextField {
            id: startDateTextField

            Layout.fillHeight: true
            Layout.fillWidth: true

            placeholderText: "01.01.2007"
        }

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Конец:"
        }

        TextField {
            id: endDateTextField

            Layout.fillHeight: true
            Layout.fillWidth: true

            placeholderText: "01.01.2007"
        }
    }

    function clear() {
        titleTextField.text = ""
        startDateTextField.text = ""
        endDateTextField.text = ""
    }
}
