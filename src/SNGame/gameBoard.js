
var maxColumn = 50;
var maxRow = 50;
var maxIndex = maxColumn*maxRow;
var board = new Array(maxIndex);
var blockSrc = "qml/Crab.qml";
var component = Qt.createComponent(blockSrc);

function createBoard()
{
	var sprite;
	for (var i = 0; i < 50; ++i) {
		for (var j = 0; j < 50; ++j) {
			if( component.status != Component.Ready )
			{
				if( component.status == Component.Error )
					console.debug("Error:"+ component.errorString() );
				return; // or maybe throw
			}
			sprite = component.createObject(scene, {"x": 64 * [i], "y": 64 * [j]});
			if (sprite == null) {
				console.log("Error creating object");
			} else {
				board[j*50+i-1] = sprite;
			}
		}
	}
	console.log("All Crabs created\n");
}

function update()
{
	for (var column = 0; column < maxColumn; column++) {
		for (var row = 0; row < maxRow; row++) {
			board[column+row*maxColumn-1].update();
		}
	}
}


