import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: gamesPage

    ListView {
        id: gamesListView
        anchors.fill: parent
        anchors.margins: 20
        boundsBehavior: Flickable.DragOverBounds

        ListHeader {
            id: listHeader
            y: -gamesListView.contentY - height - 10
            currentList: parent
        }

        ListLoading {
            id: loadingIcon
            y: -height - 14
        }

        property QtObject gamesModel: util.createGamesModel();
        model: gamesModel

        delegate: Item {
            width: parent.width
            height: childrenRect.height + 8

            RowLayout {
                id: gameRowLay
                anchors.left: parent.left
                anchors.right: parent.right

                spacing: 10

                ColumnLayout {
                    Text {
                        id: gameName2
                        text: name
                    }

                    Text {
                        id: numberOnlineGame
                        text: "Currently online: " + numberOnline
                        Layout.fillWidth: true
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    }

                    Text {
                        id: onlineStatus2
                        Layout.fillWidth: true
                        visible: text !== "" ? true : false;
                        text: {
                            var result = "";

                            if (numberOnline !== 0)
                            {
                                result = "Currently playing: " + players;
                            }

                            return result;
                        }

                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    }
                }

                Button {
                    property bool addMode: !util.isFollowingGame(name)
                    text: addMode ? "+" : "-"
                    Layout.preferredWidth: 50
                    onClicked: {
                        if (addMode)
                        {
                            util.addFollowedGame(name);
                            addMode = false;
                        }
                        else
                        {
                            util.removeFollowGame(name);
                            addMode = true;
                        }

                        settings.refreshGameList();
                    }
                }
            }

            Rectangle {
                anchors.top: gameRowLay.bottom
                anchors.topMargin: 10
                width: parent.width
                height: 1
                color: "#d3d3d3"
                visible: index < gamesListView.count-1
            }
        }

        onDragEnded: {
            if (contentY < -120)
            {
                util.queueRefresh();
            }
        }
    }

    Popup {
        id: sortModePopup

        modal: true
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: contentItem.childrenRect.width
        height: contentItem.childrenRect.height

        function resetChoices()
        {
            defaultRadio.checked = true;
        }

        property int choice: 0;

        contentItem: ColumnLayout {
            ButtonGroup {
                id: buttonGroupChoices
                buttons: sortOptionsColumn.children
            }

            ColumnLayout {
                id: sortOptionsColumn
                anchors.left: parent.left
                anchors.right: parent.right

                RadioButton {
                    id: defaultRadio
                    text: "Default"
                    checked: true
                    onClicked: {
                        if (checked)
                        {
                            sortModePopup.choice = 0;
                        }
                    }
                }

                RadioButton {
                    text: "Alphabetical"
                    checked: false
                    onClicked: {
                        if (checked)
                        {
                            sortModePopup.choice = 1;
                        }
                    }
                }

                RadioButton {
                    text: "Number of Players"
                    checked: false
                    onClicked: {
                        if (checked)
                        {
                            sortModePopup.choice = 2;
                        }
                    }
                }
            }

            Item {
                id: spacerItem
                anchors.top: sortOptionsColumn.bottom
                height: 20
                width: parent.width
            }

            RowLayout {
                id: sortConfirmRow
                anchors.top: spacerItem.bottom

                Button {
                    text: "Close"
                    onClicked: {
                        sortModePopup.close();
                    }
                }

                Button {
                    text: "Ok"
                    onClicked: {
                        gamesListView.gamesModel.setSortMode(sortModePopup.choice);
                        gamesListView.gamesModel.sortModel();
                        sortModePopup.close();
                    }
                }
            }
        }
    }


    Button {
        text: "Sort"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 30
        anchors.bottomMargin: 30

        onClicked: {
            sortModePopup.open();
        }
    }

    Connections {
        target: util
        onDataReady: {
            loadingIcon.state = "";
        }

        onUpdateQueued: {
            loadingIcon.state = "shown";
        }
    }

    Component.onDestruction: {
        if (gamesListView.gamesModel)
        {
            gamesListView.gamesModel.destroy();
        }
    }
}
