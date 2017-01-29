import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Qt.labs.settings 1.0

ApplicationWindow {
    id: mainWindow

    visible: true
    width: 640
    height: 480
    title: qsTr("Dreamcast Now")

    Settings {
        id: settings
        property bool inGames: false
    }

    header: ToolBar {
        ToolButton {
            id: menuButton
            text: "Dreamcast Now"
            enabled: false
            onClicked: {
                drawer.open();
            }
        }
    }

    Drawer {
        id: drawer
        width: 200
        height: mainWindow.height

        ListView {
            id: linksListView
            anchors.fill: parent
            currentIndex: -1

            model: ListModel {
                ListElement {
                    title: "Games"
                    source: "GamesPage.qml"
                }

                ListElement {
                    title: "Users"
                    source: "UsersPage.qml"
                }

                ListElement {
                    title: "Settings"
                    source: "SettingsPage.qml"
                }

                ListElement {
                    title: "Refresh"
                    source: ""
                }
            }

            delegate: ItemDelegate {
                text: title
                height: 40
                width: parent.width
                //horizontalAlignment: Text.AlignHCenter
                //verticalAlignment: Text.AlignVCenter
                highlighted: ListView.isCurrentItem

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (title === "Refresh")
                        {
                            //linksListView.currentIndex = -1;
                            mainContainer.replace(busyLoadingComp, StackView.Immediate);
                            util.queueRefresh();
                        }
                        else if (ListView.currentIndex !== index)
                        {
                            linksListView.currentIndex = index
                            var tempproperties = {}
                            if (source === "SettingsPage.qml")
                            {
                                tempproperties = {"settings": settings};
                            }

                            mainContainer.replace(Qt.resolvedUrl(source), tempproperties, StackView.Immediate);
                        }

                        drawer.close();
                    }
                }
            }
        }
    }

    Component {
        id: busyLoadingComp

        BusyIndicator {

        }
    }

    StackView {
        id: mainContainer
        anchors.fill: parent
        initialItem: busyLoadingComp

        /*initialItem: UsersPage {

        }
        */
    }

    /*Component.onCompleted: {
        if (settings.inGames)
        {
            mainContainer.replace(Qt.resolvedUrl("GamesPage.qml"), StackView.Immediate);
            linksListView.currentIndex = 0;
        }
        else
        {
            mainContainer.replace(Qt.resolvedUrl("UsersPage.qml"), StackView.Immediate);
            linksListView.currentIndex = 1;
        }
    }
    */

    Component {
        id: errorTextComponent

        Text {
            anchors.fill: parent

            id: errorTextText
            text: qsTr("Did not receive data");
        }
    }

    Connections {
        target: util
        onDataReady: {
            menuButton.enabled = true;

            if (linksListView.currentIndex === -1)
            {
                if (settings.inGames)
                {
                    mainContainer.replace(Qt.resolvedUrl("GamesPage.qml"), StackView.Immediate);
                    linksListView.currentIndex = 0;
                }
                else
                {
                    mainContainer.replace(Qt.resolvedUrl("UsersPage.qml"), StackView.Immediate);
                    linksListView.currentIndex = 1;
                }
            }
            else
            {
                mainContainer.replace(Qt.resolvedUrl(linksListView.model.get(linksListView.currentIndex).source),
                                      StackView.Immediate);
            }

        }

        onError: {
            mainContainer.replace(errorTextComponent, StackView.Immediate);
            linksListView.currentIndex = -1;
        }
    }
}
