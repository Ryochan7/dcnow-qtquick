import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    function parseUsers(objString)
    {
        //console.log(objString);

        cacheObject.currentlyOnline = 0;
        usersModel.clear();

        var temp = JSON.parse(objString);
        var usersList = temp["users"];
        var tempmap = {};
        var templist = [];
        for (var i = 0; i < usersList.length; i++)
        {
            var user = usersList[i];
            //console.log(user["username"]);
            var username = user["username"];
            var currentGame = user["current_game"];
            var currentlyOnline = Boolean(user["online"]);
            templist[i] = {"username": username, "current_game": currentGame, "online": currentlyOnline};
        }

        var mapped = templist.map(function(el, i) {
            return {"user": el, "index": i};
        });

        mapped.sort(function(a, b) {
            var result = 0;
            var a_user = a["user"];
            var b_user = b["user"];
            if (a_user["online"] !== b_user["online"])
            {
                if (a_user["online"])
                {
                    result = -1;
                }
                else
                {
                    result = 1;
                }
            }

            else if (a_user["username"].toLowerCase() < b_user["username"].toLowerCase())
            {
                result = -1
            }
            else if (a_user["username"].toLowerCase() > b_user["username"].toLowerCase())
            {
                result = 1;
            }

            return result;
        });

        for (i = 0; i < mapped.length; i++)
        {
            user = mapped[i]["user"];
            username = user["username"];
            currentGame = user["current_game"];
            currentlyOnline = Boolean(user["online"]);
            usersModel.append({"name": username,
                               "current_game": currentGame,
                               "online": currentlyOnline});

            if (currentlyOnline)
            {
                cacheObject.currentlyOnline++;
            }
        }
    }

    QtObject {
        id: cacheObject
        property int currentlyOnline: 0
    }

    id: usersListPage

    Rectangle {
        id: headerRect

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.topMargin: 20
        //height: childrenRect.height
        height: 20

        Text {
            text: "Current Users Online: " + cacheObject.currentlyOnline
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

        model: ListModel {
            id: usersModel

            /*ListElement {
                name: "UGB"
                currentgame: "Phantasy Star Online"
            }

            ListElement {
                name: "Ryo"
                currentgame: "ChuChu Rocket!"
            }
            */
        }

        delegate: Rectangle {
            width: parent.width
            height: childrenRect.height + 8
            color: "#d3d3d3"

            ColumnLayout {
                //anchors.fill: parent
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                //height: 60
                y: 4

                Text {
                    //height: 30
                    text: name
                }

                Text {
                    //height: 30
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
                loadingIcon.state = "shown";
            }
        }
    }

    Component.onCompleted: {
        if (util.getJsonData() !== "")
        {
            parseUsers(util.getJsonData());
        }
    }

    Connections {
        target: util
        onDataReady: {
            parseUsers(util.getJsonData());
            loadingIcon.state = "";
        }
    }
}
