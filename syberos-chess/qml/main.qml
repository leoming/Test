import QtQuick 2.2
import QtQuick.Window 2.1
import ChessGame 1.0

Window {
    id: window
    visible: true
    width: 720
    height: 830
    property var chessList: []
    property var normalList: []
    property var selectedList: []
    property var normalBoard
    property var blackSelectedBoard
    property var redSelectedBoard
    property bool gameOver: false

    function loadImageSource() {
        normalBoard = "qrc:/images/images/chess_normal.png";
        blackSelectedBoard = "qrc:/images/images/black_chess_checked.png";
        redSelectedBoard = "qrc:/images/images/red_chess_checked.png";
        //normalList
        normalList.push("qrc:/images/images/black_jiang1.png")
        normalList.push("qrc:/images/images/black_ju1.png")
        normalList.push("qrc:/images/images/black_ma1.png")
        normalList.push("qrc:/images/images/black_pao1.png")
        normalList.push("qrc:/images/images/black_si1.png")
        normalList.push("qrc:/images/images/black_xiang1.png")
        normalList.push("qrc:/images/images/black_zu1.png")
        normalList.push("qrc:/images/images/red_suai1.png")
        normalList.push("qrc:/images/images/red_ju1.png")
        normalList.push("qrc:/images/images/red_ma1.png")
        normalList.push("qrc:/images/images/red_pao1.png")
        normalList.push("qrc:/images/images/red_si1.png")
        normalList.push("qrc:/images/images/red_xiang1.png")
        normalList.push("qrc:/images/images/red_bing1.png")
        //selectedList
        selectedList.push("qrc:/images/images/black_jiang2.png")
        selectedList.push("qrc:/images/images/black_ju2.png")
        selectedList.push("qrc:/images/images/black_ma2.png")
        selectedList.push("qrc:/images/images/black_pao2.png")
        selectedList.push("qrc:/images/images/black_si2.png")
        selectedList.push("qrc:/images/images/black_xiang2.png")
        selectedList.push("qrc:/images/images/black_zu2.png")
        selectedList.push("qrc:/images/images/red_suai2.png")
        selectedList.push("qrc:/images/images/red_ju2.png")
        selectedList.push("qrc:/images/images/red_ma2.png")
        selectedList.push("qrc:/images/images/red_pao2.png")
        selectedList.push("qrc:/images/images/red_si2.png")
        selectedList.push("qrc:/images/images/red_xiang2.png")
        selectedList.push("qrc:/images/images/red_bing2.png")
    }

    function createChesses() {
        console.log("createChesses")
        var __component = Qt.createComponent("Chessman.qml");
        if (__component.status === Component.Ready)
            for (var i = 0; i < 32; ++i)
                chessList.push(__component.createObject(window));
        console.log("size: ", chessList.length);
    }

    function xPosMapToBoard(x) {
        return x * 80// + 2
    }

    function yMapToBoard(y) {
        return y * 80// + 2
    }

    function loadBoard() {
        var current = 0;
        var chessItem;
        for (var x = 0; x < 9; ++x) {
            for (var y = 0; y < 10; ++y) {
                var value = game.getChessAt(x, y)
                if (value > 0) {
                    console.log("current: ", current)
                    switch (value) {
                    case 1: //黑帅
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 2: //黑车
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 3: //黑马
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 4: //黑炮
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 5: //黑士
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 6: //黑象
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 7: //黑卒
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 8: //红将
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 9: //红车
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 10: //红马
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 11: //红炮
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 12: //红士
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 13: //红相
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 14: //红兵
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    }
                    ++current;
                }
            }
        }
    }

    ChessGame {
        id: game
    }

    Board {
        id: board
        anchors.fill: parent
    }

    Component.onCompleted: {
        loadImageSource()
        createChesses()
        loadBoard()
    }

    property var target
    function getPressedItem(x,y) {
        var item;
        for (var i = 0; i < chessList.length; ++i) {
            item = chessList[i]
            if (x > item.x && x < item.x + item.width && y > item.y && y < item.y + item.height) {
                console.log("item", item);
                return item;
            }
        }
        return null;
    }
    function getItemByPos(x, y) {
        var item;
        for (var i = 0; i < chessList.length; ++i) {
            item = chessList[i]
            if (item.xPos === x && item.yPos === y) {
                return item
            }
        }
        return null;
    }

    onTargetChanged: {
        if (target !== null) {

        }
    }

    function moveForComputerRun() {
        // move or eat
        var fromX = game.getComputerMoveFromX();
        var fromY = game.getComputerMoveFromY();
        var toX = game.getComputerMoveToX();
        var toY = game.getComputerMoveToY();
        console.log("from", fromX, fromY)
        console.log("to", toX, toY)
        var fromChess = getItemByPos(fromX, fromY);
        var toChess = getItemByPos(toX, toY);
        if (toChess !== null) {
            toChess.reset();
        }
        fromChess.x = toX * 80;
        fromChess.y = toY * 80;
        fromChess.xPos = toX;
        fromChess.yPos = toY;
    }

    function mapToBoard(pos) {
        var pos1 = Math.floor(pos / 80)
        return pos1
        //var pos2 = Math.floor((pos - 40) / 80)
        //console.log("pos1: ", pos1)
        //console.log("pos2: ", pos2)
        //return Math.floor((pos1 + pos2) / 2)

    }

    Timer {
        id: computerTimer
        repeat: false
        interval: 1000
        onTriggered: {
            game.computerRun(false);
            moveForComputerRun();
            var status = game.isGameOver();
            if (status) {
                console.log(status === 1 ? "computer win!" : "user win!")
                gameOver = true;
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPressed: {
            console.log("onPressed")
            if (gameOver) return;
            target = getPressedItem(mouse.x, mouse.y)
            if (target && target.value < 8) {
                target = null;
                return;
            }
            //target.setSource(target.value < 8 ? blackSelectedBoard : redSelectedBoard, selectedList[target.value - 1])
            if (target !== null)
                target.z = 1;
            console.log("target", target)
        }
        onReleased: {
            if (target === null) return;
            console.log("onReleased")
            //target.setSource(normalBoard, normalList[target.value - 1])
            var mouseX = mapToBoard(target.x + target.width / 2)
            var mouseY = mapToBoard(target.y + target.height / 2)
            console.log("mouse.x", mouse.x)
            console.log("mouse.y", mouse.y)
            console.log("mouse.xPos", mouseX);
            console.log("mouse.yPos", mouseY);
            var chessItem = getItemByPos(mouseX, mouseY);
            if (game.moveChess(target.xPos, target.yPos, mouseX, mouseY))
            {
                console.log("move valid!!!!!")
                if (chessItem !== null) {
                    chessItem.reset();
                }

                target.x = mouseX * 80
                target.y = mouseY * 80
                target.xPos = mouseX
                target.yPos = mouseY

                var status = game.isGameOver();
                if (status) {
                    console.log(status === 1 ? "computer win!" : "user win!")
                    gameOver = true;
                }
                else {
                    computerTimer.start()
                }
            }
            else {
                target.x = target.xPos * 80;
                target.y = target.yPos * 80;
            }
            target.z = 0;
            target = null;
        }

        drag.target: target
        drag.axis: Drag.XAndYAxis
        drag.minimumX: 0
        drag.maximumX: parent.width
        drag.minimumY: 0
        drag.maximumY: parent.height
    }
}
