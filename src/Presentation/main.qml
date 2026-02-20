import QtQuick 2.15
import QtQuick.Window 2.15

import "Views"

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    EventsList {
        id: eventsList

        anchors.fill: parent

        eventsViewModel: eventsVm
    }
}
