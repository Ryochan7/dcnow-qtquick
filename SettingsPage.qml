import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: settingsPage

    property variant settings

    Rectangle {
        anchors.fill: parent
        color: "black"

        RowLayout {
            id: testRowLay
            //anchors.fill: parent
            //anchors.centerIn: parent
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20

            spacing: 50

            Label {
                text: "Launch app showing games"
                color: "white"
                font.bold: true
                //Layout.fillWidth: true
            }

            Item {
                Layout.preferredHeight: 1
                Layout.fillWidth: true
            }

            Switch {
                id: gamesPageSwitch
                checked: settings.inGames
                Layout.fillWidth: true

                onCheckedChanged: {
                    settings.inGames = checked;

                }
            }
        }

        Rectangle {
            anchors.top: testRowLay.bottom
            anchors.topMargin: 4
            width: parent.width - 16
            x: 8
            height: 1
            color: "#F0EAD6"
        }
    }
}
