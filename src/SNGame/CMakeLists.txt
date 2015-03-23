qt5_add_resources(SNResources qml.qrc images.qrc)

add_executable(SteamNations
	main.cpp
	GameBoard.cpp
	BoardField.cpp
	TextureManager.cpp
	InfoBox.cpp
	${SNResources}
	)
qt5_use_modules(SteamNations Widgets Gui Quick)
target_link_libraries(SteamNations SNCore)