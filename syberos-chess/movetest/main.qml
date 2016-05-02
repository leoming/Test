import QtQuick 2.0
import QtQuick.Window 2.1

Window {
    id: window
    visible: true
    width: 720
    height: 830
    property var list: []
    property var animationTarget

    function createItems() {
        var __component = Qt.createComponent("Item.qml");
        if (__component.status === Component.Ready)
            for (var i = 0; i < 10; ++i)
                list.push(__component.createObject(window));
    }

    function xPosMapToBoard(x) {
        return x * 100
    }

    function yPosMapToBoard(y) {
        return y * 500
    }

    function loadBoard() {
        var current = 0;
        var oItem;
        for (var x = 0; x < 5; ++x) {
            for (var y = 0; y < 2; ++y) {
                oItem = list[current];
                oItem.xPos = x;
                oItem.yPos = y;
                oItem.x = xPosMapToBoard(x)
                oItem.y = yPosMapToBoard(y)
                oItem.setSource("./blue_circle.png", "./board212.png");
                current ++ ;
            }
        }
    }



    Back {
        id: back
        anchors.fill: parent
    }

    Component.onCompleted: {
        createItems()
        loadBoard()
        animationTarget = list[0];
    }
    property var target
    function getPressedItem(x,y) {
        var item;
        console.log("x", x);
        console.log("y", y);
        for (var i = 0; i < list.length; ++i) {
            item = list[i]
            console.log("item.x", item.x);
            console.log("item.x + item.width", item.x + item.width);
            console.log("item.y", item.y);
            console.log("item.y + item.height", item.y + item.height);
            if (x > item.x && x < item.x + item.width && y > item.y && y < item.y + item.height) {
                console.log("item", item);
                return item;
            }
        }
    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPressed: {
            console.log("onPressed")
            target = getPressedItem(mouse.x, mouse.y)
            console.log("target", target)
        }
        onReleased: {
            console.log("onReleased")
            animationTarget.x = 200;
            animationTarget.y = 200;
        }
        
        drag.target: target
        drag.axis: Drag.XAndYAxis
        drag.minimumX: 0
        drag.maximumX: parent.width
        drag.minimumY: 0
        drag.maximumY: parent.height
    }

}
