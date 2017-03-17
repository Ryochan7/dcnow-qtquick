import QtQuick 2.7
import QtQuick.XmlListModel 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Item {
    id: schedulePage

    BusyIndicator {
        id: busyLoading
        anchors.fill: parent
        running: xmlModel.status === XmlListModel.Loading
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
        model: XmlListModel {
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

        delegate: Item {
            anchors.left: parent.left
            anchors.right: parent.right
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
                visible: index < xmlModel.count-1
            }
        }
    }
}
