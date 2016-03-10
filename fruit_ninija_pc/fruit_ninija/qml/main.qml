import QtQuick 2.2
import QtQuick.Window 2.1

Window
{  
    id: root  
    width: 320  
    height: 480  
    visible: true  
  
    Image {
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -80
        source: "qrc:/qml/images/new-game.png"
        NumberAnimation on rotation {
            from: 0; to: 360; duration: 3000; loops: Animation.Infinite
        }
    }
}  

