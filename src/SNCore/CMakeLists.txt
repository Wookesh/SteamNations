add_library(SNCore
	Player.cpp
	Prototype.cpp
	Tile.cpp
	Object.cpp
	Unit.cpp
	Town.cpp
	Board.cpp
	GameManager.cpp
	)
qt5_use_modules(SNCore Core)