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

        property var gamesModel: util.createGamesModel();
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
