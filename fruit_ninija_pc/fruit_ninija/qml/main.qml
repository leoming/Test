import QtQuick 2.2
import QtQuick.Window 2.1

Window
{  
    id: root  
    width: 620
    height: 480  
    visible: true  

    Image {
        id: background
        anchors.fill: parent
        source: "qrc:/qml/images/background.jpg"

        Component.onCompleted: {
            delayTimer.start()
        }
        Timer {
            id: delayTimer
            repeat: false
            interval: 300
            onTriggered: homeMaskAni.start()
        }

        Image {
            id: homeMask
            x: 0
            y: -200
            source: "qrc:/qml/images/home-mask.png"
            PropertyAnimation {
                id: homeMaskAni
                target: homeMask
                property: "y"
                from: -200
                to: 0
                duration: 500
                onStopped: ninijaAni.start();
            }

            Image {
                id: logo
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 340
                source: "qrc:/qml/images/logo.png"
            }
        }
        Image {
            id: ninija
            x: 300
            y: -150
            source: "qrc:/qml/images/ninja.png"
            PropertyAnimation {
                id: ninijaAni
                target: ninija
                property: "y"
                from: -150
                easing.type: Easing.InBounce
                to: 50
                duration: 500
                onStopped: homeDescAni.start();
            }
        }
        Image {
            id: homeDesc
            x: -200
            y: 130
            source: "qrc:/qml/images/home-desc.png"
            PropertyAnimation {
                id: homeDescAni
                target: homeDesc
                property: "x"
                from: -200
                to: 10
                duration: 500
                onStopped: btns.visible = true;
            }
        }

        Item {
            id: btns
            anchors.top: homeMask.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            visible: false

        Image {
            id: dojo
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottomMargin: 20
            source: "qrc:/qml/images/dojo.png"
            NumberAnimation on rotation {
                from: 0; to: 360; duration: 9000; loops: Animation.Infinite
            }
            Image {
                id: peachImg
                anchors.centerIn: parent
                source: "qrc:/qml/images/fruit/peach.png"
                NumberAnimation on rotation {
                    from: 360; to: 0; duration: 4500; loops: Animation.Infinite
                }

            }
        }

        Image {
            id: newGame
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: dojo.right
            anchors.leftMargin: 35
            source: "qrc:/qml/images/new-game.png"
            NumberAnimation on rotation {
                from: 360; to: 0; duration: 9000; loops: Animation.Infinite
            }
            Image {
                id: sandiaImg
                anchors.centerIn: parent
                source: "qrc:/qml/images/fruit/sandia.png"
                NumberAnimation on rotation {
                    from: 0; to: 360; duration: 4500; loops: Animation.Infinite
                }
            }
        }

        Image {
            id: quit
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            source: "qrc:/qml/images/quit.png"
            NumberAnimation on rotation {
                from: 0; to: 360; duration: 9000; loops: Animation.Infinite
            }
            MouseArea {
                anchors.fill: parent
                onClicked: Qt.quit()
            }
            Image {
                id: boomImg
                anchors.centerIn: parent
                source: "qrc:/qml/images/fruit/boom.png"
                NumberAnimation on rotation {
                    from: 360; to: 0; duration: 9000; loops: Animation.Infinite
                }
            }
        }
        }
    }
}  

