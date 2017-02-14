import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: settingsPage

    property variant settings

    Rectangle {
        anchors.fill: parent
        color: "black"

        Item {
            id: launchInGamesItem
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            height: childrenRect.height

            RowLayout {
                id: testRowLay
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 20

                Label {
                    text: "Launch app showing games"
                    color: "white"
                    font.bold: true
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    Layout.fillWidth: true
                }

                Switch {
                    id: gamesPageSwitch
                    checked: settings.inGames
                    Layout.preferredWidth: 50
                    Layout.alignment: Qt.AlignRight

                    onCheckedChanged: {
                        settings.inGames = checked;
                    }
                }
            }

            Rectangle {
                anchors.top: testRowLay.bottom
                anchors.topMargin: 6
                width: parent.width - 16
                x: 8
                height: 1
                color: "#F0EAD6"
            }
        }


        Item {
            id: notificationGamesItem

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.top: launchInGamesItem.bottom
            anchors.topMargin: 6

            RowLayout {
                id: notificationGamesRow
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 20

                Label {
                    text: "Notify when players playing selected games"
                    color: "white"
                    font.bold: true
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    Layout.fillWidth: true
                }

                Switch {
                    id: notificationGamesSwitch
                    checked: settings.notifyGames
                    Layout.preferredWidth: 50
                    Layout.alignment: Qt.AlignRight

                    onCheckedChanged: {
                        settings.notifyGames = checked;
                    }
                }
            }

            Rectangle {
                anchors.top: notificationGamesRow.bottom
                anchors.topMargin: 4
                width: parent.width - 16
                x: 8
                height: 1
                color: "#F0EAD6"
            }
        }
    }
}
