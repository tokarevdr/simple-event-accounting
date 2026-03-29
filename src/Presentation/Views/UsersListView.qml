import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "Dialogs"

Item {
    id: root

    property var usersViewModel: null

    ColumnLayout {
        anchors.fill: root

        Button {
            text: "Create"

            onClicked: {
                createUserDialog.clear()
                createUserDialog.open()
            }
        }

        ListView {
            id: usersListView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: usersViewModel

            delegate: Item {
                height: usersListView.height / 10
                width: usersListView.width
                RowLayout {
                    anchors.fill: parent

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            anchors.fill: parent

                            text: nameRole
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 50

                        Button {
                            anchors.fill: parent

                            text: "..."

                            onClicked: userMenu.open()
                        }
                    }
                }

                Menu {
                    id: userMenu

                    MenuItem {
                        text: "Edit"

                        onTriggered: {
                            editUserDialog.userName = nameRole
                            editUserDialog.open()
                        }
                    }

                    MenuItem {
                        text: "Delete"

                        onTriggered: usersViewModel.deleteUser(
                                         index)
                    }
                }

                UserDialog {
                    id: editUserDialog

                    onAccepted: usersViewModel.updateUser(
                                    index, userName)
                }
            }
        }
    }

    UserDialog {
        id: createUserDialog

        onAccepted: usersViewModel.createUser(userName)
    }
}
