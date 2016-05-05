import QtQuick 2.2

Item {
    id: chessMan
    property bool isSelected: false
    property var xPos: -1
    property var yPos: -1
    property var value: 0
    property bool showAnimate: true
    visible: false
    width: border.width
    height: border.height
    x: -100
    y: -100
    function setSource(borderSource, wordSource) {
        border.source = borderSource;
        word.source = wordSource;
    }
    function reset() {
        xPos = -1;
        yPos = -1;
        value = 0;
        isSelected = false
        border.source = ""
        word.source = ""
        showAnimate = true
        visible = false
        x = -100
        y = -100
    }

    Image {
        id: border
        //width: 60
        //height: 60
        source: ""
        Image {
            id: word
            anchors.centerIn: parent
            source: ""
        }
    }
    Behavior on x {
            NumberAnimation { easing.type: Easing.Linear; easing.amplitude: 3.0; easing.period: 2.0; duration: !showAnimate ? 10 : 500}
    }
    Behavior on y {
            NumberAnimation { easing.type: Easing.Linear; easing.amplitude: 3.0; easing.period: 2.0; duration: !showAnimate ? 10 : 500}
    }
}
