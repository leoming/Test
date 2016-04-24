import QtQuick 2.2
import QtQuick.Window 2.1
import ChessGame 1.0

Window {
    id: window
    visible: true
    width: 720
    height: 830
    property var chessList: []

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
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/black_jiang1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 2: //黑车
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/black_ju1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 3: //黑马
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/black_ma1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 4: //黑炮
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/black_pao1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 5: //黑士
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/black_si1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 6: //黑象
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/black_xiang1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 7: //黑卒
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/black_zu1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 8: //红将
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/red_suai1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 9: //红车
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/red_ju1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 10: //红马
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/red_ma1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 11: //红炮
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/red_pao1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 12: //红士
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/red_si1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 13: //红相
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/red_xiang1.png");
                        chessItem.x = xPosMapToBoard(x)
                        chessItem.y = xPosMapToBoard(y)
                        break;
                    }
                    case 14: //红兵
                    {
                        chessItem = chessList[current];
                        chessItem.xPos = x;
                        chessItem.yPos = y;
                        chessItem.setSource("qrc:/images/images/chess_normal.png", "qrc:/images/images/red_bing1.png");
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
        createChesses()
        loadBoard()
    }
}
