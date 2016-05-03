import QtQuick 2.2
import com.syberos.basewidgets 2.0
//import QtQuick.Window 2.1
import ChessGame 1.0

CPageStackWindow {
    id: window
    visible: true
    width: 720
    //respondOnBackKeyReleased: true
    initialPage: Board{}
}
