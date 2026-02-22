import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property date selectedTime: new Date()

    Frame {
        id: frame
        anchors.fill: root

        RowLayout {
            id: row

            SpinBox {
                id: hoursSpinBox

                Layout.fillHeight: true
                Layout.fillWidth: true

                from: 0
                to: 23
                editable: true
                wrap: true

                onValueModified: root.selectedTime = getDate()
            }

            SpinBox {
                id: minutesSpinBox

                Layout.fillHeight: true
                Layout.fillWidth: true

                from: 0
                to: 59
                editable: true
                wrap: true

                onValueModified: root.selectedTime = getDate()
            }

            SpinBox {
                id: secondsSpinBox

                Layout.fillHeight: true
                Layout.fillWidth: true

                from: 0
                to: 59
                editable: true
                wrap: true

                onValueModified: root.selectedTime = getDate()
            }
        }
    }

    onSelectedTimeChanged: {
        hoursSpinBox.value = root.selectedTime.getHours()
        minutesSpinBox.value = root.selectedTime.getMinutes()
        secondsSpinBox.value = root.selectedTime.getSeconds()
    }

    function getDate() {
        return new Date(0, 0, 0, hoursSpinBox.value, minutesSpinBox.value,
                        secondsSpinBox.value)
    }
}
