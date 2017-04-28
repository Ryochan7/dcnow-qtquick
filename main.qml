import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0
import Qt.labs.settings 1.0

ApplicationWindow {
    id: mainWindow

    visible: true
    width: 640
    height: 480
    title: qsTr("Dreamcast Now")
    property real fontSizeMulti: {
        var temp = Screen.devicePixelRatio;
        if (Screen.devicePixelRatio > 1.0)
        {
            temp = temp * 0.6;
        }

        return temp;
    }

    readonly property QtObject appTheme: QtObject {
        readonly property string backgroundColor: "#000000";
        readonly property string textColor: "#FFFFFF";
        readonly property string styleColor: "#000000";
    }

    Settings {
        id: settings
        property bool inGames: false
        property bool notifyGames: false
        property bool notifyUsers: false
        property variant notifyUserList
        property variant notifyGameList

        function disconnectNotifyGames()
        {
            if (!notifyGames)
            {
                util.dataReady.disconnect(searchGameList);
            }
        }

        function connectNotifyGames()
        {
            if (notifyGames)
            {
                util.dataReady.connect(searchGameList);
            }
        }

        function toggleNotifyGames()
        {
            if (notifyGames)
            {
                connectNotifyGames();
            }
            else
            {
                disconnectNotifyGames();
            }
        }

        function refreshGameList()
        {
            var temp = [];
            var stringlist = util.getFollowedGames();
            for (var item in stringlist)
            {
                temp.push(stringlist[item]);
            }

            notifyGameList = temp;
        }

        Component.onCompleted: {
            if (notifyGameList === null)
            {
                notifyGameList = [];
            }

            if (notifyUserList === null)
            {
                notifyUserList = [];
            }

            var temp = notifyGameList;
            for (var i = 0; i < temp.length; i++)
            {
                util.addFollowedGame(temp[i]);
            }
        }
    }

    header: ToolBar {
        ToolButton {
            id: menuButton
            text: "Dreamcast Now"
            font.pointSize: 12 * mainWindow.fontSizeMulti
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
                    title: "Game Schedule"
                    source: "GameSchedule.qml"
                }

                ListElement {
                    title: "Settings"
                    source: "SettingsPage.qml"
                }
            }

            delegate: ItemDelegate {
                text: title
                height: 40
                width: parent.width
                //horizontalAlignment: Text.AlignHCenter
                //verticalAlignment: Text.AlignVCenter
                highlighted: ListView.isCurrentItem
                font.pointSize: 10 * mainWindow.fontSizeMulti

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (ListView.currentIndex !== index)
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

    Timer {
        id: gameNotifyTimer
        repeat: true
        interval: 1000 * 60 * 5
        //running: true
        triggeredOnStart: false
        onTriggered: {
            util.queueRefresh();
        }
    }

    Component.onCompleted: {
        settings.connectNotifyGames();
        settings.notifyGamesChanged.connect(settings.toggleNotifyGames);
        util.dataReady.connect(initView);
    }

    function searchGameList()
    {
        var stringlist = util.getFollowedGames();
        var output = "";
        var userstemp = [];
        var gamePlayed = {};
        var modelCreated = util.gamesModel === null ? true : false;
        var gamesModel = modelCreated ? util.createGamesModel() : util.gamesModel;
        for (var i = 0; i < gamesModel.rowCount(); i++)
        {
            var found = false;
            for (var j = 0; j < stringlist.length && !found; j++)
            {
                var temp = gamesModel.get(i);
                var search = stringlist[j];
                if (search === temp.name && temp.numberOnline > 0)
                {
                    found = true;
                    output += temp.players;
                    stringlist.splice(j, 1);

                    if (!(search in gamePlayed))
                    {
                        gamePlayed[search] = [];
                    }

                    gamePlayed[search].push(temp.players);
                }
            }
        }

        for (var game in gamePlayed)
        {
            var tempOut = gamePlayed[game];
            util.sendNotify(game, "Currently playing: " + tempOut);
        }

        if (modelCreated)
        {
            gamesModel.destroy();
        }
    }

    Component {
        id: errorTextComponent

        Text {
            anchors.fill: parent

            id: errorTextText
            text: qsTr("Did not receive data");
        }
    }

    function initView()
    {
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

        if (!gameNotifyTimer.running)
        {
            gameNotifyTimer.start();
        }
    }

    Connections {
        target: util
        onDataReady: {
            if (!gameNotifyTimer.running)
            {
                gameNotifyTimer.start();
            }
        }

        onError: {
            mainContainer.replace(errorTextComponent, StackView.Immediate);
            linksListView.currentIndex = -1;
            gameNotifyTimer.stop();
        }
    }
}
