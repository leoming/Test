import QtQuick 2.0
import QtMultimedia 5.0

Audio {
    id: player
    source: "../audio/audio_move_chess.ogg"
    function playMoveSound() {
        //player.source = "../audio/audio_move_chess.ogg"
        player.play();
    }
}

