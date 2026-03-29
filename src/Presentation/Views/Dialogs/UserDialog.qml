import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../Controls"

AnimatedDialog {
    id: root

    property alias userName: nameTextField.text

    standardButtons: Dialog.Ok | Dialog.Cancel

    GridLayout {
        anchors.fill: parent

        columns: 2

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Имя:"
        }

        TextField {
            id: nameTextField

            Layout.fillHeight: true
            Layout.fillWidth: true

            placeholderText: "Иван Иванов"
        }
    }

    function clear() {
        nameTextField.text = ""
    }
}
