import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: usersListPage

    Rectangle {
        id: headerRect

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.topMargin: 20
        height: 20

        Text {
            text: "Current Users Online: " + (util.usersModel ? util.usersModel.numberOnline : 0);
        }
    }

    ListView {
        id: usersListView

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: headerRect.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 4
        clip: true
        boundsBehavior: Flickable.DragOverBounds

        spacing: 10

        ListHeader {
            id: listHeader
            y: -usersListView.contentY - height
            currentList: parent
        }

        ListLoading {
            id: loadingIcon
            y: -height
        }

        property var userModel: util.createUsersModel()
        model: userModel

        delegate: Rectangle {
            width: parent.width
            height: childrenRect.height + 8
            color: "#d3d3d3"

            ColumnLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                y: 4

                Text {
                    text: name
                }

                Text {
                    text: {
                        var result = "";
                        if (online)
                        {
                            if (current_game)
                            {
                                result = "Currently Playing: " + current_game;
                            }
                            else
                            {
                                result = "Online";
                            }

                        }
                        else if (current_game)
                        {
                            result = "Last Played: " + current_game;
                        }

                        return result;
                    }
                }
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
        if (usersListView.userModel)
        {
            usersListView.userModel.destroy();
        }
    }
}
