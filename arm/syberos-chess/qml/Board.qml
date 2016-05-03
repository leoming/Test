import QtQuick 2.0
import com.syberos.basewidgets 2.0
//import QtQuick.Window 2.1
import ChessGame 1.0

CPage {
    id: board
    visible: true
    width: 720
    orientationLock: CPageOrientation.LockPortrait
    statusBarHoldEnabled: false
    property var margin: (window.height - 830)/2
    //height: 830
    property var chessList: []
    property var normalList: []
    property var selectedList: []
    property var normalBoard
    property var blackSelectedBoard
    property var redSelectedBoard
    property bool gameOver: false
    property bool computerThinking: false

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
        var __component = Qt.createComponent("Chessman.qml");
        if (__component.status === Component.Ready)
            for (var i = 0; i < 32; ++i)
                chessList.push(__component.createObject(board));
    }

    function xPosMapToBoard(x) {
        return x * 80
    }

    function yPosMapToBoard(y) {
        return y * 80 + margin
    }

    function loadBoard() {
        var current = 0;
        var chessItem;
        for (var x = 0; x < 9; ++x) {
            for (var y = 0; y < 10; ++y) {
                var value = game.getChessAt(x, y)
                if (value > 0) {
                    switch (value) {
                    case 1: //黑帅
                    {
                        chessItem = chessList[current];
                        chessItem.value = value;
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource(normalBoard, normalList[value - 1]);
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
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
                        chessItem.y = yPosMapToBoard(y)
                        chessItem.visible = true
                        break;
                    }
                    }
                    ++current;
                }
            }
        }
    }

    function restartGame() {
        game.reStart();
        var item;
        for (var i = 0; i < chessList.length; ++i) {
            item = chessList[i]
            item.showAnimate = true;
        }
        loadBoard();
    }

    ChessGame {
        id: game
    }

    contentAreaItem: Item {
        id: contentArea

    Image {
        id: bg
        anchors.fill: parent
        source: "qrc:/images/images/room_bg.png"
        z: -1
    }

    Item {
        id: headTools
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: margin
        z: 1
    }

    Image{
        id: boardImg
        anchors.top: headTools.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        source: "qrc:/images/images/chess_board.png"
    }

    Item {
        id: tailTools
        anchors.top: boardImg.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: margin
        z: 1

        Image {
            id: restart
            source: "qrc:/images/images/restart_img.png"
            //anchors.left: parent.left
            //anchors.leftMargin: 100
            //anchors.verticalCenter: parent.verticalCenter
            anchors.centerIn: parent
            MouseArea {
                anchors.fill: restart
                onClicked: {
                    console.log("onClicked")
                    restartGame();
                }
            }
        }
        /*
        Image {
            id: quit
            source:"qrc:/images/images/quit_img.png"
            anchors.left: restart.right
            anchors.leftMargin: 150
            anchors.right: parent.right
            anchors.rightMargin: 100
            anchors.verticalCenter: parent.verticalCenter
            MouseArea {
                anchors.fill: quit
                onClicked: {
                    console.log("onClicked")
                    confirmDialog.show();
                }
            }
        }
        */
    }

    CDialog
    {
        id: confirmDialog
        // 1 draft 2 resend 3 remove
        anchors.fill: parent
        titleAreaEnabled: false
        messageTextPixelSize: 32
        messageText: "是否退出游戏？"
        Component.onCompleted: hide();
    }
    }

    Component.onCompleted: {
        loadImageSource()
        createChesses()
        loadBoard()
        gScreenInfo.setStatusBar(false);

        console.log("margin:", margin);
    }

    property var target
    function getPressedItem(x,y) {
        var item;
        for (var i = 0; i < chessList.length; ++i) {
            item = chessList[i]
            if (x > item.x && x < item.x + item.width && y > item.y && y < item.y + item.height) {
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
        var fromChess = getItemByPos(fromX, fromY);
        var toChess = getItemByPos(toX, toY);
        if (toChess !== null) {
            toChess.reset();
        }
        fromChess.x = xPosMapToBoard(toX)//toX * 80;
        fromChess.y = yPosMapToBoard(toY)//toY * 80;
        fromChess.xPos = toX;
        fromChess.yPos = toY;
    }

    function mapToBoard(pos) {
        var pos1 = Math.floor(pos / 80)
        return pos1
    }

    Timer {
        id: computerTimer
        repeat: false
        interval: 100
        onTriggered: {
            computerThinking = true
            game.computerRun(false);
            moveForComputerRun();
            var status = game.isGameOver();
            if (status) {
                console.log(status === 1 ? "computer win!" : "user win!")
                console.log(status === 1 ? gToast.requestToast("computer win!") : gToast.requestToast("user win!"))
                gameOver = true;
            }
            resetComputer.start();
        }
    }

    Timer {
        id: resetComputer
        repeat: false
        interval: 600
        onTriggered:
            computerThinking = false

    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPressed: {
            if (gameOver || computerThinking) return;
            target = getPressedItem(mouse.x, mouse.y)
            if (target && target.value < 8) {
                target = null;
                return;
            }
            //target.setSource(target.value < 8 ? blackSelectedBoard : redSelectedBoard, selectedList[target.value - 1])
            if (target !== null) {
                target.z = 10;
                target.showAnimate = false
            }
        }
        onReleased: {
            if (target === null) return;
            //target.setSource(normalBoard, normalList[target.value - 1])
            var mouseX = mapToBoard(target.x + target.width / 2)
            var mouseY = mapToBoard(target.y + target.height / 2 - margin)
            var chessItem = getItemByPos(mouseX, mouseY);
            if (game.moveChess(target.xPos, target.yPos, mouseX, mouseY))
            {
                if (chessItem !== null) {
                    chessItem.reset();
                }

                target.x = xPosMapToBoard(mouseX)//mouseX * 80
                target.y = yPosMapToBoard(mouseY)//mouseY * 80
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
                target.x = xPosMapToBoard(target.xPos)//target.xPos * 80;
                target.y = yPosMapToBoard(target.yPos)//target.yPos * 80;
            }
            if (target !== null)
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


    Connections
    {
        target: confirmDialog
        onAccepted: {
            window.quit();
        }
    }
}
