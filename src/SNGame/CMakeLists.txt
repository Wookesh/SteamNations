qt5_add_resources(SNResources resources.qrc)

add_executable(SteamNations
	main.cpp
	${SNResources}
	)
qt5_use_modules(SteamNations Widgets Gui Quick)
target_link_libraries(SteamNations SNCore)
