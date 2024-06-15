import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "dcartcollection.js" as DCartcollection

Rectangle {
    id: usersListPage
    color: mainWindow.appTheme.backgroundColor

    Rectangle {
        id: headerRect

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        height: 24
        color: mainWindow.appTheme.backgroundColor

        Text {
            id: playersOnlineText
            anchors.top: headerRect.top
            anchors.left: headerRect.left
            text: "Players Online: " + (util.usersModel ? util.usersModel.numberOnline : 0);
            font.pointSize: 12 * mainWindow.fontSizeMulti
            color: mainWindow.appTheme.textColor
        }

        Text {
            anchors.top: headerRect.top
            anchors.right: headerRect.right
            text: (util.usersModel ? util.usersModel.numberPlayers : 0) + " Players"
            font.pointSize: 12 * mainWindow.fontSizeMulti
            color: mainWindow.appTheme.textColor
        }
    }

    ListView {
        id: usersListView

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: headerRect.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
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
            width: usersListView.width
            height: childrenRect.height + 8
            color: mainWindow.appTheme.backgroundColor

            ColumnLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10

                Image {
                    id: backImage
                    fillMode: Image.PreserveAspectCrop
                    source: {
                        var result = DCartcollection.backgrounds["UNKNOWN"];
                        if (current_game && current_game in DCartcollection.backgrounds)
                        {
                            result = DCartcollection.backgrounds[current_game];
                        }

                        return result;
                    }

                    Layout.fillWidth: true
                    Layout.preferredHeight: {
                        var result = 280;
                        if (Screen.primaryOrientation !== Qt.PortraitOrientation)
                        {
                            result = 220;
                        }

                        return result;
                    }


                    ColumnLayout {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10

                        Text {
                            text: name
                            font.pointSize: 16 * mainWindow.fontSizeMulti
                            color: mainWindow.appTheme.textColor
                            style: Text.Raised
                            styleColor: mainWindow.appTheme.styleColor
                        }

                        Text {
                            text: {
                                var result = "";
                                if (online)
                                {
                                    if (current_game)
                                    {
                                        result = current_game;
                                    }
                                    else
                                    {
                                        result = "Online";
                                    }
                                }
                                else
                                {
                                    result = "Offline";
                                }

                                return result;
                            }

                            font.pointSize: 14 * mainWindow.fontSizeMulti
                            style: Text.Raised
                            styleColor: mainWindow.appTheme.styleColor
                            color: mainWindow.appTheme.textColor
                        }


                        Text
                        {
                            id: levelText
                            text: level
                            font.pointSize: 12 * mainWindow.fontSizeMulti
                            style: Text.Raised
                            styleColor: mainWindow.appTheme.styleColor
                            color: mainWindow.appTheme.textColor
                        }

                        Item {
                            Layout.preferredWidth: 1
                            Layout.preferredHeight: 10
                        }

                        Item {
                            id: recentlyPlayedItem
                            Layout.fillWidth: true
                            visible: {
                                var result = false;
                                if (recent_games.length > 0)
                                {
                                    result = true;
                                }

                                return result;
                            }

                            Text {
                                id: playedRecentText
                                anchors.top: recentlyPlayedItem.top
                                text: qsTr("Played recently:")

                                font.pointSize: 12 * mainWindow.fontSizeMulti
                                style: Text.Raised
                                styleColor: mainWindow.appTheme.styleColor
                                color: mainWindow.appTheme.textColor
                            }

                            RowLayout {
                                anchors.top: playedRecentText.bottom
                                anchors.topMargin: 6
                                spacing: 10

                                Repeater
                                {
                                    model: recent_games
                                    delegate: Image {
                                        Layout.preferredHeight: 50
                                        Layout.preferredWidth: 50

                                        fillMode: Image.PreserveAspectFit
                                        source: {
                                            //console.log(modelData.desc);
                                            var result = DCartcollection.backgrounds["UNKNOWN"];
                                            if (modelData.desc && modelData.desc in DCartcollection.covers)
                                            {
                                                result = DCartcollection.covers[modelData.desc];
                                            }

                                            return result;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        onDragEnded: {
            var scrollDistance = Screen.desktopAvailableHeight / 4;
            if (contentY < -scrollDistance)
            {
                util.queueRefresh();
            }
        }
    }

    Connections {
        target: util
        function onDataReady() {
            loadingIcon.state = "";
        }

        function onUpdateQueued() {
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
