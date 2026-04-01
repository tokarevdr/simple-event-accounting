import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Controls"

Item {
    id: root

    property var eventViewModel: null
    required property NavigationController navController

    ColumnLayout {
        anchors.fill: parent

        Button {
            text: "К списку"

            onClicked: navController.currentView = NavigationController.EventsInfo
        }

        Label {
            text: eventViewModel.title
        }

        Label {
            text: eventViewModel.startDate
        }

        Label {
            text: eventViewModel.endDate
        }

        StackLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            currentIndex: tabBar.currentIndex


        }

        TabBar {
            id: tabBar
            Layout.preferredHeight: 40
            Layout.fillWidth: true

            TabButton {
                text: "Участники"
            }

            TabButton {
                text: "Чеки"
            }
        }
    }
}
