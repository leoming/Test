import QtQuick 2.0
import QtMultimedia 5.0

Audio {
    id: player
    source: "file:///data/apps/com.syberos.chess/audio/audio_move_check.ogg"
    volume: .5
    function playMoveSound() {
        player.play();
    }
}
