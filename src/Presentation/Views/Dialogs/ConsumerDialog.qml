import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "../Controls"

AnimatedDialog {
    id: root

    property alias consumerId: participantComboBox.currentValue
    property alias consumerName: participantComboBox.currentText
    property alias consumerIndex: participantComboBox.currentIndex
    property alias consumptionRatio: consumptionRatioSpinBox.value

    standardButtons: Dialog.Ok | Dialog.Cancel

    GridLayout {
        anchors.fill: parent

        columns: 2

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Потребитель:"
        }

        ComboBox {
            id: participantComboBox

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: eventParticipantsProxyVm
            textRole: "nameRole"
            valueRole: "idRole"
            editable: true
        }

        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "Доля:"
        }

        SpinBox {
            id: consumptionRatioSpinBox
            Layout.fillHeight: true
            Layout.fillWidth: true

            from: 1
            to: 100
        }
    }

    function clear() {
        participantComboBox.currentIndex = -1
        consumptionRatioSpinBox.value = 1
    }
}
