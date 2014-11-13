add_executable(SteamNations
	main.cpp
	Menus.cpp
	MenuController.cpp
	SNScene.cpp
	SteamNations.cpp
	GameView.cpp
	NextTurnButton.cpp
	ObjectInfoBox.cpp
	GraphicInterface.cpp
	Graphics/TileGraphics.cpp
	Graphics/UnitGraphics.cpp
	Graphics/TownGraphics.cpp
	)
qt5_use_modules(SteamNations Widgets Gui)
target_link_libraries(SteamNations SNCore)
