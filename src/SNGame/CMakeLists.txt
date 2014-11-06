add_executable(SteamNations
	main.cpp
	Menus.cpp
	MenuController.cpp
	SNScene.cpp
	SteamNations.cpp
	TileGraphics.cpp
	UnitGraphics.cpp
	TownGraphics.cpp
	GameView.cpp
	NextTurnButton.cpp
	GraphicInterface.cpp
	)
qt5_use_modules(SteamNations Widgets Gui)
target_link_libraries(SteamNations SNCore)
