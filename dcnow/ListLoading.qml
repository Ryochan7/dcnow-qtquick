import QtQuick

Image {
    id: loadingIcon

    source: "icon-loading.png"
    y: -height
    height: 48
    anchors.horizontalCenter: parent.horizontalCenter
    visible: false

    Behavior on y {
        NumberAnimation {
            duration: 200
        }
    }

    states: [
        State {
            name: "shown"
            PropertyChanges {
                target: loadingIcon
                y: 0
                visible: true
            }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "shown"
            RotationAnimation {
                target: loadingIcon
                loops: Animation.Infinite
                from: 0
                to: 360
            }
        }
    ]
}
