add_library(SNCore
	Player.cpp
	Prototype.cpp
	SettlerPrototype.cpp
	Tile.cpp
	Object.cpp
	Unit.cpp
	Settler.cpp
	Town.cpp
	Board.cpp
	GameManager.cpp
	)
qt5_use_modules(SNCore Core)