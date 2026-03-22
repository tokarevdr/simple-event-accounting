import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

AnimatedDialog {
    id: root

    property alias participantName: participantComboBox.currentText
    property alias participantId: participantComboBox.currentValue

    standardButtons: Dialog.Ok | Dialog.Cancel

    GridLayout {
        anchors.fill: parent

        columns: 2

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Участник:"
        }

        ComboBox {
            id: participantComboBox

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: participantsProxyVm
            textRole: "nameRole"
            valueRole: "idRole"
            editable: true
        }
    }

    function clear() {
        participantComboBox.currentIndex = -1
    }
}
