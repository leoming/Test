import QtQuick 2.2

Item {
    id: item
    property bool isSelected: false
    property var xPos: -1
    property var yPos: -1
    width: border.width
    height: border.height
    antialiasing: true
    function setSource(borderSource, wordSource) {
        border.source = borderSource;
        word.source = wordSource;
    }
    Image {
        id: border
        source: ""
        Image {
            id: word
            anchors.centerIn: parent
            source: ""
        }
    }
    Behavior on x {
            NumberAnimation { easing.type: Easing.Linear; easing.amplitude: 3.0; easing.period: 2.0; duration: 500 }
    }
    Behavior on y {
            NumberAnimation { easing.type: Easing.Linear; easing.amplitude: 3.0; easing.period: 2.0; duration: 500 }
    }
}
