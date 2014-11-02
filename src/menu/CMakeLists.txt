add_executable(SteamNations
	main.cpp
	Menus.cpp
	MenuController.cpp
	SteamNations.cpp
	)
qt5_use_modules(SteamNations Widgets Gui)
target_link_libraries(SteamNations gameGraphics)
