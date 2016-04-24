import QtQuick 2.2

Item {
    id: chessMan
    property bool isSelected: false
    property var xPos: -1
    property var yPos: -1
    function setSource(borderSource, wordSource) {
        border.source = borderSource;
        word.source = wordSource;
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
}
