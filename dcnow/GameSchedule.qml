import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: schedulePage

    function populateModel()
    {
        var data = util.getJsonScheduleData();
        var obj = JSON.parse(data);
        for (var i in obj["events"])
        {
            var event = obj["events"][i];
            scheduleModel.append({"name": event.name, "eventDateTime": event.dtstart})
        }
    }

    BusyIndicator {
        id: busyLoading
        anchors.fill: parent
    }

    ListModel {
        id: scheduleModel
    }

    ListView {
        id: scheduleView
        anchors.fill: parent
        anchors {
            topMargin: 20
            bottomMargin: 20
            leftMargin: 10
            rightMargin: 10
        }

        boundsBehavior: Flickable.DragOverBounds
        model: scheduleModel

        /*model: XmlListModel {
            id: xmlModel
            source: "http://23.239.26.40/extramedia/hamfest.txt"
            //source: Qt.resolvedUrl("file:/home/ryochan7/hamfest.txt");
            query: "/events/event"

            XmlRole {
                name: "name";
                query: "name/string()";
            }

            XmlRole {
                name: "eventDateTime";
                query: "xs:dateTime(dtstart)";
            }
        }
        */

        delegate: Item {
            width: scheduleView.width
            height: childrenRect.height + 10

            ColumnLayout {
                id: mainCol
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 10

                Text {
                    text: name
                }

                Text {
                    text: eventDateTime
                }
            }

            Rectangle {
                anchors.top: mainCol.bottom
                anchors.topMargin: 10
                width: parent.width
                height: 1
                color: "#d3d3d3"
                //visible: index < xmlModel.count-1
                visible: index < scheduleModel.count - 1
            }
        }
    }

    Connections
    {
        target: util
        function onScheduleDataReady() {
            scheduleView.model = null;
            populateModel();
            scheduleView.model = scheduleModel;
            busyLoading.running = false;
        }
    }

    Component.onCompleted: {
        busyLoading.running = true;
        util.queueScheduleRefresh();
    }
}
