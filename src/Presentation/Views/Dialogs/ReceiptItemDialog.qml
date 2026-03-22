import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../Controls"

AnimatedDialog {
    id: root

    property alias receiptItemName: nameTextField.text
    property alias receiptItemPrice: priceSpinBox.value
    property alias receiptItemCount: countSpinBox.value

    standardButtons: Dialog.Ok | Dialog.Cancel

    GridLayout {
        anchors.fill: parent

        columns: 2

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Наименование:"
        }

        TextField {
            id: nameTextField

            Layout.fillHeight: true
            Layout.fillWidth: true

            placeholderText: "Колбаса"
        }

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Цена:"
        }

        SpinBox {
            id: priceSpinBox

            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Количество:"
        }

        SpinBox {
            id: countSpinBox

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    function clear() {
        nameTextField.text = ""
        priceSpinBox.value = 0
        countSpinBox.value = 1
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
