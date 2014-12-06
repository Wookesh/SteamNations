import QtQuick 2.3
import SN 1.0

//Rectangle {
//	id: krab
//	width: 100
//	height: 100
//	color: "red"

//	antialiasing: true
//	SpriteSequence {
//		id: sprite
//		width: 64
//		height: 64
//		interpolate: false
//		goalSprite: ""

//		Sprite {
//			name: "idle"
//			source: "qrc:../melee-idle.png"
//			frameCount: 8
//			frameDuration: 64
//		}
//	}
//}


Crab {
	id: crab
	width: 64; 
	height: 64;
	frame: 0
	antialiasing: true

// 	function update()
// 	{
// 		crab.frame = crab.frame + 1;
// 	}
}
