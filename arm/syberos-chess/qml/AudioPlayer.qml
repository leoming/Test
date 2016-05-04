import QtQuick 2.0
import QtMultimedia 5.0

Audio {
    id: player
    source: "qrc:/audio/audio_move_chess.ogg"
    volume: 1.0
    function playMoveSound() {
        player.source = "qrc:/audio/audio_move_chess.ogg"
        player.play();
        console.log("player status:", player.status)
        console.log("player error:", player.error)
        console.log("player source:", player.source)
        console.log("player errorString:", player.errorString)
    }
}


