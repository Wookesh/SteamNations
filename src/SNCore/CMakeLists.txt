add_library(SNCore
	Board.cpp
	Console.cpp
	GameManager.cpp
	Tile.cpp
	Player.cpp
	Actions/Action.cpp
	Actions/AttackAction.cpp
	Actions/MoveAction.cpp
	Actions/SettleAction.cpp
    Actions/CreateBuildingAction.cpp
	Actions/CreateTownAction.cpp 
	Actions/CreateUnitAction.cpp
	Actions/CaptureAction.cpp
	Actions/SpawnUnitAction.cpp
    Bonuses/Bonus.cpp
    Bonuses/WarfareBonuses.cpp
    Bonuses/DefenseBonuses.cpp
    Bonuses/EconomyBonuses.cpp
    Bonuses/Bonuses.cpp
	Objects/Object.cpp
	Objects/Unit.cpp
	Objects/Settler.cpp
	Objects/Soldier.cpp
	Objects/Town.cpp
	Objects/Prototypes/Prototype.cpp
	Objects/Prototypes/SettlerPrototype.cpp
	Objects/Prototypes/SoldierPrototype.cpp
	)
qt5_use_modules(SNCore Core)


#set(test_sources
#    UnitTests/unit_tests.cpp
#)
#add_executable(sample_tests ${test_sources})

#qt5_use_modules(sample_tests Core)
#target_link_libraries(sample_tests gtest gtest_main SNCore)
