var blockSrc = "qml/Crab.qml";

function createBoard()
{
	var component = Qt.createComponent(blockSrc);
	var sprite;
	for (var i = 0; i < 30; ++i) {
		for (var j = 0; j < 30; ++j) {
			if( component.status != Component.Ready )
			{
				if( component.status == Component.Error )
					console.debug("Error:"+ component.errorString() );
				return; // or maybe throw
			}
			if(i%2 == 0)
				sprite = component.createObject(scene, {"x": 48 * i, "y": 56 * j + 28});
			else
				sprite = component.createObject(scene, {"x": 48 * i, "y": 56 * j});
			if (sprite == null) {
				console.log("Error creating object");
			}
		}
	}
	console.log("All Crabs created\n");
}

// function update()
// {
// 	for (var column = 0; column < maxColumn; column++) {
// 		for (var row = 0; row < maxRow; row++) {
// 			board[column+row*maxColumn-1].update();
// 		}
// 	}
// }


