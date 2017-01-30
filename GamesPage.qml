import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: gamesPage

    function resetGameMap()
    {
        for (var game in cacheObject.gameMap)
        {
            var gameObj = cacheObject.gameMap[game];
            gameObj = {"numOnline": 0, "players": []};
            cacheObject.gameMap[game] = gameObj;
        }
    }

    function parseGames(objString)
    {

        for (var oldGame in cacheObject.gameMap)
        {
            var oldObj = cacheObject.gameMap[oldGame];
            oldObj["numOnline"] = 0;
            oldObj["players"] = [];
        }

        var temp = JSON.parse(objString);
        var usersList = temp["users"];
        for (var i = 0; i < usersList.length; i++)
        {
            var user = usersList[i];
            var username = user["username"];
            var currentGame = user["current_game"];
            if (currentGame in cacheObject.gameMap)
            {
                var game = cacheObject.gameMap[currentGame];
                var players = game["players"];
                var found = false;
                for (var j = 0; j < players.length && !found; j++)
                {
                    var searchplayer = players[j];
                    if (searchplayer === username)
                    {
                        found = true;
                    }
                }

                if (!found)
                {
                    game["numOnline"] = game["numOnline"]++;
                    players.push(username);
                }
            }
        }

        noseNuggets.clear();
        for (var curgame in cacheObject.gameMap)
        {
            //console.log(cacheObject.gameMap[curgame]["numOnline"]);
            noseNuggets.append({"name": String(curgame),
                                "numberOnline": cacheObject.gameMap[curgame]["numOnline"]});
        }

        resetGameMap();
    }


    QtObject {
        id: cacheObject

        property var gameMap: {
            "4x4 Evolution": {"numOnline": 0, "players": []},
            "Alien Front Online": {"numOnline": 0, "players": []},
            "ChuChu Rocket": {"numOnline": 0, "players": []},
            "Crazy Taxi 2": {"numOnline": 0, "players": []},
            "Ferarri F355 Challenge": {"numOnline": 0, "players": []},
            "Maximum Pool": {"numOnline": 0, "players": []},
            "Metropolis Speed Racer": {"numOnline": 0, "players": []},
            "Phantasy Star Online": {"numOnline": 0, "players": []},
            "Planet Ring": {"numOnline": 0, "players": []},
            "Quake 3 Arena": {"numOnline": 0, "players": []},
            "Sega GT": {"numOnline": 0, "players": []},
            "Sonic Adventure": {"numOnline": 0, "players": []},
            "Sonic Adventure 2": {"numOnline": 0, "players": []},
            "Starlancer": {"numOnline": 0, "players": []},
            "The Next Tetris": {"numOnline": 0, "players": []},
            "Toy Racer": {"numOnline": 0, "players": []},
            "Worms World Party": {"numOnline": 0, "players": []},
        }
    }

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

        model: ListModel {
            id: noseNuggets
        }

        delegate: Rectangle {
            width: parent.width
            height: childrenRect.height + 8

            ColumnLayout {
                width: parent.width
                y: 4

                Text {
                    id: gameName
                    text: name
                }

                Text {
                    id: onlineStatus
                    text: {
                        var result = "";

                        if (numberOnline === 0)
                        {
                            result = "No one is playing at the moment";
                        }
                        else
                        {
                            result = "Number playing online: " + numberOnline;
                        }

                        return result;
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    //border.color: "#d3d3d3"
                    color: "#d3d3d3"
                    //border.width: 4
                    visible: index < gamesListView.count-1
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
            parseGames(util.getJsonData());
        }
    }

    Connections {
        target: util
        onDataReady: {
            parseGames(util.getJsonData());
            loadingIcon.state = "";
        }
    }
}
